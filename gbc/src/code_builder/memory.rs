use std::{collections::HashMap, panic::Location};

use clap::builder::Str;
use serde::Serialize;
use tree_sitter::Point;

use crate::{ast::ast::{Declaration, Identifier, ProcArgument}, ErrorDetails};


#[derive(Debug, Clone, Serialize)]
pub struct SymbolLocation {
    pub memory_address: usize,
    pub is_array: bool,
    pub array_bounds: Option<(i64, i64)>,
    pub is_pointer: bool,
    pub read_only: bool,
    pub initialized: bool,
}

impl SymbolLocation {
    pub fn new() -> Self {
        SymbolLocation {
            memory_address: 0,
            is_array: false,
            array_bounds: None,
            is_pointer: false,
            read_only: false,
            initialized: false,
        }
    }
}
#[derive(Debug)]
pub struct Memory {
    symbols: HashMap<String, SymbolLocation>,
    next_memory_slot: usize,
}

impl Memory {
    pub fn new() -> Self {
        Memory {
            symbols: HashMap::new(),
            next_memory_slot: 1,
        }
    }

    pub fn allocate_declaration(
        &mut self,
        dec: &Declaration,
        scope: &String,
    ) -> Result<usize, ErrorDetails> {
        let scoped_name = get_scoped_name(&dec.name, scope);

        if self.symbols.contains_key(&scoped_name) {
            return Err(ErrorDetails {
                message: format!("Variable {} already defined.", dec.name),
                location: dec.location,
                severity: crate::MessageSeverity::ERROR,
            });
        }

        if let Some((left, right)) = dec.array_size {
            let bounds = (left, right);
            if left >= 0 && right >= 0 {
                self.symbols.insert(
                    scoped_name,
                    SymbolLocation {
                        memory_address: self.next_memory_slot,
                        is_array: true,
                        array_bounds: Some(bounds),
                        is_pointer: false,
                        read_only: false,
                        initialized: false,
                    },
                );
                let ret = self.next_memory_slot;
                self.next_memory_slot += usize::try_from(right).unwrap() + 1;
                return Ok(ret);
            }
            if left < 0 && right >= 0 {
                self.next_memory_slot += usize::try_from(-left).unwrap();
                self.symbols.insert(
                    scoped_name,
                    SymbolLocation {
                        memory_address: self.next_memory_slot,
                        is_array: true,
                        array_bounds: Some(bounds),
                        is_pointer: false,
                        read_only: false,
                        initialized: false,
                    },
                );
                let ret = self.next_memory_slot;
                self.next_memory_slot += usize::try_from(right).unwrap() + 1;
                return Ok(ret);
            }
            if left < 0 && right < 0 {
                self.next_memory_slot += usize::try_from(-left).unwrap();
                self.symbols.insert(
                    scoped_name,
                    SymbolLocation {
                        memory_address: self.next_memory_slot,
                        is_array: true,
                        array_bounds: Some(bounds),
                        is_pointer: false,
                        read_only: false,
                        initialized: false,
                    },
                );
                let ret = self.next_memory_slot;
                self.next_memory_slot -= usize::try_from(-right).unwrap();
                self.next_memory_slot += 1;
                return Ok(ret);
            }

            return Err(ErrorDetails {
                message: format!("cannot allocate array with dimensions {}:{}", left, right),
                location: dec.location,
                severity: crate::MessageSeverity::ERROR,
            });
        } else {
            self.symbols.insert(
                scoped_name,
                SymbolLocation {
                    memory_address: self.next_memory_slot,
                    is_array: false,
                    array_bounds: None,
                    is_pointer: false,
                    read_only: false,
                    initialized: false,
                },
            );
            self.next_memory_slot += 1;
            return Ok(self.next_memory_slot - 1);
        }
    }

    pub fn allocate_for_iter(
        &mut self,
        dec: &Declaration,
        scope: &String,
    ) -> Result<SymbolLocation, ErrorDetails> {
        let scoped_name = get_scoped_name(&dec.name, scope);

        if self.symbols.contains_key(&scoped_name) {
            return Err(ErrorDetails {
                message: format!("Variable {} already defined.", dec.name),
                location: dec.location,
                severity: crate::MessageSeverity::ERROR,
            });
        }
        let loc: SymbolLocation = SymbolLocation {
            memory_address: self.next_memory_slot,
            is_array: false,
            array_bounds: None,
            is_pointer: false,
            read_only: true,
            initialized: true,
        };

        self.symbols.insert(
            scoped_name,
            loc.clone()
        );
        self.next_memory_slot +=1;
        return Ok(loc);
    }

    pub fn deallocate_for_iter(&mut self, dec: &Declaration, scope: &String) {

    }

    pub fn get_ident_base_location(
        &self,
        ident: &Identifier,
        scope: &String,
    ) -> Result<SymbolLocation, ErrorDetails> {
        let scoped_name = get_scoped_name(&ident.name, scope);
        if let Some(loc) = self.symbols.get(&scoped_name) {
            return Ok(loc.clone());
        } else {
            return Err(ErrorDetails {
                message: format!("{} not declared in this scope", ident.name.clone()),
                location: ident.location,
                severity: crate::MessageSeverity::ERROR,
            });
        }
    }

    pub fn get_name_location(
        &self,
        name: &String,
        scope: &String,
        loc: (Point, Point),
    ) -> Result<SymbolLocation, ErrorDetails> {
        let scoped_name = get_scoped_name(name, scope);
        if let Some(loc) = self.symbols.get(&scoped_name) {
            return Ok(loc.clone());
        } else {
            return Err(ErrorDetails {
                message: format!("{} not declared in this scope", name.clone()),
                location: loc,
                severity: crate::MessageSeverity::ERROR,
            });
        }
    }

    pub fn get_ident_base_location_no_error(
        &self,
        ident: &Identifier,
        scope: &String,
    ) -> SymbolLocation {
        let scoped_name = get_scoped_name(&ident.name, scope);
        if let Some(loc) = self.symbols.get(&scoped_name) {
            return loc.clone();
        } else {
            unreachable!("");
        }
    }

    pub fn get_constant(&mut self, constant: i64) -> Option<SymbolLocation> {
        let name = get_constant_name(constant);

        if let Some(loc) = self.symbols.get(&name) {
            return Some(loc.clone());
        } else {
            return None;
        }
    }

    pub fn allocate_procedure_arg(&mut self, arg: &ProcArgument, scope: &String) -> SymbolLocation {
        let arg_scoped_name = get_scoped_name(&arg.name, scope);

        // TODO ADD CHECK IF ITS ALREADY THERE
        let symbol_loc = SymbolLocation {
            memory_address: self.next_memory_slot,
            is_array: arg.is_array,
            array_bounds: None,
            is_pointer: true,
            read_only: false,
            initialized: true,
        };
        self.symbols.insert(arg_scoped_name, symbol_loc.clone());
        self.next_memory_slot += 1;
        return symbol_loc;
    }

    pub fn allocate_builtin_arg(&mut self, arg: &ProcArgument, scope: &String) -> SymbolLocation {
        let arg_scoped_name = get_scoped_name(&arg.name, scope);

        // TODO ADD CHECK IF ITS ALREADY THERE
        let symbol_loc = SymbolLocation {
            memory_address: self.next_memory_slot,
            is_array: arg.is_array,
            array_bounds: None,
            is_pointer: false,
            read_only: false,
            initialized: true,
        };
        self.symbols.insert(arg_scoped_name, symbol_loc.clone());
        self.next_memory_slot += 1;
        return symbol_loc;
    }

    pub fn allocate_procedure_return(&mut self, proc_name: &String) -> usize {
        self.symbols.insert(
            format!("{}::RETURN", proc_name),
            SymbolLocation {
                memory_address: self.next_memory_slot,
                is_array: false,
                array_bounds: None,
                is_pointer: false,
                read_only: true,
                initialized: true,
            },
        );
        self.next_memory_slot += 1;
        return self.next_memory_slot - 1;
    }

    pub fn allocate_constant(&mut self, constant: i64) -> usize {
        let name = get_constant_name(constant);

        self.symbols.insert(
            name,
            SymbolLocation {
                memory_address: self.next_memory_slot,
                is_array: false,
                array_bounds: None,
                is_pointer: false,
                read_only: true,
                initialized: true,
            },
        );
        self.next_memory_slot += 1;
        return self.next_memory_slot - 1;
    }
}

fn get_scoped_name(name: &String, scope: &String) -> String {
    return format!("{}::{}", scope, name);
}

fn get_constant_name(constant: i64) -> String {
    return format!("$:{}", constant);
}
