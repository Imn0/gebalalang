use std::collections::HashMap;

use crate::program::Program;

pub mod ir;
use ir::IR;
mod ir_generator;
mod ir_tac_ify;

#[derive(Debug, Clone)]
pub struct ArgInfo {
    pub name: String,
    pub is_array: bool,
    pub is_in_only: bool,
}

#[derive(Debug, Clone)]
pub struct ProcedureInfo {
    pub name: String,
    pub lbl: String,
    pub args: Vec<ArgInfo>,
    pub cmds: Vec<IR>,
}

#[derive(Default)]
pub struct IrProgram {
    pub main: Vec<IR>,
    pub procedures: HashMap<String, ProcedureInfo>,
    pub next_label: usize,
    current_scope: String,
}

impl Program {
    pub fn ir_gen(&mut self) -> Result<(), ()> {
        let mut a = IrProgram::default();
        a.generate_program(&self.ast);
        self.ir_program = a;
        // self.ir_program = a.tac_ify();

        Ok(())
    }
}
