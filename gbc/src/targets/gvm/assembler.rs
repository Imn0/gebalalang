use super::gvm_ext::{GVMe, GVMeProc};
use std::{collections::HashMap, fmt};

#[derive(Clone)]
/// Represents the set of assembly-like instructions for a virtual machine.
///
/// ## Memory and Program Counter
/// - Memory `p_i` is indexed by `i = 0, 1, 2, 3, ..., 2^62` and is not initialized.
/// - `p_0` is the accumulator.
/// - `k` is the program counter.
pub enum GVM {
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

impl fmt::Display for GVM {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            GVM::GET(val) => write!(f, "GET {}", val),
            GVM::PUT(val) => write!(f, "PUT {}", val),
            GVM::LOAD(val) => write!(f, "LOAD {}", val),
            GVM::STORE(val) => write!(f, "STORE {}", val),
            GVM::LOADI(val) => write!(f, "LOADI {}", val),
            GVM::STOREI(val) => write!(f, "STOREI {}", val),
            GVM::ADD(val) => write!(f, "ADD {}", val),
            GVM::SUB(val) => write!(f, "SUB {}", val),
            GVM::ADDI(val) => write!(f, "ADDI {}", val),
            GVM::SUBI(val) => write!(f, "SUBI {}", val),
            GVM::SET(val) => write!(f, "SET {}", val),
            GVM::HALF => write!(f, "HALF"),
            GVM::JUMP(val) => write!(f, "JUMP {}", val),
            GVM::JPOS(val) => write!(f, "JPOS {}", val),
            GVM::JZERO(val) => write!(f, "JZERO {}", val),
            GVM::JNEG(val) => write!(f, "JNEG {}", val),
            GVM::RTRN(val) => write!(f, "RTRN {}", val),
            GVM::HALT => write!(f, "HALT"),
            GVM::COMMENT { msg } => write!(f, "#{}", msg),
        }
    }
}

impl From<GVMe> for GVM {
    fn from(ir: GVMe) -> Self {
        match ir {
            GVMe::GET(i) => GVM::GET(i),
            GVMe::PUT(i) => GVM::PUT(i),
            GVMe::LOAD(i) => GVM::LOAD(i),
            GVMe::STORE(i) => GVM::STORE(i),
            GVMe::LOADI(i) => GVM::LOADI(i),
            GVMe::STOREI(i) => GVM::STOREI(i),
            GVMe::ADD(i) => GVM::ADD(i),
            GVMe::SUB(i) => GVM::SUB(i),
            GVMe::ADDI(i) => GVM::ADDI(i),
            GVMe::SUBI(i) => GVM::SUBI(i),
            GVMe::SET(x) => GVM::SET(x),
            GVMe::HALF => GVM::HALF,
            GVMe::RTRN(i) => GVM::RTRN(i),
            GVMe::HALT => GVM::HALT,

            GVMe::lbl_jump(i) => {
                panic!("Cannot convert IR::LBLJ (idx: {:?} to GVM", i)
            }
            GVMe::lbl { idx, name } => {
                panic!(
                    "Cannot convert IR::LABEL (idx: {:?}, name: {}) to GVM",
                    idx, name
                )
            }
            GVMe::call { name } => {
                panic!("Cannot convert IR::CALL (name: {}) to GVM", name)
            }
            GVMe::comment { cm } => GVM::COMMENT { msg: cm },
            _ => {
                panic!("Cannot convert IR {} to GVM", ir);
            }
        }
    }
}

pub fn assemble(gvme: &Vec<GVMe>, procs: &HashMap<String, GVMeProc>) -> Vec<GVM> {
    let mut asm_code: Vec<GVM> = vec![];

    // exapnd procedure calls
    for (i, ir) in gvme.iter().enumerate() {
        match ir {
            GVMe::call { name } => {
                let proc_info = procs.get(name).unwrap().to_owned();

                let jump_dist = distance_to_label(gvme, i, proc_info.label.0);

                let return_place = get_true_len_between(gvme, 0, i) + 3;
                asm_code.push(GVM::SET(return_place as i64));
                asm_code.push(GVM::STORE(proc_info.return_address));
                asm_code.push(GVM::JUMP(jump_dist - 2));
            }
            GVMe::lbl { idx, name } => {
                asm_code.push(GVM::COMMENT {
                    msg: format!(".L{} #{}", idx.0, name),
                });
            }
            GVMe::lbl_jump(idx) => {
                let jump_dist = distance_to_label(gvme, i, idx.clone().0);
                asm_code.push(GVM::JUMP(jump_dist));
            }
            GVMe::jz(idx) => {
                let jump_dist = distance_to_label(gvme, i, idx.clone().0);
                asm_code.push(GVM::JZERO(jump_dist));
            }
            GVMe::jnz(idx) => {
                let jump_dist = distance_to_label(gvme, i, idx.clone().0);

                asm_code.push(GVM::JZERO(2));
                if jump_dist < 0 {
                    asm_code.push(GVM::JUMP(jump_dist - 1));
                } else if jump_dist > 0 {
                    asm_code.push(GVM::JUMP(jump_dist - 1));
                }
            }
            GVMe::jpos(idx) => {
                let jump_dist = distance_to_label(gvme, i, idx.clone().0);
                asm_code.push(GVM::JPOS(jump_dist));
            }
            GVMe::jneg(idx) => {
                let jump_dist = distance_to_label(gvme, i, idx.clone().0);
                asm_code.push(GVM::JNEG(jump_dist));
            }
            GVMe::jposz(idx) => {
                let jump_dist = distance_to_label(gvme, i, idx.clone().0);

                asm_code.push(GVM::JPOS(2));
                if jump_dist < 0 {
                    asm_code.push(GVM::JUMP(jump_dist - 1));
                } else if jump_dist > 0 {
                    asm_code.push(GVM::JUMP(jump_dist - 1));
                }
            }
            GVMe::jnegz(idx) => {
                let jump_dist = distance_to_label(gvme, i, idx.clone().0);

                asm_code.push(GVM::JNEG(2));
                if jump_dist < 0 {
                    asm_code.push(GVM::JUMP(jump_dist - 1));
                } else if jump_dist > 0 {
                    asm_code.push(GVM::JUMP(jump_dist - 1));
                }
            }

            _ => {
                asm_code.push(GVM::from(ir.clone()));
            }
        }
    }

    return asm_code;
}

fn distance_to_label(code: &Vec<GVMe>, from: usize, label_code: usize) -> i64 {
    let start = from;
    let mut end = 0;
    let mut initialized = false;
    for (i, ir) in code.iter().enumerate() {
        match ir {
            GVMe::lbl { idx, name: _ } => {
                if idx.clone().0 == label_code {
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
        return get_true_len_between(code, start, end) as i64;
    }

    if start > end {
        return -(get_true_len_between(code, end, start) as i64);
    }

    unreachable!("CANNOT CALCULATE DISTANCE TO ITSELF")
}

fn get_true_len_between(code: &Vec<GVMe>, start: usize, stop: usize) -> usize {
    let mut len = 0;
    for i in start..stop {
        match code.get(i).unwrap() {
            GVMe::call { name: _ } => {
                len += 3;
            }
            GVMe::lbl { idx: _, name: _ } => {}
            GVMe::comment { cm: _ } => {}
            GVMe::jz(_) => {
                len += 1;
            }
            GVMe::jnz(_) => {
                len += 2;
            }
            GVMe::jpos(_) => {
                len += 1;
            }
            GVMe::jneg(_) => {
                len += 1;
            }
            GVMe::jposz(_) => {
                len += 2;
            }
            GVMe::jnegz(_) => {
                len += 2;
            }
            _ => {
                len += 1;
            }
        }
    }
    return len;
}
