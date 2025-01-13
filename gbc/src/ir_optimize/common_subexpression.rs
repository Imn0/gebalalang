use super::{CommonSubexpressionElimination, Optimizer};

impl Optimizer for CommonSubexpressionElimination {
    fn optimize(&self, prog: &mut crate::code_gen::IrProgram) -> Result<(), ()> {
        Ok(())
    }
}
