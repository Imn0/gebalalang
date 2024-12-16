use std::collections::HashMap;

use serde::Serialize;


#[derive(Debug, Clone, Serialize)]
struct SymbolLocation {
    memory_address: usize,
    is_array: bool,
    is_pointer: bool,
    is_procedure: bool,
    read_only: bool,
    initialized: bool,
}

pub struct Memory {
    symbols: HashMap<String, SymbolLocation>,
    next_memory_slot: usize
}


impl Memory {
    pub fn new() -> Self {
        Memory { symbols: HashMap::new(), next_memory_slot: 0 }
    }
}