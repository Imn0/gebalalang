use crate::{
    message::{DisplayMessage, Message, MessageSeverity},
    program::Program,
};

mod ast;
use std::{collections::HashMap, ops::Not};
use tree_sitter::Node;
use tree_sitter_gbl::LANGUAGE;

#[derive(Debug, Clone, Default)]
pub struct Location(pub tree_sitter::Point, pub tree_sitter::Point);
trait GetLocation {
    fn get_location(&self) -> Location;
}

impl GetLocation for Node<'_> {
    fn get_location(&self) -> Location {
        Location(self.start_position(), self.end_position())
    }
}

#[derive(Debug, Clone, Default)]
pub struct Ast {
    pub is_valid: bool,
    pub procedures: HashMap<String, Procedure>,
    pub main_block: MainBlock,
    pub location: Location,
}

#[derive(Debug, Clone)]
pub struct Procedure {
    pub name: String,
    pub args: Vec<ProcArgument>,
    pub declarations: Vec<Declaration>,
    pub commands: Vec<Command>,
    pub location: Location,
}

#[derive(Debug, Clone, Default)]
pub struct MainBlock {
    pub declarations: Vec<Declaration>,
    pub commands: Vec<Command>,
    pub location: Location,
}

#[derive(Debug, Clone)]
pub enum Command {
    Assignment {
        identifier: Identifier,
        expression: Expression,
        location: Location,
    },
    IfElse {
        condition: Condition,
        then_commands: Vec<Command>,
        else_commands: Vec<Command>,
        location: Location,
    },
    If {
        condition: Condition,
        then_commands: Vec<Command>,
        location: Location,
    },
    While {
        condition: Condition,
        commands: Vec<Command>,
        location: Location,
    },
    Repeat {
        commands: Vec<Command>,
        condition: Condition,
        location: Location,
    },
    For {
        variable: String,
        from: Value,
        to: Value,
        direction: ForDirection,
        commands: Vec<Command>,
        location: Location,
    },
    ProcedureCall {
        proc_name: String,
        arguments: Vec<Identifier>,
        location: Location,
    },
    Read(Identifier),
    Write(Value),
    NoOp,
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
    TimesPowerTwo(Value, i64),
    HalfTimes(Value, i64),
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
    pub location: Location,
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

#[derive(Debug, Clone, Default)]
pub struct Declaration {
    pub name: String,
    pub array_size: Option<(i64, i64)>,
    pub location: Location,
}

impl Program {
    pub fn ast_generate(&mut self) -> Result<(), ()> {
        let mut parser = tree_sitter::Parser::new();
        if let Err(err) = parser.set_language(&LANGUAGE.into()) {
            self.print_message(Message::GeneralMessage {
                severity: crate::message::MessageSeverity::FATAL,
                message: &err.to_string().to_ascii_lowercase(),
            });
            return Err(());
        }

        let tree = parser.parse(self.source_code.clone(), None).unwrap();

        if tree.root_node().has_error() {
            self.print_message(Message::GeneralMessage {
                severity: MessageSeverity::ERROR,
                message: "there is a syntax error somewhere go find it !",
            });
            let issue_node = rec_find_error(tree.root_node()).unwrap();
            self.print_message(Message::CodeMessage {
                severity: MessageSeverity::ERROR,
                message: format!("try somwhere here {}", issue_node.kind()).as_str(),
                location: issue_node.get_location(),
            });
            return Err(());
        }
        self.populate_ast(tree)
    }
}

fn rec_find_error(node: Node) -> Option<Node> {
    if node.is_error() || node.is_missing() {
        return Some(node.clone());
    }

    if !node.has_error() {
        return None;
    }

    let mut walker = node.walk();
    for child in node.children(&mut walker) {
        if let Some(error_node) = rec_find_error(child) {
            return Some(error_node);
        }
    }

    None
}
