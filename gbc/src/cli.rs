use crate::program::Program;

use clap::Parser;

#[derive(Parser, Debug)]
#[command(author = "Krzysztof Andrzejewski", version = "0.6", about = "Gebalalang Compiler", long_about = None)]
pub struct CliArgs {
    pub input_file: String,

    #[arg(group = "output", default_value = "a.mr")]
    pub output_file: String,

    #[arg(short, long, action = clap::ArgAction::SetTrue)]
    pub verbose: bool,
}

impl Program {
    pub fn configure_args(&mut self, cli: &CliArgs) -> Result<(), ()> {
        self.config.verbose = cli.verbose;
        Ok(())
    }
}
