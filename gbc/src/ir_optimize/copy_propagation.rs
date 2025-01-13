use super::{CopyPropagation, Optimizer};

impl Optimizer for CopyPropagation {
    fn optimize(&self, prog: &mut crate::code_gen::IrProgram) -> Result<(), ()> {
        Ok(())
    }
}
