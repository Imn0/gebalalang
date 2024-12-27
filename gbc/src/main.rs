use std::{env, process::exit};

use ast::GenerateAst;
use clap::{self, Parser as _};

mod program;
use error::DisplayError;
use program::Program;
mod ast;
mod error;

#[derive(clap::Parser, Debug)]
#[command(version = "1.0", about = "", long_about = "")]
pub struct CliArgs {
    #[arg(help = "Source code file.")]
    pub input: String,

    #[arg(short, long, default_value = "a.mr", help = "Compiled assembly file.")]
    pub out: String,
}

fn main() {
    let args = CliArgs::parse();

    let mut p = Program::default();

    if let Err(_) = p.load_code(args.input) {
        let _ = p.display_error();
        exit(1);
    }

    if let Err(_) = p.generate_ast() {
        let _ = p.display_error();
        exit(1);
    }

    // optimize_ast();

    // generate_ir();
    // generate_gvm();
    
    if let Err(_) = p.save_compiled(&args.out) {
        let _ = p.display_error();
        exit(1);
    }

    exit(0);
}
