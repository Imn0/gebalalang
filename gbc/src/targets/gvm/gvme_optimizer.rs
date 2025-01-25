use crate::targets::GvmTarget;

use super::gvm_ext::{GVMe, GVMeProgram};

pub fn optimize(gvme_prog: GVMeProgram) -> GVMeProgram {
    let mut prog = vec![];
    let mut last_stored: Option<usize> = None;
    let mut last_stored_i: Option<usize> = None;

    for ins in gvme_prog.code {
        match ins {
            GVMe::LOAD(addr) => {
                if let Some(loc) = last_stored {
                    if addr == loc {
                        continue;
                    }
                }
            }
            GVMe::LOADI(addr) => {
                if let Some(loc) = last_stored_i {
                    if addr == loc {
                        continue;
                    }
                }
            }
            GVMe::STORE(addr) => {
                last_stored = Some(addr);
                last_stored_i = None;
            }
            GVMe::STOREI(addr) => {
                last_stored = None;
                last_stored_i = Some(addr);
            }
            _ => {
                last_stored = None;
                last_stored_i = None;
            }
        }
        prog.push(ins);
    }

    let mut v = vec![];
    prog.reverse();

    last_stored = None;
    last_stored_i = None;

    for ins in prog {
        match ins {
            GVMe::STORE(addr) => {
                if let Some(loc) = last_stored {
                    if addr == loc {
                        continue;
                    }
                }
                last_stored = Some(addr);
                last_stored_i = None;
            }
            GVMe::STOREI(addr) => {
                if let Some(loc) = last_stored_i {
                    if addr == loc {
                        continue;
                    }
                }
                last_stored = None;
                last_stored_i = Some(addr);
            }
            GVMe::call { .. }
            | GVMe::lbl_jump(..)
            | GVMe::jneg(..)
            | GVMe::jpos(..)
            | GVMe::jz(..)
            | GVMe::jnz(..)
            | GVMe::RTRN(_)
            | GVMe::PUT(_)
            | GVMe::jposz(..)
            | GVMe::jnegz(..) => {
                last_stored = None;
                last_stored_i = None;
            }
            GVMe::GET(_) => {}
            GVMe::LOAD(_) => {}
            GVMe::LOADI(_) => {}
            GVMe::ADD(_) => {}
            GVMe::SUB(_) => {}
            GVMe::ADDI(_) => {}
            GVMe::SUBI(_) => {}
            GVMe::SET(_) => {
                last_stored = Some(0);
                last_stored_i = None;
            }
            GVMe::HALF => {}
            GVMe::HALT => {}
            GVMe::comment { .. } => {}
            GVMe::lbl { .. } => {}
        }

        v.push(ins);
    }

    v.reverse();
    GVMeProgram {
        code: v,
        proc_info: gvme_prog.proc_info,
    }
}
