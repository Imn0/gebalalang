use crate::{
    code_gen::ir::{IrOperand, IR},
    program::Program,
};

use super::{Compile, PythonTarget};

impl Compile for PythonTarget {
    fn compile(&self, prog: &Program) -> Result<Box<[u8]>, ()> {
        let ir_prog = &prog.ir_program;
        let mut out = String::new();

        out += "#!/bin/python\n";
        out += "#type: ignore\n";

        out += "class JumpException(Exception):\n";
        out += "\tdef __init__(self, label):\n";
        out += "\t\tself.label = label\n\n";

        for (_, proc) in ir_prog.procedures.iter() {
            out += "def ";
            out += &format!(
                "{}({}):\n",
                sanitize_name(&proc.name),
                proc.args
                    .iter()
                    .map(|arg| {
                        let what_type = if arg.is_array {
                            "dict[int, int]"
                        } else {
                            "int"
                        };
                        format!("{}: {}", sanitize_name(&arg.name), what_type)
                    })
                    .collect::<Vec<String>>()
                    .join(", ")
            );

            out += "\tlabels = {}\n";

            for (i, ir_op) in proc.cmds.iter().enumerate() {
                if let IR::Label(label) = ir_op {
                    out += &format!("\tlabels[\"{}\"] = {}\n", label, i);
                }
            }

            out += "\tIP = 0\n";
            out += &format!("\twhile IP < {}:\n", proc.cmds.len());
            out += "\t\ttry:\n\t\t\tpass\n";

            for (i, ir_op) in proc.cmds.iter().enumerate() {
                out += &format!("\t\t\tif IP == {}:\n", i);
                let compiled = compile_op(ir_op);
                if !compiled.is_empty() {
                    out += &format!("\t\t\t\t{}\n", compiled);
                }
                out += "\t\t\t\tIP += 1\n";
            }

            out += "\t\texcept JumpException as je:\n";
            out += "\t\t\tIP = labels[je.label]\n";

            out += "\treturn ";
            out += &format!(
                "{}\n\n",
                proc.args
                    .iter()
                    .map(|arg| sanitize_name(&arg.name))
                    .collect::<Vec<String>>()
                    .join(", ")
            );
        }

        out += "def main():\n";
        out += "\tlabels = {}\n";

        for (i, ir_op) in ir_prog.main.iter().enumerate() {
            if let IR::Label(label) = ir_op {
                out += &format!("\tlabels[\"{}\"] = {}\n", label, i);
            }
        }

        out += &format!("\tIP = 0\n\twhile IP < {}:\n", ir_prog.main.len());
        out += "\t\ttry:\n\t\t\tpass\n";

        for (i, ir_op) in ir_prog.main.iter().enumerate() {
            out += &format!("\t\t\tif IP == {}:\n", i);
            let compiled = compile_op(ir_op);
            if !compiled.is_empty() {
                out += &format!("\t\t\t\t{}\n", compiled);
            }
            out += "\t\t\t\tIP += 1\n";
        }

        out += "\t\texcept JumpException as je:\n";
        out += "\t\t\tIP = labels[je.label]\n\n";

        out += "if __name__ == \"__main__\":\n";
        out += "\tmain()\n";
        Ok(out.as_bytes().into())
    }
}

fn compile_op(ir_op: &IR) -> String {
    match ir_op {
        IR::Mov { dest, src } => {
            format!("{} = {}", get_ir_operand(dest), get_ir_operand_safe(src))
        }
        IR::Add { dest, left, right } => {
            format!(
                "{} = {} + {}",
                get_ir_operand(dest),
                get_ir_operand_safe(left),
                get_ir_operand_safe(right)
            )
        }
        IR::Sub { dest, left, right } => {
            format!(
                "{} = {} - {}",
                get_ir_operand(dest),
                get_ir_operand_safe(left),
                get_ir_operand_safe(right)
            )
        }
        IR::Mul { dest, left, right } => {
            format!(
                "{} = {} * {}",
                get_ir_operand(dest),
                get_ir_operand_safe(left),
                get_ir_operand_safe(right)
            )
        }
        IR::Div { dest, left, right } => {
            format!(
                "{} = {} // {} if {} != 0 else 0",
                get_ir_operand(dest),
                get_ir_operand_safe(left),
                get_ir_operand_safe(right),
                get_ir_operand_safe(right)
            )
        }
        IR::Mod { dest, left, right } => {
            format!(
                "{} = {} % {} if {} != 0 else 0",
                get_ir_operand(dest),
                get_ir_operand_safe(left),
                get_ir_operand_safe(right),
                get_ir_operand_safe(right)
            )
        }
        IR::Label(_) => {
            format!("")
        }
        IR::Jump(label) => {
            format!("raise JumpException(\"{}\")", label)
        }
        IR::JZero { left, right, label } => {
            format!(
                "if {} - {} == 0: raise JumpException(\"{}\")",
                get_ir_operand_safe(left),
                get_ir_operand_safe(right),
                label
            )
        }
        IR::JNotZero { left, right, label } => {
            format!(
                "if {} - {} != 0: raise JumpException(\"{}\")",
                get_ir_operand_safe(left),
                get_ir_operand_safe(right),
                label
            )
        }
        IR::JPositive { left, right, label } => {
            format!(
                "if {} - {} > 0: raise JumpException(\"{}\")",
                get_ir_operand_safe(left),
                get_ir_operand_safe(right),
                label
            )
        }
        IR::JNegative { left, right, label } => {
            format!(
                "if {} - {} < 0: raise JumpException(\"{}\")",
                get_ir_operand_safe(left),
                get_ir_operand_safe(right),
                label
            )
        }
        IR::JPositiveOrZero { left, right, label } => {
            format!(
                "if {} - {} >= 0: raise JumpException(\"{}\")",
                get_ir_operand_safe(left),
                get_ir_operand_safe(right),
                label
            )
        }
        IR::JNegativeOrZero { left, right, label } => {
            format!(
                "if {} - {} <= 0: raise JumpException(\"{}\")",
                get_ir_operand_safe(left),
                get_ir_operand_safe(right),
                label
            )
        }
        IR::ProcCall {
            procedure,
            arguments,
        } => {
            format!(
                "{} = {}({})",
                arguments
                    .iter()
                    .map(|o| sanitize_name(&o.to_string()))
                    .collect::<Vec<String>>()
                    .join(", "),
                sanitize_name(procedure),
                arguments
                    .iter()
                    .map(|o| sanitize_name(&o.to_string()))
                    .collect::<Vec<String>>()
                    .join(", ")
            )
        }
        IR::Return => {
            format!("")
        }
        IR::Read(ir_operand) => {
            format!("{} = int(input())", get_ir_operand(ir_operand))
        }
        IR::Write(ir_operand) => {
            format!("print(f\"{{{}}}\")", get_ir_operand_safe(ir_operand))
        }
        IR::Aloc {
            name,
            is_array,
            array_bounds: _,
        } => {
            if !*is_array {
                format!("{}=0", sanitize_name(name))
            } else {
                format!("{}={{}}", sanitize_name(name))
            }
        }
        IR::Drop { .. } => {
            format!("")
        }
        IR::Comment(_) => format!(""),
    }
}

fn get_ir_operand(operand: &IrOperand) -> String {
    match operand {
        IrOperand::Variable(name) => return sanitize_name(&get_base_name(name)),
        IrOperand::Constant(num) => format!("{}", num),
        IrOperand::ArrayConstAccess { base_name, idx } => {
            format!("{}[{}]", sanitize_name(base_name), idx)
        }
        IrOperand::ArrayDynamicAccess {
            base_name,
            idx_name,
        } => {
            format!(
                "{}[{}]",
                sanitize_name(base_name),
                sanitize_name(&get_base_name(idx_name))
            )
        }
    }
}

fn get_ir_operand_safe(operand: &IrOperand) -> String {
    match operand {
        IrOperand::Variable(name) => return sanitize_name(&get_base_name(name)),
        IrOperand::Constant(num) => format!("{}", num),
        IrOperand::ArrayConstAccess { base_name, idx } => {
            format!("{}.get({}, 0)", sanitize_name(base_name), idx)
        }
        IrOperand::ArrayDynamicAccess {
            base_name,
            idx_name,
        } => {
            format!(
                "{}.get({}, 0)",
                sanitize_name(base_name),
                sanitize_name(&get_base_name(idx_name))
            )
        }
    }
}

fn get_base_name(name: &str) -> String {
    // let parts: Vec<&str> = name.split("_:").collect();
    // parts[0].to_owned()
    name.to_owned()
}

fn sanitize_name(name: &str) -> String {
    format!("PYTHON_{name}")
}
