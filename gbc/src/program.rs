use crate::ast::Ast;
use crate::code_gen::CodeGenerator;
use crate::message::{DisplayMessage, Message, MessageSeverity};
use std::fs::{self, OpenOptions};
use std::io::Write;

#[derive(Default)]
pub struct Program {
    pub code_path: String,
    pub source_code: String,
    pub output: Box<[u8]>,

    pub config: Config,

    pub code_gen: CodeGenerator,

    pub ast: Ast,
}

pub struct Config {
    pub verbose: bool,
    pub werror: bool, 
    pub procedure_separate_namespace: bool
}

impl  Default for Config {
    fn default() -> Self {
        Config{
            verbose: false, 
            werror: true, 
            procedure_separate_namespace: false
        }
    }    
}

impl Program {
    pub fn load_code(&mut self, path: String) -> Result<(), ()> {
        match fs::read_to_string(&path) {
            Ok(code) => {
                self.code_path = path;
                self.source_code = code;
                Ok(())
            }
            Err(err) => {
                self.print_message(Message::GeneralMessage {
                    severity: MessageSeverity::ERROR,
                    message: format!("cannot load file: {}", path).as_str(),
                });
                self.print_message(Message::GeneralMessage {
                    severity: MessageSeverity::ERROR,
                    message: &err.to_string().to_ascii_lowercase(),
                });
                Err(())
            }
        }
    }

    pub fn save_compiled(&mut self, path: &str) -> Result<(), ()> {
        let r2 = OpenOptions::new()
            .create(true)
            .write(true)
            .truncate(true)
            .open(path);

        if let Err(err) = r2 {
            self.print_message(Message::GeneralMessage {
                severity: MessageSeverity::ERROR,
                message: format!(
                    "cannot open file to save: {}",
                    err.to_string().to_ascii_lowercase()
                )
                .as_str(),
            });
            return Err(());
        }

        let mut file = r2.unwrap();

        let r3 = file.write_all(&self.output);

        if let Err(err) = r3 {
            self.print_message(Message::GeneralMessage {
                severity: MessageSeverity::ERROR,
                message: format!(
                    "cannot save to file: {}",
                    err.to_string().to_ascii_lowercase()
                )
                .as_str(),
            });
            return Err(());
        }

        Ok(())
    }
}
