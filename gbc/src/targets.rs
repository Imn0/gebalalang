use crate::{
    code_gen::IrProgram,
    program::{Program, Targets},
};

mod gvm;
mod python;

trait Compile {
    fn compile(&self, ir_prog: &IrProgram) -> Box<[u8]>;
}

struct PythonTarget;
struct GvmTarget;

impl Program {
    pub fn compile_to_target(&mut self) -> Result<(), ()> {
        let target: Box<dyn Compile> = match self.config.target {
            Targets::GVM => Box::new(GvmTarget),
            Targets::PYTHON => Box::new(PythonTarget),
        };

        self.output = target.compile(&self.ir_program);

        Ok(())
    }
}
