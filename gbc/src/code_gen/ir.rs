use std::fmt;

use super::{IrProgram, ProcedureInfo};

#[derive(Debug, Clone)]
pub enum IR {
    Aloc {
        name: String,
        is_array: bool,
        array_bounds: Option<(i64, i64)>,
    },
    Drop {
        name: String,
    },
    Mov {
        dest: IrOperand,
        src: IrOperand,
    },
    Add {
        dest: IrOperand,
        left: IrOperand,
        right: IrOperand,
    },
    Sub {
        dest: IrOperand,
        left: IrOperand,
        right: IrOperand,
    },
    Mul {
        dest: IrOperand,
        left: IrOperand,
        right: IrOperand,
    },
    Div {
        dest: IrOperand,
        left: IrOperand,
        right: IrOperand,
    },
    Mod {
        dest: IrOperand,
        left: IrOperand,
        right: IrOperand,
    },
    Label(String),
    Jump(String),
    JZero {
        left: IrOperand,
        right: IrOperand,
        label: String,
    },
    JNotZero {
        left: IrOperand,
        right: IrOperand,
        label: String,
    },
    JPositive {
        left: IrOperand,
        right: IrOperand,
        label: String,
    },
    JNegative {
        left: IrOperand,
        right: IrOperand,
        label: String,
    },
    JPositiveOrZero {
        left: IrOperand,
        right: IrOperand,
        label: String,
    },
    JNegativeOrZero {
        left: IrOperand,
        right: IrOperand,
        label: String,
    },
    Call {
        procedure: String,
        arguments: Vec<IrOperand>,
    },
    Return,
    Read(IrOperand),
    Write(IrOperand),
    Comment(String),
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum IrOperand {
    Variable(String),
    Constant(i64),
    ArrayConstAccess { base_name: String, idx: i64 },
    ArrayDynamicAccess { base_name: String, idx_name: String },
}

impl fmt::Display for IR {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            IR::Label(lbl) => write!(f, "{}", lbl),
            IR::Comment(cm) => write!(f, "?# {}", cm),

            _ => {
                write!(f, "  ")?;
                match self {
                    IR::Comment(_) => unreachable!(),
                    IR::Label(_) => unreachable!(),

                    IR::Mov { dest, src } => write!(f, "store {} {}", dest, src),
                    IR::Add { dest, left, right } => write!(f, "add {} {} {}", dest, left, right),
                    IR::Sub { dest, left, right } => write!(f, "sub {} {} {}", dest, left, right),
                    IR::Mul { dest, left, right } => write!(f, "mul {} {} {}", dest, left, right),
                    IR::Div { dest, left, right } => write!(f, "div {} {} {}", dest, left, right),
                    IR::Mod { dest, left, right } => write!(f, "mod {} {} {}", dest, left, right),
                    IR::Jump(lbl) => write!(f, "jmp {}", lbl),

                    IR::JZero { left, right, label } => {
                        write!(f, "jz {} {} {}", label, left, right)
                    }
                    IR::JNotZero { left, right, label } => {
                        write!(f, "jnz {} {} {}", label, left, right)
                    }
                    IR::JPositive { left, right, label } => {
                        write!(f, "jpos {} {} {}", label, left, right)
                    }
                    IR::JNegative { left, right, label } => {
                        write!(f, "jneg {} {} {}", label, left, right)
                    }
                    IR::JPositiveOrZero { left, right, label } => {
                        write!(f, "jposz {} {} {}", label, left, right)
                    }
                    IR::JNegativeOrZero { left, right, label } => {
                        write!(f, "jnegz{} {} {}", label, left, right)
                    }
                    IR::Call {
                        procedure,
                        arguments,
                    } => {
                        write!(f, "call {}", procedure)?;
                        for op in arguments {
                            write!(f, " {}", op)?
                        }

                        write!(f, "")
                    }
                    IR::Return => write!(f, "rtn"),
                    IR::Read(ir_operand) => write!(f, "read {}", ir_operand),
                    IR::Write(ir_operand) => write!(f, "write {}", ir_operand),
                    IR::Aloc {
                        name,
                        is_array,
                        array_bounds,
                    } => {
                        write!(f, "aloc {} ", name)?;

                        if *is_array {
                            let bounds = array_bounds.unwrap();
                            write!(f, "{} {}", bounds.0, bounds.1)?;
                        }
                        write!(f, "")
                    }
                    IR::Drop { name } => write!(f, "drop {}", name),
                }
            }
        }
    }
}

impl fmt::Display for IrOperand {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            IrOperand::Variable(v) => write!(f, "{}", v),
            IrOperand::Constant(c) => write!(f, "{}", c),
            IrOperand::ArrayConstAccess { base_name, idx } => write!(f, "{}[{}]", base_name, idx),
            IrOperand::ArrayDynamicAccess {
                base_name,
                idx_name,
            } => write!(f, "{}[{}]", base_name, idx_name),
        }
    }
}

impl fmt::Display for ProcedureInfo {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "fn {}(", self.name)?;

        let mut args_str = String::new();

        for arg in self.args.iter() {
            args_str.push_str(&arg.name);
            if arg.is_array {
                args_str.push_str("@T ");
            } else {
                args_str.push(' ');
            }
        }

        args_str.pop();

        writeln!(f, "{}):", args_str)?;

        for ir_cmd in self.cmds.iter() {
            write!(f, "{}\n", ir_cmd)?;
        }
        write!(f, "")
    }
}

impl fmt::Display for IrProgram {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        for (_, proc_info) in &self.procedures {
            writeln!(f, "{}", proc_info)?;
        }

        for ir_cmd in self.main.iter() {
            write!(f, "{}\n", ir_cmd)?;
        }

        write!(f, "")
    }
}
