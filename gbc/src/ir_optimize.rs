use crate::{code_gen::IrProgram, program::Program, try_or_err};

mod constant_folding;

trait Optimizer {
    fn optimize(&self, prog: &mut IrProgram) -> Result<(), ()>;
}

struct ConstatFolding;

impl Program {
    pub fn ir_optimize(&mut self) -> Result<(), ()> {
        let optimization_passes: Vec<Box<dyn Optimizer>> = vec![Box::new(ConstatFolding)];
        for optimization_pass in optimization_passes {
            try_or_err!(optimization_pass.optimize(&mut self.ir_program));
        }

        return Ok(());
    }
}
