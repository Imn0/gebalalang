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
                if addr == 0 {
                    continue;
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

    GVMeProgram {
        code: prog,
        proc_info: gvme_prog.proc_info,
        memory: gvme_prog.memory,
    }
}
