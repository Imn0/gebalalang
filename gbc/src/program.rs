use crate::ast::Ast;
use crate::error::{Message, MessageSeverity};
use std::fs::{self, OpenOptions};
use std::io::Write;

#[derive(Default)]
pub struct Program {
    pub messages: Vec<Message>,

    pub code_path: String,
    pub source_code: String,
    pub output: Box<[u8]>,

    pub ast: Ast,
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
                self.messages.push(Message::GeneralMessage {
                    severity: MessageSeverity::ERROR,
                    message: format!("cannot load file {}", path).to_string(),
                });
                self.messages.push(Message::GeneralMessage {
                    severity: MessageSeverity::ERROR,
                    message: err.to_string().to_ascii_lowercase(),
                });
                Err(())
            }
        }
    }

    pub fn save_compiled(&mut self, path: &str) -> Result<(), ()> {
        let mut r1 = Ok(());
        if let Some(parent) = std::path::Path::new(path).parent() {
            r1 = fs::create_dir_all(parent);
        }

        if let Err(err) = r1 {
            self.messages.push(Message::GeneralMessage {
                severity: MessageSeverity::ERROR,
                message: format!(
                    "cannot create a directory {}",
                    err.to_string().to_ascii_lowercase()
                ),
            });
            return Err(());
        }

        let r2 = OpenOptions::new()
            .create(true) //
            .write(true)
            .truncate(true)
            .open(path);

        if let Err(err) = r2 {
            self.messages.push(Message::GeneralMessage {
                severity: MessageSeverity::ERROR,
                message: format!(
                    "cannot open file to save {}",
                    err.to_string().to_ascii_lowercase()
                ),
            });
            return Err(());
        }

        let mut file = r2.unwrap();

        let r3 = file.write_all(&self.output);

        if let Err(err) = r3 {
            self.messages.push(Message::GeneralMessage {
                severity: MessageSeverity::ERROR,
                message: format!(
                    "cannot save to save {}",
                    err.to_string().to_ascii_lowercase()
                ),
            });
            return Err(());
        }

        Ok(())
    }
}
