use std::fmt;

use crate::{code_builder::code_builder::CodeGenerator, ir::IR};

#[derive(Clone)]
/// Represents the set of assembly-like instructions for a virtual machine.
///
/// ## Memory and Program Counter
/// - Memory `p_i` is indexed by `i = 0, 1, 2, 3, ..., 2^62` and is not initialized.
/// - `p_0` is the accumulator.
/// - `k` is the program counter.
pub enum GvmAsm {
    /// Reads a number from the user and stores it in `p_i`.
    /// - **Effect**: `p_i = user_input`
    /// - **Cost**: 100
    /// - **Program Counter**: `k += 1`
    GET(usize),

    /// Prints the number stored in `p_i`.
    /// - **Effect**: Outputs `p_i`
    /// - **Cost**: 100
    /// - **Program Counter**: `k += 1`
    PUT(usize),

    /// Loads the value from `p_i` into `p_0` (accumulator).
    /// - **Effect**: `p_0 = p_i`
    /// - **Cost**: 10
    /// - **Program Counter**: `k += 1`
    LOAD(usize),

    /// Stores the value from `p_0` (accumulator) into `p_i`.
    /// - **Effect**: `p_i = p_0`
    /// - **Cost**: 10
    /// - **Program Counter**: `k += 1`
    STORE(usize),

    /// Loads the value from the memory address `p_i` into `p_0`.
    /// - **Effect**: `p_0 = p_{p_i}`
    /// - **Cost**: 20
    /// - **Program Counter**: `k += 1`
    LOADI(usize),

    /// Stores the value from `p_0` into the memory address `p_i`.
    /// - **Effect**: `p_{p_i} = p_0`
    /// - **Cost**: 20
    /// - **Program Counter**: `k += 1`
    STOREI(usize),

    /// Adds the value of `p_i` to `p_0`.
    /// - **Effect**: `p_0 += p_i`
    /// - **Cost**: 10
    /// - **Program Counter**: `k += 1`
    ADD(usize),

    /// Subtracts the value of `p_i` from `p_0`.
    /// - **Effect**: `p_0 -= p_i`
    /// - **Cost**: 10
    /// - **Program Counter**: `k += 1`
    SUB(usize),

    /// Adds the value at the address `p_{p_i}` to `p_0`.
    /// - **Effect**: `p_0 += p_{p_i}`
    /// - **Cost**: 20
    /// - **Program Counter**: `k += 1`
    ADDI(usize),

    /// Subtracts the value at the address `p_{p_i}` from `p_0`.
    /// - **Effect**: `p_0 -= p_{p_i}`
    /// - **Cost**: 20
    /// - **Program Counter**: `k += 1`
    SUBI(usize),

    /// Sets `p_0` to a constant value `x`.
    /// - **Effect**: `p_0 = x`
    /// - **Cost**: 50
    /// - **Program Counter**: `k += 1`
    SET(i64),

    /// Halves the value of `p_0` (integer division).
    /// - **Effect**: `p_0 = floor(p_0 / 2)`
    /// - **Cost**: 5
    /// - **Program Counter**: `k += 1`
    HALF,

    /// Jumps to a relative address by adding `j` to the program counter.
    /// - **Effect**: `k += j`
    /// - **Cost**: 1
    JUMP(i64),

    /// Jumps to a relative address `j` if `p_0 > 0`. Otherwise, increments `k` by 1.
    /// - **Effect**: `p_0 > 0 ? k += j : k += 1`
    /// - **Cost**: 1
    JPOS(i64),

    /// Jumps to a relative address `j` if `p_0 == 0`. Otherwise, increments `k` by 1.
    /// - **Effect**: `p_0 == 0 ? k += j : k += 1`
    /// - **Cost**: 1
    JZERO(i64),

    /// Jumps to a relative address `j` if `p_0 < 0`. Otherwise, increments `k` by 1.
    /// - **Effect**: `p_0 < 0 ? k += j : k += 1`
    /// - **Cost**: 1
    JNEG(i64),

    /// Sets the program counter to `p_i`.
    /// - **Effect**: `k = p_i`
    /// - **Cost**: 10
    RTRN(usize),

    /// Halts the program.
    /// - **Effect**: Stops execution.
    /// - **Cost**: 0
    HALT,

    COMMENT {
        msg: String,
    },
}

impl fmt::Display for GvmAsm {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            GvmAsm::GET(val) => write!(f, "GET {}", val),
            GvmAsm::PUT(val) => write!(f, "PUT {}", val),
            GvmAsm::LOAD(val) => write!(f, "LOAD {}", val),
            GvmAsm::STORE(val) => write!(f, "STORE {}", val),
            GvmAsm::LOADI(val) => write!(f, "LOADI {}", val),
            GvmAsm::STOREI(val) => write!(f, "STOREI {}", val),
            GvmAsm::ADD(val) => write!(f, "ADD {}", val),
            GvmAsm::SUB(val) => write!(f, "SUB {}", val),
            GvmAsm::ADDI(val) => write!(f, "ADDI {}", val),
            GvmAsm::SUBI(val) => write!(f, "SUBI {}", val),
            GvmAsm::SET(val) => write!(f, "SET {}", val),
            GvmAsm::HALF => write!(f, "HALF"),
            GvmAsm::JUMP(val) => write!(f, "JUMP {}", val),
            GvmAsm::JPOS(val) => write!(f, "JPOS {}", val),
            GvmAsm::JZERO(val) => write!(f, "JZERO {}", val),
            GvmAsm::JNEG(val) => write!(f, "JNEG {}", val),
            GvmAsm::RTRN(val) => write!(f, "RTRN {}", val),
            GvmAsm::HALT => write!(f, "HALT"),
            GvmAsm::COMMENT { msg } => write!(f, "#{}", msg),
        }
    }
}

impl From<IR> for GvmAsm {
    fn from(ir: IR) -> Self {
        match ir {
            IR::GET(i) => GvmAsm::GET(i),
            IR::PUT(i) => GvmAsm::PUT(i),
            IR::LOAD(i) => GvmAsm::LOAD(i),
            IR::STORE(i) => GvmAsm::STORE(i),
            IR::LOADI(i) => GvmAsm::LOADI(i),
            IR::STOREI(i) => GvmAsm::STOREI(i),
            IR::ADD(i) => GvmAsm::ADD(i),
            IR::SUB(i) => GvmAsm::SUB(i),
            IR::ADDI(i) => GvmAsm::ADDI(i),
            IR::SUBI(i) => GvmAsm::SUBI(i),
            IR::SET(x) => GvmAsm::SET(x),
            IR::HALF => GvmAsm::HALF,
            IR::JUMP(j) => GvmAsm::JUMP(j),
            IR::JPOS(j) => GvmAsm::JPOS(j),
            IR::JZERO(j) => GvmAsm::JZERO(j),
            IR::JNEG(j) => GvmAsm::JNEG(j),
            IR::RTRN(i) => GvmAsm::RTRN(i),
            IR::HALT => GvmAsm::HALT,

            IR::lbl_jump(i) => {
                panic!("Cannot convert IR::LBLJ (idx: {} to GvmAsm", i)
            }
            IR::LABEL { idx, name } => {
                panic!(
                    "Cannot convert IR::LABEL (idx: {}, name: {}) to GvmAsm",
                    idx, name
                )
            }
            IR::call { name } => {
                panic!("Cannot convert IR::CALL (name: {}) to GvmAsm", name)
            }
        }
    }
}

pub trait GvmTarget {
    fn to_gvm(&self) -> Vec<GvmAsm>;
}

trait IrGvmImpl {
    fn get_true_len_between(&self, start: usize, stop: usize) -> usize;
    fn get_true_len(&self, to: usize) -> usize;
    fn distance_to_label(&self, from: usize, label_idx: usize) -> i64;
}

impl GvmTarget for CodeGenerator {
    fn to_gvm(&self) -> Vec<GvmAsm> {
        let mut asm_code: Vec<GvmAsm> = vec![];

        // exapnd procedure calls
        for (i, ir) in self.assembly_code.iter().enumerate() {
            match ir {
                IR::call { name } => {
                    let proc_info = self.get_proc_info_for_name(name);

                    let jump_dist = self.distance_to_label(i, proc_info.label);

                    let return_place = self.get_true_len(i) + 3;
                    asm_code.push(GvmAsm::SET(return_place as i64));
                    asm_code.push(GvmAsm::STORE(proc_info.return_address));
                    asm_code.push(GvmAsm::JUMP(jump_dist - 2));
                }
                IR::LABEL { idx, name } => {
                    asm_code.push(GvmAsm::COMMENT {
                        msg: format!(".L{}", idx),
                    });
                }
                               IR::lbl_jump(idx) => {
                    let jump_dist = self.distance_to_label(i, idx.clone());
                    asm_code.push(GvmAsm::JUMP(jump_dist));
                    asm_code.push(GvmAsm::COMMENT {
                        msg: format!("jump .L{}", idx),
                    });
                }
                _ => {
                    asm_code.push(GvmAsm::from(ir.clone()));
                }
            }
        }

        

        return asm_code;
    }
}

impl IrGvmImpl for CodeGenerator {
    fn distance_to_label(&self, from: usize, label_code: usize) -> i64 {
        let start = from;
        let mut end = 0;
        let mut initialized = false;
        for (i, ir) in self.assembly_code.iter().enumerate() {
            match ir {
                IR::LABEL { idx, name: _ } => {
                    if idx.clone() == label_code {
                        end = i;
                        initialized = true;
                        break;
                    }
                }
                _ => {}
            }
        }
        if !initialized {
            unreachable!("THERE IS NO LABEL {}", label_code);
        }

        if start < end {
            return (self.get_true_len_between(start, end) as i64);
        }

        if start > end {
            return -(self.get_true_len_between(end, start) as i64);
        }

        unreachable!("CANNOT CALCULATE DISTANCE TO ITSELF")
    }

    fn get_true_len(&self, to: usize) -> usize {
        let mut len = 0;
        for i in 0..to {
            match self.assembly_code.get(i).unwrap() {
                IR::call { name: _ } => {
                    len += 3;
                }
                IR::LABEL { idx: _, name: _ } => {}
                _ => {
                    len += 1;
                }
            }
        }
        return len;
    }

    fn get_true_len_between(&self, start: usize, stop: usize) -> usize {
        let mut len = 0;
        for i in start..stop {
            match self.assembly_code.get(i).unwrap() {
                IR::call { name: _ } => {
                    len += 3;
                }
                IR::LABEL { idx: _, name: _ } => {}
                _ => {
                    len += 1;
                }
            }
        }
        return len;
    }
}
