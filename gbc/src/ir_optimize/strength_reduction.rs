use super::{Optimizer, StrengthReduction};

impl Optimizer for StrengthReduction {
    fn optimize(&self, prog: &mut crate::code_gen::IrProgram) -> Result<(), ()> {
        Ok(())
    }
}
