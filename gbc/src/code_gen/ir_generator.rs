use crate::ast::{
    Ast, Command, Condition, Declaration, Expression, Identifier, MainBlock, Procedure, Value,
};

use super::{
    ir::{IrOperand, IR},
    ArgInfo, IrProgram, ProcedureInfo,
};

impl IrProgram {
    pub fn generate_program(&mut self, ast: &Ast) {
        self.generate_main(&ast.main_block);
        for (_, proc) in &ast.procedures {
            self.generate_procedure(&proc);
        }
    }

    fn generate_main(&mut self, main_block: &MainBlock) {
        self.current_scope = "MAIN".to_owned();
        let mut decls = self.allocate_declarations(&main_block.declarations);
        self.main = vec![];
        self.main.push(IR::Comment("_start".to_owned()));
        self.main.append(&mut decls);
        let mut cmds = self.compile_commands(&main_block.commands);
        self.main.append(&mut cmds);
        self.current_scope = "".to_owned();
    }

    fn generate_procedure(&mut self, procedure: &Procedure) {
        self.current_scope = format!("{}", procedure.name);

        let proc_lbl = self.new_label(&procedure.name);

        let mut v = vec![];
        let mut args = vec![];

        for arg in &procedure.args {
            args.push(ArgInfo {
                name: arg.name.clone(),
                is_array: arg.is_array,
                is_in_only: false,
            });
        }

        v.append(&mut self.allocate_declarations(&procedure.declarations));
        v.append(&mut self.compile_commands(&procedure.commands));
        v.push(IR::Return);

        let proc_info = ProcedureInfo {
            lbl: proc_lbl,
            name: procedure.name.clone(),
            args: args,
            cmds: v,
        };

        self.procedures.insert(procedure.name.clone(), proc_info);

        self.current_scope = "".to_owned();
    }

    fn new_label(&mut self, prefix: &str) -> String {
        let label = format!("L{}_i{}", prefix, self.next_label);
        self.next_label += 1;
        label
    }

    fn compile_commands(&mut self, commands: &Vec<Command>) -> Vec<IR> {
        commands
            .iter()
            .map(|cmd| self.compile_command(cmd))
            .flatten()
            .collect()
    }

    fn compile_command(&mut self, command: &Command) -> Vec<IR> {
        match command {
            Command::Assignment {
                identifier,
                expression,
                ..
            } => vec![self.compile_assignment(expression, identifier)],
            Command::IfElse {
                condition,
                then_commands,
                else_commands,
                ..
            } => {
                let true_lbl = self.new_label("ifelse_true");
                let false_lbl = self.new_label("ifelse_false");
                let mut v = vec![];
                v.push(self.compile_condition(&condition.clone(), &false_lbl));
                v.append(&mut self.compile_commands(then_commands));
                v.push(IR::Jump(true_lbl.clone()));
                v.push(IR::Label(false_lbl));
                v.append(&mut self.compile_commands(else_commands));
                v.push(IR::Label(true_lbl));
                v
            }
            Command::If {
                condition,
                then_commands,
                ..
            } => {
                let false_lbl = self.new_label("if");
                let mut v = vec![];
                v.push(self.compile_condition(condition, &false_lbl));
                v.append(&mut self.compile_commands(then_commands));
                v.push(IR::Label(false_lbl));
                v
            }
            Command::While {
                condition,
                commands,
                ..
            } => {
                let while_start = self.new_label("while_start");
                let while_after = self.new_label("while_done");
                let mut v = vec![];
                v.push(IR::Label(while_start.clone()));
                v.push(self.compile_condition(&condition.clone(), &while_after));
                v.append(&mut self.compile_commands(commands));
                v.push(IR::Jump(while_start));
                v.push(IR::Label(while_after));
                v
            }
            Command::Repeat {
                commands,
                condition,
                ..
            } => {
                let mut v = vec![];

                let loop_start_lbl = self.new_label("repeat_back");
                v.push(IR::Label(loop_start_lbl.clone()));
                v.append(&mut self.compile_commands(commands));
                v.push(self.compile_condition(&condition.clone(), &loop_start_lbl));

                v
            }
            Command::For {
                variable,
                from,
                to,
                direction,
                commands,
                ..
            } => {
                let mut v = vec![];

                v.push(IR::Aloc {
                    name: variable.to_string(),
                    is_array: false,
                    array_bounds: None,
                });

                v.push(IR::Aloc {
                    name: format!("{}CNT", variable),
                    is_array: false,
                    array_bounds: None,
                });

                let for_iter = IrOperand::Variable(variable.to_string());
                let for_cnt = IrOperand::Variable(format!("{}CNT", variable));
                let one = IrOperand::Constant(1);
                let from = self.generate_value(from);
                let to = self.generate_value(to);

                let loop_start = self.new_label("for_s");
                let loop_exit = self.new_label("for_fail");

                v.push(IR::Mov {
                    dest: for_iter.clone(),
                    src: from,
                });
                v.push(IR::Mov {
                    dest: for_cnt.clone(),
                    src: to,
                });

                v.push(IR::Label(loop_start.clone()));
                match direction {
                    crate::ast::ForDirection::Ascending => {
                        v.push(IR::JPositive {
                            left: for_iter.clone(),
                            right: for_cnt.clone(),
                            label: loop_exit.clone(),
                        });
                    }
                    crate::ast::ForDirection::Descending => {
                        v.push(IR::JNegative {
                            left: for_iter.clone(),
                            right: for_cnt.clone(),
                            label: loop_exit.clone(),
                        });
                    }
                };

                v.append(&mut self.compile_commands(commands));
                match direction {
                    crate::ast::ForDirection::Ascending => {
                        v.push(IR::Add {
                            dest: for_iter.clone(),
                            left: for_iter.clone(),
                            right: one,
                        });
                    }
                    crate::ast::ForDirection::Descending => {
                        v.push(IR::Sub {
                            dest: for_iter.clone(),
                            left: for_iter.clone(),
                            right: one,
                        });
                    }
                };

                v.push(IR::Jump(loop_start));
                v.push(IR::Label(loop_exit));

                v.push(IR::Drop {
                    name: variable.to_string(),
                });

                v.push(IR::Drop {
                    name: format!("{}CNT", variable),
                });

                v
            }
            Command::ProcedureCall {
                proc_name,
                arguments,
                ..
            } => {
                vec![IR::ProcCall {
                    procedure: proc_name.clone(),
                    arguments: arguments
                        .iter()
                        .map(|arg| IrOperand::Variable(arg.name.clone()))
                        .collect(),
                }]
            }
            Command::Read(identifier) => {
                let oper = self.generate_ident(identifier);
                vec![IR::Read(oper)]
            }
            Command::Write(value) => {
                let oper = self.generate_value(value);
                vec![IR::Write(oper)]
            }
        }
    }

    fn compile_condition(&mut self, condition: &Condition, lbl_name: &str) -> IR {
        match condition {
            Condition::Equal(value, value1) => IR::JNotZero {
                left: self.generate_value(value),
                right: self.generate_value(value1),
                label: lbl_name.to_owned(),
            },
            Condition::NotEqual(value, value1) => IR::JZero {
                left: self.generate_value(value),
                right: self.generate_value(value1),
                label: lbl_name.to_owned(),
            },
            Condition::GreaterThan(value, value1) => IR::JNegativeOrZero {
                left: self.generate_value(value),
                right: self.generate_value(value1),
                label: lbl_name.to_owned(),
            },
            Condition::LessThan(value, value1) => IR::JPositiveOrZero {
                left: self.generate_value(value),
                right: self.generate_value(value1),
                label: lbl_name.to_owned(),
            },
            Condition::GreaterOrEqual(value, value1) => IR::JNegative {
                left: self.generate_value(value),
                right: self.generate_value(value1),
                label: lbl_name.to_owned(),
            },
            Condition::LessOrEqual(value, value1) => IR::JPositive {
                left: self.generate_value(value),
                right: self.generate_value(value1),
                label: lbl_name.to_owned(),
            },
        }
    }

    fn compile_assignment(&mut self, expr: &Expression, where_to: &Identifier) -> IR {
        let dst = self.generate_ident(where_to);
        let op = match expr {
            Expression::Value(value) => IR::Mov {
                dest: dst,
                src: self.generate_value(value),
            },
            Expression::Addition(value, value1) => IR::Add {
                dest: dst,
                left: self.generate_value(value),
                right: self.generate_value(value1),
            },
            Expression::Subtraction(value, value1) => IR::Sub {
                dest: dst,
                left: self.generate_value(value),
                right: self.generate_value(value1),
            },
            Expression::Multiplication(value, value1) => IR::Mul {
                dest: dst,
                left: self.generate_value(value),
                right: self.generate_value(value1),
            },
            Expression::Division(value, value1) => IR::Div {
                dest: dst,
                left: self.generate_value(value),
                right: self.generate_value(value1),
            },
            Expression::Modulo(value, value1) => IR::Mod {
                dest: dst,
                left: self.generate_value(value),
                right: self.generate_value(value1),
            },
        };

        op
    }

    fn allocate_declarations(&mut self, declarations: &Vec<Declaration>) -> Vec<IR> {
        declarations
            .iter()
            .map(|d| IR::Aloc {
                name: d.name.clone(),
                is_array: if let Some(_) = d.array_size {
                    true
                } else {
                    false
                },
                array_bounds: d.array_size,
            })
            .collect()
    }

    fn generate_value(&mut self, val: &Value) -> IrOperand {
        match val {
            Value::Number(num) => IrOperand::Constant(num.clone()),
            Value::Identifier(identifier) => self.generate_ident(identifier),
        }
    }

    fn generate_ident(&mut self, ident: &Identifier) -> IrOperand {
        match &ident.index {
            Some(idx_ident) => match &idx_ident {
                crate::ast::Either::Left(idx_name) => IrOperand::ArrayDynamicAccess {
                    base_name: ident.name.clone(),
                    idx_name: idx_name.clone(),
                },
                crate::ast::Either::Right(idx) => IrOperand::ArrayConstAccess {
                    base_name: ident.name.clone(),
                    idx: idx.clone(),
                },
            },
            None => IrOperand::Variable(ident.name.clone()),
        }
    }
}
