use clap::Parser;

#[derive(Parser, Debug)]
#[command(
    version = "1.0",
    about = "A CLI tool for processing input files and specifying output files.",
    long_about = "This is a longer description of the tool. It processes input files specified as a positional argument and writes results to the specified output file."
)]
pub struct CliArgs {
    #[arg(help = "Specify the input file.")]
    pub input: String,

    #[arg(short, long, default_value = "a.mr", help = "Specify the output file.")]
    pub out: String,
}
