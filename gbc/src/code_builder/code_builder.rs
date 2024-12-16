use std::{collections::HashMap, fs::File, io::Write};

use serde::Serialize;

use crate::{
    asm::AbstractASM, Ast, Command, Condition, Either, ErrorDetails, Expression, ForDirection,
    Identifier, MessageSeverity, Procedure, Value,
};

use super::memory::Memory;



#[derive(Clone)]
struct ProcedureInfo {
    code_location: usize,
    args: Vec<bool>,
}

pub struct CodeGenerator {
    pub messages: Vec<ErrorDetails>,
    pub assembly_code: Vec<AbstractASM>,
    memory: Memory,
    procedures: HashMap<String, ProcedureInfo>,
    last_mem_slot: usize,
    current_scope: String,
}

impl CodeGenerator {
    pub fn new() -> Self {
        CodeGenerator {
            memory: Memory::new(),
            procedures: HashMap::new(),
            last_mem_slot: 0x4000000000000000,
            assembly_code: Vec::new(),
            messages: Vec::new(),
            current_scope: "".to_owned(),
        }
    }

    pub fn generate_asm(&mut self, ast: Ast) {
        
    }

    fn push_asm(&mut self, ins: AbstractASM) {
        self.assembly_code.push(ins);
    }


    
}
