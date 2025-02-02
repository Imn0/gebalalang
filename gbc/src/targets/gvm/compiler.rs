use std::{
    collections::{HashMap, HashSet},
    usize,
};

use regex::Regex;

use crate::code_gen::{
    ir::{IRNameTransformer, IrOperand, IR},
    IrProgram, ProcedureInfo,
};

use super::{
    builtins::BUILTINS,
    gvm_ext::{GVMe, LabelIdx},
    memory::Memory,
};

pub struct GVMeProgram {
    pub code: Vec<GVMe>,
    pub proc_info: HashMap<String, GVMeProc>,
    pub memory: Memory,
}

#[derive(Debug, Clone)]
pub struct GVMeProc {
    pub label: LabelIdx,
    pub return_address: usize,
    pub do_inline: bool,
    pub args: Vec<usize>,
    pub arg_names: Vec<String>,
}

pub struct GVMeCompileContext<'a> {
    pub memory: Memory,
    pub next_available_label: usize,
    pub proc_info: HashMap<String, GVMeProc>,
    pub last_mem_slot: usize,
    pub mul_call_count: i64,
    final_code: Vec<GVMe>,
    ir_proc_info: HashMap<String, &'a ProcedureInfo>,
    current_scope: String,
    pub mod_div_call_count: i64,
    do_compile_mul: bool,
    do_compile_mod_div: bool,
    do_compile_mod: bool,
    proc_to_compile: HashSet<String>,
    use_fat_arrays: bool,
}

struct VarLoc {
    loc: usize,
    is_pointer: bool,
}

pub fn compile(ir_program: &IrProgram, use_fat_arrays: bool) -> Result<GVMeProgram, String> {
    let mut generator = GVMeCompileContext {
        final_code: vec![],
        memory: Memory::new(use_fat_arrays),
        proc_info: HashMap::new(),
        current_scope: String::new(),
        last_mem_slot: 0x4000000000000000 - 32,
        next_available_label: 0,
        do_compile_mul: false,
        mul_call_count: 0,
        do_compile_mod_div: false,
        mod_div_call_count: 0,
        do_compile_mod: false,
        ir_proc_info: HashMap::new(),
        proc_to_compile: HashSet::new(),
        use_fat_arrays,
    };

    generator.generate_code(ir_program)?;

    Ok(GVMeProgram {
        code: generator.final_code,
        proc_info: generator.proc_info,
        memory: generator.memory,
    })
}

impl<'a> GVMeCompileContext<'a> {
    fn generate_code(&mut self, ir_program: &'a IrProgram) -> Result<(), String> {
        // label setup if more are needed

        let mut buff = vec![];
        self.next_available_label = ir_program.next_label;

        // generate stubs for all procedures
        for (name, proc) in &ir_program.procedures {
            let stub = self.generate_procedure_stub(proc)?;
            self.proc_info.insert(name.clone(), stub);
            self.ir_proc_info.insert(name.clone(), proc);
        }

        // buitin procedures, not yet compiled only stubs
        let builtin_mul = self.generate_mul_procedure_stub()?;
        let builtin_mod_div = self.generate_div_mod_procedure_stub()?;
        let builtin_mod = self.generate_mod_procedure_stub()?;
        self.proc_info
            .insert(BUILTINS::MUL.to_name().to_owned(), builtin_mul);
        self.proc_info
            .insert(BUILTINS::DIV_MOD.to_name().to_owned(), builtin_mod_div);
        self.proc_info
            .insert(BUILTINS::MOD.to_name().to_owned(), builtin_mod);

        for _ in 0..ir_program.procedures.len() {
            self.figure_out_which_procs_to_inline(&ir_program);
        }

        // compile main program
        self.current_scope = "PROGRAM".to_owned();
        buff = self.compile_op(&ir_program.main, buff)?;
        buff.push(GVMe::HALT);

        let mut compiled_procs: HashSet<String> = HashSet::new();

        // hard limit for iterations
        for _ in 0..=ir_program.procedures.len() {
            let left_to_compile: Vec<String> = self
                .proc_to_compile
                .difference(&compiled_procs)
                .map(|s| s.to_string())
                .collect();

            if left_to_compile.len() == 0 {
                break;
            }
            for name in left_to_compile {
                compiled_procs.insert(name.clone());
                let proc = self.ir_proc_info.get(&name).unwrap();
                self.current_scope = name.clone();
                buff = self.compile_procedure(proc, buff)?;
                let return_addr = self.proc_info.get(&name).unwrap().return_address;
                buff.push(GVMe::RTRN(return_addr));
            }
        }

        if self.do_compile_mul {
            buff = self.compile_mul_builtin(buff)?;
        }

        if self.do_compile_mod_div {
            buff = self.compile_div_mod_builtin(buff)?;
        }

        if self.do_compile_mod {
            buff = self.compile_mod_builtin(buff)?;
        }

        // fill in all constants
        let constants = self.memory.get_constants().clone();
        for constant in constants {
            let loc = self.memory.get_const(&constant).unwrap();
            self.final_code.push(GVMe::SET(constant.clone()));
            self.final_code.push(GVMe::STORE(loc.memory_address));
        }

        self.final_code.append(&mut buff);

        return Ok(());
    }

    fn generate_procedure_stub(&mut self, proc_info: &ProcedureInfo) -> Result<GVMeProc, String> {
        let mut v_args = vec![];
        let mut arg_names = vec![];
        for arg in &proc_info.args {
            if arg.is_in_only {
                v_args.push(
                    self.memory
                        .allocate_in_arg(&arg.name, &proc_info.name)?
                        .memory_address,
                );
            } else {
                v_args.push(
                    self.memory
                        .allocate_in_out_arg(&arg.name, &proc_info.name)?
                        .memory_address,
                );
            }
            arg_names.push(arg.name.clone());
        }

        Ok(GVMeProc {
            label: self.get_label(&proc_info.lbl),
            return_address: self.memory.allocate_proc_return(&proc_info.name),
            args: v_args,
            arg_names: arg_names,
            do_inline: false,
        })
    }

    fn compile_procedure(
        &mut self,
        proc_info: &ProcedureInfo,
        mut buff: Vec<GVMe>,
    ) -> Result<Vec<GVMe>, String> {
        buff.push(GVMe::lbl {
            idx: self.get_label(&proc_info.lbl),
            name: proc_info.name.clone(),
        });
        buff = self.compile_op(&proc_info.cmds, buff)?;
        Ok(buff)
    }

    fn compile_op(&mut self, commands: &Vec<IR>, mut buff: Vec<GVMe>) -> Result<Vec<GVMe>, String> {
        for (i, op) in commands.iter().enumerate() {
            match op {
                IR::Aloc {
                    name,
                    is_array,
                    array_bounds,
                } => {
                    if *is_array {
                        let (left, right) = array_bounds.unwrap();
                        let loc =
                            self.memory
                                .allocate_array(name, &self.current_scope, left, right)?;
                        self.const_in_acc(&loc.left_offset, &mut buff);
                        buff.push(GVMe::STORE(loc.memory_address));
                    } else {
                        self.memory.allocate_var(name, &self.current_scope)?;
                    }
                }
                IR::Drop { name } => {
                    self.memory.drop_var(name, &self.current_scope);
                }
                IR::Mov { dest, src } => {
                    if let (Some(dest_loc), Some(src_loc)) = (
                        self.get_var_location_no_extra_cmds(dest),
                        self.get_var_location_no_extra_cmds(src),
                    ) {
                        self.compile_load_loc_to_acc(&src_loc, &mut buff);
                        self.compile_store_acc_to_loc(&dest_loc, &mut buff);
                    } else {
                        let dest_loc = self.get_var_location(dest, &mut buff);

                        let stored;
                        if dest_loc.loc == 0 {
                            stored = true;
                            buff.push(GVMe::STORE(self.last_mem_slot));
                        } else {
                            stored = false;
                        }

                        let src_loc = self.get_var_location(src, &mut buff);

                        self.compile_load_loc_to_acc(&src_loc, &mut buff);
                        self.compile_store_acc_to_loc(
                            &VarLoc {
                                loc: if stored {
                                    self.last_mem_slot
                                } else {
                                    dest_loc.loc
                                },
                                is_pointer: dest_loc.is_pointer,
                            },
                            &mut buff,
                        );
                    }
                }
                IR::Add { dest, left, right } => {
                    let dest_addr_loc = self.last_mem_slot;
                    let right_addr_loc = self.last_mem_slot - 1;
                    let dest_loc = self.get_var_location_not_acc(dest, dest_addr_loc, &mut buff);

                    match (self.is_pointer(left), self.is_pointer(right)) {
                        (true, true) => {
                            let right_loc =
                                self.get_var_location_not_acc(right, right_addr_loc, &mut buff);
                            self.compile_load_oper_to_acc(&left, &mut buff);
                            self.compile_add(&right_loc, &mut buff);
                            self.compile_store_acc_to_loc(&dest_loc, &mut buff);
                        }
                        (true, false) => {
                            let right_loc = self.get_var_location_no_extra_cmds(right).unwrap();

                            self.compile_load_oper_to_acc(&left, &mut buff);
                            self.compile_add(&right_loc, &mut buff);
                            self.compile_store_acc_to_loc(&dest_loc, &mut buff);
                        }
                        (false, true) => {
                            let left_loc = self.get_var_location_no_extra_cmds(left).unwrap();

                            self.compile_load_oper_to_acc(&right, &mut buff);
                            self.compile_add(&left_loc, &mut buff);
                            self.compile_store_acc_to_loc(&dest_loc, &mut buff);
                        }
                        (false, false) => {
                            let left_loc = self.get_var_location_no_extra_cmds(left).unwrap();
                            let right_loc = self.get_var_location_no_extra_cmds(right).unwrap();

                            self.compile_load_loc_to_acc(&right_loc, &mut buff);
                            self.compile_add(&left_loc, &mut buff);
                            self.compile_store_acc_to_loc(&dest_loc, &mut buff);
                        }
                    }
                }
                IR::Sub { dest, left, right } => {
                    let dest_addr_loc = self.last_mem_slot;
                    let right_addr_loc = self.last_mem_slot - 1;
                    let dest_loc = self.get_var_location_not_acc(dest, dest_addr_loc, &mut buff);

                    match (self.is_pointer(left), self.is_pointer(right)) {
                        (true, true) => {
                            let right_loc =
                                self.get_var_location_not_acc(right, right_addr_loc, &mut buff);
                            self.compile_load_oper_to_acc(&left, &mut buff);
                            self.compile_sub(&right_loc, &mut buff);
                            self.compile_store_acc_to_loc(&dest_loc, &mut buff);
                        }
                        (true, false) => {
                            let right_loc = self.get_var_location_no_extra_cmds(right).unwrap();

                            self.compile_load_oper_to_acc(&left, &mut buff);
                            self.compile_sub(&right_loc, &mut buff);
                            self.compile_store_acc_to_loc(&dest_loc, &mut buff);
                        }
                        (false, true) => {
                            let right_loc =
                                self.get_var_location_not_acc(right, right_addr_loc, &mut buff);
                            self.compile_load_oper_to_acc(&left, &mut buff);
                            self.compile_sub(&right_loc, &mut buff);
                            self.compile_store_acc_to_loc(&dest_loc, &mut buff);
                        }
                        (false, false) => {
                            let left_loc = self.get_var_location_no_extra_cmds(left).unwrap();
                            let right_loc = self.get_var_location_no_extra_cmds(right).unwrap();

                            self.compile_load_loc_to_acc(&left_loc, &mut buff);
                            self.compile_sub(&right_loc, &mut buff);
                            self.compile_store_acc_to_loc(&dest_loc, &mut buff);
                        }
                    }
                }
                IR::Mul { dest, left, right } => {
                    if let IrOperand::Constant(const_right) = right {
                        if const_right.count_ones() == 1 && *const_right <= 2048 {
                            let left_loc =
                                self.get_var_location_not_acc(left, self.last_mem_slot, &mut buff);
                            let dest_loc = self.get_var_location_not_acc(
                                dest,
                                self.last_mem_slot - 1,
                                &mut buff,
                            );
                            self.compile_load_loc_to_acc(&left_loc, &mut buff);
                            let mut c = 1;
                            while c < *const_right {
                                buff.push(GVMe::ADD(0));
                                c += c;
                            }
                            self.compile_store_acc_to_loc(&dest_loc, &mut buff);
                            continue;
                        }
                    }

                    if let IrOperand::Constant(const_left) = left {
                        if const_left.count_ones() == 1 && *const_left <= 2048 {
                            let right_loc =
                                self.get_var_location_not_acc(right, self.last_mem_slot, &mut buff);
                            let dest_loc = self.get_var_location_not_acc(
                                dest,
                                self.last_mem_slot - 1,
                                &mut buff,
                            );
                            self.compile_load_loc_to_acc(&right_loc, &mut buff);

                            let mut c = 1;
                            while c < *const_left {
                                buff.push(GVMe::ADD(0));
                                c += c;
                            }

                            self.compile_store_acc_to_loc(&dest_loc, &mut buff);
                            continue;
                        }
                    }

                    self.do_compile_mul = true;
                    self.mul_call_count += 1;

                    let left_arg_loc = self.proc_info.get(BUILTINS::MUL.to_name()).unwrap().args[0];
                    let left_loc = self.get_var_location(left, &mut buff);
                    self.compile_load_loc_to_acc(&left_loc, &mut buff);
                    buff.push(GVMe::STORE(left_arg_loc));

                    let right_arg_loc =
                        self.proc_info.get(BUILTINS::MUL.to_name()).unwrap().args[1];
                    let right_loc = self.get_var_location(right, &mut buff);
                    self.compile_load_loc_to_acc(&right_loc, &mut buff);
                    buff.push(GVMe::STORE(right_arg_loc));

                    buff.push(GVMe::call {
                        name: BUILTINS::MUL.to_name().to_owned(),
                    });

                    self.last_mem_slot -= 1;
                    let mut dest_loc = self.get_var_location(dest, &mut buff);
                    if dest_loc.loc == 0 {
                        dest_loc.loc = self.last_mem_slot + 1;
                        buff.push(GVMe::STORE(self.last_mem_slot + 1));
                    }

                    self.compile_load_loc_to_acc(
                        &VarLoc {
                            loc: self.proc_info.get(BUILTINS::MUL.to_name()).unwrap().args[2],
                            is_pointer: false,
                        },
                        &mut buff,
                    );
                    self.compile_store_acc_to_loc(&dest_loc, &mut buff);

                    self.last_mem_slot += 1;
                }
                IR::Div { dest, left, right } => {
                    if let IrOperand::Constant(const_right) = right {
                        if const_right.count_ones() == 1 && *const_right <= 2048 {
                            let left_loc =
                                self.get_var_location_not_acc(left, self.last_mem_slot, &mut buff);
                            let dest_loc = self.get_var_location_not_acc(
                                dest,
                                self.last_mem_slot - 1,
                                &mut buff,
                            );
                            self.compile_load_loc_to_acc(&left_loc, &mut buff);

                            let mut c = 1;
                            while c < *const_right {
                                buff.push(GVMe::HALF);
                                c += c;
                            }

                            self.compile_store_acc_to_loc(&dest_loc, &mut buff);
                            continue;
                        }
                    }

                    self.do_compile_mod_div = true;
                    self.mod_div_call_count += 1;

                    let left_arg_loc = self
                        .proc_info
                        .get(BUILTINS::DIV_MOD.to_name())
                        .unwrap()
                        .args[0];
                    let left_loc = self.get_var_location(left, &mut buff);
                    self.compile_load_loc_to_acc(&left_loc, &mut buff);
                    buff.push(GVMe::STORE(left_arg_loc));

                    let right_arg_loc = self
                        .proc_info
                        .get(BUILTINS::DIV_MOD.to_name())
                        .unwrap()
                        .args[1];
                    let right_loc = self.get_var_location(right, &mut buff);
                    self.compile_load_loc_to_acc(&right_loc, &mut buff);
                    buff.push(GVMe::STORE(right_arg_loc));

                    buff.push(GVMe::call {
                        name: BUILTINS::DIV_MOD.to_name().to_owned(),
                    });

                    self.last_mem_slot -= 1;
                    let mut dest_loc = self.get_var_location(dest, &mut buff);
                    if dest_loc.loc == 0 {
                        dest_loc.loc = self.last_mem_slot + 1;
                        buff.push(GVMe::STORE(self.last_mem_slot + 1));
                    }

                    self.compile_load_loc_to_acc(
                        &VarLoc {
                            loc: self
                                .proc_info
                                .get(BUILTINS::DIV_MOD.to_name())
                                .unwrap()
                                .args[2],
                            is_pointer: false,
                        },
                        &mut buff,
                    );
                    self.compile_store_acc_to_loc(&dest_loc, &mut buff);

                    self.last_mem_slot += 1;
                }
                IR::Mod { dest, left, right } => {
                    if let IrOperand::Constant(const_right) = right {
                        if const_right.count_ones() == 1 && *const_right <= 2048 {
                            let left_loc = self.last_mem_slot - 2;

                            let dest_loc = self.get_var_location_not_acc(
                                dest,
                                self.last_mem_slot - 1,
                                &mut buff,
                            );

                            let negative_check = self.next_label();
                            self.const_in_acc(&1, &mut buff);
                            self.compile_load_oper_to_acc(left, &mut buff);
                            buff.push(GVMe::STORE(left_loc));
                            buff.push(GVMe::jpos(negative_check));
                            self.const_in_acc(&0, &mut buff);
                            buff.push(GVMe::SUB(left_loc));
                            buff.push(GVMe::STORE(left_loc));

                            buff.push(GVMe::lbl {
                                idx: negative_check,
                                name: "".to_owned(),
                            });

                            let mut c = 1;
                            while c < *const_right {
                                buff.push(GVMe::HALF);
                                c += c;
                            }

                            let mut c = 1;
                            while c < *const_right {
                                buff.push(GVMe::ADD(0)); // TODO <<<--------- this
                                c += c;
                            }

                            buff.push(GVMe::SUB(left_loc));
                            buff.push(GVMe::STORE(self.last_mem_slot));
                            let zero = self.get_const_loc(&0);
                            buff.push(GVMe::LOAD(zero.loc));
                            buff.push(GVMe::SUB(self.last_mem_slot));
                            self.compile_store_acc_to_loc(&dest_loc, &mut buff);
                            continue;
                        }
                    }

                    // check two back an two forwards, if there is no div we call mod instead of div_mod
                    let mut call_mod = true;
                    for j in i - 2..=i + 2 {
                        let _op = commands.get(j).unwrap_or(&IR::Return);
                        if let IR::Div {
                            dest: _,
                            left: _,
                            right: _,
                        } = _op
                        {
                            call_mod = false;
                        }
                    }
                    if call_mod {
                        self.do_compile_mod = true;

                        let left_arg_loc =
                            self.proc_info.get(BUILTINS::MOD.to_name()).unwrap().args[0];
                        let left_loc = self.get_var_location(left, &mut buff);
                        self.compile_load_loc_to_acc(&left_loc, &mut buff);
                        buff.push(GVMe::STORE(left_arg_loc));

                        let right_arg_loc =
                            self.proc_info.get(BUILTINS::MOD.to_name()).unwrap().args[1];
                        let right_loc = self.get_var_location(right, &mut buff);
                        self.compile_load_loc_to_acc(&right_loc, &mut buff);
                        buff.push(GVMe::STORE(right_arg_loc));

                        buff.push(GVMe::call {
                            name: BUILTINS::MOD.to_name().to_owned(),
                        });

                        self.last_mem_slot -= 1;
                        let mut dest_loc = self.get_var_location(dest, &mut buff);
                        if dest_loc.loc == 0 {
                            dest_loc.loc = self.last_mem_slot + 1;
                            buff.push(GVMe::STORE(self.last_mem_slot + 1));
                        }

                        self.compile_load_loc_to_acc(
                            &VarLoc {
                                loc: self.proc_info.get(BUILTINS::MOD.to_name()).unwrap().args[2],
                                is_pointer: false,
                            },
                            &mut buff,
                        );
                        self.compile_store_acc_to_loc(&dest_loc, &mut buff);

                        self.last_mem_slot += 1;
                    } else {
                        // call div_mod
                        self.do_compile_mod_div = true;
                        self.mod_div_call_count += 1;

                        let left_arg_loc = self
                            .proc_info
                            .get(BUILTINS::DIV_MOD.to_name())
                            .unwrap()
                            .args[0];
                        let left_loc = self.get_var_location(left, &mut buff);
                        self.compile_load_loc_to_acc(&left_loc, &mut buff);
                        buff.push(GVMe::STORE(left_arg_loc));

                        let right_arg_loc = self
                            .proc_info
                            .get(BUILTINS::DIV_MOD.to_name())
                            .unwrap()
                            .args[1];
                        let right_loc = self.get_var_location(right, &mut buff);
                        self.compile_load_loc_to_acc(&right_loc, &mut buff);
                        buff.push(GVMe::STORE(right_arg_loc));

                        buff.push(GVMe::call {
                            name: BUILTINS::DIV_MOD.to_name().to_owned(),
                        });

                        self.last_mem_slot -= 1;
                        let mut dest_loc = self.get_var_location(dest, &mut buff);
                        if dest_loc.loc == 0 {
                            dest_loc.loc = self.last_mem_slot + 1;
                            buff.push(GVMe::STORE(self.last_mem_slot + 1));
                        }

                        self.compile_load_loc_to_acc(
                            &VarLoc {
                                loc: self
                                    .proc_info
                                    .get(BUILTINS::DIV_MOD.to_name())
                                    .unwrap()
                                    .args[3],
                                is_pointer: false,
                            },
                            &mut buff,
                        );
                        self.compile_store_acc_to_loc(&dest_loc, &mut buff);

                        self.last_mem_slot += 1;
                    }
                }
                IR::Label(str_lbl) => {
                    let lbl = self.get_label(&str_lbl);
                    buff.push(GVMe::lbl {
                        idx: lbl,
                        name: str_lbl.clone(),
                    });
                }
                IR::Jump(str_lbl) => {
                    let lbl = self.get_label(&str_lbl);
                    buff.push(GVMe::lbl_jump(lbl));
                }
                IR::JZero { left, right, label } => {
                    self.compile_comparison(left, right, &mut buff);
                    buff.push(GVMe::jz(self.get_label(&label)));
                }
                IR::JNotZero { left, right, label } => {
                    self.compile_comparison(left, right, &mut buff);
                    buff.push(GVMe::jnz(self.get_label(label)));
                }
                IR::JPositive { left, right, label } => {
                    self.compile_comparison(left, right, &mut buff);
                    buff.push(GVMe::jpos(self.get_label(label)));
                }
                IR::JNegative { left, right, label } => {
                    self.compile_comparison(left, right, &mut buff);
                    buff.push(GVMe::jneg(self.get_label(label)));
                }
                IR::JPositiveOrZero { left, right, label } => {
                    self.compile_comparison(left, right, &mut buff);
                    buff.push(GVMe::jposz(self.get_label(label)));
                }
                IR::JNegativeOrZero { left, right, label } => {
                    self.compile_comparison(left, right, &mut buff);
                    buff.push(GVMe::jnegz(self.get_label(label)));
                }
                IR::ProcCall {
                    procedure,
                    arguments,
                } => {
                    let proc_info = self.proc_info.get(procedure).unwrap().clone();
                    let ir_proc = *self.ir_proc_info.get(procedure).unwrap();
                    let do_inline = proc_info.do_inline;
                    let proc_args = proc_info.args.clone();

                    if do_inline {
                        buff = self.do_inline(&proc_info, arguments, ir_proc, buff)?;
                    } else {
                        self.proc_to_compile.insert(procedure.to_owned());
                        for (i, arg) in arguments.iter().enumerate() {
                            let arg_name = if let IrOperand::Variable(n) = arg {
                                n
                            } else {
                                unreachable!();
                            };
                            let arg_mem_loc =
                                self.memory.get_base_loc(&arg_name, &self.current_scope);

                            let arg_mem_loci64 = arg_mem_loc.memory_address as i64;

                            let target_mem_loc = proc_args.get(i).unwrap().clone();

                            if ir_proc.args.get(i).unwrap().is_in_only {
                                if arg_mem_loc.is_pointer {
                                    buff.push(GVMe::LOADI(arg_mem_loc.memory_address));
                                } else {
                                    buff.push(GVMe::LOAD(arg_mem_loc.memory_address));
                                }
                                buff.push(GVMe::STORE(target_mem_loc));
                            } else {
                                if arg_mem_loc.is_pointer {
                                    buff.push(GVMe::LOAD(arg_mem_loc.memory_address));
                                } else {
                                    self.const_in_acc(&arg_mem_loci64, &mut buff);
                                }
                                buff.push(GVMe::STORE(target_mem_loc));
                            }
                        }

                        buff.push(GVMe::call {
                            name: procedure.clone(),
                        });
                    }
                }
                IR::Return => {}
                IR::Read(ir_operand) => {
                    let mut var_loc = self.get_var_location(ir_operand, &mut buff);
                    if var_loc.loc == 0 {
                        var_loc.loc = self.last_mem_slot;
                        buff.push(GVMe::STORE(self.last_mem_slot));
                    }
                    if !var_loc.is_pointer {
                        buff.push(GVMe::GET(var_loc.loc));
                    } else {
                        buff.push(GVMe::GET(0));
                        buff.push(GVMe::STOREI(var_loc.loc));
                    }
                }
                IR::Write(ir_operand) => {
                    let var_loc = self.get_var_location(ir_operand, &mut buff);
                    if !var_loc.is_pointer {
                        buff.push(GVMe::PUT(var_loc.loc));
                    } else {
                        buff.push(GVMe::LOADI(var_loc.loc));
                        buff.push(GVMe::PUT(0));
                    }
                }
                IR::Comment(cm) => {
                    buff.push(GVMe::comment { cm: cm.to_string() });
                }
            }
        }
        return Ok(buff);
    }

    fn compile_comparison(&mut self, left: &IrOperand, right: &IrOperand, buff: &mut Vec<GVMe>) {
        let right_addr_loc = self.last_mem_slot;
        match (self.is_pointer(left), self.is_pointer(right)) {
            (true, true) => {
                let right_loc = self.get_var_location_not_acc(right, right_addr_loc, buff);
                self.compile_load_oper_to_acc(&left, buff);
                self.compile_sub(&right_loc, buff);
            }
            (true, false) => {
                let right_loc = self.get_var_location_no_extra_cmds(right).unwrap();

                self.compile_load_oper_to_acc(&left, buff);
                self.compile_sub(&right_loc, buff);
            }
            (false, true) => {
                let right_loc = self.get_var_location_not_acc(right, right_addr_loc, buff);
                self.compile_load_oper_to_acc(&left, buff);
                self.compile_sub(&right_loc, buff);
            }
            (false, false) => {
                let left_loc = self.get_var_location_no_extra_cmds(left).unwrap();
                if let IrOperand::Constant(c) = right {
                    if *c == 0 {
                        self.compile_load_loc_to_acc(&left_loc, buff);
                        return;
                    }
                }
                let right_loc = self.get_var_location_no_extra_cmds(right).unwrap();

                self.compile_load_loc_to_acc(&left_loc, buff);
                self.compile_sub(&right_loc, buff);
            }
        }
    }

    fn compile_load_loc_to_acc(&mut self, loc: &VarLoc, buff: &mut Vec<GVMe>) {
        if loc.is_pointer {
            buff.push(GVMe::LOADI(loc.loc));
        } else {
            buff.push(GVMe::LOAD(loc.loc));
        }
    }

    fn compile_add(&mut self, loc: &VarLoc, buff: &mut Vec<GVMe>) {
        if loc.is_pointer {
            buff.push(GVMe::ADDI(loc.loc));
        } else {
            buff.push(GVMe::ADD(loc.loc));
        }
    }

    fn compile_sub(&mut self, loc: &VarLoc, buff: &mut Vec<GVMe>) {
        if loc.is_pointer {
            buff.push(GVMe::SUBI(loc.loc));
        } else {
            buff.push(GVMe::SUB(loc.loc));
        }
    }

    fn compile_store_acc_to_loc(&mut self, loc: &VarLoc, buff: &mut Vec<GVMe>) {
        if loc.is_pointer {
            buff.push(GVMe::STOREI(loc.loc));
        } else {
            buff.push(GVMe::STORE(loc.loc));
        }
    }

    fn compile_load_oper_to_acc(&mut self, operand: &IrOperand, buff: &mut Vec<GVMe>) {
        let loc = self.get_var_location(operand, buff);
        if loc.is_pointer {
            buff.push(GVMe::LOADI(loc.loc));
        } else {
            buff.push(GVMe::LOAD(loc.loc));
        }
    }

    fn is_pointer(&mut self, operand: &IrOperand) -> bool {
        if let Some(_) = self.get_var_location_no_extra_cmds(operand) {
            return false;
        } else {
            return true;
        }
    }

    fn get_var_location_no_extra_cmds(&mut self, operand: &IrOperand) -> Option<VarLoc> {
        match operand {
            IrOperand::Variable(name) => {
                let loc = self.memory.get_base_loc(name, &self.current_scope);
                Some(VarLoc {
                    loc: loc.memory_address,
                    is_pointer: loc.is_pointer,
                })
            }
            IrOperand::Constant(val) => Some(self.get_const_loc(val)),
            IrOperand::ArrayConstAccess { base_name, idx } => {
                let base_loc = self.memory.get_base_loc(&base_name, &self.current_scope);
                if !self.use_fat_arrays {
                    if !base_loc.is_pointer {
                        return Some(VarLoc {
                            loc: (base_loc.memory_address as i64 + idx) as usize,
                            is_pointer: false,
                        });
                    }
                    return None;
                } else {
                    if !base_loc.is_pointer {
                        let loc = (base_loc.memory_address as i64 + base_loc.left_offset + idx + 1)
                            as usize;
                        return Some(VarLoc {
                            loc,
                            is_pointer: false,
                        });
                    } else {
                        return None;
                    }
                }
            }
            IrOperand::ArrayDynamicAccess { .. } => {
                return None;
            }
        }
    }

    fn get_var_location(&mut self, operand: &IrOperand, buff: &mut Vec<GVMe>) -> VarLoc {
        match operand {
            IrOperand::Variable(name) => {
                let loc = self.memory.get_base_loc(name, &self.current_scope);
                VarLoc {
                    loc: loc.memory_address,
                    is_pointer: loc.is_pointer,
                }
            }
            IrOperand::Constant(val) => self.get_const_loc(val),
            IrOperand::ArrayConstAccess { base_name, idx } => {
                let base_loc = self.memory.get_base_loc(&base_name, &self.current_scope);
                if !self.use_fat_arrays {
                    if !base_loc.is_pointer {
                        return VarLoc {
                            loc: (base_loc.memory_address as i64 + idx) as usize,
                            is_pointer: false,
                        };
                    }
                    let memory_address = base_loc.memory_address;
                    self.const_in_acc(idx, buff);
                    buff.push(GVMe::ADD(memory_address));
                    VarLoc {
                        is_pointer: true,
                        loc: 0,
                    }
                } else {
                    if !base_loc.is_pointer {
                        let loc = (base_loc.memory_address as i64 + base_loc.left_offset + idx + 1)
                            as usize;
                        return VarLoc {
                            loc,
                            is_pointer: false,
                        };
                    }
                    let memory_address = base_loc.memory_address;
                    let one = self.get_const_loc(&1).loc;
                    self.const_in_acc(idx, buff);
                    buff.push(GVMe::ADD(one));
                    buff.push(GVMe::ADD(memory_address));
                    buff.push(GVMe::ADDI(memory_address));

                    VarLoc {
                        is_pointer: true,
                        loc: 0,
                    }
                }
            }
            IrOperand::ArrayDynamicAccess {
                base_name,
                idx_name,
            } => {
                let scope = &self.current_scope;

                let base_loc = self.memory.get_base_loc(&base_name, &scope).clone();
                let idx_loc = self.memory.get_base_loc(&idx_name, &scope).clone();

                let base_address = base_loc.memory_address;
                let idx_address = idx_loc.memory_address;
                if !self.use_fat_arrays {
                    match (base_loc.is_pointer, idx_loc.is_pointer) {
                        (false, false) => {
                            self.const_in_acc(&(base_address as i64), buff);
                            buff.push(GVMe::ADD(idx_address));
                        }
                        (false, true) => {
                            self.const_in_acc(&(base_address as i64), buff);
                            buff.push(GVMe::ADDI(idx_address));
                        }
                        (true, false) => {
                            buff.push(GVMe::LOAD(base_loc.memory_address));
                            buff.push(GVMe::ADD(idx_loc.memory_address));
                        }
                        (true, true) => {
                            buff.push(GVMe::LOAD(base_loc.memory_address));
                            buff.push(GVMe::ADDI(idx_loc.memory_address));
                        }
                    }
                    VarLoc {
                        is_pointer: true,
                        loc: 0,
                    }
                } else {
                    let one = self.get_const_loc(&1).loc;
                    match (base_loc.is_pointer, idx_loc.is_pointer) {
                        (false, false) => {
                            self.const_in_acc(&(base_address as i64), buff);
                            buff.push(GVMe::ADD(idx_address));
                            buff.push(GVMe::ADD(base_address));
                        }
                        (false, true) => {
                            self.const_in_acc(&(base_address as i64), buff);
                            buff.push(GVMe::ADDI(idx_address));
                            buff.push(GVMe::ADD(base_address));
                        }
                        (true, false) => {
                            buff.push(GVMe::LOAD(base_loc.memory_address));
                            buff.push(GVMe::ADDI(base_loc.memory_address));
                            buff.push(GVMe::ADD(idx_loc.memory_address));
                        }
                        (true, true) => {
                            buff.push(GVMe::LOAD(base_loc.memory_address));
                            buff.push(GVMe::ADDI(base_loc.memory_address));
                            buff.push(GVMe::ADDI(idx_loc.memory_address));
                        }
                    }
                    buff.push(GVMe::ADD(one));
                    VarLoc {
                        is_pointer: true,
                        loc: 0,
                    }
                }
            }
        }
    }

    fn get_var_location_not_acc(
        &mut self,
        operand: &IrOperand,
        where_to_put_it: usize,
        buff: &mut Vec<GVMe>,
    ) -> VarLoc {
        let mut loc = self.get_var_location(operand, buff);
        if loc.loc == 0 {
            loc.loc = where_to_put_it;
            buff.push(GVMe::STORE(where_to_put_it));
        }

        return loc;
    }

    fn get_label(&self, str_lbl: &str) -> LabelIdx {
        let re = Regex::new(r"L\w*_i(\d+)").unwrap();
        if let Some(captures) = re.captures(str_lbl) {
            let num: usize = captures
                .get(1)
                .map(|m| m.as_str().parse().unwrap())
                .unwrap();
            return LabelIdx(num);
        }
        panic!("label was {}", str_lbl);
    }

    pub fn const_in_acc(&mut self, val: &i64, buff: &mut Vec<GVMe>) {
        let loc = self.memory.get_const_loc_or_aloc(val);
        buff.push(GVMe::LOAD(loc.memory_address));
    }

    fn get_const_loc(&mut self, val: &i64) -> VarLoc {
        let loc = self.memory.get_const_loc_or_aloc(val);
        VarLoc {
            loc: loc.memory_address,
            is_pointer: false,
        }
    }

    fn do_inline(
        &mut self,
        proc_info: &GVMeProc,
        arguments: &Vec<IrOperand>,
        ir_proc: &ProcedureInfo,
        buff: Vec<GVMe>,
    ) -> Result<Vec<GVMe>, String> {
        let mut arg_translate_map: HashMap<String, String> = HashMap::new();
        let proc_arg_names = &proc_info.arg_names;

        for (i, arg) in arguments.iter().enumerate() {
            let arg_name = if let IrOperand::Variable(n) = arg {
                n
            } else {
                unreachable!();
            };

            let proc_arg_name = proc_arg_names.get(i).unwrap();
            arg_translate_map.insert(proc_arg_name.to_string(), arg_name.to_string());
        }

        let name_transformer = IRNameTransformer {
            translate_map: arg_translate_map,
            default_prefix: &format!("I_{}_{}", ir_proc.name, self.next_available_label),
        };

        let renamed_commands = name_transformer.ir_transform(&ir_proc.cmds);

        let mut label_map: HashMap<LabelIdx, String> = HashMap::new();
        let relabeled_commands = renamed_commands
            .iter()
            .map(|cm| match cm {
                IR::Label(label) => {
                    IR::Label(self.inline_get_or_create_label(&label, &mut label_map))
                }
                IR::Jump(label) => {
                    IR::Jump(self.inline_get_or_create_label(&label, &mut label_map))
                }
                IR::JZero { left, right, label } => IR::JZero {
                    left: left.clone(),
                    right: right.clone(),
                    label: self.inline_get_or_create_label(&label, &mut label_map),
                },
                IR::JNotZero { left, right, label } => IR::JNotZero {
                    left: left.clone(),
                    right: right.clone(),
                    label: self.inline_get_or_create_label(&label, &mut label_map),
                },
                IR::JPositive { left, right, label } => IR::JPositive {
                    left: left.clone(),
                    right: right.clone(),
                    label: self.inline_get_or_create_label(&label, &mut label_map),
                },
                IR::JNegative { left, right, label } => IR::JNegative {
                    left: left.clone(),
                    right: right.clone(),
                    label: self.inline_get_or_create_label(&label, &mut label_map),
                },
                IR::JPositiveOrZero { left, right, label } => IR::JPositiveOrZero {
                    left: left.clone(),
                    right: right.clone(),
                    label: self.inline_get_or_create_label(&label, &mut label_map),
                },
                IR::JNegativeOrZero { left, right, label } => IR::JNegativeOrZero {
                    left: left.clone(),
                    right: right.clone(),
                    label: self.inline_get_or_create_label(&label, &mut label_map),
                },
                _ => cm.clone(),
            })
            .collect();
        self.compile_op(&relabeled_commands, buff)
    }

    fn inline_get_or_create_label(
        &mut self,
        label: &str,
        label_map: &mut HashMap<LabelIdx, String>,
    ) -> String {
        let idx = self.get_label(&label);
        if label_map.contains_key(&idx) {
            let label_string = label_map.get(&idx).unwrap().to_string();
            label_string
        } else {
            let new_lbl = format!("L{}_i{}", "INLINE", self.next_available_label);
            self.next_available_label += 1;
            label_map.insert(idx, new_lbl.clone());
            new_lbl
        }
    }

    pub fn next_label(&mut self) -> LabelIdx {
        let lbl = LabelIdx(self.next_available_label);
        self.next_available_label += 1;
        return lbl;
    }

    fn figure_out_which_procs_to_inline(&mut self, ir_program: &'a IrProgram) {
        let mut call_counts: HashMap<String, i64> = HashMap::new();
        let mut calls_to_process: HashSet<String> = HashSet::new();
        let mut calls_processed: HashSet<String> = HashSet::new();

        for proc in &ir_program.procedures {
            call_counts.insert(proc.0.to_string(), 0);
        }

        for cmd in &ir_program.main {
            if let IR::ProcCall {
                procedure,
                arguments: _,
            } = cmd
            {
                calls_to_process.insert(procedure.clone());
                *call_counts.get_mut(procedure).unwrap() += 1;
            }
        }

        for _ in 0..ir_program.procedures.len() {
            let to_process: HashSet<_> = calls_to_process
                .difference(&calls_processed)
                .cloned()
                .collect();
            let mut new_calls = HashSet::new();

            for proc_name in to_process {
                let code = &self.ir_proc_info.get(&proc_name).unwrap().cmds;
                for ir in code {
                    if let IR::ProcCall {
                        procedure,
                        arguments: _,
                    } = ir
                    {
                        new_calls.insert(procedure.clone());
                        *call_counts.get_mut(procedure).unwrap() += 1;
                    }
                }
            }
            calls_processed.extend(new_calls);
        }

        // if its cheaper to just do the procedure
        for proc in &ir_program.procedures {
            let call_cost: f32 = self.get_estimated_call_cost(proc.1);
            let proc_cost: f32 = self.get_estimated_proc_cost(proc.1);

            if call_cost >= proc_cost {
                self.proc_info.get_mut(proc.0).unwrap().do_inline = true;
            }
        }

        for (proc_name, count) in call_counts {
            if count == 1 {
                self.proc_info.get_mut(&proc_name).unwrap().do_inline = true;
            }
        }
    }

    fn get_estimated_call_cost(&mut self, ir_proc: &ProcedureInfo) -> f32 {
        return (ir_proc.args.len() * 25 + 61) as f32 * 1.3;
    }

    fn get_estimated_proc_cost(&mut self, ir_proc: &ProcedureInfo) -> f32 {
        return (ir_proc.cmds.len() * 20) as f32 * 0.7;
    }
}
