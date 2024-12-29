use crate::{program::Program, try_or_err};

mod no_recursion;

trait Validator {
    fn check(&self) -> Result<(), ()>;
}

struct NoRecursiveCalls<'a> {
    program: &'a Program,
}

impl Program {
    pub fn ast_validate(&mut self) -> Result<(), ()> {
        let validators = [NoRecursiveCalls { program: &self }];

        for validator in validators {
            try_or_err!(validator.check());
        }

        Ok(())
    }
}
