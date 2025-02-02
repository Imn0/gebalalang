use std::{collections::HashMap, default};

use crate::{
    ast::{
        Ast, Command, Condition, Either, Expression, ForDirection, Identifier, Location, Procedure,
        Value,
    },
    message::{DisplayMessage, Message, MessageSeverity},
    program::Program,
};

#[derive(Debug, Clone, Default)]
struct SymbolLocation {
    is_array: bool,
    is_pointer: bool,
    is_procedure: bool,
    read_only: bool,
    initialized: bool,
    left: i64,
    right: i64,
}

struct ValidateInfo {
    severity: MessageSeverity,
    message: String,
    location: Option<Location>,
}

#[derive(Clone, Debug)]
struct ProcedureInfo {
    args: Vec<bool>,
}

pub struct GeneratorValidator<'a> {
    symbols: HashMap<String, SymbolLocation>,
    procedures: HashMap<String, ProcedureInfo>,
    messages: Vec<ValidateInfo>,
    current_scope: String,
    has_warnings: bool,
    has_errors: bool,
    prog: &'a Program,
}

impl<'a> GeneratorValidator<'a> {
    pub fn new(prog: &'a Program) -> Self {
        GeneratorValidator {
            symbols: HashMap::new(),
            procedures: HashMap::new(),
            current_scope: "".to_owned(),
            has_errors: false,
            has_warnings: false,
            messages: vec![],
            prog: prog,
        }
    }

    pub fn validate(&mut self) -> Result<(), ()> {
        let werror = self.prog.config.werror;

        self.try_compile(&self.prog.ast);
        let mut info_written = false;
        for msg in &self.messages {
            match msg.severity {
                MessageSeverity::DEBUG | MessageSeverity::INFO => {
                    if let Some(loc) = msg.location {
                        self.prog.print_message(Message::CodeMessage {
                            severity: msg.severity.clone(),
                            message: &msg.message,
                            location: loc,
                        });
                    } else {
                        self.prog.print_message(Message::GeneralMessage {
                            severity: msg.severity.clone(),
                            message: &msg.message,
                        });
                    }
                }
                MessageSeverity::WARNING => {
                    let severity = if werror {
                        self.has_errors = true;
                        MessageSeverity::ERROR
                    } else {
                        self.has_warnings = true;
                        MessageSeverity::WARNING
                    };

                    if let Some(loc) = msg.location {
                        self.prog.print_message(Message::CodeMessage {
                            severity: severity,
                            message: &msg.message,
                            location: loc,
                        });
                    } else {
                        self.prog.print_message(Message::GeneralMessage {
                            severity: severity,
                            message: &msg.message,
                        });
                    }

                    if werror && !info_written {
                        self.prog.print_message(Message::GeneralMessage {
                            severity: MessageSeverity::INFO,
                            message: "to make this error go away use flag --unsafe",
                        });
                        info_written = true;
                    }
                }
                MessageSeverity::ERROR | MessageSeverity::FATAL => {
                    if let Some(loc) = msg.location {
                        self.prog.print_message(Message::CodeMessage {
                            severity: msg.severity.clone(),
                            message: &msg.message,
                            location: loc,
                        });
                    } else {
                        self.prog.print_message(Message::GeneralMessage {
                            severity: msg.severity.clone(),
                            message: &msg.message,
                        });
                    }
                    self.has_errors = true;
                }
            }
        }

        if self.has_errors {
            return Err(());
        }
        Ok(())
    }

    fn try_compile(&mut self, ast: &Ast) {
        let mut procs: Vec<Procedure> = ast.procedures.clone().into_values().collect();
        procs.sort_by(|a, b| a.prio.cmp(&b.prio));

        for procedure in &procs {
            self.generate_procedure(procedure);
        }

        self.current_scope = "".to_owned();
        for declaration in &ast.main_block.declarations {
            let r;
            if let Some((start, end)) = declaration.array_size {
                r = self.allocate_variable(declaration.name.clone(), start, end, false, false);
            } else {
                r = self.allocate_variable(declaration.name.clone(), 0, 0, false, false);
            }

            if let Err(err) = r {
                self.add_message(ValidateInfo {
                    severity: MessageSeverity::ERROR,
                    message: err,
                    location: Some(declaration.location.clone()),
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

    fn get_variable_w_idx(&mut self, name: &str, idx: i64) -> Result<(), String> {
        let scoped_name = self.current_scope.clone() + name;
        let loc = self.symbols.get(&scoped_name).unwrap().clone();

        if idx < loc.left {
            return Err(format!("out of bound access"));
        }

        if loc.right < idx {
            return Err(format!("out of bound access"));
        }

        return Ok(());
    }

    fn get_variable_current_scope(&self, name: &str) -> Result<SymbolLocation, String> {
        let scoped_name = self.current_scope.clone() + name;
        if let Some(loc) = self.symbols.get(&scoped_name) {
            return Ok(loc.clone());
        } else {
            return Err(format!("'{}' not declared in this scope", name));
        }
    }

    fn set_to_initialized_scoped(&mut self, name: &str) {
        let scoped_name = self.current_scope.clone() + name;
        if let Some(loc) = self.symbols.get_mut(&scoped_name) {
            loc.initialized = true;
        }
    }

    fn allocate_procedure(&mut self, proc_name: &str) {
        self.symbols.insert(
            proc_name.to_owned(),
            SymbolLocation {
                is_array: false,
                is_pointer: false,
                is_procedure: true,
                read_only: true,
                initialized: true,
                left: 0,
                right: 0,
            },
        );
    }

    fn allocate_arg(&mut self, name: &str, is_array: bool) -> Result<(), String> {
        let scoped_name = self.current_scope.clone() + &name;

        self.symbols.insert(
            scoped_name,
            SymbolLocation {
                is_array,
                is_pointer: true,
                is_procedure: false,
                read_only: false,
                initialized: true,
                left: 0,
                right: 0,
            },
        );
        Ok(())
    }

    fn delete_variable(&mut self, name: &str) {
        let scoped_name = self.current_scope.clone() + name;
        self.symbols.remove(&scoped_name);
    }

    fn allocate_variable(
        &mut self,
        name: String,
        left: i64,
        right: i64,
        is_pointer: bool,
        read_only: bool,
    ) -> Result<(), String> {
        let scoped_name = self.current_scope.clone() + &name;
        if self.symbols.contains_key(&scoped_name) {
            return Err(format!("'{}' already declared in this scope", name));
        }

        if left == 0 && right == 0 {
            self.symbols.insert(
                scoped_name,
                SymbolLocation {
                    is_array: false,
                    is_pointer,
                    is_procedure: false,
                    read_only,
                    initialized: false,
                    left: 0,
                    right: 0,
                },
            );
            return Ok(());
        }

        if left > right {
            return Err(format!(
                "cant allocate array with dimensions {}:{}",
                left, right
            ));
        }

        self.symbols.insert(
            scoped_name,
            SymbolLocation {
                is_array: true,
                is_pointer,
                is_procedure: false,
                read_only: read_only,
                initialized: false,
                left,
                right,
            },
        );
        return Ok(());
    }

    fn produce_value(&mut self, value: &Value) {
        match value {
            Value::Number(_) => {}
            Value::Identifier(ident) => {
                let result = self.get_variable_current_scope(&ident.name);
                match result {
                    Ok(loc) => {
                        if !loc.initialized {
                            self.add_message(ValidateInfo {
                                message: format!(
                                    "usage of not initialized variable '{}'",
                                    ident.name
                                ),
                                location: Some(ident.location.clone()),
                                severity: MessageSeverity::WARNING,
                            });
                        }
                    }
                    Err(err) => {
                        self.add_message(ValidateInfo {
                            message: err,
                            location: Some(ident.location.clone()),
                            severity: MessageSeverity::ERROR,
                        });
                        return;
                    }
                }

                if let Some(idx) = &ident.index {
                    match idx {
                        // a[b]
                        Either::Left(idx_name) => {
                            let base_loc;
                            if let Ok(_base_loc) = self.get_variable_current_scope(&ident.name) {
                                base_loc = _base_loc;
                            } else {
                                self.add_message(ValidateInfo {
                                    message: format!("'{}' not declared in this scope", ident.name),
                                    location: Some(ident.location.clone()),
                                    severity: MessageSeverity::ERROR,
                                });
                                return;
                            }

                            if !base_loc.is_array {
                                self.add_message(ValidateInfo {
                                    message: "cannot number with an index".to_owned(),
                                    location: Some(ident.location.clone()),
                                    severity: MessageSeverity::WARNING,
                                });
                                self.add_message(ValidateInfo {
                                    severity: MessageSeverity::INFO,
                                    message: format!("try '{}' instead", ident.name),
                                    location: None,
                                });
                            }

                            let idx_loc;
                            if let Ok(_idx_loc) = self.get_variable_current_scope(idx_name) {
                                idx_loc = _idx_loc;
                            } else {
                                self.add_message(ValidateInfo {
                                    message: format!("'{}' not declared in this scope", idx_name),
                                    location: Some(ident.location.clone()),
                                    severity: MessageSeverity::ERROR,
                                });
                                return;
                            }

                            if idx_loc.is_array {
                                self.add_message(ValidateInfo {
                                    message: format!(
                                        "cannot array {} without an index",
                                        ident.name
                                    ),
                                    location: Some(ident.location.clone()),
                                    severity: MessageSeverity::WARNING,
                                });
                                self.add_message(ValidateInfo {
                                    severity: MessageSeverity::INFO,
                                    message: format!("try '{}[<number>]' instead", ident.name),
                                    location: None,
                                });
                            }
                            if !idx_loc.initialized {
                                self.add_message(ValidateInfo {
                                    message: format!(
                                        "usage of not initialized variable '{}'",
                                        idx_name,
                                    ),
                                    location: Some(ident.location.clone()),
                                    severity: MessageSeverity::WARNING,
                                });
                            }
                        }
                        // a[12]
                        Either::Right(_) => {
                            let symbol_loc = self.get_variable_current_scope(&ident.name).unwrap();
                            if !symbol_loc.is_array {
                                self.add_message(ValidateInfo {
                                    message: "cannot access it like that".to_owned(),
                                    location: Some(ident.location.clone()),
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
                                message: format!("cannot access '{}' without an index", ident.name),
                                location: Some(ident.location.clone()),
                                severity: MessageSeverity::WARNING,
                            });
                        }
                    } else if let Err(e) = result {
                        self.add_message(ValidateInfo {
                            message: e,
                            location: Some(ident.location.clone()),
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
                    location: Some(ident.location.clone()),
                    severity: MessageSeverity::ERROR,
                });
                return;
            }
        }

        if dst_loc.read_only {
            if dst_loc.is_procedure {
                self.add_message(ValidateInfo {
                    message: format!("'{}' is already procedure", ident.name),
                    location: Some(ident.location.clone()),
                    severity: MessageSeverity::ERROR,
                });
            } else {
                self.add_message(ValidateInfo {
                    message: format!("for iterators are read only"),
                    location: Some(ident.location.clone()),
                    severity: MessageSeverity::ERROR,
                });
            }
            return;
        }

        self.set_to_initialized_scoped(&ident.name);

        if let Some(dest_idx) = &ident.index {
            match dest_idx {
                Either::Left(idx_name) => {
                    if !dst_loc.is_array {
                        self.add_message(ValidateInfo {
                            message: format!("cannot access number with an index"),
                            location: Some(ident.location.clone()),
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
                                location: Some(ident.location.clone()),
                                severity: MessageSeverity::ERROR,
                            });
                            return;
                        }
                    }
                    if idx_loc.is_array {
                        self.add_message(ValidateInfo {
                            message: format!("cannot index array with another array"),
                            location: Some(ident.location.clone()),
                            severity: MessageSeverity::WARNING,
                        });
                    }
                    if !idx_loc.initialized {
                        self.add_message(ValidateInfo {
                            message: format!("'{}' not initialized", idx_name),
                            location: Some(ident.location.clone()),
                            severity: MessageSeverity::WARNING,
                        });
                    }
                }
                Either::Right(idx_num) => {
                    let dest_loc = self.get_variable_current_scope(&ident.name).unwrap();
                    if !dest_loc.is_array {
                        self.add_message(ValidateInfo {
                            message: format!("cannot access number with an index "),
                            location: Some(ident.location.clone()),
                            severity: MessageSeverity::WARNING,
                        });
                    }
                    if !dest_loc.is_pointer {
                        self.get_variable_w_idx(&ident.name, *idx_num)
                            .unwrap_or_else(|e| {
                                self.add_message(ValidateInfo {
                                    message: e,
                                    location: Some(ident.location.clone()),
                                    severity: MessageSeverity::ERROR,
                                });
                                return;
                            });
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
                    location: Some(ident.location.clone()),
                    severity: MessageSeverity::ERROR,
                });
                return;
            } else {
                unreachable!();
            }
            if dest_loc.is_array {
                self.add_message(ValidateInfo {
                    message: format!("cannot access '{}' without an index", ident.name),
                    location: Some(ident.location.clone()),
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
                self.produce_value(left);
                self.produce_value(right);
            }
        }
    }

    fn generate_expression(&mut self, command: &Command) {
        if let Command::Assignment {
            identifier,
            expression,
            location: _,
        } = command
        {
            match expression {
                Expression::Value(value) => {
                    self.produce_value(value);
                    self.store_to_identifier(identifier);
                }
                Expression::Addition(left, right)
                | Expression::Division(left, right)
                | Expression::Multiplication(left, right)
                | Expression::Modulo(left, right)
                | Expression::Subtraction(left, right) => {
                    self.produce_value(left);
                    self.produce_value(right);
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
            Command::Write(value) => {
                self.produce_value(value);
            }
            Command::If {
                condition,
                then_commands,
                location: _,
            } => {
                let _jump_instruction = self.generate_condition(condition);
                for cmd in then_commands {
                    self.generate_command(cmd);
                }
            }
            Command::IfElse {
                condition,
                then_commands,
                else_commands,
                location: _,
            } => {
                let _jump_instruction = self.generate_condition(condition);
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
                location: _,
            } => {
                self.generate_condition(condition);
                for cmd in commands {
                    self.generate_command(cmd);
                }
            }
            Command::Repeat {
                commands,
                condition,
                location: _,
            } => {
                for cmd in commands {
                    self.generate_command(cmd);
                }
                self.generate_condition(condition);
            }
            Command::For {
                variable,
                from,
                to,
                direction,
                commands,
                location,
            } => {
                let _for_iter_loc = self
                    .allocate_variable(variable.to_string(), 0, 0, false, true)
                    .unwrap_or_else(|e| {
                        self.add_message(ValidateInfo {
                            message: e,
                            location: Some(location.clone()),
                            severity: MessageSeverity::ERROR,
                        });
                        return;
                    });

                let ff = self
                    .symbols
                    .get_mut(&format!("{}{}", self.current_scope.clone(), variable))
                    .unwrap();
                ff.initialized = true;

                self.produce_value(&from);
                self.produce_value(&to);

                match direction {
                    ForDirection::Ascending | ForDirection::Descending => {
                        for cmd in commands {
                            self.generate_command(cmd);
                        }
                    }
                }
                self.delete_variable(variable);
            }
            Command::ProcedureCall {
                proc_name,
                arguments,
                location,
            } => {
                let proc_info = if let Some(proc_info) = self.procedures.get(proc_name).cloned() {
                    proc_info
                } else {
                    self.add_message(ValidateInfo {
                        severity: MessageSeverity::ERROR,
                        message: format!("procedure '{}' not declared", proc_name),
                        location: Some(location.clone()),
                    });

                    if self.prog.ast.procedures.contains_key(proc_name) {
                        self.add_message(ValidateInfo {
                            severity: MessageSeverity::INFO,
                            message: format!("procedures need to be forward declared"),
                            location: None,
                        });
                    }

                    return;
                };

                if proc_info.args.len() != arguments.len() {
                    self.add_message(ValidateInfo {
                        message: format!(
                            "procedure {} expected {} arguments, got {}",
                            proc_name,
                            proc_info.args.len(),
                            arguments.len()
                        ),
                        location: Some(location.clone()),
                        severity: MessageSeverity::ERROR,
                    });

                    return;
                }

                for (i, arg) in arguments.iter().enumerate() {
                    let a = self
                        .get_variable_current_scope(&arg.name)
                        .unwrap_or_else(|e| {
                            self.add_message(ValidateInfo {
                                message: e,
                                location: Some(arg.location.clone()),
                                severity: MessageSeverity::ERROR,
                            });
                            SymbolLocation::default()
                        });

                    let arg_is_bool = *proc_info.args.get(i).unwrap();
                    if a.is_array != arg_is_bool {
                        let msg;
                        if a.is_array {
                            msg = format!("expected number got array");
                        } else {
                            msg = format!("expected array got number");
                        }

                        self.add_message(ValidateInfo {
                            message: msg,
                            location: Some(arg.location.clone()),
                            severity: MessageSeverity::ERROR,
                        });
                        return;
                    }
                    self.set_to_initialized_scoped(&arg.name);
                }
            }
        }
    }

    fn generate_procedure(&mut self, procedure: &Procedure) {
        self.allocate_procedure(&procedure.name);

        self.current_scope = format!("{}::", procedure.name.clone());

        let mut args_vec = vec![];
        self.procedures
            .insert(procedure.name.clone(), ProcedureInfo { args: vec![] });

        for arg in &procedure.args {
            if let Err(err) = self.allocate_arg(&arg.name, arg.is_array) {
                self.add_message(ValidateInfo {
                    message: err,
                    location: Some(procedure.location.clone()),
                    severity: MessageSeverity::ERROR,
                });
            }
            args_vec.push(arg.is_array);
        }

        for declaration in &procedure.declarations {
            if let Some((start, end)) = declaration.array_size {
                let result =
                    self.allocate_variable(declaration.name.clone(), start, end, false, false);
                if let Err(err) = result {
                    self.add_message(ValidateInfo {
                        message: err,
                        location: Some(declaration.location.clone()),
                        severity: MessageSeverity::ERROR,
                    });
                }
            } else {
                let result = self.allocate_variable(declaration.name.clone(), 0, 0, false, false);
                if let Err(err) = result {
                    self.add_message(ValidateInfo {
                        message: err,
                        location: Some(declaration.location.clone()),
                        severity: MessageSeverity::ERROR,
                    });
                }
            }
        }

        self.procedures
            .insert(procedure.name.clone(), ProcedureInfo { args: args_vec });

        for command in &procedure.commands {
            self.generate_command(command);
        }
    }
}
