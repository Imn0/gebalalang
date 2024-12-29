use std::{collections::HashMap, fs::File, io::Write};

use crate::{
    ast::{
        Ast, Command, Condition, Either, Expression, ForDirection, Identifier, Location, Procedure,
        Value,
    },
    message::{DisplayMessage, Message, MessageSeverity},
    program::Program,
};

#[derive(Debug, Clone)]
struct SymbolLocation {
    memory: usize,
    is_array: bool,
    is_pointer: bool,
    is_procedure: bool,
    read_only: bool,
    initialized: bool,
}

struct ValidateInfo {
    severity: MessageSeverity,
    message: String,
    location: Location,
}

#[derive(Clone)]
struct ProcedureInfo {
    code_location: usize,
    args: Vec<bool>,
}

pub struct GeneratorValidator {
    symbols: HashMap<String, SymbolLocation>,
    procedures: HashMap<String, ProcedureInfo>,
    messages: Vec<ValidateInfo>,
    next_memory_slot: usize,
    last_mem_slot: usize,
    current_scope: String,
    has_warnings: bool,
    has_errors: bool,
}

impl GeneratorValidator {
    pub fn new() -> Self {
        GeneratorValidator {
            symbols: HashMap::new(),
            procedures: HashMap::new(),
            next_memory_slot: 13213,
            last_mem_slot: 0x4000000000000000,
            current_scope: "".to_owned(),
            has_errors: false,
            has_warnings: false,
            messages: vec![],
        }
    }

    pub fn validate(&mut self, prog: &Program) -> Result<(), ()> {
        let werror = prog.config.werror;

        self.generate_asm(&prog.ast);

        for msg in &self.messages {
            match msg.severity {
                MessageSeverity::DEBUG | MessageSeverity::INFO => {
                    prog.print_message(Message::CodeMessage {
                        severity: msg.severity.clone(),
                        message: &msg.message,
                        location: msg.location.clone(),
                    });
                }
                MessageSeverity::WARNING => {
                    let severity = if werror {
                        self.has_errors = true;
                        MessageSeverity::ERROR
                    } else {
                        self.has_warnings = true;
                        MessageSeverity::WARNING
                    };

                    prog.print_message(Message::CodeMessage {
                        severity: severity,
                        message: &msg.message,
                        location: msg.location.clone(),
                    });

                    if werror {
                        prog.print_message(Message::GeneralMessage {
                            severity: MessageSeverity::INFO,
                            message: "to make this error go away use flag --unsafe",
                        });
                    }
                }
                MessageSeverity::ERROR | MessageSeverity::FATAL => {
                    prog.print_message(Message::CodeMessage {
                        severity: msg.severity.clone(),
                        message: &msg.message,
                        location: msg.location.clone(),
                    });
                    self.has_errors = true;
                }
            }
        }

        if self.has_errors {
            return Err(());
        }
        Ok(())
    }

    fn generate_asm(&mut self, ast: &Ast) {
        for (_, procedure) in &ast.procedures {
            self.generate_procedure(procedure);
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
                self.add_message(ValidateInfo {
                    severity: MessageSeverity::ERROR,
                    message: err,
                    location: declaration.location.clone(),
                });
            }
        }

        for command in &ast.main_block.commands {
            self.generate_command(command);
        }
    }

    fn add_message(&mut self, msg: ValidateInfo) {
        self.messages.push(msg);
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
            Value::Number(num) => {}
            Value::Identifier(ident) => {
                let result = self.get_variable_current_scope(&ident.name);
                match result {
                    Ok(loc) => {
                        if !loc.initialized {
                            self.add_message(ValidateInfo {
                                message: format!(
                                    "Usage of not initialized variable {}.",
                                    ident.name
                                ),
                                location: ident.location.clone(),
                                severity: MessageSeverity::WARNING,
                            });
                        }
                    }
                    Err(err) => {
                        self.add_message(ValidateInfo {
                            message: err,
                            location: ident.location.clone(),
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
                                self.add_message(ValidateInfo {
                                    message: format!("Unknown variable {}.", ident.name),
                                    location: ident.location.clone(),
                                    severity: MessageSeverity::ERROR,
                                });
                                return;
                            }

                            if !base_loc.is_array {
                                self.add_message(ValidateInfo {
                                    message: "cannot access it like that".to_owned(),
                                    location: ident.location.clone(),
                                    severity: MessageSeverity::WARNING,
                                });
                            }
                            let idx_loc;
                            if let Ok(_idx_loc) = self.get_variable_current_scope(idx_name) {
                                idx_loc = _idx_loc;
                            } else {
                                self.add_message(ValidateInfo {
                                    message: format!("unknown variable {}.", idx_name),
                                    location: ident.location.clone(),
                                    severity: MessageSeverity::ERROR,
                                });
                                return;
                            }

                            if idx_loc.is_array {
                                self.add_message(ValidateInfo {
                                    message: format!("cannot access {} like that.", ident.name),
                                    location: ident.location.clone(),
                                    severity: MessageSeverity::WARNING,
                                });
                            }
                            if !idx_loc.initialized {
                                self.add_message(ValidateInfo {
                                    message: format!(
                                        "Usage of not initialized variable {}",
                                        idx_name,
                                    ),
                                    location: ident.location.clone(),
                                    severity: MessageSeverity::WARNING,
                                });
                            }
                        }
                        Either::Right(idx_num) => {
                            let symbol_loc = self.get_variable_current_scope(&ident.name).unwrap();
                            if !symbol_loc.is_array {
                                self.add_message(ValidateInfo {
                                    message: "cannot access it like that".to_owned(),
                                    location: ident.location.clone(),
                                    severity: MessageSeverity::WARNING,
                                });
                            }
                        }
                    }
                } else {
                    let result = self.get_variable_current_scope(&ident.name);
                    if let Ok(loc) = result {
                        if loc.is_array {
                            self.add_message(ValidateInfo {
                                message: "cannot access it like that way".to_owned(),
                                location: ident.location.clone(),
                                severity: MessageSeverity::WARNING,
                            });
                        }
                    } else if let Err(e) = result {
                        self.add_message(ValidateInfo {
                            message: e,
                            location: ident.location.clone(),
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
                self.add_message(ValidateInfo {
                    message: err,
                    location: ident.location.clone(),
                    severity: MessageSeverity::ERROR,
                });
                return;
            }
        }

        if dst_loc.read_only {
            self.add_message(ValidateInfo {
                message: format!("Variable {} is read only.", ident.name),
                location: ident.location.clone(),
                severity: MessageSeverity::ERROR,
            });
            return;
        }

        self.set_to_initialized_scoped(&ident.name);

        if let Some(dest_idx) = &ident.index {
            match dest_idx {
                Either::Left(idx_name) => {
                    if !dst_loc.is_array {
                        self.add_message(ValidateInfo {
                            message: format!("Cannot access {} it like that", ident.name),
                            location: ident.location.clone(),
                            severity: MessageSeverity::WARNING,
                        });
                    }
                    let result = self.get_variable_current_scope(idx_name);
                    let idx_loc;
                    match result {
                        Ok(_r) => idx_loc = _r,
                        Err(err) => {
                            self.add_message(ValidateInfo {
                                message: err,
                                location: ident.location.clone(),
                                severity: MessageSeverity::ERROR,
                            });
                            return;
                        }
                    }

                    if idx_loc.is_array {
                        self.add_message(ValidateInfo {
                            message: format!("Cannot access {} it like that", idx_name),
                            location: ident.location.clone(),
                            severity: MessageSeverity::WARNING,
                        });
                    }

                    if !idx_loc.initialized {
                        self.add_message(ValidateInfo {
                            message: format!("Variable {} not initialized", idx_name),
                            location: ident.location.clone(),
                            severity: MessageSeverity::WARNING,
                        });
                    }
                }
                Either::Right(idx_num) => {
                    let dest_loc = self.get_variable_current_scope(&ident.name).unwrap();
                    if !dest_loc.is_array {
                        self.add_message(ValidateInfo {
                            message: "cannot access it like that".to_owned(),
                            location: ident.location.clone(),
                            severity: MessageSeverity::WARNING,
                        });
                    }
                    if !dest_loc.is_pointer {
                        let final_loc = self.get_variable_w_idx(&ident.name, *idx_num);
                    }
                }
            }
        } else {
            let result = self.get_variable_current_scope(&ident.name);
            let dest_loc;
            if let Ok(_d) = result {
                dest_loc = _d;
            } else if let Err(err) = result {
                self.add_message(ValidateInfo {
                    message: err,
                    location: ident.location.clone(),
                    severity: MessageSeverity::ERROR,
                });
                return;
            } else {
                unreachable!();
            }
            if dest_loc.is_array {
                self.add_message(ValidateInfo {
                    message: "cannot access it like that".to_owned(),
                    location: ident.location.clone(),
                    severity: MessageSeverity::WARNING,
                });
            }
        }
    }

    fn generate_condition(&mut self, condition: &Condition) {
        match condition {
            Condition::NotEqual(left, right)
            | Condition::Equal(left, right)
            | Condition::LessOrEqual(left, right)
            | Condition::GreaterOrEqual(left, right)
            | Condition::LessThan(left, right)
            | Condition::GreaterThan(left, right) => {
                self.generate_value(left);
                self.generate_value(right);
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
                    self.generate_value(right);
                    self.store_to_identifier(identifier);
                }
                Expression::Subtraction(left, right) => {
                    self.generate_value(right);
                    self.generate_value(left);
                    self.store_to_identifier(identifier);
                }
                Expression::Division(left, right) => {
                    self.generate_value(left);

                    match right {
                        Value::Number(val) => {
                            if val.clone() == 2 {
                                self.store_to_identifier(identifier);
                                return;
                            }
                        }
                        _ => {}
                    }

                    self.generate_value(left);
                    self.generate_value(right);
                    self.store_to_identifier(identifier);
                }
                Expression::Multiplication(left, right) => {
                    self.generate_value(left);

                    match right {
                        Value::Number(val) => {
                            if val.clone() == 2 {
                                self.store_to_identifier(identifier);
                                return;
                            }
                        }
                        _ => {}
                    }
                    self.generate_value(right);
                    self.generate_value(left);
                    self.store_to_identifier(identifier);
                }
                Expression::Modulo(left, right) => {
                    match right {
                        Value::Number(val) => {
                            if val.clone() == 2 {
                                self.generate_value(left);
                                self.store_to_identifier(identifier);
                            }
                        }
                        _ => {}
                    }

                    self.generate_value(left);

                    self.store_to_identifier(identifier);
                }
                Expression::TimesPowerTwo(value, _) => {
                    self.generate_value(value);
                    self.store_to_identifier(identifier);
                }
                Expression::HalfTimes(value, _) => {
                    self.generate_value(value);
                    self.store_to_identifier(identifier);
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
                self.store_to_identifier(identifier);
            }
            Command::If {
                condition,
                then_commands,
                location,
            } => {
                let jump_instruction = self.generate_condition(condition);
                for cmd in then_commands {
                    self.generate_command(cmd);
                }
            }
            Command::NoOp => {}
            Command::IfElse {
                condition,
                then_commands,
                else_commands,
                location,
            } => {
                let jump_instruction = self.generate_condition(condition);
                for cmd in then_commands {
                    self.generate_command(cmd);
                }
                for cmd in else_commands {
                    self.generate_command(cmd);
                }
            }
            Command::While {
                condition,
                commands,
                location,
            } => {
                self.generate_condition(&(condition.clone()));
                for cmd in commands {
                    self.generate_command(cmd);
                }
            }

            Command::Repeat {
                commands,
                condition,
                location,
            } => {
                for cmd in commands {
                    self.generate_command(cmd);
                }

                match condition {
                    Condition::Equal(_l, _r) => {
                        self.generate_condition(&(condition.clone()));
                    }
                    Condition::NotEqual(_l, _r) => {
                        self.generate_condition(&(condition.clone()));
                    }
                    _ => {
                        self.generate_condition(&!(condition.clone()));
                    }
                }
            }
            Command::Write(value) => {
                self.generate_value(value);
            }
            Command::ProcedureCall {
                proc_name,
                arguments,
                location,
            } => {
                let proc_info: ProcedureInfo = self.procedures.get(proc_name).unwrap().clone();

                if proc_info.args.len() != arguments.len() {
                    self.add_message(ValidateInfo {
                        message: format!(
                            "Procedure {} expected {} arguments, got {}.",
                            proc_name,
                            proc_info.args.len(),
                            arguments.len()
                        ),
                        location: location.clone(),
                        severity: MessageSeverity::ERROR,
                    });

                    return;
                }

                let jump_target = proc_info.code_location as i64;
                let return_loc = self.get_variable_global_scope(&proc_name).unwrap();

                for (i, arg) in arguments.iter().enumerate() {
                    let a = self.get_variable_current_scope(&arg.name).unwrap();

                    let arg_is_bool = *proc_info.args.get(i).unwrap();
                    if a.is_array != arg_is_bool {
                        let msg;
                        if a.is_array {
                            msg = format!("Invalid argument type, expected number got array.");
                        } else {
                            msg = format!("Invalid argument type, expected array got number.");
                        }

                        self.add_message(ValidateInfo {
                            message: msg,
                            location: arg.location.clone(),
                            severity: MessageSeverity::ERROR,
                        });
                        return;
                    }
                    self.set_to_initialized_scoped(&arg.name);
                }
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
                        self.add_message(ValidateInfo {
                            message: e,
                            location: location.clone(),
                            severity: MessageSeverity::ERROR,
                        });
                        return 1;
                    });

                let for_num_iters = self.last_mem_slot;
                self.last_mem_slot -= 1;

                self.generate_value(&from);

                self.generate_value(&to);

                match direction {
                    ForDirection::Ascending => {
                        for cmd in commands {
                            self.generate_command(cmd);
                        }
                    }
                    ForDirection::Descending => {
                        for cmd in commands {
                            self.generate_command(cmd);
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
                    self.add_message(ValidateInfo {
                        message: err,
                        location: declaration.location.clone(),
                        severity: MessageSeverity::ERROR,
                    });
                }
            } else {
                let result =
                    self.allocate_variable_scoped(declaration.name.clone(), 0, 0, false, false);
                if let Err(err) = result {
                    self.add_message(ValidateInfo {
                        message: err,
                        location: declaration.location.clone(),
                        severity: MessageSeverity::ERROR,
                    });
                }
            }
        }

        self.procedures.insert(
            procedure.name.clone(),
            ProcedureInfo {
                code_location: 0,
                args: args_vec,
            },
        );

        for command in &procedure.commands {
            self.generate_command(command);
        }

        self.current_scope = format!("");
    }
}
