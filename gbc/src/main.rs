use clap::Parser;
use serde::Serialize;
use targets::gvm::{GvmAsm, GvmTarget};
use std::fs::File;
use std::io::Write;
use std::{collections::HashMap, fs, vec};
use tree_sitter_gbl::LANGUAGE;

mod cli;
use cli::CliArgs;

mod ast;
use ast::*;

mod ast_validate;

mod error;
use error::*;

mod ir;
use ir::IR;

mod code_builder;
use code_builder::code_builder::CodeGenerator;

mod targets;


fn main() -> std::io::Result<()> {
    let args = CliArgs::parse();
    let input_file = args.input;

    let mut parser = tree_sitter::Parser::new();
    parser
        .set_language(&LANGUAGE.into())
        .expect("Error loading Gbl parser");

    let code =
        fs::read_to_string(input_file.clone()).expect("Should have been able to read the file");

    let mut ast_builder = AstBuilder::new(&code);
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

    let mut code_asm = CodeGenerator::new();
    let mut context = SourceContext::new(code.as_str(), &input_file);
    if let Either::Left(ast) = ast_builder.build_ast(&tree) {
        code_asm.generate_asm(ast);
    } else if let Either::Right(error) = ast_builder.build_ast(&tree) {
        context.add_message(error);        
    }


    let is_error: bool = code_asm
        .messages
        .iter()
        .filter(|m| m.severity == MessageSeverity::ERROR || m.severity == MessageSeverity::FATAL)
        .collect::<Vec<&ErrorDetails>>()
        .len()
        > 0;

    context.add_messages(code_asm.messages.clone());
    context.display()?;

    if is_error {
        std::process::exit(1);
    }
    let mut ir_output = String::new();

    for instruction in &code_asm.assembly_code {
        ir_output += &format!("{}\n", instruction);
    }
    println!("{}", ir_output);
    println!("\n");
    let asm: Vec<GvmAsm> = code_asm.to_gvm();

    let mut output = String::new();

    for instruction in &asm {
        output += &format!("{}\n", instruction);
    }
    println!("{}", output);
    let mut file = File::create(args.out.clone())?;
    file.write_all(output.as_bytes())?;
    Ok(())
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
