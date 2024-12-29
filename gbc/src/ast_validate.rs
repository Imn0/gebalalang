use crate::{program::Program, try_or_err};

mod no_recursion;

trait Validator {
    fn check(&self, prog: &Program) -> Result<(), ()>;
}

struct NoRecursiveCalls;

impl Program {
    pub fn ast_validate(&self) -> Result<(), ()> {
        let validators = [NoRecursiveCalls];

        for validator in &validators {
            try_or_err!(validator.check(self));
        }

        Ok(())
    }
}
