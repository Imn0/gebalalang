use std::{env, process::exit};

mod program;
use cli::{parse_args, CliArgs};
use program::Program;
mod ast;
mod ast_validate;
mod ast_optimize;
mod cli;
mod error;

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
 pub(crate) use try_or_exit;
 pub(crate) use try_or_err;

fn main() {
    let mut args = CliArgs::default();

    try_or_exit!(parse_args(env::args().collect(), &mut args));

    let mut p = Program::default();

    try_or_exit!(p.load_code(args.input_file));
    try_or_exit!(p.ast_generate());
    // println!("{:#?}", p.ast);
    try_or_exit!(p.ast_validate());
    try_or_exit!(p.ast_optimize());
    try_or_exit!(p.save_compiled(&args.output_file));

    exit(0);
}
