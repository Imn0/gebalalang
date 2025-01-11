use clap::Parser;
use std::process::exit;

mod program;
use cli::CliArgs;
use program::Program;
mod ast;
mod ast_validate;
mod cli;
mod code_gen;
mod message;
mod targets;
mod ir_optimize;

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

    try_or_exit!(p.configure_args(args));
    try_or_exit!(p.load_code());
    try_or_exit!(p.ast_generate());
    try_or_exit!(p.ast_validate());
    // println!("{:#?}", p.ast);
    try_or_exit!(p.ir_gen());
    try_or_exit!(p.ir_optimize());
    // println!("{}", p.ir_program);
    try_or_exit!(p.compile_to_target());
    try_or_exit!(p.save_compiled());
    try_or_exit!(p.run());

    exit(0);
}
