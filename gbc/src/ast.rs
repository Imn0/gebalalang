use std::{fmt, ops::Not};

use crate::{ErrorDetails, MessageSeverity};

#[derive(Debug, Clone)]
pub struct AstFlags {
    pub has_mul: bool,
    pub has_div: bool,
    pub has_mod: bool,
}

#[derive(Debug, Clone)]
pub struct Ast {
    pub flags: AstFlags,
    pub procedures: Vec<Procedure>,
    pub main_block: MainBlock,
    pub location: (tree_sitter::Point, tree_sitter::Point),
}

#[derive(Debug, Clone)]
pub struct Procedure {
    pub name: String,
    pub args: Vec<ProcArgument>,
    pub declarations: Vec<Declaration>,
    pub commands: Vec<Command>,
    pub location: (tree_sitter::Point, tree_sitter::Point),
}

#[derive(Debug, Clone)]
pub struct MainBlock {
    pub declarations: Vec<Declaration>,
    pub commands: Vec<Command>,
    pub location: (tree_sitter::Point, tree_sitter::Point),
}

#[derive(Debug, Clone)]
pub enum Command {
    Assignment {
        identifier: Identifier,
        expression: Expression,
        location: (tree_sitter::Point, tree_sitter::Point),
    },
    IfElse {
        condition: Condition,
        then_commands: Vec<Command>,
        else_commands: Vec<Command>,
        location: (tree_sitter::Point, tree_sitter::Point),
    },
    If {
        condition: Condition,
        then_commands: Vec<Command>,
        location: (tree_sitter::Point, tree_sitter::Point),
    },
    While {
        condition: Condition,
        commands: Vec<Command>,
        location: (tree_sitter::Point, tree_sitter::Point),
    },
    Repeat {
        commands: Vec<Command>,
        condition: Condition,
        location: (tree_sitter::Point, tree_sitter::Point),
    },
    For {
        variable: String,
        from: Value,
        to: Value,
        direction: ForDirection,
        commands: Vec<Command>,
        location: (tree_sitter::Point, tree_sitter::Point),
    },
    ProcedureCall {
        proc_name: String,
        arguments: Vec<Identifier>,
        location: (tree_sitter::Point, tree_sitter::Point),
    },
    Read(Identifier),
    Write(Value),
}

#[derive(Debug, Clone)]
pub enum ForDirection {
    Ascending,
    Descending,
}

#[derive(Debug, Clone)]
pub enum Expression {
    Value(Value),
    Addition(Value, Value),
    Subtraction(Value, Value),
    Multiplication(Value, Value),
    Division(Value, Value),
    Modulo(Value, Value),
}

#[derive(Debug, Clone)]
pub enum Condition {
    Equal(Value, Value),
    NotEqual(Value, Value),
    GreaterThan(Value, Value),
    LessThan(Value, Value),
    GreaterOrEqual(Value, Value),
    LessOrEqual(Value, Value),
}

impl Not for Condition {
    type Output = Condition;

    fn not(self) -> Condition {
        match self {
            Condition::Equal(left, right) => Condition::NotEqual(left, right),
            Condition::NotEqual(left, right) => Condition::Equal(left, right),
            Condition::GreaterThan(left, right) => Condition::LessOrEqual(left, right),
            Condition::LessThan(left, right) => Condition::GreaterOrEqual(left, right),
            Condition::GreaterOrEqual(left, right) => Condition::LessThan(left, right),
            Condition::LessOrEqual(left, right) => Condition::GreaterThan(left, right),
        }
    }
}

#[derive(Debug, Clone)]
pub enum Value {
    Number(i64),
    Identifier(Identifier),
}

#[derive(Debug, Clone)]
pub struct Identifier {
    pub name: String,
    pub index: Option<Either<String, i64>>,
    pub location: (tree_sitter::Point, tree_sitter::Point),
}

#[derive(Debug, Clone)]
pub enum Either<L, R> {
    Left(L),
    Right(R),
}

#[derive(Debug, Clone)]
pub struct ProcArgument {
    pub name: String,
    pub is_array: bool,
}

#[derive(Debug, Clone)]
pub struct Declaration {
    pub name: String,
    pub array_size: Option<(i64, i64)>,
    pub location: (tree_sitter::Point, tree_sitter::Point),
}

// AST Builder
pub struct AstBuilder<'a> {
    source_code: &'a str,
    flags: AstFlags,
}

impl<'a> AstBuilder<'a> {
    pub fn new(source_code: &'a str) -> Self {
        Self {
            source_code,
            flags: AstFlags {
                has_mul: false,
                has_div: false,
                has_mod: false,
            },
        }
    }

    pub fn build_ast(&mut self, tree: &tree_sitter::Tree) -> Either<Ast, ErrorDetails> {
        let root_node = tree.root_node();
        let start = root_node.start_position();
        let end = root_node.end_position();

        let mut procedures = Vec::new();
        let mut main_block = None;

        for child in root_node.named_children(&mut root_node.walk()) {
            match child.kind() {
                "procedure" => {
                    procedures.push(self.parse_procedure(&child).unwrap());
                }
                "main" => {
                    main_block = Some(self.build_main_block(&child));
                }
                _ => {
                    panic!("unknown type {}", child.kind())
                }
            }
        }

        let ast = Ast {
            flags: self.flags.clone(),
            procedures,
            main_block: main_block.expect("Main block not found"),
            location: (start, end),
        };

        let rec_calls = ast.detect_recursive_calls();
        if rec_calls.len() > 0 {
            return Either::Right(ErrorDetails {
                message: format!(
                    "recursive calls are not allowed {} : {}",
                    rec_calls[0].procedure_name,
                    rec_calls[0].recursive_path.join(" <- ")
                ),
                location: rec_calls[0]
                    .location
                    .unwrap_or((tree_sitter::Point::default(), tree_sitter::Point::default())),
                severity: MessageSeverity::ERROR,
            });
        }

        return Either::Left(ast);
    }

    fn parse_procedure(&mut self, node: &tree_sitter::Node) -> Result<Procedure, String> {
        let start = node.start_position();
        let end = node.end_position();

        let mut procedure_name = String::new();
        let mut args = Vec::new();
        let mut declarations = Vec::new();
        let mut commands = Vec::new();

        let mut skip_next = false;

        for child in node.named_children(&mut node.walk()) {
            match child.kind() {
                "proc_head" => {
                    procedure_name = self.extract_text(&child.named_child(0).unwrap());
                    if let Some(args_decl_node) = &child.named_child(1) {
                        let mut cursor = args_decl_node.walk();
                        for arg_decl_node in args_decl_node.children(&mut cursor) {
                            if skip_next {
                                skip_next = false;
                                continue;
                            }

                            match arg_decl_node.kind() {
                                "T" => {
                                    let id =
                                        self.extract_text(&arg_decl_node.next_sibling().unwrap());
                                    args.push(ProcArgument {
                                        name: id,
                                        is_array: true,
                                    });
                                    skip_next = true;
                                }
                                "pidentifier" => {
                                    let id = self.extract_text(&arg_decl_node);
                                    args.push(ProcArgument {
                                        name: id,
                                        is_array: false,
                                    });
                                }
                                _ => {}
                            }
                        }
                    }
                }
                "declarations" => {
                    declarations = self.build_declarations(&child);
                }
                "commands" => {
                    commands = self.build_commands(&child);
                }
                _ => {
                    println!("{}", child.kind())
                }
            }
        }
        Ok(Procedure {
            name: procedure_name,
            args,
            declarations,
            commands,
            location: (start, end),
        })
    }

    fn build_main_block(&mut self, node: &tree_sitter::Node) -> MainBlock {
        let start = node.start_position();
        let end = node.end_position();
        let location = (start, end);
        let mut declarations = Vec::new();
        let mut commands = Vec::new();

        for child in node.named_children(&mut node.walk()) {
            match child.kind() {
                "declarations" => {
                    declarations = self.build_declarations(&child);
                }
                "commands" => {
                    commands = self.build_commands(&child);
                }
                _ => {
                    println!("unsupported {}", child.kind())
                }
            }
        }

        MainBlock {
            declarations,
            commands,
            location,
        }
    }
    fn build_commands(&mut self, node: &tree_sitter::Node) -> Vec<Command> {
        let mut commands = Vec::new();
        for child in node.children(&mut node.walk()) {
            match child.kind() {
                "command" => {
                    let cmd = self.parse_command(&child).unwrap();
                    commands.push(cmd);
                }
                _ => {}
            }
        }
        commands
    }

    fn parse_command(&mut self, node: &tree_sitter::Node) -> Result<Command, String> {
        let start = node.start_position();
        let end = node.end_position();
        let location = (start, end);
        for child in node.children(&mut node.walk()) {
            match child.kind() {
                _ if self.is_assignment_command(&child) => {
                    let identifier = self.parse_identifier(&child).unwrap();
                    let expression = self
                        .parse_expression(&child.next_sibling().unwrap().next_sibling().unwrap())
                        .unwrap();
                    return Ok(Command::Assignment {
                        identifier,
                        expression,
                        location,
                    });
                }
                "proc_call" => {
                    let proc_name = self.extract_text(&child.named_child(0).unwrap());

                    let mut arguments: Vec<Identifier> = vec![];
                    if let Some(args_node) = child.named_child(1) {
                        for arg_node in args_node.children(&mut args_node.walk()) {
                            if arg_node.kind() == "pidentifier" {
                                arguments.push(Identifier {
                                    name: self.extract_text(&arg_node),
                                    index: None,
                                    location,
                                });
                            }
                        }
                    }

                    return Ok(Command::ProcedureCall {
                        proc_name,
                        arguments: arguments,
                        location,
                    });
                }
                "WHILE" => {
                    let condition_node = child.next_sibling().unwrap();
                    let condition = self.parse_condition(&condition_node).unwrap();

                    let commands_node = condition_node.next_named_sibling().unwrap();
                    let commands = self.build_commands(&commands_node);

                    return Ok(Command::While {
                        condition: condition,
                        commands: commands,
                        location,
                    });
                }
                "REPEAT" => {
                    let commands_node = child.next_named_sibling().unwrap();
                    let commands = self.build_commands(&commands_node);

                    let condition_node = commands_node.next_named_sibling().unwrap();
                    let condition = self.parse_condition(&condition_node).unwrap();

                    return Ok(Command::Repeat {
                        condition: condition,
                        commands: commands,
                        location,
                    });
                }
                "FOR" => {
                    let var_node = child.next_named_sibling().unwrap();
                    let var = self.extract_text(&var_node);

                    let direction: ForDirection;

                    let from_node = var_node.next_named_sibling().unwrap();
                    let from = self.parse_value(&from_node).unwrap();

                    if from_node.next_sibling().unwrap().kind() == "TO" {
                        direction = ForDirection::Ascending;
                    } else if from_node.next_sibling().unwrap().kind() == "DOWNTO" {
                        direction = ForDirection::Descending;
                    } else {
                        return Err(format!(
                            "Unsupported for direction {}",
                            from_node.next_sibling().unwrap().kind(),
                        ));
                    }

                    let to_node = from_node.next_named_sibling().unwrap();
                    let to = self.parse_value(&to_node).unwrap();

                    let commands_node = to_node.next_named_sibling().unwrap();
                    let commands = self.build_commands(&commands_node);

                    return Ok(Command::For {
                        variable: var,
                        from: from,
                        to: to,
                        direction: direction,
                        commands: commands,
                        location,
                    });
                }
                "IF" => {
                    let condition_node = child.next_sibling().unwrap();
                    let condition = self.parse_condition(&condition_node).unwrap();

                    let then_node = condition_node
                        .next_sibling()
                        .unwrap()
                        .next_sibling()
                        .unwrap();
                    let then_commands = self.build_commands(&then_node);

                    if let Some(else_node) = then_node.next_sibling().unwrap().next_sibling() {
                        let else_commands = self.build_commands(&else_node);
                        return Ok(Command::IfElse {
                            condition: condition,
                            then_commands: then_commands,
                            else_commands: else_commands,
                            location,
                        });
                    } else {
                        return Ok(Command::If {
                            condition: condition,
                            then_commands: then_commands,
                            location,
                        });
                    }
                }
                "READ" => {
                    let identifier = self
                        .parse_identifier(&child.next_sibling().unwrap())
                        .unwrap();
                    return Ok(Command::Read(identifier));
                }
                "WRITE" => {
                    let value = self.parse_value(&child.next_sibling().unwrap()).unwrap();
                    return Ok(Command::Write(value));
                }
                _ => {
                    return Err(format!("unsupported {}", child.kind()));
                }
            }
        }
        return Err(format!("unsupported {}", node.kind()));
    }

    fn parse_condition(&self, node: &tree_sitter::Node) -> Result<Condition, String> {
        assert_eq!(node.kind(), "condition");

        let left_side = self.parse_value(&node.child(0).unwrap()).unwrap();
        let right_side = self.parse_value(&node.child(2).unwrap()).unwrap();

        let operator = node
            .child(1)
            .and_then(|op| op.utf8_text(self.source_code.as_bytes()).ok())
            .ok_or("No operator found")?;

        match operator {
            "=" => Ok(Condition::Equal(left_side, right_side)),
            "!=" => Ok(Condition::NotEqual(left_side, right_side)),
            ">" => Ok(Condition::GreaterThan(left_side, right_side)),
            "<" => Ok(Condition::LessThan(left_side, right_side)),
            ">=" => Ok(Condition::GreaterOrEqual(left_side, right_side)),
            "<=" => Ok(Condition::LessOrEqual(left_side, right_side)),
            _ => Err(format!("Unknown condition operator: {}", operator)),
        }
    }

    fn parse_expression(&mut self, node: &tree_sitter::Node) -> Result<Expression, String> {
        assert_eq!(node.kind(), "expression");

        let child = node.child(0).ok_or("Empty expression")?;

        let first_val = self.parse_value(&child)?;

        if let Some(op) = child.next_sibling() {
            let second_val = self.parse_value(&op.next_sibling().unwrap()).unwrap();
            match op.kind() {
                "+" => Ok(Expression::Addition(first_val, second_val)),
                "-" => Ok(Expression::Subtraction(first_val, second_val)),
                "*" => {
                    self.flags.has_mul = true;
                    Ok(Expression::Multiplication(first_val, second_val))
                }
                "/" => {
                    self.flags.has_div = true;
                    Ok(Expression::Division(first_val, second_val))
                }
                "%" => {
                    self.flags.has_mod = true;
                    Ok(Expression::Modulo(first_val, second_val))
                }

                _ => {
                    return Err(format!("unsupported expression {}", op.kind()));
                }
            }
        } else {
            return Ok(Expression::Value(first_val));
        }
    }

    fn build_declarations(&self, node: &tree_sitter::Node) -> Vec<Declaration> {
        let mut declarations = Vec::new();

        for child in node.children(&mut node.walk()) {
            match child.kind() {
                "declaration" => {
                    declarations.push(self.build_declaration(&child).unwrap());
                }
                _ => {}
            }
        }

        declarations
    }

    fn build_declaration(&self, node: &tree_sitter::Node) -> Option<Declaration> {
        for child in node.children(&mut node.walk()) {
            let start = child.start_position();
            let end = child.end_position();
            let location = (start, end);
            match child.kind() {
                "pidentifier" => {
                    if let Some(next_sibling) = child.next_sibling() {
                        if next_sibling.kind() == "[" {
                            if let Some(first_num) = next_sibling.next_sibling() {
                                let start: i64 = self.extract_text(&first_num).parse().unwrap();
                                let end: i64 = self
                                    .extract_text(
                                        &first_num.next_sibling().unwrap().next_sibling().unwrap(),
                                    )
                                    .parse()
                                    .unwrap();
                                return Some(Declaration {
                                    name: self.extract_text(&child),
                                    array_size: Some((start, end)),
                                    location: location,
                                });
                            }
                        }
                    }

                    return Some(Declaration {
                        name: self.extract_text(&child),
                        array_size: None,
                        location: location,
                    });
                }
                _ => {
                    panic!("{}", child.kind());
                }
            }
        }
        None
    }

    fn parse_value(&self, node: &tree_sitter::Node) -> Result<Value, String> {
        assert_eq!(node.kind(), "value");
        for child in node.children(&mut node.walk()) {
            match child.kind() {
                "identifier" => {
                    let identifier = self.parse_identifier(&child).unwrap();
                    return Ok(Value::Identifier(identifier));
                }
                "num" => {
                    let num = self
                        .extract_text(&child)
                        .parse::<i64>()
                        .map_err(|_| "Invalid numeric index")?;
                    return Ok(Value::Number(num));
                }
                _ => {
                    return Err(format!("Unsupported value type: {}", child.kind(),));
                }
            }
        }
        Err(format!(""))
    }

    fn parse_identifier(&self, node: &tree_sitter::Node) -> Result<Identifier, String> {
        let start = node.start_position();
        let end = node.start_position();
        let mut name = String::new();
        let mut index = None;
        for child in node.named_children(&mut node.walk()) {
            match child.kind() {
                "pidentifier" => {
                    if name.is_empty() {
                        name = self.extract_text(&child);
                    } else {
                        index = Some(Either::Left(self.extract_text(&child)));
                    }
                }
                "num" => {
                    let num = self
                        .extract_text(&child)
                        .parse::<i64>()
                        .map_err(|_| "Invalid numeric index")?;
                    index = Some(Either::Right(num));
                }
                _ => {
                    return Err(format!("Unsupported {}", child.kind()));
                }
            }
        }

        Ok(Identifier {
            name,
            index,
            location: (start, end),
        })
    }

    fn is_assignment_command(&self, node: &tree_sitter::Node) -> bool {
        if node.kind() != "identifier" {
            return false;
        }

        node.next_sibling()
            .map(|op| self.extract_text(&op) == ":=")
            .unwrap_or(false)
    }

    fn extract_text(&self, node: &tree_sitter::Node) -> String {
        node.utf8_text(self.source_code.as_bytes())
            .unwrap()
            .to_string()
    }
}
