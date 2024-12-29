use crate::program::Program;

use clap::Parser;

#[derive(Parser, Debug)]
#[command(
    author = "Krzysztof Andrzejewski",
    version = "0.6",
    about = "Gebalalang Compiler",
    long_about = "yap yap yap"
)]
pub struct CliArgs {
    pub input_file: String,

    #[arg(default_value = "a.mr")]
    pub output_file: String,

    #[arg(long, action = clap::ArgAction::SetTrue, help="Verbose error logging")]
    pub verbose: bool,

    #[arg(short, long = "unsafe", action = clap::ArgAction::SetTrue, help="Allows for udefined access")]
    pub _unsafe: bool,

    #[arg(long, action = clap::ArgAction::SetTrue)]
    pub i_know_what_im_doing: bool,
}

impl Program {
    pub fn configure_args(&mut self, cli: &CliArgs) -> Result<(), ()> {
        self.config.verbose = cli.verbose;
        self.config.werror = !cli._unsafe;

        if cli._unsafe && !cli.i_know_what_im_doing {
            println!("This is a secure language we do not allow for unsafe code.");
            return Err(());
        }

        
        Ok(())
    }
}
