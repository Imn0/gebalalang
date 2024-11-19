use std::fs;

use clap::{builder::Str, Parser};
use tree_sitter::{Node, Tree, TreeCursor};
use tree_sitter_gbl::LANGUAGE;
#[derive(Debug, Clone)]
pub struct Program {
    pub procedures: Vec<Procedure>,
    pub main_block: Block,
}

#[derive(Debug, Clone)]
pub struct Procedure {
    pub name: String,
    pub args: Vec<Argument>,
    pub declarations: Vec<Declaration>,
    pub commands: Vec<Command>,
}

#[derive(Debug, Clone)]
pub struct Block {
    pub declarations: Vec<Declaration>,
    pub commands: Vec<Command>,
}

#[derive(Debug, Clone)]
pub enum Command {
    Assignment {
        identifier: Identifier,
        expression: Expression,
    },
    IfElse {
        condition: Condition,
        then_commands: Vec<Command>,
        else_commands: Vec<Command>,
    },
    If {
        condition: Condition,
        then_commands: Vec<Command>,
    },
    While {
        condition: Condition,
        commands: Vec<Command>,
    },
    Repeat {
        commands: Vec<Command>,
        condition: Condition,
    },
    For {
        variable: String,
        from: Value,
        to: Value,
        direction: ForDirection,
        commands: Vec<Command>,
    },
    ProcedureCall {
        name: String,
        arguments: Vec<Value>,
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
    Addition(Box<Value>, Box<Value>),
    Subtraction(Box<Value>, Box<Value>),
    Multiplication(Box<Value>, Box<Value>),
    Division(Box<Value>, Box<Value>),
    Modulo(Box<Value>, Box<Value>),
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

#[derive(Debug, Clone)]
pub enum Value {
    Number(i64),
    Identifier(Identifier),
}

#[derive(Debug, Clone)]
pub struct Identifier {
    pub name: String,
    pub index: Option<Either<String, i64>>,
}

#[derive(Debug, Clone)]
pub enum Either<L, R> {
    Left(L),
    Right(R),
}

#[derive(Debug, Clone)]
pub struct Argument {
    pub name: String,
    pub is_reference: bool,
}

#[derive(Debug, Clone)]
pub struct Declaration {
    pub name: String,
    pub array_size: Option<(i64, i64)>,
}

// AST Builder
pub struct AstBuilder<'a> {
    source_code: &'a str,
}

impl<'a> AstBuilder<'a> {
    pub fn new(source_code: &'a str) -> Self {
        Self { source_code }
    }

    pub fn build_ast(&self, tree: &tree_sitter::Tree) -> Program {
        let root_node = tree.root_node();

        let mut procedures = Vec::new();
        let mut main_block = None;

        for child in root_node.children(&mut root_node.walk()) {
            match child.kind() {
                "procedure" => {
                    // procedures.push(self.build_procedure(&child));
                }
                "main" => {
                    main_block = Some(self.build_main_block(&child));
                }
                _ => {} 
            }
        }

        Program {
            procedures,
            main_block: main_block.expect("Main block not found"),
        }
    }

    fn build_main_block(&self, node: &tree_sitter::Node) -> Block {
        let mut declarations = Vec::new();
        let mut commands = Vec::new();

        for child in node.children(&mut node.walk()) {
            match child.kind() {
                "declarations" => {
                    declarations = self.build_declarations(&child);
                }
                "commands" => {
                    commands = self.build_commands(&child);
                },
                _ => {}
            }
        }

        Block {
            declarations,
            commands,
        }
    }
    fn build_commands(&self, node: &tree_sitter::Node) -> Vec<Command> {
        let mut commands = Vec::new();
        for child in node.children(&mut node.walk()) {
            if child.kind() == "command" { 
                if let Some(cmd) = self.parse_command(&child) {
                    commands.push(cmd);
                }
            }
        }
        commands
    }

    fn parse_command(&self, node: &tree_sitter::Node) -> Option<Command> {
        for child in node.children(&mut node.walk()) {
            match child.kind() {
                _ => {
                    println!("{}", child.kind());
                }
            }
        }

        None
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
                                });
                            }
                        }
                    }

                    return Some(Declaration {
                        name: self.extract_text(&child),
                        array_size: None,
                    });
                }
                _ => {
                    panic!("{}", child.kind());
                }
            }
        }
        None
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

    #[arg(
        short,
        long,
        default_value = "a.out",
        help = "Specify the output file."
    )]
    out: String,
}

fn main() {
    let args = Args::parse();

    let mut parser = tree_sitter::Parser::new();
    parser
        .set_language(&LANGUAGE.into())
        .expect("Error loading Gbl parser");

    let code = fs::read_to_string(args.input).expect("Should have been able to read the file");

    let ast_builder = AstBuilder::new(&code);
    let tree = parser
        .parse(&code, None)
        .expect("Failed to parse source code");

    let ast = ast_builder.build_ast(&tree);

    println!(" {:?}", ast);
}
