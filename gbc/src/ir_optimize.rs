use crate::{code_gen::IrProgram, program::Program, try_or_err};

trait Optimizer {
    fn optimize(&self, prog: &mut IrProgram) -> Result<(), ()>;
}

struct RemoveTailingOperations;
struct RemoveUnusedProcedures;

impl Program {
    pub fn ir_optimize(&mut self) -> Result<(), ()> {
        let optimization_passes: Vec<Box<dyn Optimizer>> = vec![
            Box::new(RemoveTailingOperations),
            Box::new(RemoveUnusedProcedures),
        ];

        for optimization_pass in optimization_passes {
            try_or_err!(optimization_pass.optimize(&mut self.ir_program));
        }

        return Ok(());
    }
}

impl Optimizer for RemoveUnusedProcedures {
    fn optimize(&self, prog: &mut IrProgram) -> Result<(), ()> {
        Ok(())
    }
}

impl Optimizer for RemoveTailingOperations {
    fn optimize(&self, prog: &mut IrProgram) -> Result<(), ()> {
        let p = &mut prog.main;
        while let Some(last) = p.last() {
            match last {
                crate::code_gen::ir::IR::Label(_)
                | crate::code_gen::ir::IR::Jump(_)
                | crate::code_gen::ir::IR::JZero { .. }
                | crate::code_gen::ir::IR::JNotZero { .. }
                | crate::code_gen::ir::IR::JPositive { .. }
                | crate::code_gen::ir::IR::JNegative { .. }
                | crate::code_gen::ir::IR::JPositiveOrZero { .. }
                | crate::code_gen::ir::IR::JNegativeOrZero { .. }
                | crate::code_gen::ir::IR::Call { .. }
                | crate::code_gen::ir::IR::Read(_)
                | crate::code_gen::ir::IR::Write(_) => {
                    break;
                }
                _ => {}
            }
            p.pop();
        }
        Ok(())
    }
}
