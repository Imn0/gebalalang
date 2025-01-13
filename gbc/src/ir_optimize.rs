use crate::{code_gen::IrProgram, program::Program, try_or_err};

mod common_subexpression;
mod constant_folding;
mod copy_propagation;
mod dead_code_elemination;
mod strength_reduction;

trait Optimizer {
    fn optimize(&self, prog: &mut IrProgram) -> Result<(), ()>;
}

struct ConstatFolding;
struct DeadCodeElimination;
struct StrengthReduction;
struct CopyPropagation;
struct CommonSubexpressionElimination;

impl Program {
    pub fn ir_optimize(&mut self) -> Result<(), ()> {
        let optimization_passes: Vec<Box<dyn Optimizer>> = vec![
            Box::new(ConstatFolding),
            Box::new(DeadCodeElimination),
            Box::new(StrengthReduction),
            Box::new(CopyPropagation),
            Box::new(CommonSubexpressionElimination),
        ];

        for optimization_pass in optimization_passes {
            try_or_err!(optimization_pass.optimize(&mut self.ir_program));
        }

        return Ok(());
    }
}
