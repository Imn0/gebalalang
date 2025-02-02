use assembler::assemble;
use compiler::compile;
use gvme_optimizer::optimize;

use crate::{
    message::{DisplayMessage, Message, MessageSeverity},
    program::Program,
};

use super::{Compile, GvmTarget};
mod assembler;
mod builtins;
mod compiler;
mod gvme_optimizer;
mod memory;
mod gvm_ext;

impl Compile for GvmTarget {
    fn compile(&self, prog: &Program) -> Result<Box<[u8]>, ()> {
        let ir_prog = &prog.ir_program;
        let gvme_r = compile(ir_prog, false);
        let gvme = match gvme_r {
            Ok(p) => p,
            Err(_) => {
                let a = compile(ir_prog, true);
                match a {
                    Ok(p) => p,
                    Err(e) => {
                        prog.print_message(Message::GeneralMessage {
                            severity: MessageSeverity::ERROR,
                            message: &e,
                        });
                        return Err(());
                    }
                }
            }
        };

        // let optimized = gvme;
        let optimized = optimize(gvme);
        let assembled = assemble(&optimized.code, &optimized.proc_info, &optimized.memory);

        let mut out = String::new();

        for instruction in &assembled {
            out += &format!("{}\n", instruction);
        }
        Ok(out.as_bytes().into())
    }
}
