use clap::Parser;
use serde::Serialize;
use serde_json::de;
use std::cmp::Ordering;
use std::collections::HashSet;
use std::fs::File;
use std::io::{self, Write};
use std::ops::Not;
use std::result;
use std::{collections::HashMap, fmt, fs, vec};
use tree_sitter_gbl::LANGUAGE;

#[derive(Debug, Clone)]
pub struct Ast {
    pub procedures: Vec<Procedure>,
    pub main_block: Block,
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
pub struct Block {
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
#[derive(Debug, Clone)]
pub struct RecursiveCallInfo {
    pub procedure_name: String,
    pub recursive_path: Vec<String>,
    pub location: Option<(tree_sitter::Point, tree_sitter::Point)>,
}

impl Ast {
    pub fn detect_recursive_calls(&self) -> Vec<RecursiveCallInfo> {
        let mut recursive_calls = Vec::new();

        let call_graph = self.build_call_graph();
        let call_locations = self.build_call_locations();

        for procedure in &self.procedures {
            let mut visited_procedures = HashSet::new();
            if self.is_recursive(&call_graph, &procedure.name, &mut visited_procedures) {
                let recursive_path: Vec<String> = visited_procedures.into_iter().collect();

                let first_recursive_call_location = self.find_first_recursive_call_location(
                    &procedure.name,
                    &call_graph,
                    &call_locations,
                );

                recursive_calls.push(RecursiveCallInfo {
                    procedure_name: procedure.name.clone(),
                    recursive_path,
                    location: first_recursive_call_location,
                });
            }
        }

        return recursive_calls;
    }

    fn build_call_graph(&self) -> HashMap<String, HashSet<String>> {
        let mut graph = HashMap::new();

        for procedure in &self.procedures {
            graph
                .entry(procedure.name.clone())
                .or_insert_with(HashSet::new);

            let calls = self.find_procedure_calls(&procedure.commands);
            graph.get_mut(&procedure.name).unwrap().extend(calls);
        }

        return graph;
    }

    fn build_call_locations(
        &self,
    ) -> HashMap<(String, String), (tree_sitter::Point, tree_sitter::Point)> {
        let mut locations = HashMap::new();

        for procedure in &self.procedures {
            self.record_call_locations(&procedure.name, &procedure.commands, &mut locations);
        }

        return locations;
    }

    fn record_call_locations(
        &self,
        current_proc: &str,
        commands: &[Command],
        locations: &mut HashMap<(String, String), (tree_sitter::Point, tree_sitter::Point)>,
    ) {
        for command in commands {
            match command {
                Command::ProcedureCall {
                    proc_name,
                    location,
                    ..
                } => {
                    locations.insert((current_proc.to_string(), proc_name.clone()), *location);
                }
                Command::IfElse {
                    then_commands,
                    else_commands,
                    ..
                } => {
                    self.record_call_locations(current_proc, then_commands, locations);
                    self.record_call_locations(current_proc, else_commands, locations);
                }
                Command::If { then_commands, .. } => {
                    self.record_call_locations(current_proc, then_commands, locations);
                }
                Command::While { commands, .. } => {
                    self.record_call_locations(current_proc, commands, locations);
                }
                Command::Repeat { commands, .. } => {
                    self.record_call_locations(current_proc, commands, locations);
                }
                Command::For { commands, .. } => {
                    self.record_call_locations(current_proc, commands, locations);
                }
                _ => {}
            }
        }
    }

    fn find_first_recursive_call_location(
        &self,
        procedure_name: &str,
        call_graph: &HashMap<String, HashSet<String>>,
        call_locations: &HashMap<(String, String), (tree_sitter::Point, tree_sitter::Point)>,
    ) -> Option<(tree_sitter::Point, tree_sitter::Point)> {
        for (calling_proc, called_procs) in call_graph {
            if called_procs.contains(procedure_name) {
                if let Some(location) =
                    call_locations.get(&(calling_proc.to_string(), procedure_name.to_string()))
                {
                    return Some(*location);
                }
            }
        }
        return None;
    }

    fn find_procedure_calls(&self, commands: &[Command]) -> HashSet<String> {
        let mut calls = HashSet::new();

        for command in commands {
            match command {
                Command::ProcedureCall { proc_name, .. } => {
                    calls.insert(proc_name.clone());
                }
                Command::IfElse {
                    then_commands,
                    else_commands,
                    ..
                } => {
                    calls.extend(self.find_procedure_calls(then_commands));
                    calls.extend(self.find_procedure_calls(else_commands));
                }
                Command::If { then_commands, .. } => {
                    calls.extend(self.find_procedure_calls(then_commands));
                }
                Command::While { commands, .. } => {
                    calls.extend(self.find_procedure_calls(commands));
                }
                Command::Repeat { commands, .. } => {
                    calls.extend(self.find_procedure_calls(commands));
                }
                Command::For { commands, .. } => {
                    calls.extend(self.find_procedure_calls(commands));
                }
                _ => {}
            }
        }

        return calls;
    }

    fn is_recursive(
        &self,
        call_graph: &HashMap<String, HashSet<String>>,
        procedure_name: &str,
        visited: &mut HashSet<String>,
    ) -> bool {
        if visited.contains(procedure_name) {
            return true;
        }

        visited.insert(procedure_name.to_string());

        if let Some(called_procedures) = call_graph.get(procedure_name) {
            for called_proc in called_procedures {
                if self.is_recursive(call_graph, called_proc, visited) {
                    return true;
                }
            }
        }

        visited.remove(procedure_name);
        return false;
    }
}
// AST Builder
pub struct AstBuilder<'a> {
    source_code: &'a str,
}

impl<'a> AstBuilder<'a> {
    pub fn new(source_code: &'a str) -> Self {
        Self { source_code }
    }

    pub fn build_ast(&self, tree: &tree_sitter::Tree) -> Ast {
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

        Ast {
            procedures,
            main_block: main_block.expect("Main block not found"),
            location: (start, end),
        }
    }

    fn parse_procedure(&self, node: &tree_sitter::Node) -> Result<Procedure, String> {
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

    fn build_main_block(&self, node: &tree_sitter::Node) -> Block {
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

        Block {
            declarations,
            commands,
            location,
        }
    }
    fn build_commands(&self, node: &tree_sitter::Node) -> Vec<Command> {
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

    fn parse_command(&self, node: &tree_sitter::Node) -> Result<Command, String> {
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

    fn parse_expression(&self, node: &tree_sitter::Node) -> Result<Expression, String> {
        assert_eq!(node.kind(), "expression");

        let child = node.child(0).ok_or("Empty expression")?;

        let first_val = self.parse_value(&child)?;

        if let Some(op) = child.next_sibling() {
            let second_val = self.parse_value(&op.next_sibling().unwrap()).unwrap();
            match op.kind() {
                "+" => Ok(Expression::Addition(first_val, second_val)),
                "-" => Ok(Expression::Subtraction(first_val, second_val)),
                "*" => Ok(Expression::Multiplication(first_val, second_val)),
                "/" => Ok(Expression::Division(first_val, second_val)),
                "%" => Ok(Expression::Modulo(first_val, second_val)),

                _ => {
                    return Err(format!("unsuported expression {}", op.kind()));
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

#[derive(Parser, Debug)]
#[command(
    version = "1.0",
    about = "A CLI tool for processing input files and specifying output files.",
    long_about = "This is a longer description of the tool. It processes input files specified as a positional argument and writes results to the specified output file."
)]
struct Args {
    #[arg(help = "Specify the input file.")]
    input: String,

    #[arg(short, long, default_value = "a.mr", help = "Specify the output file.")]
    out: String,
}

fn find_most_specific_error(node: tree_sitter::Node, code: &str) -> ErrorDetails {
    if node.is_error() {
        return ErrorDetails {
            message: format!("Syntax error in {}", node.kind()),
            location: (node.start_position(), node.end_position()),
            severity: MessageSeverity::ERROR,
        };
    }

    let mut most_specific_error = None;
    let mut most_specific_depth = 0;

    for child in node.children(&mut node.walk()) {
        if !child.has_error() {
            continue;
        }

        let child_error = find_most_specific_error(child, code);

        let child_depth = count_node_depth(child);

        if most_specific_error.is_none() || child_depth > most_specific_depth {
            most_specific_error = Some(child_error);
            most_specific_depth = child_depth;
        }
    }

    if let Some(error) = most_specific_error {
        return error;
    }

    ErrorDetails {
        message: format!("Syntax error in {}", node.kind()),
        location: (node.start_position(), node.end_position()),
        severity: MessageSeverity::ERROR,
    }
}

fn count_node_depth(node: tree_sitter::Node) -> usize {
    let mut depth = 0;
    let mut current = node;

    while let Some(parent) = current.parent() {
        depth += 1;
        current = parent;
    }

    depth
}

#[derive(Debug, Clone)]
pub struct ErrorDetails {
    pub message: String,
    pub location: (tree_sitter::Point, tree_sitter::Point),
    pub severity: MessageSeverity,
}

#[derive(Debug, Clone, PartialEq, Eq, PartialOrd, Ord)]
pub enum MessageSeverity {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
}
impl MessageSeverity {
    fn color_code(&self) -> &str {
        match self {
            MessageSeverity::DEBUG => "\x1b[90m",   // Gray
            MessageSeverity::INFO => "\x1b[34m",    // Blue
            MessageSeverity::WARNING => "\x1b[33m", // Yellow
            MessageSeverity::ERROR => "\x1b[31m",   // Red
            MessageSeverity::FATAL => "\x1b[1;31m", // Bright Red
        }
    }

    fn prefix(&self) -> &str {
        match self {
            MessageSeverity::DEBUG => "[DEBUG] ",
            MessageSeverity::INFO => "[INFO]  ",
            MessageSeverity::WARNING => "[WARN]  ",
            MessageSeverity::ERROR => "[ERROR] ",
            MessageSeverity::FATAL => "[FATAL] ",
        }
    }
}

pub struct SourceContext<'a> {
    code: &'a str,
    filename: &'a str,
    messages: Vec<ErrorDetails>,
}

impl<'a> SourceContext<'a> {
    pub fn new(code: &'a str, filename: &'a str) -> Self {
        Self {
            code,
            filename,
            messages: Vec::new(),
        }
    }

    pub fn add_message(&mut self, message: ErrorDetails) {
        self.messages.push(message);
    }

    pub fn add_messages(&mut self, messages: Vec<ErrorDetails>) {
        self.messages.extend(messages);
    }

    pub fn display(&self) -> io::Result<()> {
        let mut sorted_messages = self.messages.clone();
        sorted_messages.sort_by(|a, b| match a.location.0.row.cmp(&b.location.0.row) {
            Ordering::Equal => b.severity.cmp(&a.severity),
            row_order => row_order,
        });

        let stderr = &mut io::stderr();
        let lines: Vec<&str> = self.code.lines().collect();

        for error in sorted_messages {
            let start_line = error.location.0.row.max(0);

            writeln!(
                stderr,
                "{}{}{}\x1b[0m",
                error.severity.color_code(),
                error.severity.prefix(),
                error.message
            )?;
            writeln!(
                stderr,
                "\x1b[1;34m{:4}\x1b[0m {} {}:{}:{}",
                "",
                "--->",
                self.filename,
                start_line + 1,
                error.location.1.column + 1
            )?;
            writeln!(
                stderr,
                "\x1b[1;34m{:4} |\x1b[0m {}",
                start_line + 1,
                lines[start_line]
            )?;

            write!(stderr, "\x1b[1;34m     |\x1b[0m ")?;

            for _ in 0..error.location.0.column {
                write!(stderr, " ")?;
            }

            write!(stderr, "{}", error.severity.color_code())?;

            if error.location.1.column > error.location.0.column {
                for _ in error.location.0.column + 1..error.location.1.column {
                    write!(stderr, "^")?;
                }
            }

            writeln!(stderr)?;
        }

        Ok(())
    }
}

fn main() -> std::io::Result<()> {
    let args = Args::parse();
    let input_file = args.input;

    let mut parser = tree_sitter::Parser::new();
    parser
        .set_language(&LANGUAGE.into())
        .expect("Error loading Gbl parser");

    let code =
        fs::read_to_string(input_file.clone()).expect("Should have been able to read the file");

    let ast_builder = AstBuilder::new(&code);
    let tree = parser
        .parse(&code, None)
        .expect("Failed to parse source code");

    let root_node = tree.root_node();

    if root_node.has_error() {
        let error_details = find_most_specific_error(root_node, &code);
        let mut context = SourceContext::new(code.as_str(), &input_file);
        context.add_message(error_details);
        context.display()?;
        std::process::exit(1);
    }

    let ast = ast_builder.build_ast(&tree);
    // print!("{:#?}", ast);
    let optimized_ast = optimize_ast(ast);
    let mut codeb = CodeGenerator::new();
    codeb.generate_asm(optimized_ast);

    let is_error: bool = codeb
        .messages
        .iter()
        .filter(|m| m.severity == MessageSeverity::ERROR || m.severity == MessageSeverity::FATAL)
        .collect::<Vec<&ErrorDetails>>()
        .len()
        > 0;

    let mut context = SourceContext::new(code.as_str(), &input_file);
    context.add_messages(codeb.messages.clone());
    context.display()?;

    if is_error {
        std::process::exit(1);
    }

    let asm: Vec<ASM> = codeb.assembly_code.clone();

    let mut output = String::new();

    for instruction in &asm {
        output += &format!("{}\n", instruction);
    }
    println!("{}", output);
    let mut file = File::create(args.out)?;
    file.write_all(output.as_bytes())?;
    codeb.save_dbg_info("da");
    Ok(())
}

fn optimize_ast(ast: Ast) -> Ast {
    ast
}

#[derive(Clone)]
/// Represents the set of assembly-like instructions for a virtual machine.
///
/// ## Memory and Program Counter
/// - Memory `p_i` is indexed by `i = 0, 1, 2, 3, ..., 2^62` and is not initialized.
/// - `p_0` is the accumulator.
/// - `k` is the program counter.
pub enum ASM {
    /// Reads a number from the user and stores it in `p_i`.
    /// - **Effect**: `p_i = user_input`
    /// - **Cost**: 100
    /// - **Program Counter**: `k += 1`
    GET(usize),

    /// Prints the number stored in `p_i`.
    /// - **Effect**: Outputs `p_i`
    /// - **Cost**: 100
    /// - **Program Counter**: `k += 1`
    PUT(usize),

    /// Loads the value from `p_i` into `p_0` (accumulator).
    /// - **Effect**: `p_0 = p_i`
    /// - **Cost**: 10
    /// - **Program Counter**: `k += 1`
    LOAD(usize),

    /// Stores the value from `p_0` (accumulator) into `p_i`.
    /// - **Effect**: `p_i = p_0`
    /// - **Cost**: 10
    /// - **Program Counter**: `k += 1`
    STORE(usize),

    /// Loads the value from the memory address `p_i` into `p_0`.
    /// - **Effect**: `p_0 = p_{p_i}`
    /// - **Cost**: 20
    /// - **Program Counter**: `k += 1`
    LOADI(usize),

    /// Stores the value from `p_0` into the memory address `p_i`.
    /// - **Effect**: `p_{p_i} = p_0`
    /// - **Cost**: 20
    /// - **Program Counter**: `k += 1`
    STOREI(usize),

    /// Adds the value of `p_i` to `p_0`.
    /// - **Effect**: `p_0 += p_i`
    /// - **Cost**: 10
    /// - **Program Counter**: `k += 1`
    ADD(usize),

    /// Subtracts the value of `p_i` from `p_0`.
    /// - **Effect**: `p_0 -= p_i`
    /// - **Cost**: 10
    /// - **Program Counter**: `k += 1`
    SUB(usize),

    /// Adds the value at the address `p_{p_i}` to `p_0`.
    /// - **Effect**: `p_0 += p_{p_i}`
    /// - **Cost**: 20
    /// - **Program Counter**: `k += 1`
    ADDI(usize),

    /// Subtracts the value at the address `p_{p_i}` from `p_0`.
    /// - **Effect**: `p_0 -= p_{p_i}`
    /// - **Cost**: 20
    /// - **Program Counter**: `k += 1`
    SUBI(usize),

    /// Sets `p_0` to a constant value `x`.
    /// - **Effect**: `p_0 = x`
    /// - **Cost**: 50
    /// - **Program Counter**: `k += 1`
    SET(i64),

    /// Halves the value of `p_0` (integer division).
    /// - **Effect**: `p_0 = floor(p_0 / 2)`
    /// - **Cost**: 5
    /// - **Program Counter**: `k += 1`
    HALF,

    /// Jumps to a relative address by adding `j` to the program counter.
    /// - **Effect**: `k += j`
    /// - **Cost**: 1
    JUMP(i64),

    /// Jumps to a relative address `j` if `p_0 > 0`. Otherwise, increments `k` by 1.
    /// - **Effect**: `p_0 > 0 ? k += j : k += 1`
    /// - **Cost**: 1
    JPOS(i64),

    /// Jumps to a relative address `j` if `p_0 == 0`. Otherwise, increments `k` by 1.
    /// - **Effect**: `p_0 == 0 ? k += j : k += 1`
    /// - **Cost**: 1
    JZERO(i64),

    /// Jumps to a relative address `j` if `p_0 < 0`. Otherwise, increments `k` by 1.
    /// - **Effect**: `p_0 < 0 ? k += j : k += 1`
    /// - **Cost**: 1
    JNEG(i64),

    /// Sets the program counter to `p_i`.
    /// - **Effect**: `k = p_i`
    /// - **Cost**: 10
    RTRN(usize),

    /// Halts the program.
    /// - **Effect**: Stops execution.
    /// - **Cost**: 0
    HALT,
}

impl fmt::Display for ASM {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            ASM::GET(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "GET {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "GET {}", val)
                }
            }
            ASM::PUT(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "PUT {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "PUT {}", val)
                }
            }
            ASM::LOAD(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "LOAD {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "LOAD {}", val)
                }
            }
            ASM::STORE(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "STORE {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "STORE {}", val)
                }
            }
            ASM::LOADI(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "LOADI {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "LOADI {}", val)
                }
            }
            ASM::STOREI(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "STOREI {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "STOREI {}", val)
                }
            }
            ASM::ADD(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "ADD {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "ADD {}", val)
                }
            }
            ASM::SUB(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "SUB {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "SUB {}", val)
                }
            }
            ASM::ADDI(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "ADDI {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "ADDI {}", val)
                }
            }
            ASM::SUBI(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "SUBI {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "SUBI {}", val)
                }
            }
            ASM::SET(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "SET {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "SET {}", val)
                }
            }
            ASM::HALF => write!(f, "HALF"),
            ASM::JUMP(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "JUMP {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "JUMP {}", val)
                }
            }
            ASM::JPOS(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "JPOS {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "JPOS {}", val)
                }
            }
            ASM::JZERO(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "JZERO {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "JZERO {}", val)
                }
            }
            ASM::JNEG(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "JNEG {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "JNEG {}", val)
                }
            }
            ASM::RTRN(val) => {
                if val.clone() > 0x2000000000000000 {
                    write!(f, "RTRN {} # \t0x{:x}", val, val)
                } else {
                    write!(f, "RTRN {}", val)
                }
            }
            ASM::HALT => write!(f, "HALT"),
        }
    }
}

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

struct CodeGenerator {
    symbols: HashMap<String, SymbolLocation>,
    procedures: HashMap<String, ProcedureInfo>,
    next_memory_slot: usize,
    last_mem_slot: usize,
    assembly_code: Vec<ASM>,
    messages: Vec<ErrorDetails>,
    current_scope: String,
}

impl CodeGenerator {
    fn new() -> Self {
        CodeGenerator {
            symbols: HashMap::new(),
            procedures: HashMap::new(),
            next_memory_slot: 1,
            last_mem_slot: 0x4000000000000000,
            assembly_code: Vec::new(),
            messages: Vec::new(),
            current_scope: "".to_owned(),
        }
    }

    fn push_asm(&mut self, ins: ASM) {
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
                self.push_asm(ASM::SET(num.clone())); // ! CONSTANT
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
                                    message: "cannot acces it like that".to_owned(),
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
                                    message: format!("Cannot acces {} like that.", ident.name),
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
                                    self.push_asm(ASM::SET(base_loc.memory as i64));
                                    self.push_asm(ASM::ADD(idx_loc.memory));
                                    self.push_asm(ASM::LOADI(0));
                                }
                                (true, false) => {
                                    self.push_asm(ASM::LOAD(base_loc.memory));
                                    self.push_asm(ASM::ADD(idx_loc.memory));
                                    self.push_asm(ASM::LOADI(0));
                                }
                                (false, true) => {
                                    self.push_asm(ASM::LOAD(idx_loc.memory));
                                    self.push_asm(ASM::ADD(base_loc.memory));
                                    self.push_asm(ASM::LOADI(0));
                                }
                                (true, true) => {
                                    self.push_asm(ASM::LOADI(idx_loc.memory));
                                    self.push_asm(ASM::ADD(base_loc.memory));
                                    self.push_asm(ASM::LOADI(0));
                                }
                            }
                        }
                        Either::Right(idx_num) => {
                            let symbol_loc = self.get_variable_current_scope(&ident.name).unwrap();
                            if !symbol_loc.is_array {
                                self.messages.push(ErrorDetails {
                                    message: "cannot acces it like that".to_owned(),
                                    location: ident.location,
                                    severity: MessageSeverity::WARNING,
                                });
                            }
                            if !symbol_loc.is_pointer {
                                let loc = self.get_variable_w_idx(&ident.name, *idx_num);
                                self.push_asm(ASM::LOAD(loc.memory));
                            } else {
                                self.push_asm(ASM::SET(*idx_num));
                                self.assembly_code.push(ASM::ADD(symbol_loc.memory));
                                self.push_asm(ASM::LOADI(0));
                            }
                        }
                    }
                } else {
                    let result = self.get_variable_current_scope(&ident.name);
                    if let Ok(loc) = result {
                        if loc.is_array {
                            self.messages.push(ErrorDetails {
                                message: "cannot acces it like thatdaw".to_owned(),
                                location: ident.location,
                                severity: MessageSeverity::WARNING,
                            });
                        }
                        if loc.is_pointer {
                            self.push_asm(ASM::LOADI(loc.memory));
                        } else {
                            self.push_asm(ASM::LOAD(loc.memory));
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
                    self.assembly_code.push(ASM::STORE(self.last_mem_slot - 1));

                    if !dst_loc.is_array {
                        self.messages.push(ErrorDetails {
                            message: format!("Cannot acces {} it like that", ident.name),
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
                            message: format!("Cannot acces {} it like that", idx_name),
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
                            self.push_asm(ASM::SET(dst_loc.memory as i64));
                            self.push_asm(ASM::ADD(idx_loc.memory));
                            self.push_asm(ASM::STORE(self.last_mem_slot));

                            self.push_asm(ASM::LOAD(self.last_mem_slot - 1));
                            self.push_asm(ASM::STOREI(self.last_mem_slot));
                        }
                        (true, false) => {
                            self.push_asm(ASM::LOAD(dst_loc.memory));
                            self.push_asm(ASM::ADD(idx_loc.memory));
                            self.push_asm(ASM::STORE(self.last_mem_slot));

                            self.push_asm(ASM::LOAD(self.last_mem_slot - 1));
                            self.push_asm(ASM::STOREI(self.last_mem_slot));
                        }
                        (false, true) => {
                            self.push_asm(ASM::LOAD(idx_loc.memory));
                            self.push_asm(ASM::ADD(dst_loc.memory));
                            self.push_asm(ASM::STORE(self.last_mem_slot));

                            self.push_asm(ASM::LOAD(self.last_mem_slot - 1));
                            self.push_asm(ASM::STOREI(self.last_mem_slot));
                        }
                        (true, true) => {
                            self.push_asm(ASM::LOADI(idx_loc.memory));
                            self.push_asm(ASM::ADD(dst_loc.memory));
                            self.push_asm(ASM::STORE(self.last_mem_slot));

                            self.push_asm(ASM::LOAD(self.last_mem_slot - 1));
                            self.push_asm(ASM::STOREI(self.last_mem_slot));
                        }
                    }
                }
                Either::Right(idx_num) => {
                    let dest_loc = self.get_variable_current_scope(&ident.name).unwrap();
                    if !dest_loc.is_array {
                        self.messages.push(ErrorDetails {
                            message: "cannot acces it like that".to_owned(),
                            location: ident.location,
                            severity: MessageSeverity::WARNING,
                        });
                    }
                    if !dest_loc.is_pointer {
                        let final_loc = self.get_variable_w_idx(&ident.name, *idx_num);
                        self.push_asm(ASM::STORE(final_loc.memory));
                    } else {
                        self.push_asm(ASM::STORE(self.last_mem_slot - 1));
                        self.push_asm(ASM::SET(*idx_num));
                        self.push_asm(ASM::ADD(dest_loc.memory));
                        self.push_asm(ASM::STORE(self.last_mem_slot + 0));
                        self.push_asm(ASM::LOAD(self.last_mem_slot - 1));
                        self.push_asm(ASM::STOREI(self.last_mem_slot + 0));
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
                    message: "cannot acces it like that".to_owned(),
                    location: ident.location,
                    severity: MessageSeverity::WARNING,
                });
            }

            if dest_loc.is_pointer {
                self.assembly_code.push(ASM::STOREI(dest_loc.memory));
            } else {
                self.assembly_code.push(ASM::STORE(dest_loc.memory));
            }
        }
    }

    fn generate_condition(&mut self, condition: &Condition) -> ASM {
        match condition {
            Condition::NotEqual(left, right) => {
                self.generate_value(left);
                self.assembly_code.push(ASM::STORE(self.last_mem_slot));
                self.generate_value(right);
                self.assembly_code.push(ASM::SUB(self.last_mem_slot));
                ASM::JZERO(0)
            }
            Condition::Equal(left, right) => {
                self.generate_value(left);
                self.assembly_code.push(ASM::STORE(self.last_mem_slot));
                self.generate_value(right);
                self.assembly_code.push(ASM::SUB(self.last_mem_slot));
                self.push_asm(ASM::JZERO(2));
                ASM::JUMP(0)
            }
            Condition::LessOrEqual(left, right) => {
                self.generate_value(right);
                self.assembly_code.push(ASM::STORE(self.last_mem_slot));
                self.generate_value(left);
                self.assembly_code.push(ASM::SUB(self.last_mem_slot));
                ASM::JPOS(0)
            }
            Condition::GreaterOrEqual(left, right) => {
                self.generate_value(left);
                self.assembly_code.push(ASM::STORE(self.last_mem_slot));
                self.generate_value(right);
                self.assembly_code.push(ASM::SUB(self.last_mem_slot));
                ASM::JPOS(0)
            }
            Condition::GreaterThan(left, right) => {
                self.generate_value(right);
                self.assembly_code.push(ASM::STORE(self.last_mem_slot));
                self.generate_value(left);
                self.assembly_code.push(ASM::SUB(self.last_mem_slot));
                self.push_asm(ASM::JPOS(2));
                ASM::JUMP(0)
            }
            Condition::LessThan(left, right) => {
                self.generate_value(left);
                self.assembly_code.push(ASM::STORE(self.last_mem_slot));
                self.generate_value(right);
                self.assembly_code.push(ASM::SUB(self.last_mem_slot));
                self.push_asm(ASM::JPOS(2));
                ASM::JUMP(0)
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
                    self.assembly_code.push(ASM::STORE(self.last_mem_slot));
                    self.generate_value(right);
                    self.assembly_code.push(ASM::ADD(self.last_mem_slot));
                    self.store_to_identifier(identifier);
                }
                Expression::Subtraction(left, right) => {
                    self.generate_value(right);
                    self.assembly_code.push(ASM::STORE(self.last_mem_slot));
                    self.generate_value(left);
                    self.assembly_code.push(ASM::SUB(self.last_mem_slot));
                    self.store_to_identifier(identifier);
                }
                Expression::Division(left, right) => {
                    self.generate_value(left);
                    self.assembly_code.push(ASM::STORE(self.last_mem_slot));

                    match right {
                        Value::Number(val) => {
                            if val.clone() == 2 {
                                self.push_asm(ASM::HALF);
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

                    self.push_asm(ASM::SET(0));
                    self.push_asm(ASM::STORE(sign));

                    self.generate_value(left);

                    /*
                    if left < 0:
                    sign = -sign
                    left = -left
                    */
                    self.push_asm(ASM::STORE(l));
                    self.push_asm(ASM::JPOS(6));
                    self.push_asm(ASM::SET(-1));
                    self.push_asm(ASM::STORE(sign));
                    self.push_asm(ASM::SET(0));
                    self.push_asm(ASM::SUB(l));
                    self.push_asm(ASM::STORE(l));

                    /*
                    if right < 0:
                    sign = -sign
                    right = -right
                    */
                    self.generate_value(right);
                    self.push_asm(ASM::STORE(r));
                    self.push_asm(ASM::JPOS(7));
                    self.push_asm(ASM::SET(0));
                    self.push_asm(ASM::LOAD(sign));
                    self.push_asm(ASM::STORE(sign));
                    self.push_asm(ASM::SET(0));
                    self.push_asm(ASM::SUB(r));
                    self.push_asm(ASM::STORE(r));

                    self.push_asm(ASM::SET(0)); // quotient = 0
                    self.push_asm(ASM::STORE(quotient));

                    self.push_asm(ASM::LOAD(r));
                    self.push_asm(ASM::STORE(current_divisor)); //current_divisor = right

                    self.push_asm(ASM::SET(1));
                    self.push_asm(ASM::STORE(current_multiple)); // current_multiple = 1

                    /*
                    while current_divisor <= left:
                        current_divisor += current_divisor
                        current_multiple += current_multiple
                    */
                    self.push_asm(ASM::LOAD(current_divisor));
                    self.push_asm(ASM::SUB(l));
                    self.push_asm(ASM::JPOS(8));

                    self.push_asm(ASM::LOAD(current_divisor));
                    self.push_asm(ASM::ADD(current_divisor));
                    self.push_asm(ASM::STORE(current_divisor));

                    self.push_asm(ASM::LOAD(current_multiple));
                    self.push_asm(ASM::ADD(current_multiple));
                    self.push_asm(ASM::STORE(current_multiple));

                    self.push_asm(ASM::JUMP(-9));

                    /*
                    while right <= left:
                        current_divisor //= 2
                        current_multiple //= 2

                        if current_divisor <= left:
                            left -= current_divisor
                            quotient += current_multiple
                    */

                    self.push_asm(ASM::LOAD(r));
                    self.push_asm(ASM::SUB(l));
                    self.push_asm(ASM::JPOS(16));

                    self.push_asm(ASM::LOAD(current_multiple));
                    self.push_asm(ASM::HALF);
                    self.push_asm(ASM::STORE(current_multiple));

                    self.push_asm(ASM::LOAD(current_divisor));
                    self.push_asm(ASM::HALF);
                    self.push_asm(ASM::STORE(current_divisor));

                    self.push_asm(ASM::SUB(l));
                    self.push_asm(ASM::JPOS(7));
                    self.push_asm(ASM::LOAD(l));
                    self.push_asm(ASM::SUB(current_divisor));
                    self.push_asm(ASM::STORE(l));

                    self.push_asm(ASM::LOAD(quotient));
                    self.push_asm(ASM::ADD(current_multiple));
                    self.push_asm(ASM::STORE(quotient));
                    self.push_asm(ASM::JUMP(-17));
                    self.push_asm(ASM::LOAD(quotient));
                    self.store_to_identifier(identifier);
                    self.last_mem_slot += 6;
                }
                Expression::Multiplication(left, right) => {
                    self.generate_value(left);
                    self.assembly_code.push(ASM::STORE(self.last_mem_slot));

                    match right {
                        Value::Number(val) => {
                            if val.clone() == 2 {
                                self.push_asm(ASM::ADD(self.last_mem_slot));
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
                    self.push_asm(ASM::STORE(r));
                    self.push_asm(ASM::SET(0));
                    self.push_asm(ASM::STORE(result));
                    self.generate_value(left);
                    self.push_asm(ASM::STORE(l));

                    // loop start
                    self.push_asm(ASM::JZERO(16)); 
                    self.push_asm(ASM::HALF); // l%2
                    self.push_asm(ASM::ADD(0)); // l%2
                    self.push_asm(ASM::SUB(l)); // l%2

                    self.push_asm(ASM::JZERO(5)); // IF l%2=1 THEN
                    self.push_asm(ASM::LOAD(l));
                    self.push_asm(ASM::LOAD(result)); // result := result + r;
                    self.push_asm(ASM::ADD(r)); // result := result + r;
                    self.push_asm(ASM::STORE(result)); // result := result + r;
                                                       // ENDFI

                    self.push_asm(ASM::LOAD(r));
                    self.push_asm(ASM::ADD(r));
                    self.push_asm(ASM::STORE(r));

                    self.push_asm(ASM::LOAD(l));
                    self.push_asm(ASM::HALF);
                    self.push_asm(ASM::STORE(l));

                    self.push_asm(ASM::JUMP(-16));

                    self.push_asm(ASM::LOAD(result));
                    self.store_to_identifier(identifier);
                    self.last_mem_slot += 3;
                }
                Expression::Modulo(left, right) => {
                    match right {
                        Value::Number(val) => {
                            if val.clone() == 2 {
                                self.generate_value(left);
                                self.push_asm(ASM::STORE(self.last_mem_slot));
                                self.push_asm(ASM::HALF);
                                self.push_asm(ASM::ADD(0));
                                self.push_asm(ASM::STORE(self.last_mem_slot - 1));
                                self.push_asm(ASM::LOAD(self.last_mem_slot));
                                self.push_asm(ASM::SUB(self.last_mem_slot - 1));
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

                    self.push_asm(ASM::SET(0));
                    self.push_asm(ASM::STORE(sign));

                    self.generate_value(left);

                    /*
                    if left < 0:
                    sign = -sign
                    left = -left
                    */
                    self.push_asm(ASM::STORE(l));
                    self.push_asm(ASM::JPOS(6));
                    self.push_asm(ASM::SET(-1));
                    self.push_asm(ASM::STORE(sign));
                    self.push_asm(ASM::SET(0));
                    self.push_asm(ASM::SUB(l));
                    self.push_asm(ASM::STORE(l));

                    /*
                    if right < 0:
                    sign = -sign
                    right = -right
                    */
                    self.generate_value(right);
                    self.push_asm(ASM::STORE(r));
                    self.push_asm(ASM::JPOS(7));
                    self.push_asm(ASM::SET(0));
                    self.push_asm(ASM::LOAD(sign));
                    self.push_asm(ASM::STORE(sign));
                    self.push_asm(ASM::SET(0));
                    self.push_asm(ASM::SUB(r));
                    self.push_asm(ASM::STORE(r));

                    self.push_asm(ASM::SET(0)); // quotient = 0
                    self.push_asm(ASM::STORE(quotient));

                    self.push_asm(ASM::LOAD(r));
                    self.push_asm(ASM::STORE(current_divisor)); //current_divisor = right

                    self.push_asm(ASM::SET(1));
                    self.push_asm(ASM::STORE(current_multiple)); // current_multiple = 1

                    /*
                    while current_divisor <= left:
                        current_divisor += current_divisor
                        current_multiple += current_multiple
                    */
                    self.push_asm(ASM::LOAD(current_divisor));
                    self.push_asm(ASM::SUB(l));
                    self.push_asm(ASM::JPOS(8));

                    self.push_asm(ASM::LOAD(current_divisor));
                    self.push_asm(ASM::ADD(current_divisor));
                    self.push_asm(ASM::STORE(current_divisor));

                    self.push_asm(ASM::LOAD(current_multiple));
                    self.push_asm(ASM::ADD(current_multiple));
                    self.push_asm(ASM::STORE(current_multiple));

                    self.push_asm(ASM::JUMP(-9));

                    /*
                    while right <= left:
                        current_divisor //= 2
                        current_multiple //= 2

                        if current_divisor <= left:
                            left -= current_divisor
                            quotient += current_multiple
                    */

                    self.push_asm(ASM::LOAD(r));
                    self.push_asm(ASM::SUB(l));
                    self.push_asm(ASM::JPOS(16));

                    self.push_asm(ASM::LOAD(current_multiple));
                    self.push_asm(ASM::HALF);
                    self.push_asm(ASM::STORE(current_multiple));

                    self.push_asm(ASM::LOAD(current_divisor));
                    self.push_asm(ASM::HALF);
                    self.push_asm(ASM::STORE(current_divisor));

                    self.push_asm(ASM::SUB(l));
                    self.push_asm(ASM::JPOS(7));
                    self.push_asm(ASM::LOAD(l));
                    self.push_asm(ASM::SUB(current_divisor));
                    self.push_asm(ASM::STORE(l));

                    self.push_asm(ASM::LOAD(quotient));
                    self.push_asm(ASM::ADD(current_multiple));
                    self.push_asm(ASM::STORE(quotient));
                    self.push_asm(ASM::JUMP(-17));
                    self.push_asm(ASM::LOAD(l));
                    self.store_to_identifier(identifier);
                    self.last_mem_slot += 6;
                }
            }
        } else {
            unreachable!();
        }
    }

    fn genearate_command(&mut self, command: &Command) {
        match command {
            Command::Assignment {
                identifier: _,
                expression: _,
                location: _,
            } => self.generate_expression(command),
            Command::Read(identifier) => {
                self.push_asm(ASM::GET(0));
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
                    self.genearate_command(cmd);
                }
                let then_end = self.assembly_code.len() as i64;

                if let Some(instruction) = self.assembly_code.get_mut(jump_pos) {
                    match instruction {
                        ASM::JZERO(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        ASM::JPOS(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        ASM::JNEG(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        ASM::JUMP(offset) => {
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
                    self.genearate_command(cmd);
                }
                self.push_asm(ASM::JUMP(0));
                let then_end = self.assembly_code.len() as i64;

                let else_start = self.assembly_code.len() as i64;
                for cmd in else_commands {
                    self.genearate_command(cmd);
                }
                let else_end = self.assembly_code.len() as i64;

                if let Some(instruction) = self.assembly_code.get_mut(jump_pos) {
                    match instruction {
                        ASM::JZERO(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        ASM::JPOS(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        ASM::JNEG(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        ASM::JUMP(offset) => {
                            *offset = (then_end - then_start + 1) as i64;
                        }
                        _ => {}
                    }
                }
                if let Some(ASM::JUMP(offset)) = self.assembly_code.get_mut((then_end - 1) as usize)
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
                    self.genearate_command(cmd);
                }

                let loop_end = self.assembly_code.len() as i64;
                self.assembly_code
                    .push(ASM::JUMP(before_condition - loop_end));

                let after_loop = self.assembly_code.len() as i64;
                if let Some(instruction) = self.assembly_code.get_mut(jump_pos) {
                    match instruction {
                        ASM::JZERO(offset) => {
                            *offset = after_loop - after_condition + 1;
                        }
                        ASM::JPOS(offset) => {
                            *offset = after_loop - after_condition + 1;
                        }
                        ASM::JNEG(offset) => {
                            *offset = after_loop - after_condition + 1;
                        }
                        ASM::JUMP(offset) => {
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
                    self.genearate_command(cmd);
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
                        ASM::JZERO(offset) => {
                            *offset = loop_start - after_condition + 1;
                        }
                        ASM::JPOS(offset) => {
                            *offset = loop_start - after_condition + 1;
                        }
                        ASM::JNEG(offset) => {
                            *offset = loop_start - after_condition + 1;
                        }
                        ASM::JUMP(offset) => {
                            *offset = loop_start - after_condition + 1;
                        }
                        _ => {}
                    }
                }
            }
            Command::Write(value) => {
                self.generate_value(value);
                self.push_asm(ASM::PUT(0));
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
                        self.push_asm(ASM::LOAD(a.memory));
                        self.push_asm(ASM::STORE(return_loc.memory + i + 1));
                    } else {
                        self.push_asm(ASM::SET(a.memory as i64));
                        self.push_asm(ASM::STORE(return_loc.memory + i + 1));
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
                self.assembly_code.push(ASM::SET(current_loc + 3));
                self.assembly_code.push(ASM::STORE(return_loc.memory));

                self.assembly_code.push(ASM::JUMP(jump_dist as i64));
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
                self.push_asm(ASM::STORE(for_iter_loc));

                self.generate_value(&to);
                self.push_asm(ASM::STORE(for_num_iters));

                match direction {
                    ForDirection::Ascending => {
                        let loop_start = self.assembly_code.len() as i64;

                        self.push_asm(ASM::LOAD(for_iter_loc));
                        self.push_asm(ASM::SUB(for_num_iters));

                        let jump_instruction = ASM::JPOS(0);
                        let jump_pos = self.assembly_code.len();
                        self.push_asm(jump_instruction);

                        for cmd in commands {
                            self.genearate_command(cmd);
                        }

                        self.push_asm(ASM::LOAD(for_iter_loc));
                        self.push_asm(ASM::SET(1));
                        self.push_asm(ASM::ADD(for_iter_loc));
                        self.push_asm(ASM::STORE(for_iter_loc));

                        self.push_asm(ASM::JUMP(loop_start - self.assembly_code.len() as i64));

                        let after_loop = self.assembly_code.len() as i64;
                        if let Some(instruction) = self.assembly_code.get_mut(jump_pos) {
                            if let ASM::JPOS(offset) = instruction {
                                *offset = after_loop - jump_pos as i64; // -2 to account for LOAD SUB before jump pos
                            }
                        }
                    }
                    ForDirection::Descending => {
                        let loop_start = self.assembly_code.len() as i64;

                        self.push_asm(ASM::LOAD(for_iter_loc));
                        self.push_asm(ASM::SUB(for_num_iters));

                        let jump_instruction = ASM::JNEG(0);
                        let jump_pos = self.assembly_code.len();
                        self.push_asm(jump_instruction);

                        for cmd in commands {
                            self.genearate_command(cmd);
                        }

                        self.push_asm(ASM::LOAD(for_iter_loc));
                        self.push_asm(ASM::SET(1));
                        self.push_asm(ASM::SUB(for_iter_loc));
                        self.push_asm(ASM::STORE(for_iter_loc));

                        self.push_asm(ASM::JUMP(loop_start - self.assembly_code.len() as i64));

                        let after_loop = self.assembly_code.len() as i64;
                        if let Some(instruction) = self.assembly_code.get_mut(jump_pos) {
                            if let ASM::JNEG(offset) = instruction {
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
            self.genearate_command(command);
        }

        self.assembly_code.push(ASM::RTRN(return_address_location));
        self.current_scope = format!("");
    }

    fn generate_asm(&mut self, ast: Ast) {
        let recursive_calls = ast.detect_recursive_calls();
        if recursive_calls.len() > 0 {
            self.messages.push(ErrorDetails {
                message: format!(
                    "Recrusive calls are not allowed {} : {}",
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
            self.push_asm(ASM::JUMP(0));
        }

        for procedure in &ast.procedures {
            self.generate_procedure(procedure);
        }

        if ast.procedures.len() > 0 {
            let len_after_proc = self.assembly_code.len();
            let a = self.assembly_code.get_mut(0).unwrap();
            match a {
                ASM::JUMP(dist) => {
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
            self.genearate_command(command);
        }

        self.save_dbg_info("awd.json");
        self.push_asm(ASM::HALT);
    }

    fn save_dbg_info(&self, filename: &str) -> std::io::Result<()> {
        let json = serde_json::to_string_pretty(&self.symbols)?;
        let mut file = File::create(filename)?;
        file.write_all(json.as_bytes())?;
        Ok(())
    }
}
