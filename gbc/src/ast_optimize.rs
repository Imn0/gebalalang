use crate::{ast::Ast, program::Program};

mod normalize;

trait Optimization {
    fn run(&mut self, prog: &mut Program);
}

struct Normalize;

impl Program {
    pub fn ast_optimize(&mut self) -> Result<(), ()> {
        
        let mut passes = vec![Normalize];

        for o in &mut passes {
            o.run(self);
        }

        Ok(())
    }
}
