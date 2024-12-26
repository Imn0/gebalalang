use std::collections::HashMap;

use tree_sitter::Point;

use crate::{
    ast::ast::{
        Command, Condition, Declaration, Either, Expression, ForDirection, Identifier, MainBlock,
        ProcArgument, Procedure, Value,
    },
    ir::{LabelIdx, IR},
    ErrorDetails, MessageSeverity,
};

use super::super::ast::ast::Ast;

use super::memory::{Memory, SymbolLocation};

const MIN_CONST_USAGE: i64 = 1;

#[derive(Clone)]
pub struct ProcedureInfo {
    pub label: usize,
    pub return_address: usize,
    pub args: Vec<SymbolLocation>,
}

#[derive(Debug)]
struct ConstInfo {
    pub num_used: i64,
    pub val: i64,
    pub location: usize,
}

pub struct CodeGenerator {
    pub messages: Vec<ErrorDetails>,
    pub assembly_code: Vec<IR>,
    memory: Memory,
    constants: HashMap<i64, ConstInfo>,
    procedures: HashMap<String, ProcedureInfo>,
    next_label: usize,
    last_mem_slot: usize,
    current_scope: String,
}

impl CodeGenerator {
    pub fn new() -> Self {
        CodeGenerator {
            memory: Memory::new(),
            constants: HashMap::new(),
            procedures: HashMap::new(),
            last_mem_slot: 0x4000000000000000,
            assembly_code: Vec::new(),
            messages: Vec::new(),
            current_scope: "".to_owned(),
            next_label: 0,
        }
    }

    pub fn generate_asm(&mut self, ast: Ast) {
        let mut main_jump = false;

        if ast.flags.has_div || ast.flags.has_mod || ast.flags.has_mul || ast.procedures.len() > 0 {
            main_jump = true;
        }

        let mut main_lbl = 0;
        if main_jump {
            main_lbl = self.next_label;
            self.next_label += 1;
            self.push_asm(IR::lbl_jump(LabelIdx(main_lbl)));
        }

        if ast.flags.has_mul {
            self.compile_mul_procedure();
        }

        if ast.flags.has_div || ast.flags.has_mod {
            self.compile_mod_div_procedure();
        }

        if ast.procedures.len() > 0 {
            for proc in &ast.procedures {
                self.compile_procedure(proc);
            }
        }

        if main_jump {
            self.push_asm(IR::LABEL {
                idx: LabelIdx(main_lbl),
                name: format!("MAIN"),
            });
        }

        self.compile_main(&ast.main_block);
        self.push_asm(IR::HALT);

        let mut cc = self.fill_in_constants();

        cc.extend(self.assembly_code.clone());
        self.assembly_code = cc;

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

    fn push_label(&mut self) -> LabelIdx {
        let lbl = self.next_label;
        self.push_asm(IR::LABEL {
            idx: LabelIdx(lbl),
            name: "".to_owned(),
        });
        self.next_label += 1;
        return LabelIdx(lbl);
    }

    fn push_label_name(&mut self, name: &String) -> usize {
        let lbl = self.next_label;
        self.push_asm(IR::LABEL {
            idx: LabelIdx(lbl),
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
            Command::HasEffect(_) => {}
            Command::Assignment {
                identifier,
                expression,
                location,
            } => {
                self.compile_expression(identifier, expression, *location);
            }
            Command::If {
                condition,
                then_commands,
                location,
            } => {
                let label_idx = LabelIdx(self.next_label);
                self.next_label += 1;
                self.compile_condition(condition, label_idx.clone());
                self.compile_commands(then_commands);
                self.push_asm(IR::LABEL {
                    idx: label_idx,
                    name: format!(""),
                });
            }
            Command::IfElse {
                condition,
                then_commands,
                else_commands,
                location,
            } => {
                let cond_fail_lbl = LabelIdx(self.next_label);
                self.next_label += 1;

                let skip_else_cmds = LabelIdx(self.next_label);
                self.next_label += 1;

                self.compile_condition(condition, cond_fail_lbl.clone());
                self.compile_commands(then_commands);
                self.push_asm(IR::lbl_jump(skip_else_cmds.clone()));

                self.push_asm(IR::LABEL {
                    idx: cond_fail_lbl,
                    name: format!(""),
                });
                self.compile_commands(else_commands);
                self.push_asm(IR::LABEL {
                    idx: skip_else_cmds,
                    name: format!(""),
                });
            }
            Command::While {
                condition,
                commands,
                location,
            } => {
                let cond_start = LabelIdx(self.next_label);
                self.next_label += 1;

                let while_after = LabelIdx(self.next_label);
                self.next_label += 1;
                self.push_asm(IR::LABEL {
                    idx: cond_start.clone(),
                    name: format!(""),
                });
                self.compile_condition(condition, while_after.clone());

                self.compile_commands(commands);
                self.push_asm(IR::lbl_jump(cond_start));
                self.push_asm(IR::LABEL {
                    idx: while_after,
                    name: format!(""),
                });
            }
            Command::Repeat {
                commands,
                condition,
                location,
            } => {
                let loop_start_lbl = self.push_label();

                self.compile_commands(commands);
                self.compile_condition(condition, loop_start_lbl);
            }
            Command::For {
                variable,
                from,
                to,
                direction,
                commands,
                location,
            } => {
                let for_iter_maybe = self.memory.allocate_for_iter(
                    &Declaration {
                        name: variable.to_string(),
                        array_size: None,
                        location: *location,
                    },
                    &self.current_scope,
                );

                let for_iter_loc;
                if let Err(e) = for_iter_maybe {
                    self.add_message(e);
                    return;
                }
                for_iter_loc = for_iter_maybe.unwrap().memory_address;

                let for_exit_lbl = LabelIdx(self.next_label);
                self.next_label += 1;

                let for_loop_start = LabelIdx(self.next_label);
                self.next_label += 1;

                let for_num_iters = self
                    .memory
                    .allocate_for_iter(
                        &Declaration {
                            name: format!("{}::cnt", variable),
                            array_size: None,
                            location: *location,
                        },
                        &self.current_scope,
                    )
                    .unwrap()
                    .memory_address;

                self.ensure_constant(1);

                self.generate_value_in_acc(from);
                self.push_asm(IR::STORE(for_iter_loc));

                self.generate_value_in_acc(to);
                self.push_asm(IR::STORE(for_num_iters));

                self.push_asm(IR::LOAD(for_iter_loc));
                self.push_asm(IR::LABEL {
                    idx: for_loop_start.clone(),
                    name: format!(""),
                });
                self.push_asm(IR::SUB(for_num_iters));
                match direction {
                    ForDirection::Ascending => {
                        self.push_asm(IR::jp(for_exit_lbl.clone()));
                    }
                    ForDirection::Descending => {
                        self.push_asm(IR::jn(for_exit_lbl.clone()));
                    }
                }

                self.compile_commands(commands);

                self.push_asm(IR::LOAD(for_iter_loc));
                let one_loc = self.ensure_constant(1).memory_address;
                match direction {
                    ForDirection::Ascending => {
                        self.push_asm(IR::ADD(one_loc));
                    }
                    ForDirection::Descending => {
                        self.push_asm(IR::SUB(one_loc));
                    }
                }
                self.push_asm(IR::STORE(for_iter_loc));
                self.push_asm(IR::lbl_jump(for_loop_start));
                self.push_asm(IR::LABEL {
                    idx: for_exit_lbl,
                    name: format!(""),
                });

                self.memory.deallocate_for_iter(
                    &Declaration {
                        name: variable.to_string(),
                        array_size: None,
                        location: *location,
                    },
                    &self.current_scope,
                );
                self.last_mem_slot += 2;
            }
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
                                self.ensure_constant_in_acc(arg_mem_loc.memory_address as i64);
                                self.push_asm(IR::STORE(target_mem_loc.memory_address));
                            }
                        }

                        self.push_asm(IR::call {
                            name: proc_name.clone(),
                        });
                    }
                }
            } // _ => unimplemented!(),
        }
    }

    fn compile_condition(&mut self, condition: &Condition, fail_label: LabelIdx) {
        macro_rules! generate_and_subtract {
            ($self:ident, $left:expr, $right:expr, $op_mem_2:expr) => {{
                let left_loc = $self.generate_value_loc_not_in_acc($left, $op_mem_2);
                $self.generate_value_in_acc($right);

                if left_loc.is_pointer {
                    $self.push_asm(IR::SUBI(left_loc.memory_address));
                } else {
                    $self.push_asm(IR::SUB(left_loc.memory_address));
                }
            }};
        }

        let op_mem_1 = self.last_mem_slot;
        self.last_mem_slot -= 1;
        let op_mem_2 = self.last_mem_slot;
        self.last_mem_slot -= 1;

        match condition {
            Condition::NotEqual(left, right) => {
                generate_and_subtract!(self, left, right, op_mem_1);
                self.push_asm(IR::jz(fail_label));
            }
            Condition::Equal(left, right) => {
                generate_and_subtract!(self, left, right, op_mem_1);
                self.push_asm(IR::jnz(fail_label));
            }
            Condition::LessOrEqual(left, right) => {
                generate_and_subtract!(self, left, right, op_mem_1);
                self.push_asm(IR::jn(fail_label));
            }
            Condition::GreaterOrEqual(left, right) => {
                generate_and_subtract!(self, left, right, op_mem_1);
                self.push_asm(IR::jp(fail_label));
            }
            Condition::GreaterThan(left, right) => {
                generate_and_subtract!(self, left, right, op_mem_1);
                self.push_asm(IR::jzn(fail_label));
            }
            Condition::LessThan(left, right) => {
                generate_and_subtract!(self, left, right, op_mem_1);
                self.push_asm(IR::jzp(fail_label));
            }
        }

        self.last_mem_slot += 2;
    }

    fn compile_expression(
        &mut self,
        target_identifier: &Identifier,
        expression: &Expression,
        loc: (Point, Point),
    ) {
        match expression {
            Expression::Value(value) => {
                self.generate_value_in_acc(value);
                self.compile_store_location_to_identifier(
                    SymbolLocation {
                        memory_address: 0,
                        is_array: false,
                        array_bounds: None,
                        is_pointer: false,
                        read_only: true,
                        initialized: true,
                    },
                    target_identifier,
                );
            }

            Expression::Addition(left, right) => {
                let left_loc = self.generate_value_loc_not_in_acc(left, self.last_mem_slot);
                self.generate_value_in_acc(right);
                if left_loc.is_pointer {
                    self.push_asm(IR::ADDI(left_loc.memory_address));
                } else {
                    self.push_asm(IR::ADD(left_loc.memory_address));
                }

                self.compile_store_location_to_identifier(
                    SymbolLocation {
                        memory_address: 0,
                        is_array: false,
                        array_bounds: None,
                        is_pointer: false,
                        read_only: true,
                        initialized: true,
                    },
                    target_identifier,
                );
            }
            Expression::Subtraction(left, right) => {
                let right_loc = self.generate_value_loc_not_in_acc(right, self.last_mem_slot);
                self.generate_value_in_acc(left);
                if right_loc.is_pointer {
                    self.push_asm(IR::SUBI(right_loc.memory_address));
                } else {
                    self.push_asm(IR::SUB(right_loc.memory_address));
                }

                self.compile_store_location_to_identifier(
                    SymbolLocation {
                        memory_address: 0,
                        is_array: false,
                        array_bounds: None,
                        is_pointer: false,
                        read_only: true,
                        initialized: true,
                    },
                    target_identifier,
                );
            }
            _ => {
                let left;
                let right;
                let proc_name;

                match expression {
                    Expression::Multiplication(_left, _right) => {
                        left = _left;
                        right = _right;
                        proc_name = format!("__BUILTIN_MUL");
                    }
                    Expression::Modulo(_left, _right) => {
                        left = _left;
                        right = _right;
                        proc_name = format!("__BUILTIN_DIV_MOD");
                    }
                    Expression::Division(_left, _right) => {
                        left = _left;
                        right = _right;
                        proc_name = format!("__BUILTIN_DIV_MOD");
                    }
                    _ => unreachable!(),
                }
                let op_proc = self.procedures.get(&proc_name).unwrap().clone();

                self.generate_value_in_acc(left);
                self.push_asm(IR::STORE(op_proc.args.get(0).unwrap().memory_address));

                self.generate_value_in_acc(right);
                self.push_asm(IR::STORE(op_proc.args.get(1).unwrap().memory_address));

                let a;

                match expression {
                    Expression::Modulo(_left, _right) => {
                        a = op_proc.args.get(3).unwrap().clone();
                    }
                    _ => {
                        a = op_proc.args.get(2).unwrap().clone();
                    }
                }
                self.push_asm(IR::call { name: proc_name });

                self.compile_store_location_to_identifier(a, target_identifier);
            }
        }
    }

    fn compile_store_location_to_identifier(
        &mut self,
        mut what: SymbolLocation,
        to_where: &Identifier,
    ) {
        if let Some(target_loc) = self.generate_ident_no_extra_asm(to_where) {
            if what.memory_address != 0 || what.is_pointer {
                self.compile_load_from_symbol(what);
            }
            self.compile_store_to_symbol(target_loc);
            return;
        }

        self.last_mem_slot -= 2;
        if what.memory_address == 0 {
            what.memory_address = self.last_mem_slot + 1;
            self.push_asm(IR::STORE(self.last_mem_slot + 1));
        }
        let mut target_loc = self.generate_ident(to_where);
        if target_loc.memory_address == 0 {
            target_loc.memory_address = self.last_mem_slot + 2;
            self.push_asm(IR::STORE(self.last_mem_slot + 2));
        }
        self.compile_load_from_symbol(what);
        self.compile_store_to_symbol(target_loc);
        self.last_mem_slot += 2;
    }

    fn compile_load_from_symbol(&mut self, what: SymbolLocation) {
        if what.is_pointer {
            self.push_asm(IR::LOADI(what.memory_address));
        } else {
            if what.memory_address == 0 {
                return;
            }
            self.push_asm(IR::LOAD(what.memory_address));
        }
    }

    fn compile_store_to_symbol(&mut self, to_where: SymbolLocation) {
        if to_where.is_pointer {
            self.push_asm(IR::STOREI(to_where.memory_address));
        } else {
            self.push_asm(IR::STORE(to_where.memory_address));
        }
    }

    fn generate_ident_no_extra_asm(&mut self, ident: &Identifier) -> Option<SymbolLocation> {
        //TODO validate access //
        match &ident.index {
            None => {
                let r = self
                    .memory
                    .get_ident_base_location(ident, &self.current_scope);

                match r {
                    Ok(loc) => return Some(loc),
                    Err(err) => {
                        self.add_message(err);
                        return None;
                    }
                }
            }
            Some(idx) => match idx {
                Either::Left(_) => {
                    return None;
                }
                Either::Right(idx_val) => {
                    let array_base_loc = self
                        .memory
                        .get_ident_base_location_no_error(ident, &self.current_scope);

                    if array_base_loc.is_pointer {
                        return None;
                    } else {
                        return Some(SymbolLocation {
                            memory_address: (array_base_loc.memory_address as i64 + idx_val)
                                as usize,
                            is_array: false,
                            array_bounds: None,
                            is_pointer: false,
                            read_only: false,
                            initialized: true,
                        });
                    }
                }
            },
        }
    }

    /// can overwrite acc
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
                Either::Left(idx_name) => {
                    let r = self.memory.get_name_location(
                        idx_name,
                        &self.current_scope,
                        ident.location,
                    );

                    match r {
                        Err(err) => {
                            self.add_message(err);
                            return SymbolLocation::new();
                        }
                        _ => {}
                    }
                    let idx_location = r.unwrap();

                    let array_base_loc = self
                        .memory
                        .get_ident_base_location_no_error(ident, &self.current_scope);

                    match (array_base_loc.is_pointer, idx_location.is_pointer) {
                        (false, false) => {
                            self.ensure_constant_in_acc(array_base_loc.memory_address as i64);
                            self.push_asm(IR::ADD(idx_location.memory_address));
                        }
                        (false, true) => {
                            self.ensure_constant_in_acc(array_base_loc.memory_address as i64);
                            self.push_asm(IR::ADDI(idx_location.memory_address));
                        }
                        (true, false) => {
                            self.push_asm(IR::LOAD(array_base_loc.memory_address));
                            self.push_asm(IR::ADD(idx_location.memory_address));
                        }
                        (true, true) => {
                            self.push_asm(IR::LOAD(array_base_loc.memory_address));
                            self.push_asm(IR::ADDI(idx_location.memory_address));
                        }
                    }

                    return SymbolLocation {
                        memory_address: 0,
                        is_array: false,
                        array_bounds: None,
                        is_pointer: true,
                        read_only: true,
                        initialized: true,
                    };
                }
                Either::Right(idx_val) => {
                    let array_base_loc = self
                        .memory
                        .get_ident_base_location_no_error(ident, &self.current_scope);

                    if array_base_loc.is_pointer {
                        self.ensure_constant_in_acc(*idx_val);
                        self.push_asm(IR::ADD(array_base_loc.memory_address));

                        return SymbolLocation {
                            memory_address: 0,
                            is_array: false,
                            array_bounds: None,
                            is_pointer: true,
                            read_only: true,
                            initialized: true,
                        };
                    } else {
                        return SymbolLocation {
                            memory_address: (array_base_loc.memory_address as i64 + idx_val)
                                as usize,
                            is_array: false,
                            array_bounds: None,
                            is_pointer: false,
                            read_only: false,
                            initialized: true,
                        };
                    }
                }
            },
        }
    }

    fn generate_value_loc_not_in_acc(
        &mut self,
        val: &Value,
        mem_slot_to_use: usize,
    ) -> SymbolLocation {
        let mut loc;
        match val {
            Value::Number(num) => {
                loc = self.ensure_constant(num.clone());
            }
            Value::Identifier(ident) => {
                loc = self.generate_ident(ident);
            }
        }

        if loc.memory_address == 0 {
            self.push_asm(IR::STORE(mem_slot_to_use));
            loc.memory_address = mem_slot_to_use;
        }
        return loc;
    }

    fn generate_value_in_acc(&mut self, val: &Value) {
        let loc;
        match val {
            Value::Number(num) => {
                self.ensure_constant_in_acc(*num);
                return;
            }
            Value::Identifier(ident) => {
                loc = self.generate_ident(ident);
            }
        }

        if loc.memory_address == 0 && loc.is_pointer {
            self.push_asm(IR::LOADI(0));
        }
        if loc.memory_address != 0 {
            match loc.is_pointer {
                true => self.push_asm(IR::LOADI(loc.memory_address)),
                false => self.push_asm(IR::LOAD(loc.memory_address)),
            }
        }
    }

    /// Can overwrite acc
    fn generate_value(&mut self, val: &Value) -> SymbolLocation {
        match val {
            Value::Number(num) => {
                return self.ensure_constant(num.clone());
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

            self.constants.insert(
                constant,
                ConstInfo {
                    num_used: 1,
                    val: constant,
                    location: mem_loc,
                },
            );

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

    pub fn ensure_constant_in_acc(&mut self, constant: i64) {
        if let Some(loc) = self.memory.get_constant(constant.clone()) {
            self.push_asm(IR::LOAD(loc.memory_address));
        } else {
            let mem_loc = self.memory.allocate_constant(constant.clone());
            self.constants.insert(
                constant,
                ConstInfo {
                    num_used: 1,
                    val: constant,
                    location: mem_loc,
                },
            );

            self.push_asm(IR::SET(constant));
        }
    }

    fn fill_in_constants(&mut self) -> Vec<IR> {
        for instruction in self.assembly_code.iter_mut() {
            match instruction {
                IR::SET(val) => {
                    let default_const = ConstInfo {
                        num_used: -999,
                        val: *val,
                        location: 999,
                    };
                    let const_info = self.constants.get(val).unwrap_or(&default_const);

                    if const_info.num_used >= MIN_CONST_USAGE {
                        *instruction = IR::LOAD(const_info.location);
                    }
                }
                _ => {}
            }
        }

        let mut v = Vec::new();
        for (_, c) in &self.constants {
            v.push(IR::SET(c.val));
            v.push(IR::STORE(c.location));
        }
        return v;
    }

    pub fn get_proc_info_for_name(&self, proc_name: &String) -> ProcedureInfo {
        self.procedures.get(proc_name).unwrap().clone()
    }

    fn compile_mul_procedure(&mut self) {
        self.current_scope = format!("__BUILTIN_MUL");
        let proc_lbl = self.push_label_name(&format!("__BUILTIN_MUL"));
        let ret_addr = self
            .memory
            .allocate_procedure_return(&format!("__BUILTIN_MUL"));
        let mut proc_info = ProcedureInfo {
            return_address: ret_addr,
            label: proc_lbl,
            args: vec![],
        };

        let p_arg1 = self.memory.allocate_builtin_arg(
            &ProcArgument {
                name: "arg1".to_string(),
                is_array: false,
            },
            &self.current_scope,
        );

        let p_arg2 = self.memory.allocate_builtin_arg(
            &ProcArgument {
                name: "arg2".to_string(),
                is_array: false,
            },
            &self.current_scope,
        );

        let p_result = self.memory.allocate_builtin_arg(
            &ProcArgument {
                name: "rtn".to_string(),
                is_array: false,
            },
            &self.current_scope,
        );

        proc_info
            .args
            .extend([p_arg1.clone(), p_arg2.clone(), p_result.clone()]);

        let arg1 = p_arg1.memory_address;

        let arg2 = p_arg2.memory_address;

        self.ensure_constant_in_acc(0);
        self.push_asm(IR::STORE(p_result.memory_address));

        self.push_asm(IR::LOAD(p_arg2.memory_address));

        let loop_end_lbl = LabelIdx(self.next_label);
        self.next_label += 1;
        let loop_start_lbl = LabelIdx(self.next_label);
        self.next_label += 1;

        let skip_add = LabelIdx(self.next_label);
        self.next_label += 1;

        let sign_flag = self.last_mem_slot - 1;
        let arg_1_pos = LabelIdx(self.next_label);
        self.next_label += 1;
        let arg_2_pos = LabelIdx(self.next_label);
        self.next_label += 1;

        self.ensure_constant_in_acc(1);
        self.push_asm(IR::STORE(sign_flag));

        self.push_asm(IR::LOAD(arg1));
        self.push_asm(IR::jp(arg_1_pos.clone()));

        self.ensure_constant_in_acc(-1);
        self.push_asm(IR::STORE(sign_flag));
        self.ensure_constant_in_acc(0);
        self.push_asm(IR::SUB(arg1));
        self.push_asm(IR::STORE(arg1));

        self.push_asm(IR::LABEL {
            idx: arg_1_pos,
            name: format!(""),
        });

        self.push_asm(IR::LOAD(arg2));
        self.push_asm(IR::jp(arg_2_pos.clone()));

        self.ensure_constant_in_acc(0);

        self.push_asm(IR::SUB(sign_flag));
        self.push_asm(IR::STORE(sign_flag));
        self.ensure_constant_in_acc(0);

        self.push_asm(IR::SUB(arg2));
        self.push_asm(IR::STORE(arg2));

        self.push_asm(IR::LABEL {
            idx: arg_2_pos,
            name: format!(""),
        });

        self.push_asm(IR::LOAD(p_arg1.memory_address));

        self.push_asm(IR::LABEL {
            idx: loop_start_lbl.clone(),
            name: format!(""),
        });
        self.push_asm(IR::jz(loop_end_lbl.clone()));

        self.push_asm(IR::HALF);
        self.push_asm(IR::ADD(0));
        self.push_asm(IR::SUB(arg1));

        self.push_asm(IR::jz(skip_add.clone()));
        self.push_asm(IR::LOAD(arg1));
        self.push_asm(IR::LOAD(p_result.memory_address));
        self.push_asm(IR::ADD(arg2));
        self.push_asm(IR::STORE(p_result.memory_address));
        self.push_asm(IR::LABEL {
            idx: skip_add,
            name: format!(""),
        });

        self.push_asm(IR::LOAD(arg2));
        self.push_asm(IR::ADD(arg2));
        self.push_asm(IR::STORE(arg2));

        self.push_asm(IR::LOAD(arg1));
        self.push_asm(IR::HALF);
        self.push_asm(IR::STORE(arg1));

        self.push_asm(IR::lbl_jump(loop_start_lbl));
        self.push_asm(IR::LABEL {
            idx: loop_end_lbl,
            name: format!(""),
        });

        let is_pos = LabelIdx(self.next_label);
        self.next_label += 1;

        let skip = LabelIdx(self.next_label);
        self.next_label += 1;

        self.push_asm(IR::LOAD(sign_flag));
        self.push_asm(IR::jp(is_pos.clone()));

        self.ensure_constant_in_acc(0);
        self.push_asm(IR::SUB(p_result.memory_address));
        self.push_asm(IR::lbl_jump(skip.clone()));

        self.push_asm(IR::LABEL {
            idx: is_pos,
            name: format!(""),
        });
        self.push_asm(IR::LOAD(p_result.memory_address));
        self.push_asm(IR::LABEL {
            idx: skip,
            name: format!(""),
        });
        self.push_asm(IR::STORE(p_result.memory_address));

        self.push_asm(IR::RTRN(ret_addr));
        self.procedures.insert(format!("__BUILTIN_MUL"), proc_info);
    }

    fn compile_mod_div_procedure(&mut self) {
        self.current_scope = format!("__BUILTIN_DIV_MOD");
        let proc_lbl = self.push_label_name(&format!("__BUILTIN_DIV_MOD"));
        let ret_addr = self
            .memory
            .allocate_procedure_return(&format!("__BUILTIN_DIV_MOD"));
        let mut proc_info = ProcedureInfo {
            return_address: ret_addr,
            label: proc_lbl,
            args: vec![],
        };

        let p_arg1 = self.memory.allocate_builtin_arg(
            &ProcArgument {
                name: "arg1".to_string(),
                is_array: false,
            },
            &self.current_scope,
        );

        let p_arg2 = self.memory.allocate_builtin_arg(
            &ProcArgument {
                name: "arg2".to_string(),
                is_array: false,
            },
            &self.current_scope,
        );

        let div_result = self.memory.allocate_builtin_arg(
            &ProcArgument {
                name: "dividend".to_string(),
                is_array: false,
            },
            &self.current_scope,
        );

        let mod_result = self.memory.allocate_builtin_arg(
            &ProcArgument {
                name: "divisor".to_string(),
                is_array: false,
            },
            &self.current_scope,
        );

        let arg1 = p_arg1.memory_address;

        let arg2 = p_arg2.memory_address;

        proc_info
            .args
            .extend([p_arg1, p_arg2, div_result.clone(), mod_result.clone()]);

        // setup

        let sign_flag = self.last_mem_slot;
        let mod_final_sign = self.last_mem_slot - 1;

        let quotient = self.last_mem_slot - 2;
        let power_of_two = self.last_mem_slot - 3;

        let arg_1_pos = LabelIdx(self.next_label);
        self.next_label += 1;
        let arg_2_pos = LabelIdx(self.next_label);
        self.next_label += 1;

        // if b == 0
        self.push_asm(IR::LOAD(arg2));
        self.push_asm(IR::jnz(LabelIdx(self.next_label)));
        self.ensure_constant_in_acc(0);
        self.push_asm(IR::STORE(div_result.memory_address));
        self.push_asm(IR::STORE(mod_result.memory_address));
        self.push_asm(IR::RTRN(ret_addr));
        self.push_label();

        // sign = 1, mod_sign = 1
        self.ensure_constant_in_acc(1);
        self.push_asm(IR::STORE(sign_flag));
        self.push_asm(IR::STORE(mod_final_sign));

        // if arg1 < 0
        self.push_asm(IR::LOAD(arg1));
        self.push_asm(IR::jp(arg_1_pos.clone()));

        self.ensure_constant_in_acc(-1);
        self.push_asm(IR::STORE(sign_flag));
        self.ensure_constant_in_acc(0);
        self.push_asm(IR::SUB(arg1));
        self.push_asm(IR::STORE(arg1));

        self.push_asm(IR::LABEL {
            idx: arg_1_pos,
            name: format!(""),
        });

        // if arg2 < 0
        self.push_asm(IR::LOAD(arg2));
        self.push_asm(IR::jp(arg_2_pos.clone()));

        self.ensure_constant_in_acc(0);
        self.push_asm(IR::SUB(sign_flag));
        self.push_asm(IR::STORE(sign_flag));

        self.ensure_constant_in_acc(0);
        self.push_asm(IR::SUB(mod_final_sign));
        self.push_asm(IR::STORE(mod_final_sign));

        self.ensure_constant_in_acc(0);
        self.push_asm(IR::SUB(arg2));
        self.push_asm(IR::STORE(arg2));

        self.push_asm(IR::LABEL {
            idx: arg_2_pos,
            name: format!(""),
        });

        self.ensure_constant_in_acc(0);
        self.push_asm(IR::STORE(quotient));

        self.ensure_constant_in_acc(1);
        self.push_asm(IR::STORE(power_of_two));

        /*
        while arg2 - arg1 < 0:
            arg2 += arg2
            power_of_two += power_of_two
        */
        let loop1_start = self.push_label();
        self.push_asm(IR::LOAD(arg2));
        self.push_asm(IR::SUB(arg1));
        self.push_asm(IR::jp(LabelIdx(self.next_label)));
        self.push_asm(IR::LOAD(arg2));
        self.push_asm(IR::ADD(arg2));
        self.push_asm(IR::STORE(arg2));

        self.push_asm(IR::LOAD(power_of_two));
        self.push_asm(IR::ADD(power_of_two));
        self.push_asm(IR::STORE(power_of_two));

        self.push_asm(IR::lbl_jump(loop1_start));
        self.push_label();

        /*
        while !power_of_two <= 0:
            if arg1 - arg2 >= 0 :
                arg1 -= arg2
                quotient += power_of_two

            arg2 = arg2 // 2
            power_of_two = power_of_two // 2
        */
        let loop2_start = self.push_label();
        let loop2_end = LabelIdx(self.next_label);
        self.next_label += 1;

        self.push_asm(IR::LOAD(power_of_two));
        self.push_asm(IR::jzp(loop2_end.clone()));
        self.push_asm(IR::comment {
            cm: "fae".to_string(),
        });

        self.push_asm(IR::LOAD(arg1));
        self.push_asm(IR::SUB(arg2));
        self.push_asm(IR::jn(LabelIdx(self.next_label)));
        self.push_asm(IR::LOAD(arg1));
        self.push_asm(IR::SUB(arg2));
        self.push_asm(IR::STORE(arg1));

        self.push_asm(IR::LOAD(quotient));
        self.push_asm(IR::ADD(power_of_two));
        self.push_asm(IR::STORE(quotient));

        self.push_label();

        self.push_asm(IR::LOAD(arg2));
        self.push_asm(IR::HALF);
        self.push_asm(IR::STORE(arg2));

        self.push_asm(IR::LOAD(power_of_two));
        self.push_asm(IR::HALF);
        self.push_asm(IR::STORE(power_of_two));

        self.push_asm(IR::lbl_jump(loop2_start));
        self.push_asm(IR::LABEL {
            idx: loop2_end,
            name: format!(""),
        });

        self.push_asm(IR::LOAD(quotient));
        self.push_asm(IR::STORE(div_result.memory_address));

        self.push_asm(IR::LOAD(arg1));
        self.push_asm(IR::STORE(mod_result.memory_address));

        self.push_asm(IR::RTRN(ret_addr));
        self.procedures
            .insert(format!("__BUILTIN_DIV_MOD"), proc_info);
    }
}
