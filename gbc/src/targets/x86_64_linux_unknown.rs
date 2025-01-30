use std::{collections::HashMap, process::Command};

use crate::code_gen::ir::{IrOperand, IR};

use super::{Compile, X86_64LinuxUnknownTarget};

struct CodeBlock {
    vars: HashMap<String, i64>,
    cur_offset: i64,
    asm: String,
}

impl Compile for X86_64LinuxUnknownTarget {
    fn compile(&self, ir_prog: &crate::code_gen::IrProgram) -> Box<[u8]> {
        let mut out = String::new();

        out += &compile_header();

        let main_bloc = CodeBlock::compile_main(&ir_prog.main);
        out += &main_bloc.asm;
        if cfg!(debug_assertions) {
            let _ = std::fs::write("./a.asm", out.clone());
        }
        let _ = std::fs::write("/tmp/a.asm", out);
        let assembly_status = Command::new("fasm")
            .arg("/tmp/a.asm")
            .arg("/tmp/a.out")
            .output()
            .expect("something went wrong");

        if !assembly_status.status.success() {
            println!("Status: {}", assembly_status.status);
            println!("{}", String::from_utf8_lossy(&assembly_status.stdout));
            println!("{}", String::from_utf8_lossy(&assembly_status.stderr));
        }

        let compiled = std::fs::read("/tmp/a.out").unwrap();
        compiled.into()
    }
}

impl CodeBlock {
    fn compile_main(ir: &Vec<IR>) -> Self {
        // let mut out = String::new();

        let mut out_block = CodeBlock {
            cur_offset: 0,
            vars: HashMap::new(),
            asm: "".to_owned(),
        };

        let allocs: Vec<&IR> = ir
            .iter()
            .filter_map(|ir| {
                if let IR::Aloc { .. } = ir {
                    Some(ir)
                } else {
                    None
                }
            })
            .collect();

        out_block.asm += "_start:\n";
        out_block.asm += "push rbp\nmov rbp, rsp\n";
        out_block.asm += &format!("sub rsp, {}\n", allocs.len() * 8);
        out_block.cur_offset = 8;

        for aloc in allocs {
            match aloc {
                IR::Aloc {
                    name,
                    is_array,
                    array_bounds: _,
                } => {
                    if !is_array {
                        out_block
                            .vars
                            .insert(name.to_string(), out_block.cur_offset);
                        out_block.asm += &format!("mov qword [rbp-{}], 0\n", out_block.cur_offset);
                        out_block.cur_offset += 8;
                    } else {
                        todo!();
                    }
                }
                _ => {}
            }
        }
        for ins in ir {
            out_block.compile_op(ins);
        }

        out_block.asm += "xor rdi, rdi;\n";
        out_block.asm += "mov rax, 60\n";
        out_block.asm += "syscall\n";
        out_block
    }

    fn compile_op(&mut self, op: &IR) {
        match op {
            IR::Aloc { .. } => {}
            IR::Read(ir_operand) => {
                let loc = self.get_ir_operand_loc(ir_operand);
                self.asm += "call __BUILTIN_READ\n";
                self.asm += &format!("mov {}, rax\n", loc);
            }
            IR::Write(ir_operand) => {
                let loc = self.get_ir_operand_loc(ir_operand);
                self.asm += &format!("mov rax, {}\n", loc);
                self.asm += "call __BUILTIN_WRITE\n";
            }
            IR::Add { dest, left, right } => {
                let left = self.get_ir_operand_loc(left);
                self.asm += &format!("mov rax, {}\n", left);
                let right = self.get_ir_operand_loc(right);
                self.asm += &format!("add rax, {}\n", right);

                let dest = self.get_ir_operand_loc(dest);
                self.asm += &format!("mov {}, rax\n", dest);
            }
            IR::Sub { dest, left, right } => {
                let left = self.get_ir_operand_loc(left);
                self.asm += &format!("mov rax, {}\n", left);
                let right = self.get_ir_operand_loc(right);
                self.asm += &format!("sub rax, {}\n", right);

                let dest = self.get_ir_operand_loc(dest);
                self.asm += &format!("mov {}, rax\n", dest);
            }
            IR::Mul { dest, left, right } => {
                let left = self.get_ir_operand_loc(left);
                self.asm += &format!("mov rax, {}\n", left);
                let right = self.get_ir_operand_loc(right);
                self.asm += &format!("imul rax, {}\n", right);

                let dest = self.get_ir_operand_loc(dest);
                self.asm += &format!("mov {}, rax\n", dest);
            }
            IR::Mov { dest, src } => {
                let src = self.get_ir_operand_loc(src);
                let dest = self.get_ir_operand_loc(dest);
                self.asm += &format!("mov {}, {}\n", dest, src);
            }
            IR::Div { dest, left, right } => {
                self.asm += &format!("xor rdx, rdx\n");
                let left = self.get_ir_operand_loc(left);
                self.asm += &format!("mov rax, {}\n", left);
                let right = self.get_ir_operand_loc(right);
                self.asm += &format!("mov rbx, {}\n", right);
                self.asm += &format!("idiv rbx\n");

                let dest = self.get_ir_operand_loc(dest);
                self.asm += &format!("mov {}, rax\n", dest);
            }
            IR::Mod { dest, left, right } => {
                let left = self.get_ir_operand_loc(left);
                self.asm += &format!("mov rax, {}\n", left);
                let right = self.get_ir_operand_loc(right);

                self.asm += &format!("mov rbx, {}\n", right);
                self.asm += &format!("idiv rbx\n");

                let dest = self.get_ir_operand_loc(dest);
                self.asm += &format!("mov {}, rdx\n", dest);
            }
            IR::Comment(_) => {}
            IR::Label(name) => {
                self.asm += &format!("{}:\n", name);
            }
            IR::Jump(name) => {
                self.asm += &format!("jmp {}\n", name);
            }
            IR::JNegativeOrZero { left, right, label } => {
                let left = self.get_ir_operand_loc(left);
                self.asm += &format!("mov rax, {}\n", left);
                let right = self.get_ir_operand_loc(right);
                self.asm += &format!("cmp rax, {}\n", right);
                self.asm += &format!("jle {}\n", label);
            }
            IR::JZero { left, right, label } => {
                let left = self.get_ir_operand_loc(left);
                self.asm += &format!("mov rax, {}\n", left);
                let right = self.get_ir_operand_loc(right);
                self.asm += &format!("cmp rax, {}\n", right);
                self.asm += &format!("je {}\n", label);
            }
            IR::JNotZero { left, right, label } => {
                let left = self.get_ir_operand_loc(left);
                self.asm += &format!("mov rax, {}\n", left);
                let right = self.get_ir_operand_loc(right);
                self.asm += &format!("cmp rax, {}\n", right);
                self.asm += &format!("jne {}\n", label);
            }
            IR::JPositive { left, right, label } => {
                let left = self.get_ir_operand_loc(left);
                self.asm += &format!("mov rax, {}\n", left);
                let right = self.get_ir_operand_loc(right);
                self.asm += &format!("cmp rax, {}\n", right);
                self.asm += &format!("jle {}\n", label);
            }
            IR::JNegative { left, right, label } => {
                let left = self.get_ir_operand_loc(left);
                self.asm += &format!("mov rax, {}\n", left);
                let right = self.get_ir_operand_loc(right);
                self.asm += &format!("cmp rax, {}\n", right);
                self.asm += &format!("jns {}\n", label);
            }
            IR::JPositiveOrZero { left, right, label } => {
                let left = self.get_ir_operand_loc(left);
                self.asm += &format!("mov rax, {}\n", left);
                let right = self.get_ir_operand_loc(right);
                self.asm += &format!("cmp rax, {}\n", right);
                self.asm += &format!("js {}\n", label);
            }
            IR::ProcCall { .. } => todo!(),
            IR::Return => todo!(),
            IR::Drop { .. } => {}
        }
    }

    fn get_ir_operand_loc(&mut self, oper: &IrOperand) -> String {
        match oper {
            IrOperand::Variable(name) => {
                let offset = self.vars.get(&get_base_name(name)).unwrap();

                return format!("qword [rbp-{}]", offset);
            }
            IrOperand::Constant(val) => {
                return format!("{}", val);
            }
            IrOperand::ArrayConstAccess { .. } => todo!(),
            IrOperand::ArrayDynamicAccess { .. } => todo!(),
        }
    }
}

fn get_base_name(name: &str) -> String {
    // let parts: Vec<&str> = name.split("_:").collect();
    // parts[0].to_owned()
    name.to_owned()
}

fn compile_header() -> String {
    let mut out = String::new();

    out += "format ELF64 executable\n";
    out += "segment readable writeable\nnewline db 0xa\nminus db '-'\nnum rb 16\nresult rb 16\n";
    out += "\nentry _start\n";
    out += "segment readable executable\n";
    out += "__BUILTIN_READ:
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    
    ; Read input
    mov rax, 0          ; sys_read
    mov rdi, 0          ; stdin
    mov rsi, num        ; buffer
    mov rdx, 16         ; max length
    syscall
    
    ; Convert ASCII to integer
    mov rcx, rax        ; save length
    mov rsi, num        ; source string
    xor rax, rax        ; clear rax
    xor rbx, rbx        ; clear rbx
    
    ; Check for minus sign
    movzx rdx, byte [rsi]
    cmp rdx, '-'
    jne .positive_start
    inc rsi            ; skip minus sign
    dec rcx            ; decrease length
    mov rbx, 1         ; flag for negative number
    jmp .convert_loop
    
.positive_start:
    xor rbx, rbx        ; flag for positive number
    
.convert_loop:
    movzx rdx, byte [rsi]  ; get current char
    cmp rdx, 0xa           ; check for newline
    je .convert_done
    sub rdx, '0'           ; convert ASCII to number
    imul rax, 10          ; multiply current result by 10
    add rax, rdx           ; add new digit
    inc rsi                ; move to next char
    dec rcx
    jnz .convert_loop
    
.convert_done:
    ; Check if number should be negative
    test rbx, rbx
    jz .finish
    neg rax             ; make number negative if minus sign was present
    
.finish:
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    ret

; Function to convert number to ASCII and print
; Input: RAX = number to print
__BUILTIN_WRITE:
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    
    ; Check if number is negative
    test rax, rax
    jns .positive
    
    ; Handle negative number
    push rax            ; save number
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    mov rsi, minus      ; minus sign
    mov rdx, 1          ; length
    syscall
    pop rax             ; restore number
    neg rax             ; make positive for conversion
    
.positive:
    ; Convert integer to ASCII
    mov rcx, 0            ; digit counter
    mov rbx, 10           ; divisor
    mov rsi, result
    add rsi, 15           ; point to end of buffer
    
.convert_loop:
    xor rdx, rdx          ; clear rdx for division
    div rbx               ; divide by 10
    add dl, '0'           ; convert remainder to ASCII
    dec rsi               ; move pointer back
    mov [rsi], dl         ; store digit
    inc rcx               ; increment counter
    test rax, rax         ; check if more digits
    jnz .convert_loop
    
    ; Print number
    mov rax, 1            ; sys_write
    mov rdi, 1            ; stdout
    mov rdx, rcx          ; length
    syscall
    
    ; Print newline
    mov rax, 1            ; sys_write
    mov rdi, 1            ; stdout
    mov rsi, newline      ; newline character
    mov rdx, 1            ; length
    syscall
    
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    ret\n\n";
    return out;
}
