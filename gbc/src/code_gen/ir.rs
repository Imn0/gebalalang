use std::{collections::HashMap, fmt};

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
    ProcCall {
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
                        write!(f, "jnegz {} {} {}", label, left, right)
                    }
                    IR::ProcCall {
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

impl IrOperand {
    pub fn base_name(&self) -> &str {
        match self {
            IrOperand::Variable(name) => &name,
            IrOperand::Constant(_) => "CONST",
            IrOperand::ArrayConstAccess { base_name, .. } => &base_name,
            IrOperand::ArrayDynamicAccess { base_name, .. } => &base_name,
        }
    }
    pub fn is_array(&self) -> bool {
        match self {
            IrOperand::Variable(_) => return false,
            IrOperand::Constant(_) => return false,
            IrOperand::ArrayConstAccess { .. } => return true,
            IrOperand::ArrayDynamicAccess { .. } => return true,
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

pub struct IRNameTransformer<'a> {
    pub translate_map: HashMap<String, String>,
    pub default_prefix: &'a str,
}

impl<'a> IRNameTransformer<'a> {
    pub fn ir_transform(&self, original: &Vec<IR>) -> Vec<IR> {
        let mut v = vec![];
        for op in original.iter() {
            v.push(match op {
                IR::Aloc {
                    name,
                    is_array,

                    array_bounds,
                } => IR::Aloc {
                    name: self.name_transform(name),
                    is_array: *is_array,
                    array_bounds: *array_bounds,
                },
                IR::Drop { name } => IR::Drop {
                    name: self.name_transform(name),
                },
                IR::Mov { dest, src } => IR::Mov {
                    dest: self.ir_oper_transform(dest),
                    src: self.ir_oper_transform(src),
                },
                IR::Add { dest, right, left } => IR::Add {
                    dest: self.ir_oper_transform(dest),
                    right: self.ir_oper_transform(right),
                    left: self.ir_oper_transform(left),
                },
                IR::Sub { dest, left, right } => IR::Sub {
                    dest: self.ir_oper_transform(dest),
                    right: self.ir_oper_transform(right),
                    left: self.ir_oper_transform(left),
                },
                IR::Mul { dest, left, right } => IR::Mul {
                    dest: self.ir_oper_transform(dest),
                    right: self.ir_oper_transform(right),
                    left: self.ir_oper_transform(left),
                },
                IR::Div { dest, left, right } => IR::Div {
                    dest: self.ir_oper_transform(dest),
                    right: self.ir_oper_transform(right),
                    left: self.ir_oper_transform(left),
                },
                IR::Mod { dest, left, right } => IR::Mod {
                    dest: self.ir_oper_transform(dest),
                    right: self.ir_oper_transform(right),
                    left: self.ir_oper_transform(left),
                },
                IR::Label(_) => op.clone(),
                IR::Jump(_) => op.clone(),
                IR::JZero { left, right, label } => IR::JZero {
                    left: self.ir_oper_transform(left),
                    right: self.ir_oper_transform(right),
                    label: label.to_string(),
                },
                IR::JNotZero { left, right, label } => IR::JNotZero {
                    left: self.ir_oper_transform(left),
                    right: self.ir_oper_transform(right),
                    label: label.to_string(),
                },
                IR::JPositive { left, right, label } => IR::JPositive {
                    left: self.ir_oper_transform(left),
                    right: self.ir_oper_transform(right),
                    label: label.to_string(),
                },
                IR::JNegative { left, right, label } => IR::JNegative {
                    left: self.ir_oper_transform(left),
                    right: self.ir_oper_transform(right),
                    label: label.to_string(),
                },
                IR::JPositiveOrZero { left, right, label } => IR::JPositiveOrZero {
                    left: self.ir_oper_transform(left),
                    right: self.ir_oper_transform(right),
                    label: label.to_string(),
                },
                IR::JNegativeOrZero { left, right, label } => IR::JNegativeOrZero {
                    left: self.ir_oper_transform(left),
                    right: self.ir_oper_transform(right),
                    label: label.to_string(),
                },
                IR::ProcCall {
                    procedure,
                    arguments,
                } => IR::ProcCall {
                    procedure: procedure.to_string(),
                    arguments: arguments
                        .iter()
                        .map(|arg| self.ir_oper_transform(arg))
                        .collect(),
                },
                IR::Return => IR::Return,
                IR::Read(ir_operand) => IR::Read(self.ir_oper_transform(ir_operand)),
                IR::Write(ir_operand) => IR::Write(self.ir_oper_transform(ir_operand)),
                IR::Comment(c) => IR::Comment(c.to_string()),
            })
        }
        v
    }

    fn ir_oper_transform(&self, var: &IrOperand) -> IrOperand {
        match &var {
            IrOperand::Variable(name) => IrOperand::Variable(self.name_transform(name)),
            IrOperand::Constant(_) => var.clone(),
            IrOperand::ArrayConstAccess { base_name, idx } => IrOperand::ArrayConstAccess {
                base_name: self.name_transform(base_name),
                idx: *idx,
            },
            IrOperand::ArrayDynamicAccess {
                base_name,
                idx_name,
            } => IrOperand::ArrayDynamicAccess {
                base_name: self.name_transform(&base_name),
                idx_name: self.name_transform(&idx_name),
            },
        }
    }

    fn name_transform(&self, name: &str) -> String {
        self.translate_map
            .get(name)
            .map_or(format!("{}{}", self.default_prefix, name), |s| s.clone())
    }
}
