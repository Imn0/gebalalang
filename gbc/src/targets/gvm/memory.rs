use std::{
    cmp::{max, min},
    collections::{HashMap, HashSet},
    f32::consts::E,
};

use crate::ast::{Declaration, Identifier, Location, ProcArgument};

#[derive(Debug, Clone)]
pub struct SymbolLocation {
    pub memory_address: usize,
    pub is_array: bool,
    pub is_pointer: bool,
}

impl SymbolLocation {
    pub fn new() -> Self {
        SymbolLocation {
            memory_address: 0,
            is_array: false,
            is_pointer: false,
        }
    }
}
#[derive(Debug, Default)]
pub struct Memory {
    symbols: HashMap<String, SymbolLocation>,
    constants: HashSet<i64>,
    next_memory_slot: usize,
}

impl Memory {
    pub fn new() -> Self {
        Memory {
            symbols: HashMap::new(),
            constants: HashSet::new(),
            next_memory_slot: 1,
        }
    }

    pub fn allocate_array(&mut self, name: &str, scope: &str, left: i64, right: i64) {
        let scoped_name = scoped_name(name, scope);

        let move_left = min(left, 0);
        self.next_memory_slot += (-move_left) as usize;

        let move_right = right;

        self.symbols.insert(
            scoped_name,
            SymbolLocation {
                memory_address: self.next_memory_slot,
                is_array: true,
                is_pointer: false,
            },
        );
        if move_right < 0 {
            self.next_memory_slot -= (-move_right) as usize;
        } else {
            self.next_memory_slot += move_right as usize;
        }
        self.next_memory_slot += 1;
    }

    pub fn allocate_var(&mut self, name: &str, scope: &str) {
        let scoped_name = scoped_name(name, scope);
        self.allocate(scoped_name, false, false);
    }

    pub fn allocate_proc_arg(&mut self, name: &str, scope: &str, is_array: bool) -> SymbolLocation {
        let scoped_name = scoped_name(name, scope);
        self.allocate(scoped_name, is_array, true)
    }

    pub fn allocate_proc_return(&mut self, name: &str) -> usize {
        self.symbols.insert(
            name.to_owned(),
            SymbolLocation {
                memory_address: self.next_memory_slot,
                is_array: false,
                is_pointer: false,
            },
        );
        self.next_memory_slot += 1;
        return self.next_memory_slot - 1;
    }

    fn allocate(
        &mut self,
        scoped_name: String,
        is_array: bool,
        is_pointer: bool,
    ) -> SymbolLocation {
        self.symbols.insert(
            scoped_name,
            SymbolLocation {
                memory_address: self.next_memory_slot,
                is_array: is_array,
                is_pointer: is_pointer,
            },
        );
        self.next_memory_slot += 1;
        return SymbolLocation {
            memory_address: self.next_memory_slot - 1,
            is_array: is_array,
            is_pointer: is_pointer,
        };
    }

    pub fn drop_var(&mut self, name: &str, scope: &str) {
        let scoped_name = scoped_name(name, scope);
        self.symbols.remove(&scoped_name);
    }

    pub fn get_base_loc(&self, name: &str, scope: &str) -> &SymbolLocation {
        let scoped_name = scoped_name(name, scope);
        self.symbols.get(&scoped_name).unwrap()
    }

    pub fn get_const(&self, constant: &i64) -> &SymbolLocation {
        let c_name = constant_name(constant);
        self.symbols.get(&c_name).unwrap()
    }

    pub fn get_constants(&self) -> Vec<&i64> {
        return self.constants.iter().collect();
    }

    pub fn get_const_loc_or_aloc(&mut self, constant: &i64) -> &SymbolLocation {
        let c_name = constant_name(constant);

        if !self.symbols.contains_key(&c_name) {
            self.symbols.insert(
                c_name.clone(),
                SymbolLocation {
                    memory_address: self.next_memory_slot,
                    is_array: false,
                    is_pointer: false,
                },
            );
            self.next_memory_slot += 1;
            self.constants.insert(constant.clone());
        }

        self.symbols.get(&c_name).unwrap()
    }
}

fn scoped_name(name: &str, scope: &str) -> String {
    return format!("{}::{}", scope, name);
}

fn constant_name(constant: &i64) -> String {
    return format!("$:{}", constant);
}
