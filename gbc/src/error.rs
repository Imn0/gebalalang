use std::io::{self, Write};

use crate::Program;

#[derive(Debug, Clone, PartialEq, Eq, PartialOrd, Ord)]
pub enum MessageSeverity {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
}
impl MessageSeverity {
    fn color_code(&self) -> &str {
        match self {
            MessageSeverity::DEBUG => "\x1b[90m",   // Gray
            MessageSeverity::INFO => "\x1b[34m",    // Blue
            MessageSeverity::WARNING => "\x1b[33m", // Yellow
            MessageSeverity::ERROR => "\x1b[31m",   // Red
            MessageSeverity::FATAL => "\x1b[1;31m", // Bright Red
        }
    }

    fn prefix(&self) -> &str {
        match self {
            MessageSeverity::DEBUG => "[debug] ",
            MessageSeverity::INFO => "[infp]  ",
            MessageSeverity::WARNING => "[warning]  ",
            MessageSeverity::ERROR => "[error] ",
            MessageSeverity::FATAL => "[FATAL] ",
        }
    }
}

pub enum Message {
    GeneralMessage {
        severity: MessageSeverity,
        message: String,
    },
    CodeMessage {
        severity: MessageSeverity,
        message: String,
    },
}

pub trait DisplayError {
    fn display_error(&self) -> io::Result<()>;
}

impl DisplayError for Program {
    fn display_error(&self) -> io::Result<()> {
        let stderr = &mut io::stderr();
        for message in &self.messages {
            match message {
                Message::GeneralMessage { severity, message } => {
                    writeln!(
                        stderr,
                        "GBC: {}{}\x1b[m{}\x1b[0m",
                        severity.color_code(),
                        severity.prefix(),
                        message
                    )?;
                }
                Message::CodeMessage { severity, message } => {

                }
            }
        }
        Ok(())
    }
}
