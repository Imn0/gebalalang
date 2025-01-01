use crate::ast::Ast;
use crate::code_gen::IrProgram;
use crate::message::{DisplayMessage, Message, MessageSeverity};
use std::fs::{self, OpenOptions};
use std::io::{self, BufRead, BufReader, Write};
use std::os::unix::fs::PermissionsExt;
use std::process::{Command, Stdio};
use std::thread;

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
    pub run: bool,
    pub run_cmd: Command,
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
            run: false,
            run_cmd: Command::new(""),
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

    pub fn run(&mut self) -> Result<(), ()> {
        if !self.config.run {
            return Ok(());
        }

        self.print_message(Message::GeneralMessage {
            severity: MessageSeverity::DEBUG,
            message: &format!("running program"),
        });

        let mut command = self
            .config
            .run_cmd
            .stdout(Stdio::piped())
            .stderr(Stdio::piped())
            .spawn()
            .map_err(|e| {
                self.print_message(Message::GeneralMessage {
                    severity: MessageSeverity::ERROR,
                    message: &format!("error running program: {}", e),
                });
                ()
            })?;

        let stdout = command.stdout.take().unwrap();
        let stdout_handle = thread::spawn(move || {
            let reader = BufReader::new(stdout);
            for line in reader.lines() {
                if let Ok(line) = line {
                    println!("{}", line);
                }
            }
        });

        let stderr = command.stderr.take().unwrap();
        let stderr_handle = thread::spawn(move || {
            let reader = BufReader::new(stderr);
            for line in reader.lines() {
                if let Ok(line) = line {
                    println!("{}", line);
                }
            }
        });
        match command.wait() {
            Ok(status) => {
                if !status.success() {
                    self.print_message(Message::GeneralMessage {
                        severity: MessageSeverity::ERROR,
                        message: &format!("program exited with status: {}", status),
                    });
                    return Err(());
                }
            }
            Err(e) => {
                self.print_message(Message::GeneralMessage {
                    severity: MessageSeverity::ERROR,
                    message: &format!("failed to wait for program: {}", e),
                });
                return Err(());
            }
        }
        stdout_handle.join().unwrap();
        stderr_handle.join().unwrap();
        self.print_message(Message::GeneralMessage {
            severity: MessageSeverity::DEBUG,
            message: &format!("done"),
        });
        return Ok(());
    }
}
