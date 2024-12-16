use std::{collections::HashMap, fs::File};

use clap::builder::Str;
use serde::Serialize;
use tree_sitter::Point;

use crate::{
    ir::IR, main, Ast, Command, Condition, Declaration, Either, ErrorDetails, Expression,
    ForDirection, Identifier, MainBlock, MessageSeverity, Procedure, Value,
};

use super::memory::{Memory, SymbolLocation};

#[derive(Clone)]
pub struct ProcedureInfo {
    pub label: usize,
    pub return_address: usize,
    pub args: Vec<SymbolLocation>,
}

pub struct CodeGenerator {
    pub messages: Vec<ErrorDetails>,
    pub assembly_code: Vec<IR>,
    memory: Memory,
    procedures: HashMap<String, ProcedureInfo>,
    next_label: usize,
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
            next_label: 0,
        }
    }

    pub fn generate_asm(&mut self, ast: Ast) {
        if ast.procedures.len() > 0 {
            let main_lbl = self.next_label;
            self.next_label += 1;
            self.push_asm(IR::lbl_jump(main_lbl));
            for proc in &ast.procedures {
                self.compile_procedure(proc);
            }
            self.push_asm(IR::LABEL {
                idx: main_lbl,
                name: format!("MAIN"),
            });
        }

        self.compile_main(&ast.main_block);
        self.push_asm(IR::HALT);

        println!("{:#?}", self.memory)
    }

    fn compile_main(&mut self, main: &MainBlock) {
        self.current_scope = "MAIN".to_string();
        self.allocate_declarations(&main.declarations);
        self.compile_commands(&main.commands);
    }

    fn compile_procedure(&mut self, procedure: &Procedure) {
        //TODO check if proc is not being redefined

        self.current_scope = format!("{}", procedure.name);
        let proc_lbl = self.push_label_name(&procedure.name);
        let ret_addr = self.memory.allocate_procedure_return(&procedure.name);
        let mut proc_info = ProcedureInfo {
            return_address: ret_addr,
            label: proc_lbl,
            args: vec![],
        };
        for arg in &procedure.args {
            proc_info
                .args
                .push(self.memory.allocate_procedure_arg(arg, &self.current_scope));
        }
        self.allocate_declarations(&procedure.declarations);
        self.compile_commands(&procedure.commands);
        self.push_asm(IR::RTRN(ret_addr));

        self.procedures.insert(procedure.name.clone(), proc_info);
    }

    fn add_message(&mut self, msg: ErrorDetails) {
        self.messages.push(msg);
    }

    fn push_asm(&mut self, ins: IR) {
        self.assembly_code.push(ins);
    }

    fn push_label(&mut self) -> usize {
        let lbl = self.next_label;
        self.push_asm(IR::LABEL {
            idx: lbl,
            name: "".to_owned(),
        });
        self.next_label += 1;
        return lbl;
    }

    fn push_label_name(&mut self, name: &String) -> usize {
        let lbl = self.next_label;
        self.push_asm(IR::LABEL {
            idx: lbl,
            name: name.clone(),
        });
        self.next_label += 1;
        return lbl;
    }

    fn allocate_declarations(&mut self, declarations: &Vec<Declaration>) {
        for dec in declarations {
            let r = self.memory.allocate_declaration(dec, &self.current_scope);

            if let Err(error) = r {
                self.add_message(error);
            }
        }
    }

    fn compile_commands(&mut self, commands: &Vec<Command>) {
        for cmd in commands {
            self.compile_command(cmd);
        }
    }

    fn compile_command(&mut self, command: &Command) {
        match command {
            Command::Read(ident) => {
                let sym_loc = self.generate_ident(ident);

                if sym_loc.is_pointer {
                    self.push_asm(IR::GET(0));
                    self.push_asm(IR::STOREI(sym_loc.memory_address));
                } else {
                    self.push_asm(IR::GET(sym_loc.memory_address));
                }
            }
            Command::Write(value) => {
                let sym_loc = self.generate_value(value);

                if sym_loc.is_pointer {
                    self.push_asm(IR::LOADI(sym_loc.memory_address));
                    self.push_asm(IR::PUT(0));
                } else {
                    self.push_asm(IR::PUT(sym_loc.memory_address));
                }
            }
            Command::ProcedureCall {
                proc_name,
                arguments,
                location,
            } => {
                // TODO add validation to a separate function
                let maybe_proc_info = self.procedures.get(proc_name).cloned();
                match maybe_proc_info {
                    None => {
                        self.add_message(ErrorDetails {
                            message: format!("procedure {} not defined", proc_name),
                            location: *location,
                            severity: MessageSeverity::ERROR,
                        });
                        return;
                    }
                    Some(proc_info) => {
                        if proc_info.args.len() != arguments.len() {
                            self.messages.push(ErrorDetails {
                                message: format!(
                                    "procedure {} expected {} arguments, got {}",
                                    proc_name,
                                    proc_info.args.len(),
                                    arguments.len()
                                ),
                                location: *location,
                                severity: MessageSeverity::ERROR,
                            });
                            return;
                        }
                        for (i, arg) in arguments.iter().enumerate() {
                            let arg_mem_loc = self
                                .memory
                                .get_ident_base_location(&arg, &self.current_scope)
                                .unwrap();

                            let target_mem_loc = proc_info.args.get(i).unwrap();

                            // TODO CHECK IF ARRAY IS ARRAY etc.

                            if arg_mem_loc.is_pointer {
                                self.push_asm(IR::LOAD(arg_mem_loc.memory_address));
                                self.push_asm(IR::STORE(target_mem_loc.memory_address));
                            } else {
                                let _l = 
                                self.push_asm(IR::SET(arg_mem_loc.memory_address as i64));
                                self.push_asm(IR::LOAD(0));
                                self.push_asm(IR::STORE(target_mem_loc.memory_address));
                            }
                        }

                        self.push_asm(IR::call {
                            name: proc_name.clone(),
                        });
                    }
                }
            }
            _ => unimplemented!(),
        }
    }

    fn generate_ident(&mut self, ident: &Identifier) -> SymbolLocation {
        //TODO validate access //
        match &ident.index {
            None => {
                let r = self
                    .memory
                    .get_ident_base_location(ident, &self.current_scope);

                match r {
                    Ok(loc) => return loc,
                    Err(err) => {
                        self.add_message(err);
                        return SymbolLocation::new();
                    }
                }
            }
            Some(idx) => match idx {
                Either::Left(idx_name) => unimplemented!(),
                Either::Right(idx_val) => {
                    let array_base_loc = self
                        .memory
                        .get_ident_base_location_no_error(ident, &self.current_scope);

                    if array_base_loc.is_pointer {
                        unimplemented!();
                    }

                    return SymbolLocation {
                        memory_address: (array_base_loc.memory_address as i64 + idx_val) as usize,
                        is_array: false,
                        array_bounds: None,
                        is_pointer: false,
                        read_only: false,
                        initialized: false,
                    };
                }
            },
        }
    }

    fn generate_value(&mut self, val: &Value) -> SymbolLocation {
        match val {
            Value::Number(num) => {
                return  self.ensure_constant(num.clone());
            }
            Value::Identifier(ident) => {
                return self.generate_ident(ident);
            }
        }
    }

    pub fn ensure_constant(&mut self, constant: i64) -> SymbolLocation {
        if let Some(loc) = self.memory.get_constant(constant.clone()) {
            return loc;
        } else {
            let mem_loc = self.memory.allocate_constant(constant.clone());
            self.push_asm(IR::SET(constant.clone()));
            self.push_asm(IR::STORE(mem_loc));

            return SymbolLocation {
                memory_address: mem_loc,
                is_array: false,
                array_bounds: None,
                is_pointer: false,
                read_only: true,
                initialized: true,
            };
        }
    }

    pub fn get_proc_info_for_name(&self, proc_name: &String) -> ProcedureInfo {
        self.procedures.get(proc_name).unwrap().clone()
    }
}
