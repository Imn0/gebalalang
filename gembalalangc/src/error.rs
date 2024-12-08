use std::cmp::Ordering;
use std::io::{self, Write};

#[derive(Debug, Clone)]
pub struct ErrorDetails {
    pub message: String,
    pub location: (tree_sitter::Point, tree_sitter::Point),
    pub severity: MessageSeverity,
}

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
            MessageSeverity::DEBUG => "[DEBUG] ",
            MessageSeverity::INFO => "[INFO]  ",
            MessageSeverity::WARNING => "[WARN]  ",
            MessageSeverity::ERROR => "[ERROR] ",
            MessageSeverity::FATAL => "[FATAL] ",
        }
    }
}

pub struct SourceContext<'a> {
    code: &'a str,
    filename: &'a str,
    messages: Vec<ErrorDetails>,
}

impl<'a> SourceContext<'a> {
    pub fn new(code: &'a str, filename: &'a str) -> Self {
        Self {
            code,
            filename,
            messages: Vec::new(),
        }
    }

    pub fn add_message(&mut self, message: ErrorDetails) {
        self.messages.push(message);
    }

    pub fn add_messages(&mut self, messages: Vec<ErrorDetails>) {
        self.messages.extend(messages);
    }

    pub fn display(&self) -> io::Result<()> {
        let mut sorted_messages = self.messages.clone();
        sorted_messages.sort_by(|a, b| match a.location.0.row.cmp(&b.location.0.row) {
            Ordering::Equal => b.severity.cmp(&a.severity),
            row_order => row_order,
        });

        let stderr = &mut io::stderr();
        let lines: Vec<&str> = self.code.lines().collect();

        for error in sorted_messages {
            let start_line = error.location.0.row.max(0);

            writeln!(
                stderr,
                "{}{}{}\x1b[0m",
                error.severity.color_code(),
                error.severity.prefix(),
                error.message
            )?;
            writeln!(
                stderr,
                "\x1b[1;34m{:4}\x1b[0m {} {}:{}:{}",
                "",
                "--->",
                self.filename,
                start_line + 1,
                error.location.1.column + 1
            )?;
            writeln!(
                stderr,
                "\x1b[1;34m{:4} |\x1b[0m {}",
                start_line + 1,
                lines[start_line]
            )?;

            write!(stderr, "\x1b[1;34m     |\x1b[0m ")?;

            for _ in 0..error.location.0.column {
                write!(stderr, " ")?;
            }

            write!(stderr, "{}", error.severity.color_code())?;

            if error.location.1.column > error.location.0.column {
                for _ in error.location.0.column + 1..error.location.1.column {
                    write!(stderr, "^")?;
                }
            }

            writeln!(stderr)?;
        }

        Ok(())
    }
}
