use std::process::Command;

use crate::program::Program;
use crate::program::Targets;
use clap::parser::ValueSource;
use clap::CommandFactory;
use clap::{Parser, ValueEnum};

#[derive(Parser, Debug)]
#[command(
    author = "Krzysztof Andrzejewski",
    version = "0.6",
    about = "Gebalalang Compiler",
    long_about = "yap yap yap"
)]
pub struct CliArgs {
    input_file: String,

    #[arg(default_value = "a.mr")]
    output_file: String,

    #[arg(long, action = clap::ArgAction::SetTrue, help="Verbose error logging")]
    verbose: bool,

    #[arg(long, action = clap::ArgAction::SetTrue, help="Use separate namesapces for variable and procedure names")]
    variable_separation: bool,

    #[arg(short, long = "unsafe", action = clap::ArgAction::SetTrue, help="Allows for udefined access")]
    _unsafe: bool,

    #[arg(long, action = clap::ArgAction::SetTrue, hide=true)]
    i_know_what_im_doing: bool,

    #[arg(short, long, default_value = "gvm")]
    target: Target,

    #[arg(short, long, action = clap::ArgAction::SetTrue, help="Whether to run the compiled program")]
    run: bool,

    #[arg(
        long,
        default_value = "",
        help = "Path for program runner, it will be run as <run_path> <output_file>, not needed when compiling for python"
    )]
    run_path: String,

    #[arg(long, action = clap::ArgAction::SetTrue, help="Wheter to save IR of the program")]
    emit_ir: bool,
}

#[derive(Copy, Clone, PartialEq, Eq, PartialOrd, Ord, ValueEnum, Debug)]
enum Target {
    GVM,
    Python,
}

impl Program {
    pub fn configure_args(&mut self, cli: CliArgs) -> Result<(), ()> {
        let matches = CliArgs::command().get_matches();
        self.config.verbose = cli.verbose;
        self.config.werror = !cli._unsafe;

        if cli._unsafe && !cli.i_know_what_im_doing {
            println!("This is a secure language we do not allow for unsafe code.");
            return Err(());
        }

        self.config.source_path = cli.input_file;
        self.config.output_path = cli.output_file;
        self.config.procedure_separate_namespace = cli.variable_separation;

        let out_default = matches.value_source("output_file") == Some(ValueSource::DefaultValue);

        match cli.target {
            Target::GVM => {
                self.config.target = {
                    if out_default {
                        self.config.output_path = "a.mr".to_owned();
                    }
                    Targets::GVM
                }
            }
            Target::Python => {
                self.config.target = {
                    if out_default {
                        self.config.output_path = "a.py".to_owned();
                    }
                    self.config.set_out_to_exe = true;
                    Targets::PYTHON
                }
            }
        }

        self.config.run = cli.run;
        if cli.run {
            if cli.run_path.is_empty() {
                match cli.target {
                    Target::GVM => {
                        self.config.run_cmd = Command::new("gvm");
                    }
                    Target::Python => {
                        self.config.run_cmd = Command::new("python3");
                    }
                }
            } else {
                self.config.run_cmd = Command::new(cli.run_path);
            }
            self.config.run_cmd.arg(self.config.output_path.clone());
        }

        self.config.save_ir = cli.emit_ir;

        Ok(())
    }
}
