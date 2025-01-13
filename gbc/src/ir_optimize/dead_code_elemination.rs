use std::collections::{HashMap, HashSet};

use crate::code_gen::{
    ir::{IrOperand, IR},
    IrProgram,
};

use super::{DeadCodeElimination, Optimizer};

impl Optimizer for DeadCodeElimination {
    fn optimize(&self, prog: &mut IrProgram) -> Result<(), ()> {
        Ok(())
    }
}
