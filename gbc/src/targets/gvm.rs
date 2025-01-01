use assembler::assemble;
use gvm_ext::compile;

use super::{Compile, GvmTarget};

mod assembler;
mod gvm_ext;
mod memory;

impl Compile for GvmTarget {
    fn compile(&self, ir_prog: &crate::code_gen::IrProgram) -> Box<[u8]> {
        let gvme = compile(ir_prog);
        let assembled = assemble(&gvme.code, &gvme.proc_info);

        let mut out = String::new();

        for instruction in &assembled {
            out += &format!("{}\n", instruction);
        }
        out.as_bytes().into()
    }
}
