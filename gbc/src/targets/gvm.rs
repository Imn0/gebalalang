use assembler::assemble;
use gvm_ext::compile;
use gvme_optimizer::optimize;

use super::{Compile, GvmTarget, IR};
mod assembler;
mod gvm_ext;
mod gvme_optimizer;
mod memory;

impl Compile for GvmTarget {
    fn compile(&self, ir_prog: &crate::code_gen::IrProgram) -> Box<[u8]> {
        let gvme = compile(ir_prog);
        let optimized = optimize(gvme);
        let assembled = assemble(&optimized.code, &optimized.proc_info);

        let mut out = String::new();

        for instruction in &assembled {
            out += &format!("{}\n", instruction);
        }
        out.as_bytes().into()
    }
}
