use std::{env, process::exit};

use ast::GenerateAst;

mod program;
use cli::{parse_args, CliArgs};
use program::Program;
mod ast;
mod error;

mod cli;

macro_rules! try_or_exit {
    ($expr:expr) => {
        if let Err(_) = $expr {
            std::process::exit(1);
        }
    };
}

fn main() {
    let mut args = CliArgs::default();

    try_or_exit!(parse_args(env::args().collect(), &mut args));

    let mut p = Program::default();

    try_or_exit!(p.load_code(args.input_file));
    try_or_exit!(p.generate_ast());
    println!("{:#?}", p.ast);
    try_or_exit!(p.save_compiled(&args.output_file));

    exit(0);
}
