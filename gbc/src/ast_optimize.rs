use crate::program::Program;

mod constant_folding;
mod normalize;

trait Optimization {
    fn run(&mut self, prog: &mut Program);
}

struct Normalize;
struct ConstantFolding;

impl Program {
    pub fn ast_optimize(&mut self) -> Result<(), ()> {
        let mut passes: Vec<Box<dyn Optimization>> =
            vec![Box::new(Normalize), Box::new(ConstantFolding)];

        for o in &mut passes {
            o.run(self);
        }

        Ok(())
    }
}
