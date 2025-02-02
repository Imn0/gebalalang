use std::{
    cmp::min,
    collections::{HashMap, HashSet},
};

#[derive(Debug, Clone)]
pub struct SymbolLocation {
    pub memory_address: usize,
    pub is_pointer: bool,
    pub left_offset: i64,
}

#[derive(Debug, Default, Clone)]
pub struct Memory {
    symbols: HashMap<String, SymbolLocation>,
    constants: HashSet<i64>,
    next_memory_slot: usize,
    use_fat_arrays: bool,
    last_possible_mem_slot: usize,
}

impl Memory {
    pub fn new(use_fat_arrays: bool) -> Self {
        Memory {
            symbols: HashMap::new(),
            constants: HashSet::new(),
            next_memory_slot: 1,
            use_fat_arrays,
            last_possible_mem_slot: 0x4000000000000000 - 400,
        }
    }

    pub fn allocate_array(
        &mut self,
        name: &str,
        scope: &str,
        left: i64,
        right: i64,
    ) -> Result<SymbolLocation, String> {
        let scoped_name = scoped_name(name, scope);

        if !self.use_fat_arrays {
            let move_left = min(left, 0);
            self.next_memory_slot = match self.next_memory_slot.checked_add((-move_left) as usize) {
                Some(n) => n,
                None => {
                    return Err(get_out_of_memory_error_message(name));
                }
            };

            let move_right = right;

            let loc = SymbolLocation {
                memory_address: self.next_memory_slot,
                is_pointer: false,
                left_offset: 0,
            };

            self.symbols.insert(scoped_name, loc.clone());
            if move_right < 0 {
                self.next_memory_slot =
                    match self.next_memory_slot.checked_sub((-move_right) as usize) {
                        Some(n) => n,
                        None => {
                            return Err(get_out_of_memory_error_message(name));
                        }
                    };
            } else {
                self.next_memory_slot += move_right as usize;
                self.next_memory_slot =
                    match self.next_memory_slot.checked_add((move_right) as usize) {
                        Some(n) => n,
                        None => {
                            return Err(get_out_of_memory_error_message(name));
                        }
                    };
            }

            if self.next_memory_slot < self.last_possible_mem_slot {
                self.next_memory_slot += 1;
                return Ok(loc);
            } else {
                return Err(get_out_of_memory_error_message(name));
            }
        } else {
            let arr_len = right - left + 1 + 1; // len is r - l + 1 and +1 to store left offset
            let left_offset = -left;

            let loc = SymbolLocation {
                memory_address: self.next_memory_slot,
                is_pointer: false,
                left_offset: left_offset,
            };

            self.symbols.insert(scoped_name, loc.clone());
            self.next_memory_slot = match self.next_memory_slot.checked_add((arr_len) as usize) {
                Some(n) => n,
                None => {
                    return Err(get_out_of_memory_error_message(name));
                }
            };
            if self.next_memory_slot < self.last_possible_mem_slot {
                self.next_memory_slot += 1;
                return Ok(loc);
            } else {
                return Err(get_out_of_memory_error_message(name));
            }
        }
    }

    pub fn allocate_var(&mut self, name: &str, scope: &str) -> Result<SymbolLocation, String> {
        let scoped_name = scoped_name(name, scope);
        return self.allocate(scoped_name, false);
    }

    pub fn allocate_in_out_arg(
        &mut self,
        name: &str,
        scope: &str,
    ) -> Result<SymbolLocation, String> {
        let scoped_name = scoped_name(name, scope);
        self.allocate(scoped_name, true)
    }

    pub fn allocate_in_arg(&mut self, name: &str, scope: &str) -> Result<SymbolLocation, String> {
        let arg_scoped_name = scoped_name(&name, scope);

        let loc = SymbolLocation {
            memory_address: self.next_memory_slot,
            is_pointer: false,
            left_offset: 0,
        };

        self.symbols.insert(arg_scoped_name, loc.clone());
        self.next_memory_slot += 1;
        if self.next_memory_slot < self.last_possible_mem_slot {
            return Ok(loc);
        } else {
            Err(get_out_of_memory_error_message(name))
        }
    }

    pub fn allocate_proc_return(&mut self, name: &str) -> usize {
        self.symbols.insert(
            name.to_owned(),
            SymbolLocation {
                memory_address: self.next_memory_slot,
                is_pointer: false,
                left_offset: 0,
            },
        );
        self.next_memory_slot += 1;
        return self.next_memory_slot - 1;
    }

    fn allocate(
        &mut self,
        scoped_name: String,
        is_pointer: bool,
    ) -> Result<SymbolLocation, String> {
        self.symbols.insert(
            scoped_name,
            SymbolLocation {
                memory_address: self.next_memory_slot,
                is_pointer: is_pointer,
                left_offset: 0,
            },
        );
        self.next_memory_slot += 1;
        if self.next_memory_slot < self.last_possible_mem_slot {
            return Ok(SymbolLocation {
                memory_address: self.next_memory_slot - 1,
                is_pointer: is_pointer,
                left_offset: 0,
            });
        } else {
            Err(format!("too little memory"))
        }
    }

    pub fn drop_var(&mut self, name: &str, scope: &str) {
        let scoped_name = scoped_name(name, scope);
        self.symbols.remove(&scoped_name);
    }

    pub fn get_base_loc(&mut self, name: &str, scope: &str) -> &SymbolLocation {
        let scoped_name = scoped_name(name, scope);
        self.symbols.get(&scoped_name).unwrap()
    }

    pub fn get_const(&self, constant: &i64) -> Option<&SymbolLocation> {
        let c_name = constant_name(constant);
        self.symbols.get(&c_name)
    }

    pub fn get_constants(&mut self) -> Vec<i64> {
        return self.constants.clone().iter().copied().collect();
    }

    pub fn get_const_loc_or_aloc(&mut self, constant: &i64) -> &SymbolLocation {
        let c_name = constant_name(constant);

        if !self.symbols.contains_key(&c_name) {
            self.symbols.insert(
                c_name.clone(),
                SymbolLocation {
                    memory_address: self.next_memory_slot,
                    is_pointer: false,
                    left_offset: 0,
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
    return format!("$::{}", constant);
}

fn get_out_of_memory_error_message(name: &str) -> String{
    return format!("cannot allocate '{name}', too little memory")
}