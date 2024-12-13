use std::fmt;


#[derive(Clone)]
/// Represents the set of assembly-like instructions for a virtual machine.
///
/// ## Memory and Program Counter
/// - Memory `p_i` is indexed by `i = 0, 1, 2, 3, ..., 2^62` and is not initialized.
/// - `p_0` is the accumulator.
/// - `k` is the program counter.
pub enum AbstractASM {
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
}

impl fmt::Display for AbstractASM {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            AbstractASM::GET(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "GET {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "GET {}", val)
                }
            }
            AbstractASM::PUT(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "PUT {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "PUT {}", val)
                }
            }
            AbstractASM::LOAD(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "LOAD {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "LOAD {}", val)
                }
            }
            AbstractASM::STORE(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "STORE {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "STORE {}", val)
                }
            }
            AbstractASM::LOADI(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "LOADI {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "LOADI {}", val)
                }
            }
            AbstractASM::STOREI(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "STOREI {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "STOREI {}", val)
                }
            }
            AbstractASM::ADD(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "ADD {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "ADD {}", val)
                }
            }
            AbstractASM::SUB(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "SUB {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "SUB {}", val)
                }
            }
            AbstractASM::ADDI(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "ADDI {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "ADDI {}", val)
                }
            }
            AbstractASM::SUBI(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "SUBI {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "SUBI {}", val)
                }
            }
            AbstractASM::SET(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "SET {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "SET {}", val)
                }
            }
            AbstractASM::HALF => write!(f, "HALF"),
            AbstractASM::JUMP(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "JUMP {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "JUMP {}", val)
                }
            }
            AbstractASM::JPOS(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "JPOS {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "JPOS {}", val)
                }
            }
            AbstractASM::JZERO(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "JZERO {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "JZERO {}", val)
                }
            }
            AbstractASM::JNEG(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "JNEG {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "JNEG {}", val)
                }
            }
            AbstractASM::RTRN(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "RTRN {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "RTRN {}", val)
                }
            }
            AbstractASM::HALT => write!(f, "HALT"),
        }
    }
}
