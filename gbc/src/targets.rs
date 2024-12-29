use gvm::GvmTarget;

use crate::program::Program;

mod gvm;

pub enum Targets {
    GVM,
}

impl Program {
    pub fn compile_to_target(&mut self, target: Targets) -> Result<(), ()> {
        match target {
            Targets::GVM => {
                let asm = self.code_gen.to_gvm();
                let mut output: String = String::new();

                for instruction in &asm {
                    output += &format!("{}\n", instruction);
                }
                self.output = output.as_bytes().into();
            }
        }

        Ok(())
    }
}
