use std::collections::HashMap;

use crate::program::Program;

pub mod ir;
use ir::IR;
mod ir_generator;

pub struct ArgInfo {
    pub name: String,
    pub is_array: bool,
}

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
    pub fn gen_ir(&mut self) -> Result<(), ()> {
        self.ir_program.generate_program(&self.ast);
        Ok(())
    }
}
