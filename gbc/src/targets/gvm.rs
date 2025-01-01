use super::{Compile, GvmTarget};

impl Compile for GvmTarget {
    fn compile(&self, ir_prog: &crate::code_gen::IrProgram) -> Box<[u8]> {
        let mut out = String::new();

        out.as_bytes().into()
    }
}
