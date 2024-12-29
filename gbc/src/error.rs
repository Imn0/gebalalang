use core::fmt;
use std::process::exit;

use crate::{ast::Location, Program};

#[derive(Debug, Clone, PartialEq, Eq, PartialOrd, Ord)]
pub enum MessageSeverity {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
}

impl MessageSeverity {
    pub fn color_code(&self) -> &str {
        match self {
            MessageSeverity::DEBUG => "\x1b[1;90m",   // Gray
            MessageSeverity::INFO => "\x1b[1;34m",    // Blue
            MessageSeverity::WARNING => "\x1b[1;33m", // Yellow
            MessageSeverity::ERROR => "\x1b[1;31m",   // Red
            MessageSeverity::FATAL => "\x1b[1;31m",   // Bright Red
        }
    }

    pub fn prefix(&self) -> &str {
        match self {
            MessageSeverity::DEBUG => "[debug] ",
            MessageSeverity::INFO => "[info]  ",
            MessageSeverity::WARNING => "[warning]  ",
            MessageSeverity::ERROR => "[error] ",
            MessageSeverity::FATAL => "[FATAL] ",
        }
    }
}

pub enum Message<'a> {
    GeneralMessage {
        severity: MessageSeverity,
        message: &'a str,
    },
    CodeMessage {
        severity: MessageSeverity,
        message: &'a str,
        location: Location,
    },
}

pub trait DisplayMessage {
    fn print_message(&self, message: Message);
}

impl DisplayMessage for Program {
    fn print_message(&self, message: Message) {
        if self.config.verbose {
            let severity = match message {
                Message::CodeMessage { severity, .. } => severity,
                Message::GeneralMessage { severity, .. } => severity,
            };
            if severity == MessageSeverity::ERROR || severity == MessageSeverity::FATAL {
                eprintln!("no");
                exit(1);
            }
            return;
        }

        match message {
            Message::GeneralMessage { severity, message } => {
                eprintln!(
                    "GBC: {}{}\x1b[m{}\x1b[0m",
                    severity.color_code(),
                    severity.prefix(),
                    message
                );
            }
            Message::CodeMessage {
                severity,
                message,
                location,
            } => {
                let mut lines: Vec<&str> = self.source_code.lines().collect();
                lines.push(" ");

                let header_spaces_num = (lines.len() as f32).log10() as usize + 2;
                let header_spaces = " ".repeat(header_spaces_num);

                let start_row = location.0.row;
                let start_column = location.0.column;
                let end_row = location.1.row;
                let end_column = location.1.column;

                eprint!(
                    "GBC: {}{}\x1b[m{}\x1b[0m ",
                    severity.color_code(),
                    severity.prefix(),
                    message
                );

                eprintln!(
                    "\x1b[1;34m\x1b[0m {} {}:{}:{}",
                    "--->",
                    self.code_path,
                    start_row + 1,
                    start_column + 1
                );
                eprintln!("\x1b[1;34m{}|\x1b[0m ", header_spaces);
                if start_row == end_row {
                    let end = if start_column == end_column {
                        end_column + 1
                    } else {
                        end_column
                    };

                    eprint!(
                        "\x1b[1;34m{:>width$} |\x1b[0m ",
                        start_row + 1,
                        width = header_spaces_num - 1
                    );
                    eprintln!("{}", lines[start_row]);
                    eprint!("\x1b[1;34m{}|\x1b[0m ", header_spaces);

                    for _ in 0..start_column {
                        eprint!(" ")
                    }
                    eprint!("{}", severity.color_code());
                    for _ in start_column..end {
                        eprint!("^")
                    }
                    eprint!("\x1b[0m");
                    eprintln!();
                    return;
                } else {
                    eprint!("\x1b[1;34m{}|\x1b[0m ", header_spaces);

                    eprint!("{}", severity.color_code());
                    for _ in start_column..lines[start_row].len() {
                        eprint!("v")
                    }
                    eprint!("\x1b[0m");

                    eprintln!();
                    eprint!(
                        "\x1b[1;34m{:>width$} \x1b[0m{}>\x1b[0m ",
                        start_row + 1,
                        severity.color_code(),
                        width = header_spaces_num - 1,
                    );
                    eprint!("{}", lines[start_row]);
                    eprint!("\x1b[0m");
                    eprintln!();
                }

                for row in start_row + 1..end_row {
                    eprint!(
                        "\x1b[1;34m{:>width$} \x1b[0m{}>\x1b[0m ",
                        row + 1,
                        severity.color_code(),
                        width = header_spaces_num - 1,
                    );
                    eprint!("{}", lines[row]);
                    eprintln!("\x1b[0m");
                }

                eprint!(
                    "\x1b[1;34m{:>width$}\x1b[0m{} >\x1b[0m ",
                    end_row + 1,
                    severity.color_code(),
                    width = header_spaces_num - 1
                );
                eprintln!("{}", lines[end_row]);

                eprint!("\x1b[1;34m{}|\x1b[0m ", header_spaces);
                let num_spaces = lines[end_row].chars().take_while(|&c| c == ' ').count();
                for _ in 0..num_spaces {
                    eprint!(" ")
                }

                eprint!("{}", severity.color_code());
                for _ in num_spaces..end_column {
                    eprint!("^")
                }
                eprintln!("\x1b[0m");

                return;
            }
        }
    }
}
