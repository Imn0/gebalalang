use std::{fmt::{self, write}, usize};

#[derive(Clone, Debug)]

pub enum IR {
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
    JUMP(i64),
    JPOS(i64),
    JZERO(i64),
    JNEG(i64),
    RTRN(usize),
    HALT,
    LABEL { idx: usize, name: String },
    call { name: String },
    lbl_jump(usize),
}

impl fmt::Display for IR {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            IR::LABEL { idx, name } => write!(f, ".L{} #{}", idx, name),
            _ => {
                write!(f, "    ");
                match self {
                    IR::GET(val) => write!(f, "GET {}", val),
                    IR::PUT(val) => write!(f, "PUT {}", val),
                    IR::LOAD(val) => write!(f, "LOAD {}", val),
                    IR::STORE(val) => write!(f, "STORE {}", val),
                    IR::LOADI(val) => write!(f, "LOADI {}", val),
                    IR::STOREI(val) => write!(f, "STOREI {}", val),
                    IR::ADD(val) => write!(f, "ADD {}", val),
                    IR::SUB(val) => write!(f, "SUB {}", val),
                    IR::ADDI(val) => write!(f, "ADDI {}", val),
                    IR::SUBI(val) => write!(f, "SUBI {}", val),
                    IR::SET(val) => write!(f, "SET {}", val),
                    IR::HALF => write!(f, "HALF"),
                    IR::JUMP(val) => write!(f, "JUMP {}", val),
                    IR::JPOS(val) => write!(f, "JPOS {}", val),
                    IR::JZERO(val) => write!(f, "JZERO {}", val),
                    IR::JNEG(val) => write!(f, "JNEG {}", val),
                    IR::RTRN(val) => write!(f, "RTRN {}", val),
                    IR::HALT => write!(f, "HALT"),
                    IR::call { name } => write!(f, "call {}", name),
                    IR::lbl_jump(val) => write!(f, "lbl_jumb .L{}", val),
                    _ => Ok(()),
                }
            }
        }
    }
}
