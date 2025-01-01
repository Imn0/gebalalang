use no_invalid_accesses::GeneratorValidator;

use crate::{program::Program, try_or_err};

mod no_invalid_accesses;
mod no_recursion;

trait Validator {
    fn check(&self, prog: &Program) -> Result<(), ()>;
}

struct NoRecursiveCalls;
struct NoInvalidAccesses;

impl Validator for NoRecursiveCalls {
    fn check(&self, prog: &Program) -> Result<(), ()> {
        self.detect_recursive_calls(prog)
    }
}

impl Validator for NoInvalidAccesses {
    fn check(&self, prog: &Program) -> Result<(), ()> {
        let mut val = GeneratorValidator::new();
        val.validate(prog)
    }
}

impl Program {
    pub fn ast_validate(&self) -> Result<(), ()> {
        let validators: Vec<Box<dyn Validator>> =
            vec![Box::new(NoRecursiveCalls), Box::new(NoInvalidAccesses)];

        for validator in &validators {
            try_or_err!(validator.check(self));
        }

        Ok(())
    }
}
