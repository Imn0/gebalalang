use std::collections::HashMap;

use super::{
    ir::{IrOperand, IR},
    ArgInfo, IrProgram, ProcedureInfo,
};

#[derive(Default)]
struct CodeBlock {
    pub code: Vec<IR>,
    vars: HashMap<String, i64>,
}
#[allow(dead_code)]
impl IrProgram {
    pub fn tac_ify(self) -> IrProgram {
        let mut main_block = CodeBlock::default();
        main_block.tac_ify_instructions(self.main, &vec![]);

        let mut procedures: HashMap<String, ProcedureInfo> = HashMap::new();
        for proc in self.procedures {
            let mut c = CodeBlock::default();
            c.tac_ify_instructions(proc.1.cmds, &proc.1.args);
            procedures.insert(
                proc.0.to_string(),
                ProcedureInfo {
                    name: proc.1.name,
                    lbl: proc.1.lbl,
                    args: proc.1.args,
                    cmds: c.code,
                },
            );
        }

        IrProgram {
            main: main_block.code,
            procedures,
            next_label: self.next_label,
            current_scope: self.current_scope,
        }
    }
}

impl CodeBlock {
    fn tac_ify_instructions(&mut self, ins: Vec<IR>, args: &Vec<ArgInfo>) {
        for arg in args {
            self.vars.insert(arg.name.to_string(), 0);
        }
        self.code = vec![];
        for op in ins {
            let app = match &op {
                IR::Aloc { name, .. } => {
                    self.vars.insert(name.to_string(), 0);
                    op
                }
                IR::Drop { .. } => op,
                IR::Label(_) => op,
                IR::Jump(_) => op,
                IR::Return => op,
                IR::Comment(_) => op,
                IR::Mov { dest, src } => {
                    let src = self.get_current_var(src);
                    let dest = self.update_var(dest);

                    IR::Mov { dest: dest, src }
                }
                IR::Add { dest, right, left } => {
                    let left = self.get_current_var(left);
                    let right = self.get_current_var(right);
                    let dest = self.update_var(dest);
                    IR::Add { dest, left, right }
                }
                IR::Sub { dest, left, right } => {
                    let left = self.get_current_var(left);
                    let right = self.get_current_var(right);
                    let dest = self.update_var(dest);
                    IR::Sub { dest, left, right }
                }
                IR::Mul { dest, left, right } => {
                    let left = self.get_current_var(left);
                    let right = self.get_current_var(right);
                    let dest = self.update_var(dest);
                    IR::Mul { dest, left, right }
                }
                IR::Div { dest, left, right } => {
                    let left = self.get_current_var(left);
                    let right = self.get_current_var(right);
                    let dest = self.update_var(dest);
                    IR::Div { dest, left, right }
                }
                IR::Mod { dest, left, right } => {
                    let left = self.get_current_var(left);
                    let right = self.get_current_var(right);
                    let dest = self.update_var(dest);
                    IR::Mod { dest, left, right }
                }

                IR::JZero { left, right, label } => {
                    let left = self.get_current_var(left);
                    let right = self.get_current_var(right);
                    IR::JZero {
                        left,
                        right,
                        label: label.clone(),
                    }
                }
                IR::JNotZero { left, right, label } => {
                    let left = self.get_current_var(left);
                    let right = self.get_current_var(right);
                    IR::JNotZero {
                        left,
                        right,
                        label: label.clone(),
                    }
                }
                IR::JPositive { left, right, label } => {
                    let left = self.get_current_var(left);
                    let right = self.get_current_var(right);
                    IR::JPositive {
                        left,
                        right,
                        label: label.clone(),
                    }
                }
                IR::JNegative { left, right, label } => {
                    let left = self.get_current_var(left);
                    let right = self.get_current_var(right);
                    IR::JNegative {
                        left,
                        right,
                        label: label.clone(),
                    }
                }
                IR::JPositiveOrZero { left, right, label } => {
                    let left = self.get_current_var(left);
                    let right = self.get_current_var(right);
                    IR::JPositiveOrZero {
                        left,
                        right,
                        label: label.clone(),
                    }
                }
                IR::JNegativeOrZero { left, right, label } => {
                    let left = self.get_current_var(left);
                    let right = self.get_current_var(right);
                    IR::JNegativeOrZero {
                        left,
                        right,
                        label: label.clone(),
                    }
                }
                IR::ProcCall {
                    procedure,
                    arguments,
                } => {
                    let args = arguments
                        .iter()
                        .map(|arg| self.get_current_var(arg))
                        .collect();
                    IR::ProcCall {
                        procedure: procedure.clone(),
                        arguments: args,
                    }
                }

                IR::Read(ir_operand) => {
                    let oper = self.update_var(ir_operand);
                    IR::Read(oper)
                }
                IR::Write(ir_operand) => {
                    let oper = self.get_current_var(ir_operand);
                    IR::Write(oper)
                }
            };
            self.code.push(app);
        }

        for arg in args {
            let _ = self.get_current_var(&IrOperand::Variable(arg.name.clone()));
        }
    }

    fn update_var(&mut self, operand: &IrOperand) -> IrOperand {
        self._get_var_m_inc(operand, true)
    }

    fn get_current_var(&mut self, operand: &IrOperand) -> IrOperand {
        self._get_var_m_inc(operand, false)
    }

    fn _get_var_m_inc(&mut self, operand: &IrOperand, do_inc: bool) -> IrOperand {
        match operand {
            IrOperand::Variable(name) => {
                let cnt = self.vars.get_mut(name).unwrap();
                if do_inc {
                    *cnt += 1;
                }
                let new_name = format!("{}_:{}", name, cnt);

                return IrOperand::Variable(new_name);
            }
            IrOperand::Constant(_) => {
                return operand.clone();
            }
            IrOperand::ArrayConstAccess { .. } => {
                return operand.clone();
            }
            IrOperand::ArrayDynamicAccess {
                base_name,
                idx_name,
            } => {
                let cnt = self.vars.get_mut(idx_name).unwrap();
                let new_idx_name = format!("{}_:{}", idx_name, cnt);

                return IrOperand::ArrayDynamicAccess {
                    base_name: base_name.to_string(),
                    idx_name: new_idx_name,
                };
            }
        }
    }
}
