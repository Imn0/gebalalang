use std::{
    collections::HashMap,
    fmt::{self},
    process::id,
    usize,
};

use regex::Regex;

use crate::code_gen::{
    ir::{IrOperand, IR},
    IrProgram, ProcedureInfo,
};

use super::memory::Memory;

#[derive(Clone, Debug, Default)]
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
pub struct GVMeProc {
    pub label: LabelIdx,
    pub return_address: usize,
    args: Vec<usize>,
}

struct GVMeGnerator<'a> {
    code: Vec<GVMe>,
    proc_info: HashMap<String, GVMeProc>,
    memory: Memory,
    current_scope: &'a str,
    last_mem_slot: usize,
}

struct VarLoc {
    loc: usize,
    is_pointer: bool,
}

pub fn compile(ir_program: &IrProgram) -> GVMeProgram {
    let mut generator = GVMeGnerator {
        code: vec![],
        memory: Memory::new(),
        proc_info: HashMap::new(),
        current_scope: "",
        last_mem_slot: 0x4000000000000000,
    };

    generator.generate_code(ir_program);

    GVMeProgram {
        code: generator.code,
        proc_info: generator.proc_info,
    }
}

impl<'a> GVMeGnerator<'a> {
    fn generate_code(&mut self, ir_program: &IrProgram) {
        for (_, proc) in &ir_program.procedures {
            self.generate_procedure_stub(proc);
        }

        self.current_scope = "PROGRAM";
        for op in &ir_program.main {
            self.compile_op(op);
        }
        self.code.push(GVMe::HALT);
        // TODO ADD PROCEDURES !!!

        let mut c = vec![];
        for constant in self.memory.get_constants() {
            let loc = self.memory.get_const(constant);
            c.push(GVMe::SET(constant.clone()));
            c.push(GVMe::STORE(loc.memory_address));
        }

        c.append(&mut self.code);
        self.code = c;
    }

    fn generate_procedure_stub(&mut self, proc_info: &ProcedureInfo) -> GVMeProc {
        let mut v_args = vec![];
        for arg in &proc_info.args {
            v_args.push(
                self.memory
                    .allocate_proc_arg(&arg.name, &proc_info.name, arg.is_array)
                    .memory_address,
            );
        }

        GVMeProc {
            label: self.get_label(&proc_info.lbl),
            return_address: self.memory.allocate_proc_return(&proc_info.name),
            args: v_args,
        }
    }

    fn compile_procedure(&mut self, proc_info: &ProcedureInfo) {
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
                        .allocate_array(name, self.current_scope, left, right);
                } else {
                    self.memory.allocate_var(name, self.current_scope);
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
                        self.code.push(GVMe::STORE(self.last_mem_slot));
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
                // TODO extra cmds

                if let (Some(dest_loc), Some(left_loc), Some(right_loc)) = (
                    self.get_var_location_no_extra_cmds(dest),
                    self.get_var_location_no_extra_cmds(left),
                    self.get_var_location_no_extra_cmds(right),
                ) {
                    self.compile_load_loc_to_acc(&left_loc);
                    if right_loc.is_pointer {
                        self.code.push(GVMe::ADDI(right_loc.loc));
                    } else {
                        self.code.push(GVMe::ADD(right_loc.loc));
                    }
                    self.compile_store_acc_to_loc(&dest_loc);
                }

                Some(())
            }
            IR::Sub { dest, left, right } => {
                // TODO extra cmds

                if let (Some(dest_loc), Some(left_loc), Some(right_loc)) = (
                    self.get_var_location_no_extra_cmds(dest),
                    self.get_var_location_no_extra_cmds(left),
                    self.get_var_location_no_extra_cmds(right),
                ) {
                    self.compile_load_loc_to_acc(&left_loc);
                    if right_loc.is_pointer {
                        self.code.push(GVMe::SUBI(right_loc.loc));
                    } else {
                        self.code.push(GVMe::SUB(right_loc.loc));
                    }
                    self.compile_store_acc_to_loc(&dest_loc);
                }

                Some(())
            }
            IR::Mul { dest, left, right } => todo!(),
            IR::Div { dest, left, right } => todo!(),
            IR::Mod { dest, left, right } => todo!(),
            IR::Label(str_lbl) => {
                let lbl = self.get_label(&str_lbl);
                self.code.push(GVMe::lbl {
                    idx: lbl,
                    name: str_lbl.clone(),
                });
                Some(())
            }
            IR::Jump(str_lbl) => {
                let lbl = self.get_label(&str_lbl);
                self.code.push(GVMe::lbl_jump(lbl));
                Some(())
            }
            IR::JZero { left, right, label } => {
                self.compile_sub_res_in_acc(left, right);
                self.code.push(GVMe::jz(self.get_label(&label)));
                Some(())
            }
            IR::JNotZero { left, right, label } => {
                self.compile_sub_res_in_acc(left, right);
                self.code.push(GVMe::jnz(self.get_label(label)));
                Some(())
            }
            IR::JPositive { left, right, label } => {
                self.compile_sub_res_in_acc(left, right);
                self.code.push(GVMe::jpos(self.get_label(label)));
                Some(())
            }
            IR::JNegative { left, right, label } => {
                self.compile_sub_res_in_acc(left, right);
                self.code.push(GVMe::jneg(self.get_label(label)));
                Some(())
            }
            IR::JPositiveOrZero { left, right, label } => {
                self.compile_sub_res_in_acc(left, right);
                self.code.push(GVMe::jposz(self.get_label(label)));
                Some(())
            }
            IR::JNegativeOrZero { left, right, label } => {
                self.compile_sub_res_in_acc(left, right);
                self.code.push(GVMe::jnegz(self.get_label(label)));
                Some(())
            }
            IR::Call {
                procedure,
                arguments,
            } => {Some(())},
            IR::Return => todo!(),
            IR::Read(ir_operand) => {
                let var_loc = self.get_var_location(ir_operand);
                if !var_loc.is_pointer {
                    self.code.push(GVMe::GET(var_loc.loc));
                } else {
                    self.code.push(GVMe::GET(0));
                    self.code.push(GVMe::STOREI(var_loc.loc));
                }
                Some(())
            }
            IR::Write(ir_operand) => {
                let var_loc = self.get_var_location(ir_operand);
                if !var_loc.is_pointer {
                    self.code.push(GVMe::PUT(var_loc.loc));
                } else {
                    self.code.push(GVMe::LOADI(var_loc.loc));
                    self.code.push(GVMe::PUT(0));
                }
                Some(())
            }
            IR::Comment(cm) => {
                self.code.push(GVMe::comment { cm: cm.to_string() });
                Some(())
            }
        }
    }

    fn compile_sub_res_in_acc(&mut self, left: &IrOperand, right: &IrOperand) {
        // TODO extra cmds
        if let (Some(left_loc), Some(right_loc)) = (
            self.get_var_location_no_extra_cmds(left),
            self.get_var_location_no_extra_cmds(right),
        ) {
            if left_loc.is_pointer {
                self.code.push(GVMe::LOADI(left_loc.loc));
            } else {
                self.code.push(GVMe::LOAD(left_loc.loc));
            }

            if right_loc.is_pointer {
                self.code.push(GVMe::SUBI(right_loc.loc));
            } else {
                self.code.push(GVMe::SUB(right_loc.loc));
            }
        }
    }

    fn compile_load_loc_to_acc(&mut self, loc: &VarLoc) {
        if loc.is_pointer {
            self.code.push(GVMe::LOADI(loc.loc));
        } else {
            self.code.push(GVMe::LOAD(loc.loc));
        }
    }
    fn compile_store_acc_to_loc(&mut self, loc: &VarLoc) {
        if loc.is_pointer {
            self.code.push(GVMe::STOREI(loc.loc));
        } else {
            self.code.push(GVMe::STORE(loc.loc));
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

                if !base_loc.is_array {
                    return VarLoc {
                        loc: (base_loc.memory_address as i64 + idx) as usize,
                        is_pointer: false,
                    };
                }
                let memory_address = base_loc.memory_address;
                self.const_in_acc(idx);
                self.code.push(GVMe::ADD(memory_address));
                VarLoc {
                    is_pointer: true,
                    loc: 0,
                }
            }
            IrOperand::ArrayDynamicAccess {
                base_name,
                idx_name,
            } => {
                let scope = self.current_scope;
                let base_loc = self.memory.get_base_loc(&base_name, &scope);
                let idx_loc = self.memory.get_base_loc(&idx_name, &scope);
                let base_addr = base_loc.memory_address;
                let idx_addr = idx_loc.memory_address;

                let base_address = base_loc.memory_address;
                let idx_address = idx_loc.memory_address;
                match (base_loc.is_pointer, idx_loc.is_pointer) {
                    (false, false) => {
                        self.const_in_acc(&(base_addr as i64));
                        self.code.push(GVMe::ADD(idx_addr));
                    }
                    (false, true) => {
                        self.const_in_acc(&(base_address as i64));
                        self.code.push(GVMe::ADDI(idx_address));
                    }
                    (true, false) => {
                        self.code.push(GVMe::LOAD(base_loc.memory_address));
                        self.code.push(GVMe::ADD(idx_loc.memory_address));
                    }
                    (true, true) => {
                        self.code.push(GVMe::LOAD(base_loc.memory_address));
                        self.code.push(GVMe::ADDI(idx_loc.memory_address));
                    }
                }
                VarLoc {
                    is_pointer: true,
                    loc: 0,
                }
            }
        }
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
        self.code.push(GVMe::LOAD(loc.memory_address));
    }

    fn get_const_loc(&mut self, val: &i64) -> VarLoc {
        let loc = self.memory.get_const_loc_or_aloc(val);
        VarLoc {
            loc: loc.memory_address,
            is_pointer: false,
        }
    }
}
