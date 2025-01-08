use crate::code_gen::ir::{IrOperand, IR};

use super::{Compile, X86_64LinuxUnknownTarget};

impl Compile for X86_64LinuxUnknownTarget {
    fn compile(&self, ir_prog: &crate::code_gen::IrProgram) -> Box<[u8]> {
        let mut out = String::new();

        out += "format ELF64 executable 3\n";
        out += "segment readable executable\n";
        out += "entry _start\n";

        out += &compile_main(&ir_prog.main);

        out.as_bytes().into()
    }
}

fn compile_main(main: &Vec<IR>) -> String {
    let mut out = String::new();
    out += "_start:\n";

    out += "xor rdi, rdi;\n";
    out += "mov rax, 60\n";
    out += "syscall\n";
    return out;
}

fn compile_op(op: &IR) {}

fn compile_memory(mem: &IrOperand) {}
