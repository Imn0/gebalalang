use tree_sitter::{Node, Tree};

use crate::{ast::*, program::Program};

use super::GetLocation;


impl Program {
    pub fn populate_ast(&mut self, tree: Tree) -> Result<(), ()> {
        let root_node = tree.root_node();
        let location = root_node.get_location();
        self.ast.is_valid = true;
        self.ast.location = location;

        if let Some(procedures_node) = root_node.child_by_field_name("procedures") {
            self.populate_procedures(procedures_node);
        }

        let main_node = root_node.child_by_field_name("main_program").unwrap();
        self.populate_main(main_node);

        if self.ast.is_valid {
            Ok(())
        } else {
            Err(())
        }
    }

    fn populate_main(&mut self, node: Node) {
        assert_eq!(node.kind(), "main");

        self.ast.main_block.declarations = node
            .child_by_field_name("declarations")
            .map(|declarations_node| self.gen_declarations(declarations_node))
            .unwrap_or_else(Vec::new);

        self.ast.main_block.commands = node
            .child_by_field_name("commands")
            .map(|declarations_node| self.gen_commands(declarations_node))
            .unwrap_or_else(Vec::new);
    }

    fn populate_procedures(&mut self, node: Node) {
        assert_eq!(node.kind(), "procedures");

        for child in node.named_children(&mut node.walk()) {
            let proc = self.gen_procedure(child);

            if let Some(Procedure {
                name,
                args: _,
                declarations: _,
                commands: _,
                location,
            }) = self.ast.procedures.get(&proc.name)
            {
                self.ast.is_valid = false;
                self.print_message(Message::CodeMessage {
                    severity: MessageSeverity::ERROR,
                    message: format!("procedure {} already defined", name).as_str(),
                    location: proc.location,
                });
                self.print_message(Message::CodeMessage {
                    severity: MessageSeverity::INFO,
                    message: format!("procedure {} previously defined here", name).as_str(),
                    location: location.clone(),
                });
                self.ast.is_valid = false;

                return;
            }

            self.ast.procedures.insert(proc.name.clone(), proc);
        }
    }

    fn gen_procedure(&mut self, node: Node) -> Procedure {
        assert_eq!(node.kind(), "procedure");

        let proc_head_node = node.child_by_field_name("header").unwrap();
        let name = self.get_text(proc_head_node.child_by_field_name("name").unwrap());

        let args = if let Some(args_decl_node) = proc_head_node.child_by_field_name("arguments") {
            self.gen_args_decl(args_decl_node)
        } else {
            Vec::new()
        };

        let declarations = if let Some(declarations_node) = node.child_by_field_name("declarations")
        {
            self.gen_declarations(declarations_node)
        } else {
            Vec::new()
        };

        let commands = if let Some(commands_node) = node.child_by_field_name("commands") {
            self.gen_commands(commands_node)
        } else {
            Vec::new()
        };

        Procedure {
            name,
            args,
            declarations,
            commands,
            location: proc_head_node.get_location(),
        }
    }

    fn gen_declarations(&self, node: Node) -> Vec<Declaration> {
        assert_eq!(node.kind(), "declarations");
        node.named_children(&mut node.walk())
            .map(|child| self.gen_declaration(child))
            .collect()
    }

    fn gen_commands(&mut self, node: Node) -> Vec<Command> {
        assert_eq!(node.kind(), "commands");
        node.named_children(&mut node.walk())
            .map(|child| self.gen_command(child))
            .collect()
    }

    fn gen_command(&mut self, node: Node) -> Command {
        assert_eq!(node.kind(), "command");

        let actual_command = node.child(0).unwrap();

        match actual_command.kind() {
            "assignment_command" => return self.gen_assignment(node),
            "if_else_command" => return self.gen_if_else(node),
            "if_command" => return self.gen_if(node),
            "while_command" => return self.gen_while(node),
            "repeat_until_command" => return self.gen_repeat(node),
            "for_to_command" => return self.gen_for_to(node),
            "for_downto_command" => return self.gen_for_downto(node),
            "procedure_call_command" => return self.gen_proc_call(node),
            "read_command" => return self.gen_read(node),
            "write_command" => return self.gen_write(node),
            _ => {
                unreachable!()
            }
        }
    }

    fn gen_expression(&self, node: Node) -> Expression {
        if let Some(val) = node.child_by_field_name("value") {
            return Expression::Value(self.gen_value(val));
        }
        let left = self.gen_value(node.child_by_field_name("left").unwrap());
        let op = self.get_text(node.child_by_field_name("op").unwrap());
        let right = self.gen_value(node.child_by_field_name("right").unwrap());

        match op.as_str().trim() {
            "+" => Expression::Addition(left, right),
            "-" => Expression::Subtraction(left, right),
            "*" => Expression::Multiplication(left, right),
            "/" => Expression::Division(left, right),
            "%" => Expression::Modulo(left, right),
            _ => {
                unreachable!()
            }
        }
    }

    fn gen_condition(&self, node: Node) -> Condition {
        let left = self.gen_value(node.child_by_field_name("left").unwrap());
        let op = self.get_text(node.child_by_field_name("op").unwrap());
        let right = self.gen_value(node.child_by_field_name("right").unwrap());

        match op.as_str() {
            "=" => Condition::Equal(left, right),
            "!=" => Condition::NotEqual(left, right),
            ">" => Condition::GreaterThan(left, right),
            "<" => Condition::LessThan(left, right),
            ">=" => Condition::GreaterOrEqual(left, right),
            "<=" => Condition::LessOrEqual(left, right),
            _ => {
                unreachable!()
            }
        }
    }

    fn gen_assignment(&self, node: Node) -> Command {
        assert_eq!(node.kind(), "command");

        Command::Assignment {
            identifier: self.gen_identifier(node.child_by_field_name("target").unwrap()),
            expression: self.gen_expression(node.child_by_field_name("expression").unwrap()),
            location: node.get_location(),
        }
    }

    fn gen_if_else(&mut self, node: Node) -> Command {
        assert_eq!(node.kind(), "command");
        Command::IfElse {
            condition: self.gen_condition(node.child_by_field_name("condition").unwrap()),
            then_commands: self.gen_commands(node.child_by_field_name("then_branch").unwrap()),
            else_commands: self.gen_commands(node.child_by_field_name("else_branch").unwrap()),
            location: node.get_location(),
        }
    }

    fn gen_if(&mut self, node: Node) -> Command {
        assert_eq!(node.kind(), "command");
        Command::If {
            condition: self.gen_condition(node.child_by_field_name("condition").unwrap()),
            then_commands: self.gen_commands(node.child_by_field_name("then_branch").unwrap()),
            location: node.get_location(),
        }
    }

    fn gen_while(&mut self, node: Node) -> Command {
        assert_eq!(node.kind(), "command");
        Command::While {
            condition: self.gen_condition(node.child_by_field_name("condition").unwrap()),
            commands: self.gen_commands(node.child_by_field_name("body").unwrap()),
            location: node.get_location(),
        }
    }

    fn gen_repeat(&mut self, node: Node) -> Command {
        assert_eq!(node.kind(), "command");
        Command::Repeat {
            commands: self.gen_commands(node.child_by_field_name("body").unwrap()),
            condition: self.gen_condition(node.child_by_field_name("condition").unwrap()),
            location: node.get_location(),
        }
    }

    fn gen_for_to(&mut self, node: Node) -> Command {
        assert_eq!(node.kind(), "command");
        Command::For {
            variable: self.get_text(node.child_by_field_name("variable").unwrap()),
            from: self.gen_value(node.child_by_field_name("start").unwrap()),
            to: self.gen_value(node.child_by_field_name("end").unwrap()),
            direction: ForDirection::Ascending,
            commands: self.gen_commands(node.child_by_field_name("body").unwrap()),
            location: node.get_location(),
        }
    }

    fn gen_for_downto(&mut self, node: Node) -> Command {
        assert_eq!(node.kind(), "command");
        Command::For {
            variable: self.get_text(node.child_by_field_name("variable").unwrap()),
            from: self.gen_value(node.child_by_field_name("start").unwrap()),
            to: self.gen_value(node.child_by_field_name("end").unwrap()),
            direction: ForDirection::Descending,
            commands: self.gen_commands(node.child_by_field_name("body").unwrap()),
            location: node.get_location(),
        }
    }

    fn gen_proc_call(&mut self, node: Node) -> Command {
        assert_eq!(node.kind(), "command");

        let proc_call_node = node.child_by_field_name("procedure_call").unwrap();
        let proc_name = self.get_text(proc_call_node.child_by_field_name("name").unwrap());

        let args = if let Some(args_node) = proc_call_node.child_by_field_name("arguments") {
            self.gen_args(args_node)
        } else {
            vec![]
        };

        if let None = self.ast.procedures.get(&proc_name) {
            self.print_message(Message::CodeMessage {
                severity: MessageSeverity::ERROR,
                message: format!("procedure {} not defined", proc_name).as_str(),
                location: node.get_location(),
            });
            self.ast.is_valid = false;
        }

        Command::ProcedureCall {
            proc_name: proc_name,
            arguments: args,
            location: node.get_location(),
        }
    }

    fn gen_read(&self, node: Node) -> Command {
        assert_eq!(node.kind(), "command");
        Command::Read(self.gen_identifier(node.child_by_field_name("target").unwrap()))
    }

    fn gen_write(&self, node: Node) -> Command {
        assert_eq!(node.kind(), "command");
        Command::Write(self.gen_value(node.child_by_field_name("value").unwrap()))
    }

    fn gen_args(&self, node: Node) -> Vec<Identifier> {
        assert_eq!(node.kind(), "args");
        node.named_children(&mut node.walk())
            .map(|child| Identifier {
                name: self.get_text(child),
                index: None,
                location: child.get_location(),
            })
            .collect()
    }

    fn gen_identifier(&self, node: Node) -> Identifier {
        let name = self.get_text(node.child_by_field_name("name").unwrap());

        let index = if let Some(index_node) = node.child_by_field_name("index") {
            match index_node.kind() {
                "num" => Some(Either::Right(self.get_text(index_node).parse().unwrap())),
                "pidentifier" => Some(Either::Left(self.get_text(index_node))),
                _ => {
                    unreachable!()
                }
            }
        } else {
            None
        };

        Identifier {
            name,
            index,
            location: node.get_location(),
        }
    }

    fn gen_value(&self, node: Node) -> Value {
        if let Some(num_node) = node.child_by_field_name("number") {
            Value::Number(self.get_text(num_node).parse().unwrap())
        } else if let Some(identifier_node) = node.child_by_field_name("identifier") {
            Value::Identifier(self.gen_identifier(identifier_node))
        } else {
            {
                unreachable!()
            }
        }
    }

    fn gen_declaration(&self, node: Node) -> Declaration {
        assert_eq!(node.kind(), "declaration");

        let name = self.get_text(node.child_by_field_name("identifier").unwrap());

        let location = node.get_location();

        let size = node
            .child_by_field_name("start")
            .zip(node.child_by_field_name("end"))
            .map(|(start, end)| {
                (
                    self.get_text(start).parse().unwrap(),
                    self.get_text(end).parse().unwrap(),
                )
            });

        Declaration {
            name,
            array_size: size,
            location,
        }
    }

    fn gen_args_decl(&self, node: Node) -> Vec<ProcArgument> {
        assert_eq!(node.kind(), "args_decl");

        let args = node
            .named_children(&mut node.walk())
            .map(|child| {
                let is_array = if let Some(_) = child.child_by_field_name("T") {
                    true
                } else {
                    false
                };

                ProcArgument {
                    name: self.get_text(child.child_by_field_name("name").unwrap()),
                    is_array,
                }
            })
            .collect();

        args
    }

    fn get_text(&self, node: Node) -> String {
        node.utf8_text(&self.source_code.as_bytes())
            .unwrap()
            .to_string()
    }
}
