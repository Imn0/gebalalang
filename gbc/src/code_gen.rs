use std::collections::HashMap;

use ir::IR;
use memory::{Memory, SymbolLocation};

use crate::program::Program;

mod code_gen;
pub mod ir;
mod memory;

const MIN_CONST_USAGE: i64 = 1;

#[derive(Clone)]
pub struct ProcedureInfo {
    pub label: usize,
    pub return_address: usize,
    pub args: Vec<SymbolLocation>,
}

#[derive(Debug)]
struct ConstInfo {
    pub num_used: i64,
    pub val: i64,
    pub location: usize,
}

pub struct CodeGenerator {
    pub assembly_code: Vec<IR>,
    memory: Memory,
    constants: HashMap<i64, ConstInfo>,
    procedures: HashMap<String, ProcedureInfo>,
    next_label: usize,
    last_mem_slot: usize,
    current_scope: String,
}

impl Program {
    pub fn gen_ir(&mut self) -> Result<(), ()> {
        self.code_gen.generate_asm(&self.ast);
        Ok(())
    }
}
