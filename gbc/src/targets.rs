use crate::{
    code_gen::IrProgram,
    program::{Program, Target},
};

mod gvm;
mod python;
mod x86_64_linux_unknown;
trait Compile {
    fn compile(&self, ir_prog: &IrProgram) -> Box<[u8]>;
}
struct PythonTarget;
struct GvmTarget;
struct X86_64LinuxUnknownTarget;

impl Program {
    pub fn compile_to_target(&mut self) -> Result<(), ()> {
        let target: Box<dyn Compile> = match self.config.target {
            Target::GVM => Box::new(GvmTarget),
            Target::Python => Box::new(PythonTarget),
            Target::X86_64_LinuxUnknown => Box::new(X86_64LinuxUnknownTarget),
        };

        self.output = target.compile(&self.ir_program);

        Ok(())
    }
}
