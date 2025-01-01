use crate::ast::Ast;
use crate::code_gen::IrProgram;
use crate::message::{DisplayMessage, Message, MessageSeverity};
use std::fs::{self, OpenOptions};
use std::io::Write;
use std::os::unix::fs::PermissionsExt;

#[derive(Default)]
pub struct Program {
    pub source_code: String,
    pub output: Box<[u8]>,

    pub config: Config,

    pub ir_program: IrProgram,

    pub ast: Ast,
}

pub struct Config {
    pub verbose: bool,
    pub werror: bool,
    pub procedure_separate_namespace: bool,
    pub target: Targets,
    pub source_path: String,
    pub output_path: String,
    pub set_out_to_exe: bool,
}

pub enum Targets {
    GVM,
    PYTHON,
}

impl Default for Config {
    fn default() -> Self {
        Config {
            verbose: false,
            werror: true,
            procedure_separate_namespace: false,
            target: Targets::GVM,
            source_path: "".to_owned(),
            output_path: "".to_owned(),
            set_out_to_exe: false,
        }
    }
}

impl Program {
    pub fn load_code(&mut self) -> Result<(), ()> {
        let path = &self.config.source_path;
        match fs::read_to_string(&path) {
            Ok(code) => {
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

    pub fn save_compiled(&mut self) -> Result<(), ()> {
        let path = &self.config.output_path;
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

        if self.config.set_out_to_exe {
            let metadata = fs::metadata(path).unwrap(); 
            let mut permissions = metadata.permissions();
            permissions.set_mode(0o755); 
            fs::set_permissions(path, permissions).unwrap();
        }

        Ok(())
    }
}
