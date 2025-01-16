use std::{
    collections::{HashMap, HashSet},
    fmt::{self, Arguments},
    usize,
};

use regex::Regex;

use crate::code_gen::{
    ir::{self, IRNameTransformer, IrOperand, IR},
    IrProgram, ProcedureInfo,
};

use super::memory::Memory;

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq, Hash)]
pub struct LabelIdx(pub usize);

#[allow(non_camel_case_types)]
#[derive(Clone, Debug)]
pub enum GVMe {
    GET(usize),
    PUT(usize),
    LOAD(usize),
    STORE(usize),
    LOADI(usize),
    STOREI(usize),
    ADD(usize),
    SUB(usize),
    ADDI(usize),
    SUBI(usize),
    SET(i64),
    HALF,
    RTRN(usize),
    HALT,
    lbl { idx: LabelIdx, name: String },
    call { name: String },
    lbl_jump(LabelIdx),
    jz(LabelIdx),
    jnz(LabelIdx),
    jpos(LabelIdx),
    jneg(LabelIdx),
    jposz(LabelIdx),
    jnegz(LabelIdx),
    comment { cm: String },
}

#[allow(non_camel_case_types)]
enum BUILTINS {
    MUL,
    DIV_MOD,
}
impl BUILTINS {
    fn to_name(&self) -> &'static str {
        match self {
            BUILTINS::MUL => "__BUILTIN_MUL",
            BUILTINS::DIV_MOD => "__BUILTIN_DIV_MOD",
        }
    }
}

impl fmt::Display for GVMe {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            GVMe::lbl { idx, name } => write!(f, ".L{:?} #{}", idx, name),
            _ => {
                write!(f, "    ")?;
                match self {
                    GVMe::GET(val) => write!(f, "GET {}", val),
                    GVMe::PUT(val) => write!(f, "PUT {}", val),
                    GVMe::LOAD(val) => write!(f, "LOAD {}", val),
                    GVMe::STORE(val) => write!(f, "STORE {}", val),
                    GVMe::LOADI(val) => write!(f, "LOADI {}", val),
                    GVMe::STOREI(val) => write!(f, "STOREI {}", val),
                    GVMe::ADD(val) => write!(f, "ADD {}", val),
                    GVMe::SUB(val) => write!(f, "SUB {}", val),
                    GVMe::ADDI(val) => write!(f, "ADDI {}", val),
                    GVMe::SUBI(val) => write!(f, "SUBI {}", val),
                    GVMe::SET(val) => write!(f, "SET {}", val),
                    GVMe::HALF => write!(f, "HALF"),
                    GVMe::RTRN(val) => write!(f, "RTRN {}", val),
                    GVMe::HALT => write!(f, "HALT"),
                    GVMe::call { name } => write!(f, "call {}", name),
                    GVMe::lbl_jump(val) => write!(f, "lbl_jumb .L{}", val.0),
                    GVMe::jz(val) => write!(f, "jz .L{}", val.0),
                    GVMe::jnz(val) => write!(f, "jnz .L{}", val.0),
                    GVMe::jpos(val) => write!(f, "jp .L{}", val.0),
                    GVMe::jneg(val) => write!(f, "jn .L{}", val.0),
                    GVMe::jposz(val) => write!(f, "jzp .L{}", val.0),
                    GVMe::jnegz(val) => write!(f, "jzn .L{}", val.0),
                    GVMe::comment { cm } => write!(f, "{}", cm),
                    _ => Ok(()),
                }
            }
        }
    }
}

pub struct GVMeProgram {
    pub code: Vec<GVMe>,
    pub proc_info: HashMap<String, GVMeProc>,
}
#[derive(Debug, Clone)]
pub struct GVMeProc {
    pub label: LabelIdx,
    pub return_address: usize,
    do_inline: bool,
    args: Vec<usize>,
    arg_names: Vec<String>,
}

struct GVMeGnerator<'a> {
    buff: Vec<GVMe>,
    code: Vec<GVMe>,
    proc_info: HashMap<String, GVMeProc>,
    ir_proc_info: HashMap<String, &'a ProcedureInfo>,
    memory: Memory,
    current_scope: String,
    last_mem_slot: usize,
    next_available_label: usize,
    do_compile_mul: bool,
    do_compile_mod_div: bool,
    proc_to_compile: HashSet<String>,
}

struct VarLoc {
    loc: usize,
    is_pointer: bool,
}

pub fn compile(ir_program: &IrProgram) -> GVMeProgram {
    let mut generator = GVMeGnerator {
        buff: vec![],
        code: vec![],
        memory: Memory::new(),
        proc_info: HashMap::new(),
        current_scope: String::new(),
        last_mem_slot: 0x4000000000000000 - 32,
        next_available_label: 0,
        do_compile_mul: false,
        do_compile_mod_div: false,
        ir_proc_info: HashMap::new(),
        proc_to_compile: HashSet::new(),
    };

    generator.generate_code(ir_program);

    GVMeProgram {
        code: generator.code,
        proc_info: generator.proc_info,
    }
}

impl<'a> GVMeGnerator<'a> {
    fn generate_code(&mut self, ir_program: &'a IrProgram) {
        // label setup if more are needed
        self.next_available_label = ir_program.next_label;

        // TODO figure out which procedures to inline !!

        // generate stubs for all procedures
        for (name, proc) in &ir_program.procedures {
            let stub = self.generate_procedure_stub(proc);
            self.proc_info.insert(name.clone(), stub);
            self.ir_proc_info.insert(name.clone(), proc);
        }

        // buitin procedures, not yet compiled only stubs
        let builtin_mul = self.generate_mul_procedure_stub();
        let builtin_mod_div = self.generate_div_mod_procedure_stub();
        self.proc_info
            .insert(BUILTINS::MUL.to_name().to_owned(), builtin_mul);
        self.proc_info
            .insert(BUILTINS::DIV_MOD.to_name().to_owned(), builtin_mod_div);

        // compile main program
        self.current_scope = "PROGRAM".to_owned();
        for op in &ir_program.main {
            self.compile_op(op);
        }
        self.buff.push(GVMe::HALT);

        let mut compiled_procs: HashSet<String> = HashSet::new();

        for _ in 0..=ir_program.procedures.len() { // hard limit for iterations
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
                self.compile_procedure(proc);
                let return_addr = self.proc_info.get(&name).unwrap().return_address;
                self.buff.push(GVMe::RTRN(return_addr));
            }
        }

        if self.do_compile_mul {
            self.compile_mul_builtin();
        }

        if self.do_compile_mod_div {
            self.compile_div_mod_builtin();
        }

        // fill in all constants
        let constants = self.memory.get_constants().clone();
        for constant in constants {
            let loc = self.memory.get_const(&constant);
            self.code.push(GVMe::SET(constant.clone()));
            self.code.push(GVMe::STORE(loc.memory_address));
        }

        self.code.append(&mut self.buff);
    }

    fn generate_procedure_stub(&mut self, proc_info: &ProcedureInfo) -> GVMeProc {
        let mut v_args = vec![];
        let mut arg_names = vec![];
        for arg in &proc_info.args {
            v_args.push(
                self.memory
                    .allocate_proc_arg(&arg.name, &proc_info.name, arg.is_array)
                    .memory_address,
            );
            arg_names.push(arg.name.clone());
        }

        GVMeProc {
            label: self.get_label(&proc_info.lbl),
            return_address: self.memory.allocate_proc_return(&proc_info.name),
            args: v_args,
            arg_names: arg_names,
            do_inline: false,
        }
    }

    fn compile_procedure(&mut self, proc_info: &ProcedureInfo) {
        self.buff.push(GVMe::lbl {
            idx: self.get_label(&proc_info.lbl),
            name: proc_info.name.clone(),
        });
        for op in &proc_info.cmds {
            self.compile_op(op);
        }
    }

    fn compile_op(&mut self, op: &IR) -> Option<()> {
        match op {
            IR::Aloc {
                name,
                is_array,
                array_bounds,
            } => {
                if *is_array {
                    let (left, right) = array_bounds.unwrap();
                    self.memory
                        .allocate_array(name, &self.current_scope, left, right);
                } else {
                    self.memory.allocate_var(name, &self.current_scope);
                }
                Some(())
            }
            IR::Drop { name } => {
                self.memory.drop_var(name, &self.current_scope);
                Some(())
            }
            IR::Mov { dest, src } => {
                if let (Some(dest_loc), Some(src_loc)) = (
                    self.get_var_location_no_extra_cmds(dest),
                    self.get_var_location_no_extra_cmds(src),
                ) {
                    self.compile_load_loc_to_acc(&src_loc);
                    self.compile_store_acc_to_loc(&dest_loc);
                    return Some(());
                } else {
                    let dest_loc = self.get_var_location(dest);

                    let stored;
                    if dest_loc.loc == 0 {
                        stored = true;
                        self.buff.push(GVMe::STORE(self.last_mem_slot));
                    } else {
                        stored = false;
                    }

                    let src_loc = self.get_var_location(src);

                    self.compile_load_loc_to_acc(&src_loc);
                    self.compile_store_acc_to_loc(&VarLoc {
                        loc: if stored {
                            self.last_mem_slot
                        } else {
                            dest_loc.loc
                        },
                        is_pointer: dest_loc.is_pointer,
                    });
                    Some(())
                }
            }
            IR::Add { dest, left, right } => {
                if let (Some(dest_loc), Some(left_loc), Some(right_loc)) = (
                    self.get_var_location_no_extra_cmds(dest),
                    self.get_var_location_no_extra_cmds(left),
                    self.get_var_location_no_extra_cmds(right),
                ) {
                    self.compile_load_loc_to_acc(&left_loc);
                    if right_loc.is_pointer {
                        self.buff.push(GVMe::ADDI(right_loc.loc));
                    } else {
                        self.buff.push(GVMe::ADD(right_loc.loc));
                    }
                    self.compile_store_acc_to_loc(&dest_loc);
                } else {
                    let mut dst_loc = self.get_var_location(dest);
                    if dst_loc.loc == 0 {
                        self.buff.push(GVMe::STORE(self.last_mem_slot));
                        dst_loc.loc = self.last_mem_slot;
                    }

                    let mut left_loc = self.get_var_location(left);
                    if left_loc.loc == 0 {
                        self.buff.push(GVMe::STORE(self.last_mem_slot - 1));
                        left_loc.loc = self.last_mem_slot - 1;
                    }

                    let right_loc = self.get_var_location(right);
                    if right_loc.is_pointer {
                        self.buff.push(GVMe::LOADI(right_loc.loc));
                    } else {
                        self.buff.push(GVMe::LOAD(right_loc.loc));
                    }

                    if left_loc.is_pointer {
                        self.buff.push(GVMe::ADDI(left_loc.loc));
                    } else {
                        self.buff.push(GVMe::ADD(left_loc.loc));
                    }

                    self.compile_store_acc_to_loc(&dst_loc);
                }

                Some(())
            }
            IR::Sub { dest, left, right } => {
                if let (Some(dest_loc), Some(left_loc), Some(right_loc)) = (
                    self.get_var_location_no_extra_cmds(dest),
                    self.get_var_location_no_extra_cmds(left),
                    self.get_var_location_no_extra_cmds(right),
                ) {
                    self.compile_load_loc_to_acc(&left_loc);
                    if right_loc.is_pointer {
                        self.buff.push(GVMe::SUBI(right_loc.loc));
                    } else {
                        self.buff.push(GVMe::SUB(right_loc.loc));
                    }
                    self.compile_store_acc_to_loc(&dest_loc);
                    Some(())
                } else {
                    let mut dst_loc = self.get_var_location(dest);
                    if dst_loc.loc == 0 {
                        self.buff.push(GVMe::STORE(self.last_mem_slot));
                        dst_loc.loc = self.last_mem_slot;
                    }

                    let mut right_loc = self.get_var_location(right);
                    if right_loc.loc == 0 {
                        self.buff.push(GVMe::STORE(self.last_mem_slot - 1));
                        right_loc.loc = self.last_mem_slot - 1;
                    }

                    let left_loc = self.get_var_location(left);
                    if left_loc.is_pointer {
                        self.buff.push(GVMe::LOADI(left_loc.loc));
                    } else {
                        self.buff.push(GVMe::LOAD(left_loc.loc));
                    }

                    if right_loc.is_pointer {
                        self.buff.push(GVMe::SUBI(right_loc.loc));
                    } else {
                        self.buff.push(GVMe::SUB(right_loc.loc));
                    }

                    self.compile_store_acc_to_loc(&dst_loc);
                    Some(())
                }
            }
            IR::Mul { dest, left, right } => {
                if let IrOperand::Constant(const_right) = right {
                    if *const_right == 2 {
                        let left_loc = self.get_var_location_not_acc(left, self.last_mem_slot);
                        let dest_loc = self.get_var_location_not_acc(dest, self.last_mem_slot - 1);
                        self.compile_load_loc_to_acc(&left_loc);
                        self.buff.push(GVMe::ADD(0));
                        self.compile_store_acc_to_loc(&dest_loc);
                        return Some(());
                    }
                }

                if let IrOperand::Constant(const_left) = left {
                    if *const_left == 2 {
                        let right_loc = self.get_var_location_not_acc(right, self.last_mem_slot);
                        let dest_loc = self.get_var_location_not_acc(dest, self.last_mem_slot - 1);
                        self.compile_load_loc_to_acc(&right_loc);
                        self.buff.push(GVMe::ADD(0));
                        self.compile_store_acc_to_loc(&dest_loc);
                        return Some(());
                    }
                }

                self.do_compile_mul = true;

                let left_arg_loc = self.proc_info.get(BUILTINS::MUL.to_name()).unwrap().args[0];
                let left_loc = self.get_var_location(left);
                self.compile_load_loc_to_acc(&left_loc);
                self.buff.push(GVMe::STORE(left_arg_loc));

                let right_arg_loc = self.proc_info.get(BUILTINS::MUL.to_name()).unwrap().args[1];
                let right_loc = self.get_var_location(right);
                self.compile_load_loc_to_acc(&right_loc);
                self.buff.push(GVMe::STORE(right_arg_loc));

                self.buff.push(GVMe::call {
                    name: BUILTINS::MUL.to_name().to_owned(),
                });

                self.last_mem_slot -= 1;
                let mut dest_loc = self.get_var_location(dest);
                if dest_loc.loc == 0 {
                    dest_loc.loc = self.last_mem_slot + 1;
                    self.buff.push(GVMe::STORE(self.last_mem_slot + 1));
                }

                self.compile_load_loc_to_acc(&VarLoc {
                    loc: self.proc_info.get(BUILTINS::MUL.to_name()).unwrap().args[2],
                    is_pointer: false,
                });
                self.compile_store_acc_to_loc(&dest_loc);

                self.last_mem_slot += 1;
                Some(())
            }
            IR::Div { dest, left, right } => {
                if let IrOperand::Constant(const_right) = right {
                    if *const_right == 2 {
                        let left_loc = self.get_var_location_not_acc(left, self.last_mem_slot);
                        let dest_loc = self.get_var_location_not_acc(dest, self.last_mem_slot - 1);
                        self.compile_load_loc_to_acc(&left_loc);
                        self.buff.push(GVMe::HALF);
                        self.compile_store_acc_to_loc(&dest_loc);
                        return Some(());
                    }
                }

                self.do_compile_mod_div = true;

                let left_arg_loc = self
                    .proc_info
                    .get(BUILTINS::DIV_MOD.to_name())
                    .unwrap()
                    .args[0];
                let left_loc = self.get_var_location(left);
                self.compile_load_loc_to_acc(&left_loc);
                self.buff.push(GVMe::STORE(left_arg_loc));

                let right_arg_loc = self
                    .proc_info
                    .get(BUILTINS::DIV_MOD.to_name())
                    .unwrap()
                    .args[1];
                let right_loc = self.get_var_location(right);
                self.compile_load_loc_to_acc(&right_loc);
                self.buff.push(GVMe::STORE(right_arg_loc));

                self.buff.push(GVMe::call {
                    name: BUILTINS::DIV_MOD.to_name().to_owned(),
                });

                self.last_mem_slot -= 1;
                let mut dest_loc = self.get_var_location(dest);
                if dest_loc.loc == 0 {
                    dest_loc.loc = self.last_mem_slot + 1;
                    self.buff.push(GVMe::STORE(self.last_mem_slot + 1));
                }

                self.compile_load_loc_to_acc(&VarLoc {
                    loc: self
                        .proc_info
                        .get(BUILTINS::DIV_MOD.to_name())
                        .unwrap()
                        .args[2],
                    is_pointer: false,
                });
                self.compile_store_acc_to_loc(&dest_loc);

                self.last_mem_slot += 1;
                Some(())
            }
            IR::Mod { dest, left, right } => {
                self.do_compile_mod_div = true;

                let left_arg_loc = self
                    .proc_info
                    .get(BUILTINS::DIV_MOD.to_name())
                    .unwrap()
                    .args[0];
                let left_loc = self.get_var_location(left);
                self.compile_load_loc_to_acc(&left_loc);
                self.buff.push(GVMe::STORE(left_arg_loc));

                let right_arg_loc = self
                    .proc_info
                    .get(BUILTINS::DIV_MOD.to_name())
                    .unwrap()
                    .args[1];
                let right_loc = self.get_var_location(right);
                self.compile_load_loc_to_acc(&right_loc);
                self.buff.push(GVMe::STORE(right_arg_loc));

                self.buff.push(GVMe::call {
                    name: BUILTINS::DIV_MOD.to_name().to_owned(),
                });

                self.last_mem_slot -= 1;
                let mut dest_loc = self.get_var_location(dest);
                if dest_loc.loc == 0 {
                    dest_loc.loc = self.last_mem_slot + 1;
                    self.buff.push(GVMe::STORE(self.last_mem_slot + 1));
                }

                self.compile_load_loc_to_acc(&VarLoc {
                    loc: self
                        .proc_info
                        .get(BUILTINS::DIV_MOD.to_name())
                        .unwrap()
                        .args[3],
                    is_pointer: false,
                });
                self.compile_store_acc_to_loc(&dest_loc);

                self.last_mem_slot += 1;
                Some(())
            }
            IR::Label(str_lbl) => {
                let lbl = self.get_label(&str_lbl);
                self.buff.push(GVMe::lbl {
                    idx: lbl,
                    name: str_lbl.clone(),
                });
                Some(())
            }
            IR::Jump(str_lbl) => {
                let lbl = self.get_label(&str_lbl);
                self.buff.push(GVMe::lbl_jump(lbl));
                Some(())
            }
            IR::JZero { left, right, label } => {
                self.compile_comparison(left, right);
                self.buff.push(GVMe::jz(self.get_label(&label)));
                Some(())
            }
            IR::JNotZero { left, right, label } => {
                self.compile_comparison(left, right);
                self.buff.push(GVMe::jnz(self.get_label(label)));
                Some(())
            }
            IR::JPositive { left, right, label } => {
                self.compile_comparison(left, right);
                self.buff.push(GVMe::jpos(self.get_label(label)));
                Some(())
            }
            IR::JNegative { left, right, label } => {
                self.compile_comparison(left, right);
                self.buff.push(GVMe::jneg(self.get_label(label)));
                Some(())
            }
            IR::JPositiveOrZero { left, right, label } => {
                self.compile_comparison(left, right);
                self.buff.push(GVMe::jposz(self.get_label(label)));
                Some(())
            }
            IR::JNegativeOrZero { left, right, label } => {
                self.compile_comparison(left, right);
                self.buff.push(GVMe::jnegz(self.get_label(label)));
                Some(())
            }
            IR::Call {
                procedure,
                arguments,
            } => {
                let proc_info = self.proc_info.get(procedure).unwrap().clone();
                let ir_proc = *self.ir_proc_info.get(procedure).unwrap();
                let do_inline = proc_info.do_inline;
                let proc_args = proc_info.args.clone();

                if do_inline {
                    self.do_inline(&proc_info, arguments, ir_proc);

                    return Some(());
                } else {
                    self.proc_to_compile.insert(procedure.to_owned());
                    for (i, arg) in arguments.iter().enumerate() {
                        let arg_name = if let IrOperand::Variable(n) = arg {
                            n
                        } else {
                            unreachable!();
                        };
                        let arg_mem_loc = self.memory.get_base_loc(&arg_name, &self.current_scope);

                        let arg_mem_loci64 = arg_mem_loc.memory_address as i64;

                        let target_mem_loc = proc_args.get(i).unwrap().clone();

                        if arg_mem_loc.is_pointer {
                            self.buff.push(GVMe::LOAD(arg_mem_loc.memory_address));
                            self.buff.push(GVMe::STORE(target_mem_loc));
                        } else {
                            self.const_in_acc(&arg_mem_loci64);
                            self.buff.push(GVMe::STORE(target_mem_loc));
                        }
                    }

                    self.buff.push(GVMe::call {
                        name: procedure.clone(),
                    });
                }

                Some(())
            }
            IR::Return => Some(()),
            IR::Read(ir_operand) => {
                let mut var_loc = self.get_var_location(ir_operand);
                if var_loc.loc == 0 {
                    var_loc.loc = self.last_mem_slot;
                    self.buff.push(GVMe::STORE(self.last_mem_slot));
                }
                if !var_loc.is_pointer {
                    self.buff.push(GVMe::GET(var_loc.loc));
                } else {
                    self.buff.push(GVMe::GET(0));
                    self.buff.push(GVMe::STOREI(var_loc.loc));
                }
                Some(())
            }
            IR::Write(ir_operand) => {
                let var_loc = self.get_var_location(ir_operand);
                if !var_loc.is_pointer {
                    self.buff.push(GVMe::PUT(var_loc.loc));
                } else {
                    self.buff.push(GVMe::LOADI(var_loc.loc));
                    self.buff.push(GVMe::PUT(0));
                }
                Some(())
            }
            IR::Comment(cm) => {
                self.buff.push(GVMe::comment { cm: cm.to_string() });
                Some(())
            }
        }
    }

    fn compile_comparison(&mut self, left: &IrOperand, right: &IrOperand) {
        if let (Some(left_loc), Some(right_loc)) = (
            self.get_var_location_no_extra_cmds(left),
            self.get_var_location_no_extra_cmds(right),
        ) {
            if let IrOperand::Constant(c) = right {
                if *c == 0 {
                    if left_loc.is_pointer {
                        self.buff.push(GVMe::LOADI(left_loc.loc));
                    } else {
                        self.buff.push(GVMe::LOAD(left_loc.loc));
                    }
                    return;
                }
            }

            if left_loc.is_pointer {
                self.buff.push(GVMe::LOADI(left_loc.loc));
            } else {
                self.buff.push(GVMe::LOAD(left_loc.loc));
            }

            if right_loc.is_pointer {
                self.buff.push(GVMe::SUBI(right_loc.loc));
            } else {
                self.buff.push(GVMe::SUB(right_loc.loc));
            }
        } else {
            let mut right_loc = self.get_var_location(right);
            if right_loc.loc == 0 {
                right_loc.loc = self.last_mem_slot;
                self.buff.push(GVMe::STORE(self.last_mem_slot));
            }

            let left_loc = self.get_var_location(left);
            self.compile_load_loc_to_acc(&left_loc);
            if right_loc.is_pointer {
                self.buff.push(GVMe::SUBI(right_loc.loc));
            } else {
                self.buff.push(GVMe::SUB(right_loc.loc));
            }
        }
    }

    fn compile_load_loc_to_acc(&mut self, loc: &VarLoc) {
        if loc.is_pointer {
            self.buff.push(GVMe::LOADI(loc.loc));
        } else {
            self.buff.push(GVMe::LOAD(loc.loc));
        }
    }
    fn compile_store_acc_to_loc(&mut self, loc: &VarLoc) {
        if loc.is_pointer {
            self.buff.push(GVMe::STOREI(loc.loc));
        } else {
            self.buff.push(GVMe::STORE(loc.loc));
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

                if !base_loc.is_array {
                    return Some(VarLoc {
                        loc: (base_loc.memory_address as i64 + idx) as usize,
                        is_pointer: false,
                    });
                }
                return None;
            }
            IrOperand::ArrayDynamicAccess { .. } => {
                return None;
            }
        }
    }

    fn get_var_location(&mut self, operand: &IrOperand) -> VarLoc {
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

                if !base_loc.is_pointer {
                    return VarLoc {
                        loc: (base_loc.memory_address as i64 + idx) as usize,
                        is_pointer: false,
                    };
                }
                let memory_address = base_loc.memory_address;
                self.const_in_acc(idx);
                self.buff.push(GVMe::ADD(memory_address));
                VarLoc {
                    is_pointer: true,
                    loc: 0,
                }
            }
            IrOperand::ArrayDynamicAccess {
                base_name,
                idx_name,
            } => {
                let scope = &self.current_scope;

                let base_loc = self.memory.get_base_loc(&base_name, &scope).clone();
                let idx_loc = self.memory.get_base_loc(&idx_name, &scope).clone();
                let base_addr = base_loc.memory_address;
                let idx_addr = idx_loc.memory_address;

                let base_address = base_loc.memory_address;
                let idx_address = idx_loc.memory_address;
                match (base_loc.is_pointer, idx_loc.is_pointer) {
                    (false, false) => {
                        self.const_in_acc(&(base_addr as i64));
                        self.buff.push(GVMe::ADD(idx_addr));
                    }
                    (false, true) => {
                        self.const_in_acc(&(base_address as i64));
                        self.buff.push(GVMe::ADDI(idx_address));
                    }
                    (true, false) => {
                        self.buff.push(GVMe::LOAD(base_loc.memory_address));
                        self.buff.push(GVMe::ADD(idx_loc.memory_address));
                    }
                    (true, true) => {
                        self.buff.push(GVMe::LOAD(base_loc.memory_address));
                        self.buff.push(GVMe::ADDI(idx_loc.memory_address));
                    }
                }
                VarLoc {
                    is_pointer: true,
                    loc: 0,
                }
            }
        }
    }

    fn get_var_location_not_acc(&mut self, operand: &IrOperand, where_to_put_it: usize) -> VarLoc {
        let mut loc = self.get_var_location(operand);
        if loc.loc == 0 {
            loc.loc = where_to_put_it;
            self.buff.push(GVMe::STORE(where_to_put_it));
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

    fn const_in_acc(&mut self, val: &i64) {
        let loc = self.memory.get_const_loc_or_aloc(val);
        self.buff.push(GVMe::LOAD(loc.memory_address));
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
    ) {
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

        for cm in renamed_commands.iter() {
            let new_cm: IR = match cm {
                IR::Label(label) => IR::Label(self.get_or_create_label(label, &mut label_map)),
                IR::Jump(label) => IR::Jump(self.get_or_create_label(label, &mut label_map)),
                IR::JZero { left, right, label } => IR::JZero {
                    left: left.clone(),
                    right: right.clone(),
                    label: self.get_or_create_label(label, &mut label_map),
                },
                IR::JNotZero { left, right, label } => IR::JNotZero {
                    left: left.clone(),
                    right: right.clone(),
                    label: self.get_or_create_label(label, &mut label_map),
                },
                IR::JPositive { left, right, label } => IR::JPositive {
                    left: left.clone(),
                    right: right.clone(),
                    label: self.get_or_create_label(label, &mut label_map),
                },
                IR::JNegative { left, right, label } => IR::JNegative {
                    left: left.clone(),
                    right: right.clone(),
                    label: self.get_or_create_label(label, &mut label_map),
                },
                IR::JPositiveOrZero { left, right, label } => IR::JPositiveOrZero {
                    left: left.clone(),
                    right: right.clone(),
                    label: self.get_or_create_label(label, &mut label_map),
                },
                IR::JNegativeOrZero { left, right, label } => IR::JNegativeOrZero {
                    left: left.clone(),
                    right: right.clone(),
                    label: self.get_or_create_label(label, &mut label_map),
                },
                _ => cm.clone(),
            };
            println!("{} -> {}", cm, new_cm);

            self.compile_op(&new_cm);
        }
    }

    fn get_or_create_label(
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

    /// BUILTIN PROCEDURES !!!!
    fn generate_mul_procedure_stub(&mut self) -> GVMeProc {
        let proc_name = BUILTINS::MUL.to_name();

        let mut args = vec![];
        args.push(
            self.memory
                .allocate_builtin_arg("arg1", &proc_name)
                .memory_address,
        );
        args.push(
            self.memory
                .allocate_builtin_arg("arg2", &proc_name)
                .memory_address,
        );
        args.push(
            self.memory
                .allocate_builtin_arg("rtn", &proc_name)
                .memory_address,
        );

        self.memory.allocate_builtin_arg("last_arg1", &proc_name);
        self.memory.allocate_builtin_arg("last_arg2", &proc_name);

        self.next_available_label += 1;
        GVMeProc {
            label: LabelIdx(self.next_available_label - 1),
            return_address: self.memory.allocate_proc_return(&proc_name),
            args: args,
            do_inline: false,
            arg_names: vec![
                "arg1".to_owned(),
                "arg2".to_owned(),
                "rtn".to_owned(),
                "last_arg1".to_owned(),
                "last_arg2".to_owned(),
            ],
        }
    }

    fn generate_div_mod_procedure_stub(&mut self) -> GVMeProc {
        let proc_name = BUILTINS::DIV_MOD.to_name();

        let mut args = vec![];
        args.push(
            self.memory
                .allocate_builtin_arg("arg1", &proc_name)
                .memory_address,
        );
        args.push(
            self.memory
                .allocate_builtin_arg("arg2", &proc_name)
                .memory_address,
        );
        args.push(
            self.memory
                .allocate_builtin_arg("dividend", &proc_name)
                .memory_address,
        );
        args.push(
            self.memory
                .allocate_builtin_arg("divisor", &proc_name)
                .memory_address,
        );

        self.memory.allocate_builtin_arg("last_arg1", &proc_name);
        self.memory.allocate_builtin_arg("last_arg2", &proc_name);

        self.next_available_label += 1;

        GVMeProc {
            label: LabelIdx(self.next_available_label - 1),
            return_address: self.memory.allocate_proc_return(&proc_name),
            args: args,
            do_inline: false,
            arg_names: vec![
                "arg1".to_owned(),
                "arg2".to_owned(),
                "dividend".to_owned(),
                "divisor".to_owned(),
                "last_arg1".to_owned(),
                "last_arg2".to_owned(),
            ],
        }
    }

    fn compile_mul_builtin(&mut self) {
        let proc_info = self
            .proc_info
            .get(BUILTINS::MUL.to_name())
            .cloned()
            .unwrap();
        self.buff.push(GVMe::lbl {
            idx: proc_info.label.clone(),
            name: BUILTINS::MUL.to_name().to_owned(),
        });
        let arg1 = proc_info.args[0];
        let arg2 = proc_info.args[1];
        let res = proc_info.args[2];

        let last_arg1 = self
            .memory
            .get_base_loc("last_arg1", &BUILTINS::MUL.to_name())
            .memory_address;

        let last_arg2 = self
            .memory
            .get_base_loc("last_arg2", &BUILTINS::MUL.to_name())
            .memory_address;

        let zero = 0;
        let one = 1;
        let m_one = -1;
        self.const_in_acc(&zero);
        self.buff.push(GVMe::STORE(res));

        let loop_end_lbl = self.next_label();
        let loop_start_lbl = self.next_label();

        let skip_add = self.next_label();

        let sign_flag = self.last_mem_slot - 1;
        let arg_1_pos = self.next_label();
        let arg_2_pos = self.next_label();

        self.const_in_acc(&one);
        self.buff.push(GVMe::STORE(sign_flag));

        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::jpos(arg_1_pos.clone()));

        self.const_in_acc(&m_one);
        self.buff.push(GVMe::STORE(sign_flag));
        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(arg1));
        self.buff.push(GVMe::STORE(arg1));

        self.buff.push(GVMe::lbl {
            idx: arg_1_pos,
            name: format!(""),
        });

        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::jpos(arg_2_pos.clone()));

        self.const_in_acc(&zero);

        self.buff.push(GVMe::SUB(sign_flag));
        self.buff.push(GVMe::STORE(sign_flag));
        self.const_in_acc(&zero);

        self.buff.push(GVMe::SUB(arg2));
        self.buff.push(GVMe::STORE(arg2));

        self.buff.push(GVMe::lbl {
            idx: arg_2_pos,
            name: format!(""),
        });
        //TODO VVVVVV
        // SWAP ARGS SO THE SMALLER ONE IS SECOND

        // CHECK IF LAST ARGS ARE THE SAME

        // STORE CURRENT ARGS TO LAST ARGS

        // CARRY ON
        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::lbl {
            idx: loop_start_lbl.clone(),
            name: format!(""),
        });
        self.buff.push(GVMe::jz(loop_end_lbl.clone()));

        self.buff.push(GVMe::HALF);
        self.buff.push(GVMe::ADD(0));
        self.buff.push(GVMe::SUB(arg1));

        self.buff.push(GVMe::jz(skip_add.clone()));
        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::LOAD(res));
        self.buff.push(GVMe::ADD(arg2));
        self.buff.push(GVMe::STORE(res));
        self.buff.push(GVMe::lbl {
            idx: skip_add,
            name: format!(""),
        });

        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::ADD(arg2));
        self.buff.push(GVMe::STORE(arg2));

        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::HALF);
        self.buff.push(GVMe::STORE(arg1));

        self.buff.push(GVMe::lbl_jump(loop_start_lbl));
        self.buff.push(GVMe::lbl {
            idx: loop_end_lbl,
            name: format!(""),
        });

        let is_pos = self.next_label();

        let skip = self.next_label();

        self.buff.push(GVMe::LOAD(sign_flag));
        self.buff.push(GVMe::jpos(is_pos.clone()));

        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(res));
        self.buff.push(GVMe::lbl_jump(skip.clone()));

        self.buff.push(GVMe::lbl {
            idx: is_pos,
            name: format!(""),
        });
        self.buff.push(GVMe::LOAD(res));
        self.buff.push(GVMe::lbl {
            idx: skip,
            name: format!(""),
        });
        self.buff.push(GVMe::STORE(res));

        self.buff.push(GVMe::RTRN(proc_info.return_address));
    }

    fn compile_div_mod_builtin(&mut self) {
        let proc_info = self
            .proc_info
            .get(BUILTINS::DIV_MOD.to_name())
            .cloned()
            .unwrap();
        self.buff.push(GVMe::lbl {
            idx: proc_info.label.clone(),
            name: BUILTINS::DIV_MOD.to_name().to_owned(),
        });

        let arg1 = proc_info.args[0];
        let arg2 = proc_info.args[1];
        let div_res = proc_info.args[2];
        let mod_res = proc_info.args[3];

        let zero = 0;
        let one = 1;
        let m_one = -1;
        let arg1_positive = self.last_mem_slot;
        let arg2_positive = self.last_mem_slot - 1;

        let power_of_two = self.last_mem_slot - 2;

        let arg2_cpy = self.last_mem_slot - 3;

        let arg_1_pos = self.next_label();
        let arg_2_pos = self.next_label();
        let arg_2_zero = self.next_label();
        // if b == 0
        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::jnz(arg_2_zero.clone()));
        self.const_in_acc(&zero);
        self.buff.push(GVMe::STORE(div_res));
        self.buff.push(GVMe::STORE(mod_res));
        self.buff.push(GVMe::RTRN(proc_info.return_address));
        self.buff.push(GVMe::lbl {
            idx: arg_2_zero,
            name: format!(""),
        });

        // sign = 1, mod_sign = 1
        self.const_in_acc(&one);
        self.buff.push(GVMe::STORE(arg1_positive));
        self.buff.push(GVMe::STORE(arg2_positive));

        // if arg1 < 0
        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::jpos(arg_1_pos.clone()));

        self.const_in_acc(&m_one);
        self.buff.push(GVMe::STORE(arg1_positive));
        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(arg1));
        self.buff.push(GVMe::STORE(arg1));

        self.buff.push(GVMe::lbl {
            idx: arg_1_pos,
            name: format!(""),
        });

        // if arg2 < 0
        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::jpos(arg_2_pos.clone()));

        self.const_in_acc(&m_one);
        self.buff.push(GVMe::STORE(arg2_positive));

        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(arg2));
        self.buff.push(GVMe::STORE(arg2));

        self.buff.push(GVMe::lbl {
            idx: arg_2_pos,
            name: format!(""),
        });
        self.buff.push(GVMe::STORE(arg2_cpy));

        //TODO VVVVVV

        // CHECK IF LAST ARGS ARE THE SAME

        // STORE CURRENT ARGS TO LAST ARGS

        // CARRY ON

        self.const_in_acc(&zero);
        self.buff.push(GVMe::STORE(div_res));

        self.const_in_acc(&one);
        self.buff.push(GVMe::STORE(power_of_two));

        /*
        while arg2 - arg1 < 0:
            arg2 += arg2
            power_of_two += power_of_two
        */
        let loop1_start = self.next_label();
        let loop_exit1 = self.next_label();
        self.buff.push(GVMe::lbl {
            idx: loop1_start.clone(),
            name: format!(""),
        });
        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::SUB(arg1));
        self.buff.push(GVMe::jpos(loop_exit1.clone()));
        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::ADD(arg2));
        self.buff.push(GVMe::STORE(arg2));

        self.buff.push(GVMe::LOAD(power_of_two));
        self.buff.push(GVMe::ADD(power_of_two));
        self.buff.push(GVMe::STORE(power_of_two));

        self.buff.push(GVMe::lbl_jump(loop1_start));
        self.buff.push(GVMe::lbl {
            idx: loop_exit1,
            name: format!(""),
        });

        /*
        while !power_of_two <= 0:
            if arg1 - arg2 >= 0 :
                arg1 -= arg2
                quotient += power_of_two

            arg2 = arg2 // 2
            power_of_two = power_of_two // 2
        */
        let loop2_start = self.next_label();
        let loop2_end = self.next_label();
        let inner_if_fail = self.next_label();

        self.buff.push(GVMe::lbl {
            idx: loop2_start.clone(),
            name: format!(""),
        });
        self.buff.push(GVMe::LOAD(power_of_two));
        self.buff.push(GVMe::jnegz(loop2_end.clone()));

        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::SUB(arg2));
        self.buff.push(GVMe::jneg(inner_if_fail.clone()));
        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::SUB(arg2));
        self.buff.push(GVMe::STORE(arg1));

        self.buff.push(GVMe::LOAD(div_res));
        self.buff.push(GVMe::ADD(power_of_two));
        self.buff.push(GVMe::STORE(div_res));

        self.buff.push(GVMe::lbl {
            idx: inner_if_fail,
            name: format!(""),
        });

        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::HALF);
        self.buff.push(GVMe::STORE(arg2));

        self.buff.push(GVMe::LOAD(power_of_two));
        self.buff.push(GVMe::HALF);
        self.buff.push(GVMe::STORE(power_of_two));

        self.buff.push(GVMe::lbl_jump(loop2_start));
        self.buff.push(GVMe::lbl {
            idx: loop2_end,
            name: format!(""),
        });

        // arg1 positive
        let arg1_is_in_fact_negative = self.next_label();
        self.buff.push(GVMe::LOAD(arg1_positive));
        self.buff.push(GVMe::jneg(arg1_is_in_fact_negative));

        // arg1 pos, arg2 pos
        let arg1_pos_and_arg2_negative = self.next_label();
        self.buff.push(GVMe::LOAD(arg2_positive));
        self.buff.push(GVMe::jneg(arg1_pos_and_arg2_negative));
        // x>0 y>0 -> nothing
        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::STORE(mod_res));
        self.buff.push(GVMe::RTRN(proc_info.return_address));

        // arg1 pos, arg2 neg
        self.buff.push(GVMe::lbl {
            idx: arg1_pos_and_arg2_negative,
            name: format!(""),
        });
        // x>0 y<0 -> q = -1 - q and r = r - y
        self.const_in_acc(&m_one);
        self.buff.push(GVMe::SUB(div_res));
        self.buff.push(GVMe::STORE(div_res));
        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::SUB(arg2_cpy));
        self.buff.push(GVMe::STORE(mod_res));
        self.buff.push(GVMe::RTRN(proc_info.return_address));

        // arg1 negative
        self.buff.push(GVMe::lbl {
            idx: arg1_is_in_fact_negative,
            name: format!(""),
        });

        let arg1_neg_and_arg2_neg = self.next_label();
        self.buff.push(GVMe::LOAD(arg2_positive));
        self.buff.push(GVMe::jneg(arg1_neg_and_arg2_neg));
        // x<0 y>0 -> q = -1 - q and r = y - r
        self.const_in_acc(&m_one);
        self.buff.push(GVMe::SUB(div_res));
        self.buff.push(GVMe::STORE(div_res));
        self.buff.push(GVMe::LOAD(arg2_cpy));
        self.buff.push(GVMe::SUB(arg1));
        self.buff.push(GVMe::STORE(mod_res));
        self.buff.push(GVMe::RTRN(proc_info.return_address));

        self.buff.push(GVMe::lbl {
            idx: arg1_neg_and_arg2_neg,
            name: format!(""),
        });
        // x<0 y<0 -> r = -r
        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(arg1));
        self.buff.push(GVMe::STORE(mod_res));

        self.buff.push(GVMe::RTRN(proc_info.return_address));
    }

    fn next_label(&mut self) -> LabelIdx {
        let lbl = LabelIdx(self.next_available_label);
        self.next_available_label += 1;
        return lbl;
    }
}
