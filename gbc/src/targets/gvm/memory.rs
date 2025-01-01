use std::collections::HashMap;

use crate::ast::{Declaration, Identifier, Location, ProcArgument};

#[derive(Debug, Clone)]
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
#[derive(Debug, Default)]
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
}

fn get_scoped_name(name: &String, scope: &String) -> String {
    return format!("{}::{}", scope, name);
}

fn get_constant_name(constant: i64) -> String {
    return format!("$:{}", constant);
}
