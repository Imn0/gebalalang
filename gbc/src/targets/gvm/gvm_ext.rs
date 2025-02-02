use std::fmt;

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
