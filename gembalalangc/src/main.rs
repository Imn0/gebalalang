use clap::Parser;
use std::fs::File;
use std::io::prelude::*;
use std::io::Write;
use std::process::{exit, id};
use std::string;
use std::{collections::HashMap, fmt, fs, vec};
use tree_sitter_gbl::LANGUAGE;

#[derive(Debug, Clone)]
pub struct Ast {
    pub procedures: Vec<Procedure>,
    pub main_block: Block,
}

#[derive(Debug, Clone)]
pub struct Procedure {
    pub name: String,
    pub args: Vec<ProcArgument>,
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
        proc_name: String,
        arguments: Vec<Identifier>,
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
pub struct ProcArgument {
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

    pub fn build_ast(&self, tree: &tree_sitter::Tree) -> Ast {
        let root_node = tree.root_node();

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
        }
    }

    fn parse_procedure(&self, node: &tree_sitter::Node) -> Result<Procedure, String> {
        let mut procedure_name = String::new();
        let mut args = Vec::new();
        let mut declarations = Vec::new();
        let mut commands = Vec::new();

        let mut skip_next = false;

        for child in node.named_children(&mut node.walk()) {
            match child.kind() {
                "proc_head" => {
                    procedure_name = self.extract_text(&child.named_child(0).unwrap());

                    let args_decl_node = &child.named_child(1).unwrap();
                    let mut cursor = args_decl_node.walk();
                    for arg_decl_node in args_decl_node.children(&mut cursor) {
                        if skip_next {
                            skip_next = false;
                            continue;
                        }

                        match arg_decl_node.kind() {
                            "T" => {
                                let id = self.extract_text(&arg_decl_node.next_sibling().unwrap());
                                args.push(ProcArgument {
                                    name: id,
                                    is_reference: true,
                                });
                                skip_next = true;
                            }
                            "pidentifier" => {
                                let id = self.extract_text(&arg_decl_node);
                                args.push(ProcArgument {
                                    name: id,
                                    is_reference: false,
                                });
                            }
                            _ => {}
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
        })
    }

    fn build_main_block(&self, node: &tree_sitter::Node) -> Block {
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
                    });
                }
                "proc_call" => {
                    let proc_name = self.extract_text(&child.named_child(0).unwrap());

                    let mut arguments: Vec<Identifier> = vec![];
                    let args_node = child.named_child(1).unwrap();
                    for arg_node in args_node.children(&mut args_node.walk()) {
                        if arg_node.kind() == "pidentifier" {
                            arguments.push(Identifier {
                                name: self.extract_text(&arg_node),
                                index: None,
                            });
                        }
                    }

                    return Ok(Command::ProcedureCall {
                        proc_name,
                        arguments: arguments,
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
                            from_node.next_sibling().unwrap().kind()
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
                        });
                    } else {
                        return Ok(Command::If {
                            condition: condition,
                            then_commands: then_commands,
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

        Ok(Identifier { name, index })
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

#[derive(Debug)]
struct ErrorDetails {
    message: String,
    start: tree_sitter::Point,
    end: tree_sitter::Point,
}

fn find_most_specific_error(node: tree_sitter::Node, code: &str) -> ErrorDetails {
    if node.is_error() {
        return ErrorDetails {
            message: format!("Syntax error in {}", node.kind()),
            start: node.start_position(),
            end: node.end_position(),
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
        start: node.start_position(),
        end: node.end_position(),
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
fn print_error_with_context(code: &str, error: &ErrorDetails) {
    let lines: Vec<&str> = code.lines().collect();

    let start_line = error.start.row.max(0);
    let end_line = error.end.row.min(lines.len() - 1);

    eprintln!("\x1b[1;31m{}\x1b[0m", error.message);
    eprintln!("");

    for (line_index, &line) in lines[start_line..=end_line].iter().enumerate() {
        let actual_line_num = start_line + line_index + 1;

        eprint!("\x1b[1;34m{:4} |\x1b[0m ", actual_line_num);

        eprintln!("{}", line);

        if actual_line_num - 1 == error.start.row {
            eprint!("\x1b[1;34m     |\x1b[0m ");

            for _ in 0..error.start.column {
                eprint!(" ");
            }

            eprint!("\x1b[1;31m^\x1b[0m");

            if error.end.column > error.start.column {
                for _ in error.start.column + 1..error.end.column {
                    eprint!("\x1b[1;31m^\x1b[0m");
                }
            }

            eprintln!(" \x1b[1;31mError here\x1b[0m");
        }
    }
}

fn main() -> std::io::Result<()> {
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

    let root_node = tree.root_node();

    if root_node.has_error() {
        // Find and report the most specific error
        let error_details = find_most_specific_error(root_node, &code);

        print_error_with_context(&code, &error_details);

        std::process::exit(1);
    }

    let ast = ast_builder.build_ast(&tree);
    print!("{:#?}", ast);
    let optimized_ast = optimize_ast(ast);
    let mut codeb = CodeGenerator::new();
    codeb.generate_asm(optimized_ast);

    let asm: Vec<AsmInstruction> = codeb.assembly_code;

    let mut output = String::new();

    for instruction in &asm {
        output += &format!("{}\n", instruction);
    }
    println!("{}", output);
    let mut file = File::create(args.out)?;
    file.write_all(output.as_bytes())?;
    Ok(())
}

fn optimize_ast(ast: Ast) -> Ast {
    ast
}

/// Represents the set of assembly-like instructions for a virtual machine.
///
/// ## Memory and Program Counter
/// - Memory `p_i` is indexed by `i = 0, 1, 2, 3, ..., 2^62` and is not initialized.
/// - `p_0` is the accumulator.
/// - `k` is the program counter.
pub enum AsmInstruction {
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
    RTRN(i64),

    /// Halts the program.
    /// - **Effect**: Stops execution.
    /// - **Cost**: 0
    HALT,
}

impl fmt::Display for AsmInstruction {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            AsmInstruction::GET(val) => write!(f, "GET {}", val),
            AsmInstruction::PUT(val) => write!(f, "PUT {}", val),
            AsmInstruction::LOAD(val) => write!(f, "LOAD {}", val),
            AsmInstruction::STORE(val) => write!(f, "STORE {}", val),
            AsmInstruction::LOADI(val) => write!(f, "LOADI {}", val),
            AsmInstruction::STOREI(val) => write!(f, "STOREI {}", val),
            AsmInstruction::ADD(val) => write!(f, "ADD {}", val),
            AsmInstruction::SUB(val) => write!(f, "SUB {}", val),
            AsmInstruction::ADDI(val) => write!(f, "ADDI {}", val),
            AsmInstruction::SUBI(val) => write!(f, "SUBI {}", val),
            AsmInstruction::SET(val) => write!(f, "SET {}", val),
            AsmInstruction::HALF => write!(f, "HALF"),
            AsmInstruction::JUMP(val) => write!(f, "JUMP {}", val),
            AsmInstruction::JPOS(val) => write!(f, "JPOS {}", val),
            AsmInstruction::JZERO(val) => write!(f, "JZERO {}", val),
            AsmInstruction::JNEG(val) => write!(f, "JNEG {}", val),
            AsmInstruction::RTRN(val) => write!(f, "RTRN {}", val),
            AsmInstruction::HALT => write!(f, "HALT"),
        }
    }
}

#[derive(Debug, Clone)]
struct VariableLocation {
    memory: usize,
    is_pointer: bool,
}

struct CodeGenerator {
    variables: HashMap<String, VariableLocation>,

    next_memory_slot: usize,

    assembly_code: Vec<AsmInstruction>,
}

impl CodeGenerator {
    fn new() -> Self {
        CodeGenerator {
            variables: HashMap::new(),
            next_memory_slot: 1,
            assembly_code: Vec::new(),
        }
    }

    fn get_variable_w_idx(&self, name: &str, idx: i64) -> VariableLocation {
        let mut loc = self.variables.get(name).unwrap().clone();
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
    fn get_variable(&self, name: &str) -> VariableLocation {
        let loc = self.variables.get(name).unwrap().clone();
        return loc;
    }

    fn allocate_variable(&mut self, name: String, left: i64, right: i64) {
        if left == 0 && right == 0 {
            self.variables.insert(
                name,
                VariableLocation {
                    memory: self.next_memory_slot,
                    is_pointer: false,
                },
            );
            self.next_memory_slot += 1;
            return;
        }

        if left > right {
            panic!("cant allocate array with dimensions {}:{}", left, right);
        }

        if left >= 0 && right >= 0 {
            self.variables.insert(
                name,
                VariableLocation {
                    memory: self.next_memory_slot,
                    is_pointer: false,
                },
            );
            self.next_memory_slot += usize::try_from(right).unwrap() + 1;
            return;
        }

        if left < 0 && right >= 0 {
            self.next_memory_slot += usize::try_from(-left).unwrap();
            self.variables.insert(
                name,
                VariableLocation {
                    memory: self.next_memory_slot,
                    is_pointer: false,
                },
            );
            self.next_memory_slot += usize::try_from(right).unwrap() + 1;
            return;
        }

        if left < 0 && right < 0 {
            self.next_memory_slot += usize::try_from(-left).unwrap();
            self.variables.insert(
                name,
                VariableLocation {
                    memory: self.next_memory_slot,
                    is_pointer: false,
                },
            );
            self.next_memory_slot -= usize::try_from(-right).unwrap();
            self.next_memory_slot += 1;
            return;
        }

        panic!("cant allocate array with dimensions {}:{}", left, right);
    }

    /// Loads value to p_0
    fn generate_value(&mut self, value: &Value) {
        match value {
            Value::Number(num) => {
                self.assembly_code.push(AsmInstruction::SET(num.clone())); // ! CONSTANT
            }
            Value::Identifier(ident) => {
                if let Some(idx) = &ident.index {
                    match idx {
                        Either::Left(idx_name) => {
                            let base_loc = self.get_variable(&ident.name).memory;
                            let idx_loc = self.get_variable(idx_name).memory;
                            
                            self.assembly_code.push(AsmInstruction::SET(base_loc as i64));
                            self.assembly_code.push(AsmInstruction::ADD(idx_loc));
                            self.assembly_code.push(AsmInstruction::STORE(self.next_memory_slot));
                            self.assembly_code.push(AsmInstruction::LOADI(self.next_memory_slot));
                        }
                        Either::Right(idx_num) => {
                            let loc = self.get_variable_w_idx(&ident.name, *idx_num).memory;
                            self.assembly_code.push(AsmInstruction::LOAD(loc));
                        }
                    }
                } else {
                    let loc = self.get_variable(&ident.name).memory;
                    self.assembly_code.push(AsmInstruction::LOAD(loc));
                }
            }
        }
    }


    /// Stores p_0 do ident location 
    fn store_to_identifier(&mut self, ident: &Identifier) {
        if let Some(dest_idx) = &ident.index {
            match dest_idx {
                Either::Left(idx_name) => {
                    self.assembly_code.push(AsmInstruction::STORE(self.next_memory_slot + 1));
                    
                    let base_loc = self.get_variable(&ident.name).memory;
                    let idx_loc = self.get_variable(idx_name).memory;
                    
                    self.assembly_code.push(AsmInstruction::SET(base_loc as i64));
                    self.assembly_code.push(AsmInstruction::ADD(idx_loc));
                    self.assembly_code.push(AsmInstruction::STORE(self.next_memory_slot));
                    
                    self.assembly_code.push(AsmInstruction::LOAD(self.next_memory_slot + 1));
                    self.assembly_code.push(AsmInstruction::STOREI(self.next_memory_slot));
                }
                Either::Right(idx_num) => {
                    let dest_loc = self.get_variable_w_idx(&ident.name, *idx_num).memory;
                    self.assembly_code.push(AsmInstruction::STORE(dest_loc));
                }
            }
        } else {
            let dest_loc = self.get_variable(&ident.name).memory;
            self.assembly_code.push(AsmInstruction::STORE(dest_loc));
        }
    }

    fn genearate_command(&mut self, command: &Command) {
        match command {
            Command::Assignment { identifier, expression } => {
                match expression {
                    Expression::Value(value) => {
                        self.generate_value(value);
                        self.store_to_identifier(identifier);
                    }
                    Expression::Addition(left, right) => {
                        self.generate_value(left);
                        self.assembly_code.push(AsmInstruction::STORE(self.next_memory_slot));
                        self.generate_value(right);
                        self.assembly_code.push(AsmInstruction::ADD(self.next_memory_slot));
                        self.store_to_identifier(identifier);
                    }
                    _ => unimplemented!("Expression {:?} not implemented yet", expression),
                }
            }
            Command::Read(identifier) => {
                if let Some(idx) = &identifier.index {
                    match idx {
                        Either::Left(idx_name) => {
                            let base_loc = self.get_variable(&identifier.name).memory;
                            let idx_loc = self.get_variable(idx_name).memory;
                            
                            self.assembly_code.push(AsmInstruction::SET(base_loc as i64));
                            self.assembly_code.push(AsmInstruction::ADD(idx_loc));
                            self.assembly_code.push(AsmInstruction::STORE(self.next_memory_slot));
                            self.assembly_code.push(AsmInstruction::GET(0));
                            self.assembly_code.push(AsmInstruction::STOREI(self.next_memory_slot));
                        }
                        Either::Right(idx_num) => {
                            let loc = self.get_variable_w_idx(&identifier.name, *idx_num).memory;
                            self.assembly_code.push(AsmInstruction::GET(loc));
                        }
                    }
                } else {
                    let loc = self.get_variable(&identifier.name).memory;
                    self.assembly_code.push(AsmInstruction::GET(loc));
                }
            }
            Command::Write(value) => {
                self.generate_value(value);
                self.assembly_code.push(AsmInstruction::PUT(0));
            }
            _ => {
                unimplemented!("command {:?} not implemented yet", command)
            }
        }
    }

    fn generate_asm(&mut self, ast: Ast) {
        if ast.procedures.len() > 0 {
            unimplemented!("prcedures arent implemented yet")
        }

        for declaration in &ast.main_block.declarations {
            if let Some((start, end)) = declaration.array_size {
                self.allocate_variable(declaration.name.clone(), start, end);
            } else {
                self.allocate_variable(declaration.name.clone(), 0, 0);
            }
        }

        for command in &ast.main_block.commands {
            self.genearate_command(command);
        }

        self.assembly_code.push(AsmInstruction::HALT);
        println!("{:?}", self.variables);
    }
}
