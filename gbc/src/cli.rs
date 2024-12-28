use crate::error::{Message, MessageSeverity};

#[derive(Default)]
pub struct CliArgs {
    pub input_file: String,
    pub output_file: String,
}

pub fn parse_args(args: Vec<String>, cli_args: &mut CliArgs) -> Result<(), ()> {
    if args.len() < 2 {
        eprintln!(
            "{}",
            Message::GeneralMessage {
                severity: MessageSeverity::ERROR,
                message: "no input file provided"
            }
        );

        return Err(());
    }

    let output = if args.len() == 3 {
        args.get(2).unwrap().to_owned()
    } else {
        "./a.mr".to_string()
    };

    cli_args.input_file = args.get(1).unwrap().to_owned();
    cli_args.output_file = output;

    Ok(())
}
