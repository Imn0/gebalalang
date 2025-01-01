use std::process::exit;
use clap::Parser;

mod program;
use cli::CliArgs;
use program::Program;
mod ast;
mod ast_optimize;
mod ast_validate;
mod cli;
mod code_gen;
mod targets;
use targets::Targets;



mod message;
mod tests;

macro_rules! try_or_exit {
    ($expr:expr) => {
        if let Err(_) = $expr {
            std::process::exit(1);
        }
    };
}

macro_rules! try_or_err {
    ($expr:expr) => {
        if let Err(_) = $expr {
            return Err(());
        }
    };
}
pub(crate) use try_or_err;
pub(crate) use try_or_exit;

fn main() {
    let args = CliArgs::parse();
    let mut p = Program::default();

    try_or_exit!(p.configure_args(&args));
    try_or_exit!(p.load_code(args.input_file));
    try_or_exit!(p.ast_generate());
    try_or_exit!(p.ast_validate());
    try_or_exit!(p.ast_optimize());
    println!("{:#?}", p.ast);
    try_or_exit!(p.gen_ir());
    try_or_exit!(p.compile_to_target(Targets::GVM));
    try_or_exit!(p.save_compiled(&args.output_file));

    exit(0);
}
