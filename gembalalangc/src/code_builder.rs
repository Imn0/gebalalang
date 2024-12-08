use std::{collections::HashMap, fs::File, io::Write};

use serde::Serialize;

use crate::{asm::AbstractASM, Ast, Command, Condition, Either, ErrorDetails, Expression, ForDirection, Identifier, MessageSeverity, Procedure, Value };

#[derive(Debug, Clone, Serialize)]
struct SymbolLocation {
    memory: usize,
    is_array: bool,
    is_pointer: bool,
    is_procedure: bool,
    read_only: bool,
    initialized: bool,
}

#[derive(Clone)]
struct ProcedureInfo {
    code_location: usize,
    args: Vec<bool>,
}

pub struct CodeGenerator {
    pub messages: Vec<ErrorDetails>,
    pub assembly_code: Vec<AbstractASM>,
    symbols: HashMap<String, SymbolLocation>,
    procedures: HashMap<String, ProcedureInfo>,
    next_memory_slot: usize,
    last_mem_slot: usize,
    current_scope: String,
}


impl CodeGenerator {
    pub fn new() -> Self {
        CodeGenerator {
            symbols: HashMap::new(),
            procedures: HashMap::new(),
            next_memory_slot: 13213,
            last_mem_slot: 0x4000000000000000,
            assembly_code: Vec::new(),
            messages: Vec::new(),
            current_scope: "".to_owned(),
        }
    }

    fn push_asm(&mut self, ins: AbstractASM) {
        self.assembly_code.push(ins);
    }

    fn get_variable_w_idx(&self, name: &str, idx: i64) -> SymbolLocation {
        let scoped_name = self.current_scope.clone() + name;
        let mut loc = self.symbols.get(&scoped_name).unwrap().clone();
        if idx != 0 {
            if idx < 0 {
                loc.memory -= usize::try_from(-idx).unwrap();
                return loc;
            } else {
                loc.memory += usize::try_from(idx).unwrap();
                return loc;
            }
        } else {
            return loc;
        }
    }

    fn get_variable_current_scope(&self, name: &str) -> Result<SymbolLocation, String> {
        let scoped_name = self.current_scope.clone() + name;
        if let Some(loc) = self.symbols.get(&scoped_name) {
            return Ok(loc.clone());
        } else {
            return Err(format!("Variable {} not declared in this scope.", name));
        }
    }

    fn get_variable_global_scope(&self, name: &str) -> Result<SymbolLocation, String> {
        if let Some(loc) = self.symbols.get(name) {
            return Ok(loc.clone());
        } else {
            return Err(format!("Variable {} not declared in this scope.", name));
        }
    }

    fn set_to_initialized_scoped(&mut self, name: &str) {
        let scoped_name = self.current_scope.clone() + name;
        self.set_to_initialized_global(&scoped_name);
    }

    fn set_to_initialized_global(&mut self, name: &str) {
        if let Some(loc) = self.symbols.get_mut(name) {
            loc.initialized = true;
        }
    }

    fn allocate_procedure(&mut self, proc_name: String) -> usize {
        self.symbols.insert(
            proc_name,
            SymbolLocation {
                memory: self.next_memory_slot,
                is_array: false,
                is_pointer: false,
                is_procedure: true,
                read_only: true,
                initialized: true,
            },
        );
        self.next_memory_slot += 1;
        return self.next_memory_slot - 1;
    }

    fn allocate_arg(&mut self, name: String, is_array: bool) {
        let scoped_name = self.current_scope.clone() + &name;

        self.symbols.insert(
            scoped_name,
            SymbolLocation {
                memory: self.next_memory_slot,
                is_array,
                is_pointer: true,
                is_procedure: false,
                read_only: false,
                initialized: true,
            },
        );
        self.next_memory_slot += 1;
    }

    fn allocate_variable_global(
        &mut self,
        name: String,
        left: i64,
        right: i64,
        is_pointer: bool,
        read_only: bool,
    ) -> Result<usize, String> {
        if self.symbols.contains_key(&name) {
            return Err(format!("Variable {} already defined", name.clone()));
        }

        let mem_slot = self.next_memory_slot;
        if left == 0 && right == 0 {
            self.symbols.insert(
                name,
                SymbolLocation {
                    memory: self.next_memory_slot,
                    is_array: false,
                    is_pointer,
                    is_procedure: false,
                    read_only: read_only,
                    initialized: false,
                },
            );
            self.next_memory_slot += 1;
            return Ok(mem_slot);
        }

        if left > right {
            return Err(format!(
                "Cant allocate array with dimensions {}:{}",
                left, right
            ));
        }

        if left >= 0 && right >= 0 {
            self.symbols.insert(
                name,
                SymbolLocation {
                    memory: self.next_memory_slot,
                    is_array: true,
                    is_pointer,
                    is_procedure: false,
                    read_only: read_only,
                    initialized: false,
                },
            );
            self.next_memory_slot += usize::try_from(right).unwrap() + 1;
            return Ok(mem_slot);
        }

        if left < 0 && right >= 0 {
            self.next_memory_slot += usize::try_from(-left).unwrap();
            self.symbols.insert(
                name,
                SymbolLocation {
                    memory: self.next_memory_slot,
                    is_array: true,
                    is_pointer,
                    is_procedure: false,
                    read_only: read_only,
                    initialized: false,
                },
            );
            self.next_memory_slot += usize::try_from(right).unwrap() + 1;
            return Ok(mem_slot);
        }

        if left < 0 && right < 0 {
            self.next_memory_slot += usize::try_from(-left).unwrap();
            self.symbols.insert(
                name,
                SymbolLocation {
                    memory: self.next_memory_slot,
                    is_array: true,
                    is_pointer,
                    is_procedure: false,
                    read_only: read_only,
                    initialized: false,
                },
            );
            self.next_memory_slot -= usize::try_from(-right).unwrap();
            self.next_memory_slot += 1;
            return Ok(mem_slot);
        }

        return Err(format!(
            "Cant allocate array with dimensions {}:{}",
            left, right
        ));
    }

    fn delete_variable_scoped(&mut self, name: String) {
        let scoped_name = self.current_scope.clone() + &name;
        if let Some(value) = self.symbols.remove(&scoped_name) {
        } else {
        }
    }

    fn allocate_variable_scoped(
        &mut self,
        name: String,
        left: i64,
        right: i64,
        is_pointer: bool,
        read_only: bool,
    ) -> Result<usize, String> {
        let scoped_name = self.current_scope.clone() + &name;
        return self.allocate_variable_global(scoped_name, left, right, is_pointer, read_only);
    }

    /// Loads value to p_0
    fn generate_value(&mut self, value: &Value) {
        match value {
            Value::Number(num) => {
                self.push_asm(AbstractASM::SET(num.clone())); // ! CONSTANT
            }
            Value::Identifier(ident) => {
                let result = self.get_variable_current_scope(&ident.name);
                match result {
                    Ok(loc) => {
                        if !loc.initialized {
                            self.messages.push(ErrorDetails {
                                message: format!(
                                    "Usage of not initialized variable {}.",
                                    ident.name
                                ),
                                location: ident.location,
                                severity: MessageSeverity::WARNING,
                            });
                        }
                    }
                    Err(err) => {
                        self.messages.push(ErrorDetails {
                            message: err,
                            location: ident.location,
                            severity: MessageSeverity::ERROR,
                        });
                        return;
                    }
                }

                if let Some(idx) = &ident.index {
                    match idx {
                        Either::Left(idx_name) => {
                            let base_loc;
                            if let Ok(_base_loc) = self.get_variable_current_scope(&ident.name) {
                                base_loc = _base_loc;
                            } else {
                                self.messages.push(ErrorDetails {
                                    message: format!("Unknown variable {}.", ident.name),
                                    location: ident.location,
                                    severity: MessageSeverity::ERROR,
                                });
                                return;
                            }

                            if !base_loc.is_array {
                                self.messages.push(ErrorDetails {
                                    message: "cannot access it like that".to_owned(),
                                    location: ident.location,
                                    severity: MessageSeverity::WARNING,
                                });
                            }
                            let idx_loc;
                            if let Ok(_idx_loc) = self.get_variable_current_scope(idx_name) {
                                idx_loc = _idx_loc;
                            } else {
                                self.messages.push(ErrorDetails {
                                    message: format!("Unknown variable {}.", idx_name),
                                    location: ident.location,
                                    severity: MessageSeverity::ERROR,
                                });
                                return;
                            }

                            if idx_loc.is_array {
                                self.messages.push(ErrorDetails {
                                    message: format!("Cannot access {} like that.", ident.name),
                                    location: ident.location,
                                    severity: MessageSeverity::WARNING,
                                });
                            }
                            if !idx_loc.initialized {
                                self.messages.push(ErrorDetails {
                                    message: format!(
                                        "Usage of not initialized variable {}",
                                        idx_name,
                                    ),
                                    location: ident.location,
                                    severity: MessageSeverity::WARNING,
                                });
                            }
                            match (base_loc.is_pointer, idx_loc.is_pointer) {
                                (false, false) => {
                                    self.push_asm(AbstractASM::SET(base_loc.memory as i64));
                                    self.push_asm(AbstractASM::ADD(idx_loc.memory));
                                    self.push_asm(AbstractASM::LOADI(0));
                                }
                                (true, false) => {
                                    self.push_asm(AbstractASM::LOAD(base_loc.memory));
                                    self.push_asm(AbstractASM::ADD(idx_loc.memory));
                                    self.push_asm(AbstractASM::LOADI(0));
                                }
                                (false, true) => {
                                    self.push_asm(AbstractASM::SET(base_loc.memory as i64));
                                    self.push_asm(AbstractASM::ADDI(idx_loc.memory));
                                    self.push_asm(AbstractASM::LOADI(0));
                                }
                                (true, true) => {
                                    self.push_asm(AbstractASM::LOAD(base_loc.memory));
                                    self.push_asm(AbstractASM::ADDI(idx_loc.memory));
                                    self.push_asm(AbstractASM::LOADI(0));
                                }
                            }
                        }
                        Either::Right(idx_num) => {
                            let symbol_loc = self.get_variable_current_scope(&ident.name).unwrap();
                            if !symbol_loc.is_array {
                                self.messages.push(ErrorDetails {
                                    message: "cannot access it like that".to_owned(),
                                    location: ident.location,
                                    severity: MessageSeverity::WARNING,
                                });
                            }
                            if !symbol_loc.is_pointer {
                                let loc = self.get_variable_w_idx(&ident.name, *idx_num);
                                self.push_asm(AbstractASM::LOAD(loc.memory));
                            } else {
                                self.push_asm(AbstractASM::SET(*idx_num));
                                self.push_asm(AbstractASM::ADD(symbol_loc.memory));
                                self.push_asm(AbstractASM::LOADI(0));
                            }
                        }
                    }
                } else {
                    let result = self.get_variable_current_scope(&ident.name);
                    if let Ok(loc) = result {
                        if loc.is_array {
                            self.messages.push(ErrorDetails {
                                message: "cannot access it like that way".to_owned(),
                                location: ident.location,
                                severity: MessageSeverity::WARNING,
                            });
                        }
                        if loc.is_pointer {
                            self.push_asm(AbstractASM::LOADI(loc.memory));
                        } else {
                            self.push_asm(AbstractASM::LOAD(loc.memory));
                        }
                    } else if let Err(e) = result {
                        self.messages.push(ErrorDetails {
                            message: e,
                            location: ident.location,
                            severity: MessageSeverity::ERROR,
                        });
                    }
                }
            }
        }
    }

    fn store_to_identifier(&mut self, ident: &Identifier) {
        let dst_loc;
        match self.get_variable_current_scope(&ident.name) {
            Ok(_r) => dst_loc = _r,
            Err(err) => {
                self.messages.push(ErrorDetails {
                    message: err,
                    location: ident.location,
                    severity: MessageSeverity::ERROR,
                });
                return;
            }
        }

        if dst_loc.read_only {
            self.messages.push(ErrorDetails {
                message: format!("Variable {} is read only.", ident.name),
                location: ident.location,
                severity: MessageSeverity::ERROR,
            });
            return;
        }

        self.set_to_initialized_scoped(&ident.name);

        if let Some(dest_idx) = &ident.index {
            match dest_idx {
                Either::Left(idx_name) => {
                    self.push_asm(AbstractASM::STORE(self.last_mem_slot - 1));

                    if !dst_loc.is_array {
                        self.messages.push(ErrorDetails {
                            message: format!("Cannot access {} it like that", ident.name),
                            location: ident.location,
                            severity: MessageSeverity::WARNING,
                        });
                    }
                    let result = self.get_variable_current_scope(idx_name);
                    let idx_loc;
                    match result {
                        Ok(_r) => idx_loc = _r,
                        Err(err) => {
                            self.messages.push(ErrorDetails {
                                message: err,
                                location: ident.location,
                                severity: MessageSeverity::ERROR,
                            });
                            return;
                        }
                    }

                    if idx_loc.is_array {
                        self.messages.push(ErrorDetails {
                            message: format!("Cannot access {} it like that", idx_name),
                            location: ident.location,
                            severity: MessageSeverity::WARNING,
                        });
                    }

                    if !idx_loc.initialized {
                        self.messages.push(ErrorDetails {
                            message: format!("Variable {} not initialized", idx_name),
                            location: ident.location,
                            severity: MessageSeverity::WARNING,
                        });
                    }
                    match (dst_loc.is_pointer, idx_loc.is_pointer) {
                        (false, false) => {
                            self.push_asm(AbstractASM::SET(dst_loc.memory as i64));
                            self.push_asm(AbstractASM::ADD(idx_loc.memory));
                            self.push_asm(AbstractASM::STORE(self.last_mem_slot));

                            self.push_asm(AbstractASM::LOAD(self.last_mem_slot - 1));
                            self.push_asm(AbstractASM::STOREI(self.last_mem_slot));
                        }
                        (true, false) => {
                            self.push_asm(AbstractASM::LOAD(dst_loc.memory));
                            self.push_asm(AbstractASM::ADD(idx_loc.memory));
                            self.push_asm(AbstractASM::STORE(self.last_mem_slot));

                            self.push_asm(AbstractASM::LOAD(self.last_mem_slot - 1));
                            self.push_asm(AbstractASM::STOREI(self.last_mem_slot));
                        }
                        (false, true) => {
                            self.push_asm(AbstractASM::SET(dst_loc.memory as i64));
                            self.push_asm(AbstractASM::ADDI(idx_loc.memory));
                            self.push_asm(AbstractASM::STORE(self.last_mem_slot));

                            self.push_asm(AbstractASM::LOAD(self.last_mem_slot - 1));
                            self.push_asm(AbstractASM::STOREI(self.last_mem_slot));
                        }
                        (true, true) => {
                            self.push_asm(AbstractASM::LOAD(dst_loc.memory));
                            self.push_asm(AbstractASM::ADDI(idx_loc.memory));
                            self.push_asm(AbstractASM::STORE(self.last_mem_slot));

                            self.push_asm(AbstractASM::LOAD(self.last_mem_slot - 1));
                            self.push_asm(AbstractASM::STOREI(self.last_mem_slot));
                        }
                    }
                }
                Either::Right(idx_num) => {
                    let dest_loc = self.get_variable_current_scope(&ident.name).unwrap();
                    if !dest_loc.is_array {
                        self.messages.push(ErrorDetails {
                            message: "cannot access it like that".to_owned(),
                            location: ident.location,
                            severity: MessageSeverity::WARNING,
                        });
                    }
                    if !dest_loc.is_pointer {
                        let final_loc = self.get_variable_w_idx(&ident.name, *idx_num);
                        self.push_asm(AbstractASM::STORE(final_loc.memory));
                    } else {
                        self.push_asm(AbstractASM::STORE(self.last_mem_slot - 1));
                        self.push_asm(AbstractASM::SET(*idx_num));
                        self.push_asm(AbstractASM::ADD(dest_loc.memory));
                        self.push_asm(AbstractASM::STORE(self.last_mem_slot + 0));
                        self.push_asm(AbstractASM::LOAD(self.last_mem_slot - 1));
                        self.push_asm(AbstractASM::STOREI(self.last_mem_slot + 0));
                    }
                }
            }
        } else {
            let result = self.get_variable_current_scope(&ident.name);
            let dest_loc;
            if let Ok(_d) = result {
                dest_loc = _d;
            } else if let Err(err) = result {
                self.messages.push(ErrorDetails {
                    message: err,
                    location: ident.location,
                    severity: MessageSeverity::ERROR,
                });
                return;
            } else {
                unreachable!();
            }
            if dest_loc.is_array {
                self.messages.push(ErrorDetails {
                    message: "cannot access it like that".to_owned(),
                    location: ident.location,
                    severity: MessageSeverity::WARNING,
                });
            }

            if dest_loc.is_pointer {
                self.push_asm(AbstractASM::STOREI(dest_loc.memory));
            } else {
                self.push_asm(AbstractASM::STORE(dest_loc.memory));
            }
        }
    }

    fn generate_condition(&mut self, condition: &Condition) -> AbstractASM {
        match condition {
            Condition::NotEqual(left, right) => {
                self.generate_value(left);
                self.push_asm(AbstractASM::STORE(self.last_mem_slot));
                self.generate_value(right);
                self.push_asm(AbstractASM::SUB(self.last_mem_slot));
                AbstractASM::JZERO(0)
            }
            Condition::Equal(left, right) => {
                self.generate_value(left);
                self.push_asm(AbstractASM::STORE(self.last_mem_slot));
                self.generate_value(right);
                self.push_asm(AbstractASM::SUB(self.last_mem_slot));
                self.push_asm(AbstractASM::JZERO(2));
                AbstractASM::JUMP(0)
            }
            Condition::LessOrEqual(left, right) => {
                self.generate_value(right);
                self.push_asm(AbstractASM::STORE(self.last_mem_slot));
                self.generate_value(left);
                self.push_asm(AbstractASM::SUB(self.last_mem_slot));
                AbstractASM::JPOS(0)
            }
            Condition::GreaterOrEqual(left, right) => {
                self.generate_value(left);
                self.push_asm(AbstractASM::STORE(self.last_mem_slot));
                self.generate_value(right);
                self.push_asm(AbstractASM::SUB(self.last_mem_slot));
                AbstractASM::JPOS(0)
            }
            Condition::GreaterThan(left, right) => {
                self.generate_value(right);
                self.push_asm(AbstractASM::STORE(self.last_mem_slot));
                self.generate_value(left);
                self.push_asm(AbstractASM::SUB(self.last_mem_slot));
                self.push_asm(AbstractASM::JPOS(2));
                AbstractASM::JUMP(0)
            }
            Condition::LessThan(left, right) => {
                self.generate_value(left);
                self.push_asm(AbstractASM::STORE(self.last_mem_slot));
                self.generate_value(right);
                self.push_asm(AbstractASM::SUB(self.last_mem_slot));
                self.push_asm(AbstractASM::JPOS(2));
                AbstractASM::JUMP(0)
            }
        }
    }

    fn generate_expression(&mut self, command: &Command) {
        if let Command::Assignment {
            identifier,
            expression,
            location,
        } = command
        {
            match expression {
                Expression::Value(value) => {
                    self.generate_value(value);
                    self.store_to_identifier(identifier);
                }
                Expression::Addition(left, right) => {
                    self.generate_value(left);
                    self.push_asm(AbstractASM::STORE(self.last_mem_slot));
                    self.generate_value(right);
                    self.push_asm(AbstractASM::ADD(self.last_mem_slot));
                    self.store_to_identifier(identifier);
                }
                Expression::Subtraction(left, right) => {
                    self.generate_value(right);
                    self.push_asm(AbstractASM::STORE(self.last_mem_slot));
                    self.generate_value(left);
                    self.push_asm(AbstractASM::SUB(self.last_mem_slot));
                    self.store_to_identifier(identifier);
                }
                Expression::Division(left, right) => {
                    self.generate_value(left);
                    self.push_asm(AbstractASM::STORE(self.last_mem_slot));

                    match right {
                        Value::Number(val) => {
                            if val.clone() == 2 {
                                self.push_asm(AbstractASM::HALF);
                                self.store_to_identifier(identifier);
                                return;
                            }
                        }
                        _ => {}
                    }

                    let sign = self.last_mem_slot;
                    self.last_mem_slot -= 1;

                    let quotient = self.last_mem_slot;
                    self.last_mem_slot -= 1;

                    let current_divisor = self.last_mem_slot;
                    self.last_mem_slot -= 1;

                    let current_multiple = self.last_mem_slot;
                    self.last_mem_slot -= 1;
                    let l = self.last_mem_slot;
                    self.last_mem_slot -= 1;

                    let r = self.last_mem_slot;
                    self.last_mem_slot -= 1;

                    self.push_asm(AbstractASM::SET(0));
                    self.push_asm(AbstractASM::STORE(sign));

                    self.generate_value(left);

                    /*
                    if left < 0:
                    sign = -sign
                    left = -left
                    */
                    self.push_asm(AbstractASM::STORE(l));
                    self.push_asm(AbstractASM::JPOS(6));
                    self.push_asm(AbstractASM::SET(-1));
                    self.push_asm(AbstractASM::STORE(sign));
                    self.push_asm(AbstractASM::SET(0));
                    self.push_asm(AbstractASM::SUB(l));
                    self.push_asm(AbstractASM::STORE(l));

                    /*
                    if right < 0:
                    sign = -sign
                    right = -right
                    */
                    self.generate_value(right);
                    self.push_asm(AbstractASM::STORE(r));
                    self.push_asm(AbstractASM::JPOS(7));
                    self.push_asm(AbstractASM::SET(0));
                    self.push_asm(AbstractASM::LOAD(sign));
                    self.push_asm(AbstractASM::STORE(sign));
                    self.push_asm(AbstractASM::SET(0));
                    self.push_asm(AbstractASM::SUB(r));
                    self.push_asm(AbstractASM::STORE(r));

                    self.push_asm(AbstractASM::SET(0)); // quotient = 0
                    self.push_asm(AbstractASM::STORE(quotient));

                    self.push_asm(AbstractASM::LOAD(r));
                    self.push_asm(AbstractASM::STORE(current_divisor)); //current_divisor = right

                    self.push_asm(AbstractASM::SET(1));
                    self.push_asm(AbstractASM::STORE(current_multiple)); // current_multiple = 1

                    /*
                    while current_divisor <= left:
                        current_divisor += current_divisor
                        current_multiple += current_multiple
                    */
                    self.push_asm(AbstractASM::LOAD(current_divisor));
                    self.push_asm(AbstractASM::SUB(l));
                    self.push_asm(AbstractASM::JPOS(8));

                    self.push_asm(AbstractASM::LOAD(current_divisor));
                    self.push_asm(AbstractASM::ADD(current_divisor));
                    self.push_asm(AbstractASM::STORE(current_divisor));

                    self.push_asm(AbstractASM::LOAD(current_multiple));
                    self.push_asm(AbstractASM::ADD(current_multiple));
                    self.push_asm(AbstractASM::STORE(current_multiple));

                    self.push_asm(AbstractASM::JUMP(-9));

                    /*
                    while right <= left:
                        current_divisor //= 2
                        current_multiple //= 2

                        if current_divisor <= left:
                            left -= current_divisor
                            quotient += current_multiple
                    */

                    self.push_asm(AbstractASM::LOAD(r));
                    self.push_asm(AbstractASM::SUB(l));
                    self.push_asm(AbstractASM::JPOS(16));

                    self.push_asm(AbstractASM::LOAD(current_multiple));
                    self.push_asm(AbstractASM::HALF);
                    self.push_asm(AbstractASM::STORE(current_multiple));

                    self.push_asm(AbstractASM::LOAD(current_divisor));
                    self.push_asm(AbstractASM::HALF);
                    self.push_asm(AbstractASM::STORE(current_divisor));

                    self.push_asm(AbstractASM::SUB(l));
                    self.push_asm(AbstractASM::JPOS(7));
                    self.push_asm(AbstractASM::LOAD(l));
                    self.push_asm(AbstractASM::SUB(current_divisor));
                    self.push_asm(AbstractASM::STORE(l));

                    self.push_asm(AbstractASM::LOAD(quotient));
                    self.push_asm(AbstractASM::ADD(current_multiple));
                    self.push_asm(AbstractASM::STORE(quotient));
                    self.push_asm(AbstractASM::JUMP(-17));
                    self.push_asm(AbstractASM::LOAD(quotient));
                    self.store_to_identifier(identifier);
                    self.last_mem_slot += 6;
                }
                Expression::Multiplication(left, right) => {
                    self.generate_value(left);
                    self.push_asm(AbstractASM::STORE(self.last_mem_slot));

                    match right {
                        Value::Number(val) => {
                            if val.clone() == 2 {
                                self.push_asm(AbstractASM::ADD(self.last_mem_slot));
                                self.store_to_identifier(identifier);
                                return;
                            }
                        }
                        _ => {}
                    }

                    let l = self.last_mem_slot;
                    self.last_mem_slot -= 1;

                    let r = self.last_mem_slot;
                    self.last_mem_slot -= 1;

                    let result = self.last_mem_slot;
                    self.last_mem_slot -= 1;

                    self.generate_value(right);
                    self.push_asm(AbstractASM::STORE(r));
                    self.push_asm(AbstractASM::SET(0));
                    self.push_asm(AbstractASM::STORE(result));
                    self.generate_value(left);
                    self.push_asm(AbstractASM::STORE(l));

                    // loop start
                    self.push_asm(AbstractASM::JZERO(16));
                    self.push_asm(AbstractASM::HALF); // l%2
                    self.push_asm(AbstractASM::ADD(0)); // l%2
                    self.push_asm(AbstractASM::SUB(l)); // l%2

                    self.push_asm(AbstractASM::JZERO(5)); // IF l%2=1 THEN
                    self.push_asm(AbstractASM::LOAD(l));
                    self.push_asm(AbstractASM::LOAD(result)); // result := result + r;
                    self.push_asm(AbstractASM::ADD(r)); // result := result + r;
                    self.push_asm(AbstractASM::STORE(result)); // result := result + r;
                                                               // ENDIF

                    self.push_asm(AbstractASM::LOAD(r));
                    self.push_asm(AbstractASM::ADD(r));
                    self.push_asm(AbstractASM::STORE(r));

                    self.push_asm(AbstractASM::LOAD(l));
                    self.push_asm(AbstractASM::HALF);
                    self.push_asm(AbstractASM::STORE(l));

                    self.push_asm(AbstractASM::JUMP(-16));

                    self.push_asm(AbstractASM::LOAD(result));
                    self.store_to_identifier(identifier);
                    self.last_mem_slot += 3;
                }
                Expression::Modulo(left, right) => {
                    match right {
                        Value::Number(val) => {
                            if val.clone() == 2 {
                                self.generate_value(left);
                                self.push_asm(AbstractASM::STORE(self.last_mem_slot));
                                self.push_asm(AbstractASM::HALF);
                                self.push_asm(AbstractASM::ADD(0));
                                self.push_asm(AbstractASM::STORE(self.last_mem_slot - 1));
                                self.push_asm(AbstractASM::LOAD(self.last_mem_slot));
                                self.push_asm(AbstractASM::SUB(self.last_mem_slot - 1));
                                self.store_to_identifier(identifier);
                            }
                        }
                        _ => {}
                    }
                    let sign = self.last_mem_slot;
                    self.last_mem_slot -= 1;

                    let quotient = self.last_mem_slot;
                    self.last_mem_slot -= 1;

                    let current_divisor = self.last_mem_slot;
                    self.last_mem_slot -= 1;

                    let current_multiple = self.last_mem_slot;
                    self.last_mem_slot -= 1;
                    let l = self.last_mem_slot;
                    self.last_mem_slot -= 1;

                    let r = self.last_mem_slot;
                    self.last_mem_slot -= 1;

                    self.push_asm(AbstractASM::SET(0));
                    self.push_asm(AbstractASM::STORE(sign));

                    self.generate_value(left);

                    /*
                    if left < 0:
                    sign = -sign
                    left = -left
                    */
                    self.push_asm(AbstractASM::STORE(l));
                    self.push_asm(AbstractASM::JPOS(6));
                    self.push_asm(AbstractASM::SET(-1));
                    self.push_asm(AbstractASM::STORE(sign));
                    self.push_asm(AbstractASM::SET(0));
                    self.push_asm(AbstractASM::SUB(l));
                    self.push_asm(AbstractASM::STORE(l));

                    /*
                    if right < 0:
                    sign = -sign
                    right = -right
                    */
                    self.generate_value(right);
                    self.push_asm(AbstractASM::STORE(r));
                    self.push_asm(AbstractASM::JPOS(7));
                    self.push_asm(AbstractASM::SET(0));
                    self.push_asm(AbstractASM::LOAD(sign));
                    self.push_asm(AbstractASM::STORE(sign));
                    self.push_asm(AbstractASM::SET(0));
                    self.push_asm(AbstractASM::SUB(r));
                    self.push_asm(AbstractASM::STORE(r));

                    self.push_asm(AbstractASM::SET(0)); // quotient = 0
                    self.push_asm(AbstractASM::STORE(quotient));

                    self.push_asm(AbstractASM::LOAD(r));
                    self.push_asm(AbstractASM::STORE(current_divisor)); //current_divisor = right

                    self.push_asm(AbstractASM::SET(1));
                    self.push_asm(AbstractASM::STORE(current_multiple)); // current_multiple = 1

                    /*
                    while current_divisor <= left:
                        current_divisor += current_divisor
                        current_multiple += current_multiple
                    */
                    self.push_asm(AbstractASM::LOAD(current_divisor));
                    self.push_asm(AbstractASM::SUB(l));
                    self.push_asm(AbstractASM::JPOS(8));

                    self.push_asm(AbstractASM::LOAD(current_divisor));
                    self.push_asm(AbstractASM::ADD(current_divisor));
                    self.push_asm(AbstractASM::STORE(current_divisor));

                    self.push_asm(AbstractASM::LOAD(current_multiple));
                    self.push_asm(AbstractASM::ADD(current_multiple));
                    self.push_asm(AbstractASM::STORE(current_multiple));

                    self.push_asm(AbstractASM::JUMP(-9));

                    /*
                    while right <= left:
                        current_divisor //= 2
                        current_multiple //= 2

                        if current_divisor <= left:
                            left -= current_divisor
                            quotient += current_multiple
                    */

                    self.push_asm(AbstractASM::LOAD(r));
                    self.push_asm(AbstractASM::SUB(l));
                    self.push_asm(AbstractASM::JPOS(16));

                    self.push_asm(AbstractASM::LOAD(current_multiple));
                    self.push_asm(AbstractASM::HALF);
                    self.push_asm(AbstractASM::STORE(current_multiple));

                    self.push_asm(AbstractASM::LOAD(current_divisor));
                    self.push_asm(AbstractASM::HALF);
                    self.push_asm(AbstractASM::STORE(current_divisor));

                    self.push_asm(AbstractASM::SUB(l));
                    self.push_asm(AbstractASM::JPOS(7));
                    self.push_asm(AbstractASM::LOAD(l));
                    self.push_asm(AbstractASM::SUB(current_divisor));
                    self.push_asm(AbstractASM::STORE(l));

                    self.push_asm(AbstractASM::LOAD(quotient));
                    self.push_asm(AbstractASM::ADD(current_multiple));
                    self.push_asm(AbstractASM::STORE(quotient));
                    self.push_asm(AbstractASM::JUMP(-17));
                    self.push_asm(AbstractASM::LOAD(l));
                    self.store_to_identifier(identifier);
                    self.last_mem_slot += 6;
                }
            }
        } else {
            unreachable!();
        }
    }

    fn generate_command(&mut self, command: &Command) {
        match command {
            Command::Assignment {
                identifier: _,
                expression: _,
                location: _,
            } => self.generate_expression(command),
            Command::Read(identifier) => {
                self.push_asm(AbstractASM::GET(0));
                self.store_to_identifier(identifier);
            }
            Command::If {
                condition,
                then_commands,
                location,
            } => {
                let jump_instruction = self.generate_condition(condition);
                let jump_pos = self.assembly_code.len();
                self.push_asm(jump_instruction);
                let then_start = self.assembly_code.len() as i64;
                for cmd in then_commands {
                    self.generate_command(cmd);
                }
                let then_end = self.assembly_code.len() as i64;

                if let Some(instruction) = self.assembly_code.get_mut(jump_pos) {
                    match instruction {
                        AbstractASM::JZERO(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        AbstractASM::JPOS(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        AbstractASM::JNEG(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        AbstractASM::JUMP(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        _ => {}
                    }
                }
            }
            Command::IfElse {
                condition,
                then_commands,
                else_commands,
                location,
            } => {
                let jump_instruction = self.generate_condition(condition);
                let jump_pos = self.assembly_code.len();
                self.push_asm(jump_instruction);
                let then_start = self.assembly_code.len() as i64;
                for cmd in then_commands {
                    self.generate_command(cmd);
                }
                self.push_asm(AbstractASM::JUMP(0));
                let then_end = self.assembly_code.len() as i64;

                let else_start = self.assembly_code.len() as i64;
                for cmd in else_commands {
                    self.generate_command(cmd);
                }
                let else_end = self.assembly_code.len() as i64;

                if let Some(instruction) = self.assembly_code.get_mut(jump_pos) {
                    match instruction {
                        AbstractASM::JZERO(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        AbstractASM::JPOS(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        AbstractASM::JNEG(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        AbstractASM::JUMP(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        _ => {}
                    }
                }
                if let Some(AbstractASM::JUMP(offset)) =
                    self.assembly_code.get_mut((then_end - 1) as usize)
                {
                    *offset = (else_end - else_start + 1) as i64;
                } else {
                    panic!("FE");
                }
            }
            Command::While {
                condition,
                commands,
                location,
            } => {
                let before_condition = self.assembly_code.len() as i64;
                let jump_instruction;
                match condition {
                    Condition::Equal(_l, _r) => {
                        jump_instruction = self.generate_condition(&(condition.clone()));
                    }
                    Condition::NotEqual(_l, _r) => {
                        jump_instruction = self.generate_condition(&(condition.clone()));
                    }
                    _ => {
                        jump_instruction = self.generate_condition(&(condition.clone()));
                    }
                }
                let jump_pos = self.assembly_code.len();
                self.push_asm(jump_instruction);
                let after_condition = self.assembly_code.len() as i64;

                for cmd in commands {
                    self.generate_command(cmd);
                }

                let loop_end = self.assembly_code.len() as i64;
                self.assembly_code
                    .push(AbstractASM::JUMP(before_condition - loop_end));

                let after_loop = self.assembly_code.len() as i64;
                if let Some(instruction) = self.assembly_code.get_mut(jump_pos) {
                    match instruction {
                        AbstractASM::JZERO(offset) => {
                            *offset = after_loop - after_condition + 1;
                        }
                        AbstractASM::JPOS(offset) => {
                            *offset = after_loop - after_condition + 1;
                        }
                        AbstractASM::JNEG(offset) => {
                            *offset = after_loop - after_condition + 1;
                        }
                        AbstractASM::JUMP(offset) => {
                            *offset = after_loop - after_condition + 1;
                        }
                        _ => {}
                    }
                }
            }

            Command::Repeat {
                commands,
                condition,
                location,
            } => {
                let loop_start = self.assembly_code.len() as i64;

                for cmd in commands {
                    self.generate_command(cmd);
                }

                let jump_instruction;
                match condition {
                    Condition::Equal(_l, _r) => {
                        jump_instruction = self.generate_condition(&(condition.clone()));
                    }
                    Condition::NotEqual(_l, _r) => {
                        jump_instruction = self.generate_condition(&(condition.clone()));
                    }
                    _ => {
                        jump_instruction = self.generate_condition(&!(condition.clone()));
                    }
                }
                let jump_pos = self.assembly_code.len();
                self.push_asm(jump_instruction);
                let after_condition = self.assembly_code.len() as i64;

                if let Some(instruction) = self.assembly_code.get_mut(jump_pos) {
                    match instruction {
                        AbstractASM::JZERO(offset) => {
                            *offset = loop_start - after_condition + 1;
                        }
                        AbstractASM::JPOS(offset) => {
                            *offset = loop_start - after_condition + 1;
                        }
                        AbstractASM::JNEG(offset) => {
                            *offset = loop_start - after_condition + 1;
                        }
                        AbstractASM::JUMP(offset) => {
                            *offset = loop_start - after_condition + 1;
                        }
                        _ => {}
                    }
                }
            }
            Command::Write(value) => {
                self.generate_value(value);
                self.push_asm(AbstractASM::PUT(0));
            }
            Command::ProcedureCall {
                proc_name,
                arguments,
                location,
            } => {
                let proc_info: ProcedureInfo = self.procedures.get(proc_name).unwrap().clone();

                if proc_info.args.len() != arguments.len() {
                    self.messages.push(ErrorDetails {
                        message: format!(
                            "Procedure {} expected {} arguments, got {}.",
                            proc_name,
                            proc_info.args.len(),
                            arguments.len()
                        ),
                        location: *location,
                        severity: MessageSeverity::ERROR,
                    });

                    return;
                }

                let jump_target = proc_info.code_location as i64;
                let return_loc = self.get_variable_global_scope(&proc_name).unwrap();

                for (i, arg) in arguments.iter().enumerate() {
                    let a = self.get_variable_current_scope(&arg.name).unwrap();
                    if a.is_pointer {
                        self.push_asm(AbstractASM::LOAD(a.memory));
                        self.push_asm(AbstractASM::STORE(return_loc.memory + i + 1));
                    } else {
                        self.push_asm(AbstractASM::SET(a.memory as i64));
                        self.push_asm(AbstractASM::STORE(return_loc.memory + i + 1));
                    }

                    let arg_is_bool = *proc_info.args.get(i).unwrap();
                    if a.is_array != arg_is_bool {
                        let msg;
                        if a.is_array {
                            msg = format!("Invalid argument type, expected number got array.");
                        } else {
                            msg = format!("Invalid argument type, expected array got number.");
                        }

                        self.messages.push(ErrorDetails {
                            message: msg,
                            location: arg.location,
                            severity: MessageSeverity::ERROR,
                        });
                        return;
                    }
                    self.set_to_initialized_scoped(&arg.name);
                }

                let current_loc = self.assembly_code.len() as i64;
                let jump_dist = jump_target - current_loc - 2;
                self.push_asm(AbstractASM::SET(current_loc + 3));
                self.push_asm(AbstractASM::STORE(return_loc.memory));

                self.push_asm(AbstractASM::JUMP(jump_dist as i64));
            }
            Command::For {
                variable,
                from,
                to,
                direction,
                commands,
                location,
            } => {
                let for_iter_loc = self
                    .allocate_variable_scoped(variable.to_string(), 0, 0, false, true)
                    .unwrap_or_else(|e| {
                        self.messages.push(ErrorDetails {
                            message: e,
                            location: *location,
                            severity: MessageSeverity::ERROR,
                        });
                        return 1;
                    });

                let for_num_iters = self.last_mem_slot;
                self.last_mem_slot -= 1;

                self.generate_value(&from);
                self.push_asm(AbstractASM::STORE(for_iter_loc));

                self.generate_value(&to);
                self.push_asm(AbstractASM::STORE(for_num_iters));

                match direction {
                    ForDirection::Ascending => {
                        let loop_start = self.assembly_code.len() as i64;

                        self.push_asm(AbstractASM::LOAD(for_iter_loc));
                        self.push_asm(AbstractASM::SUB(for_num_iters));

                        let jump_instruction = AbstractASM::JPOS(0);
                        let jump_pos = self.assembly_code.len();
                        self.push_asm(jump_instruction);

                        for cmd in commands {
                            self.generate_command(cmd);
                        }

                        self.push_asm(AbstractASM::LOAD(for_iter_loc));
                        self.push_asm(AbstractASM::SET(1));
                        self.push_asm(AbstractASM::ADD(for_iter_loc));
                        self.push_asm(AbstractASM::STORE(for_iter_loc));

                        self.push_asm(AbstractASM::JUMP(
                            loop_start - self.assembly_code.len() as i64,
                        ));

                        let after_loop = self.assembly_code.len() as i64;
                        if let Some(instruction) = self.assembly_code.get_mut(jump_pos) {
                            if let AbstractASM::JPOS(offset) = instruction {
                                *offset = after_loop - jump_pos as i64; // -2 to account for LOAD SUB before jump pos
                            }
                        }
                    }
                    ForDirection::Descending => {
                        let loop_start = self.assembly_code.len() as i64;

                        self.push_asm(AbstractASM::LOAD(for_iter_loc));
                        self.push_asm(AbstractASM::SUB(for_num_iters));

                        let jump_instruction = AbstractASM::JNEG(0);
                        let jump_pos = self.assembly_code.len();
                        self.push_asm(jump_instruction);

                        for cmd in commands {
                            self.generate_command(cmd);
                        }

                        self.push_asm(AbstractASM::LOAD(for_iter_loc));
                        self.push_asm(AbstractASM::SET(1));
                        self.push_asm(AbstractASM::SUB(for_iter_loc));
                        self.push_asm(AbstractASM::STORE(for_iter_loc));

                        self.push_asm(AbstractASM::JUMP(
                            loop_start - self.assembly_code.len() as i64,
                        ));

                        let after_loop = self.assembly_code.len() as i64;
                        if let Some(instruction) = self.assembly_code.get_mut(jump_pos) {
                            if let AbstractASM::JNEG(offset) = instruction {
                                *offset = after_loop - jump_pos as i64; // -2 to account for LOAD SUB before jump pos
                            }
                        }
                    }
                }
                self.delete_variable_scoped(variable.to_string());
                self.last_mem_slot += 1;
            }
        }
    }

    fn generate_procedure(&mut self, procedure: &Procedure) {
        let return_address_location = self.allocate_procedure(procedure.name.clone());
        self.current_scope = format!("${}$", procedure.name.clone());

        let mut args_vec = vec![];

        for arg in &procedure.args {
            self.allocate_arg(arg.name.clone(), arg.is_array);
            args_vec.push(arg.is_array);
        }

        for declaration in &procedure.declarations {
            if let Some((start, end)) = declaration.array_size {
                let result = self.allocate_variable_scoped(
                    declaration.name.clone(),
                    start,
                    end,
                    false,
                    false,
                );
                if let Err(err) = result {
                    self.messages.push(ErrorDetails {
                        message: err,
                        location: declaration.location,
                        severity: MessageSeverity::ERROR,
                    });
                }
            } else {
                let result =
                    self.allocate_variable_scoped(declaration.name.clone(), 0, 0, false, false);
                if let Err(err) = result {
                    self.messages.push(ErrorDetails {
                        message: err,
                        location: declaration.location,
                        severity: MessageSeverity::ERROR,
                    });
                }
            }
        }

        let proc_start = self.assembly_code.len();
        self.procedures.insert(
            procedure.name.clone(),
            ProcedureInfo {
                code_location: proc_start,
                args: args_vec,
            },
        );

        for command in &procedure.commands {
            self.generate_command(command);
        }

        self.push_asm(AbstractASM::RTRN(return_address_location));
        self.current_scope = format!("");
    }

    pub fn generate_asm(&mut self, ast: Ast) {
        let recursive_calls = ast.detect_recursive_calls();
        if recursive_calls.len() > 0 {
            self.messages.push(ErrorDetails {
                message: format!(
                    "recursive calls are not allowed {} : {}",
                    recursive_calls[0].procedure_name,
                    recursive_calls[0].recursive_path.join(" <- ")
                ),
                location: recursive_calls[0]
                    .location
                    .unwrap_or((tree_sitter::Point::default(), tree_sitter::Point::default())),
                severity: MessageSeverity::ERROR,
            });
            return;
        }

        if ast.procedures.len() > 0 {
            self.push_asm(AbstractASM::JUMP(0));
        }

        for procedure in &ast.procedures {
            self.generate_procedure(procedure);
        }

        if ast.procedures.len() > 0 {
            let len_after_proc = self.assembly_code.len();
            let a = self.assembly_code.get_mut(0).unwrap();
            match a {
                AbstractASM::JUMP(dist) => {
                    *dist = len_after_proc as i64;
                }
                _ => {}
            }
        }

        for declaration in &ast.main_block.declarations {
            let r;
            if let Some((start, end)) = declaration.array_size {
                r = self.allocate_variable_scoped(
                    declaration.name.clone(),
                    start,
                    end,
                    false,
                    false,
                );
            } else {
                r = self.allocate_variable_scoped(declaration.name.clone(), 0, 0, false, false);
            }

            if let Err(err) = r {
                self.messages.push(ErrorDetails {
                    message: err,
                    location: declaration.location,
                    severity: MessageSeverity::ERROR,
                });
            }
        }

        for command in &ast.main_block.commands {
            self.generate_command(command);
        }

        self.push_asm(AbstractASM::HALT);
    }

    fn save_dbg_info(&self, filename: &str) -> std::io::Result<()> {
        let json = serde_json::to_string_pretty(&self.symbols)?;
        let mut file = File::create(filename)?;
        file.write_all(json.as_bytes())?;
        Ok(())
    }
}
