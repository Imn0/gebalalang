use std::{
    collections::HashMap,
    fmt::{self},
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
        println!("{:#?}", self.memory);
        self.code.push(GVMe::HALT);
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

    fn compile_op(&mut self, op: &IR) {
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
            }
            IR::Drop { name } => {
                self.memory.drop_var(name, &self.current_scope);
            }
            IR::Mov { dest, src } => todo!(),
            IR::Add { dest, left, right } => todo!(),
            IR::Sub { dest, left, right } => todo!(),
            IR::Mul { dest, left, right } => todo!(),
            IR::Div { dest, left, right } => todo!(),
            IR::Mod { dest, left, right } => todo!(),
            IR::Label(str_lbl) => {
                let lbl = self.get_label(&str_lbl);
                self.code.push(GVMe::lbl {
                    idx: lbl,
                    name: str_lbl.clone(),
                });
            }
            IR::Jump(str_lbl) => {
                let lbl = self.get_label(&str_lbl);
                self.code.push(GVMe::lbl_jump(lbl));
            },
            IR::JZero { left, right, label } => todo!(),
            IR::JNotZero { left, right, label } => todo!(),
            IR::JPositive { left, right, label } => todo!(),
            IR::JNegative { left, right, label } => todo!(),
            IR::JPositiveOrZero { left, right, label } => todo!(),
            IR::JNegativeOrZero { left, right, label } => todo!(),
            IR::Call {
                procedure,
                arguments,
            } => todo!(),
            IR::Return => todo!(),
            IR::Read(ir_operand) => {
                let var_loc = self.get_var_location_no_extra_cmds(ir_operand);
                if !var_loc.is_pointer {
                    self.code.push(GVMe::GET(var_loc.loc));
                } else {
                    self.code.push(GVMe::GET(0));
                    self.code.push(GVMe::STOREI(var_loc.loc));
                }
            }
            IR::Write(ir_operand) => {
                let var_loc = self.get_var_location_no_extra_cmds(ir_operand);
                if !var_loc.is_pointer {
                    self.code.push(GVMe::PUT(var_loc.loc));
                } else {
                    self.code.push(GVMe::LOADI(var_loc.loc));
                    self.code.push(GVMe::PUT(0));
                }
            }
        }
    }

    fn get_var_location_no_extra_cmds(&mut self, operand: &IrOperand) -> VarLoc {
        match operand {
            IrOperand::Variable(name) => {
                let loc = self.memory.get_base_loc(name, &self.current_scope);
                VarLoc {
                    loc: loc.memory_address,
                    is_pointer: loc.is_pointer,
                }
            }
            IrOperand::Constant(val) => todo!(),
            IrOperand::ArrayConstAccess { base_name, idx } => todo!(),
            IrOperand::ArrayDynamicAccess {
                base_name,
                idx_name,
            } => todo!(),
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
        panic!();
    }
}
