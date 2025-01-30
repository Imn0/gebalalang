use std::collections::{HashMap, HashSet};

use crate::{
    code_gen::{
        ir::{IrOperand, IR},
        IrProgram, ProcedureInfo,
    },
    program::Program,
};

trait Optimizer {
    fn optimize(&self, prog: &mut IrProgram);
}

struct RemoveTailingOperations;
struct ConstantFolding;
struct RemoveUnusedProcedures;
struct OptimizeInOutParameters;

impl Program {
    pub fn ir_optimize(&mut self) -> Result<(), ()> {
        let optimization_passes: Vec<Box<dyn Optimizer>> = vec![
            Box::new(RemoveTailingOperations),
            Box::new(RemoveUnusedProcedures),
            Box::new(ConstantFolding),
            Box::new(OptimizeInOutParameters),
        ];

        for optimization_pass in optimization_passes {
            optimization_pass.optimize(&mut self.ir_program);
        }

        return Ok(());
    }
}

impl Optimizer for RemoveUnusedProcedures {
    fn optimize(&self, _prog: &mut IrProgram) {
        // yeah so basically its done somewhere else
    }
}

impl Optimizer for ConstantFolding {
    fn optimize(&self, prog: &mut IrProgram) {
        for op in &mut prog.main {
            *op = self.optimize(&op);
        }
        for (_, proc) in prog.procedures.iter_mut() {
            for op in &mut proc.cmds {
                *op = self.optimize(&op);
            }
        }
    }
}

impl ConstantFolding {
    fn optimize(&self, op: &IR) -> IR {
        match op {
            IR::Add { dest, left, right } => {
                if let (IrOperand::Constant(a), IrOperand::Constant(b)) = (left, right) {
                    if let Some(new) = a.checked_add(*b) {
                        return IR::Mov {
                            dest: dest.clone(),
                            src: IrOperand::Constant(new),
                        };
                    }
                }
                op.clone()
            }
            IR::Sub { dest, left, right } => {
                if let (IrOperand::Constant(a), IrOperand::Constant(b)) = (left, right) {
                    if let Some(new) = a.checked_sub(*b) {
                        return IR::Mov {
                            dest: dest.clone(),
                            src: IrOperand::Constant(new),
                        };
                    }
                }
                op.clone()
            }
            IR::Mul { dest, left, right } => {
                if let (IrOperand::Constant(a), IrOperand::Constant(b)) = (left, right) {
                    if let Some(new) = a.checked_mul(*b) {
                        return IR::Mov {
                            dest: dest.clone(),
                            src: IrOperand::Constant(new),
                        };
                    }
                }
                op.clone()
            }
            IR::Div { dest, left, right } => {
                if let (IrOperand::Constant(x), IrOperand::Constant(y)) = (left, right) {
                    if *y == 0 {
                        return IR::Mov {
                            dest: dest.clone(),
                            src: IrOperand::Constant(0),
                        };
                    }
                    let result = (x / y)
                        - if x % y != 0 && ((*x < 0) != (*y < 0)) {
                            1
                        } else {
                            0
                        };
                    return IR::Mov {
                        dest: dest.clone(),
                        src: IrOperand::Constant(result),
                    };
                }
                op.clone()
            }
            IR::Mod { dest, left, right } => {
                if let (IrOperand::Constant(x), IrOperand::Constant(y)) = (left, right) {
                    if *y == 0 {
                        return IR::Mov {
                            dest: dest.clone(),
                            src: IrOperand::Constant(0),
                        };
                    }

                    return IR::Mov {
                        dest: dest.clone(),
                        src: IrOperand::Constant(((x % y) + y) % y),
                    };
                }
                op.clone()
            }
            _ => op.clone(),
        }
    }
}

impl Optimizer for RemoveTailingOperations {
    fn optimize(&self, prog: &mut IrProgram) {
        let p = &mut prog.main;
        while let Some(last) = p.last() {
            match last {
                crate::code_gen::ir::IR::Label(_)
                | crate::code_gen::ir::IR::Jump(_)
                | crate::code_gen::ir::IR::JZero { .. }
                | crate::code_gen::ir::IR::JNotZero { .. }
                | crate::code_gen::ir::IR::JPositive { .. }
                | crate::code_gen::ir::IR::JNegative { .. }
                | crate::code_gen::ir::IR::JPositiveOrZero { .. }
                | crate::code_gen::ir::IR::JNegativeOrZero { .. }
                | crate::code_gen::ir::IR::ProcCall { .. }
                | crate::code_gen::ir::IR::Read(_)
                | crate::code_gen::ir::IR::Write(_) => {
                    break;
                }
                _ => {}
            }
            p.pop();
        }
    }
}

impl Optimizer for OptimizeInOutParameters {
    fn optimize(&self, prog: &mut IrProgram) {
        let cpy = prog.procedures.clone();
        for (_, proc) in &mut prog.procedures {
            let written_to = self.get_all_writes(&proc.cmds, &cpy);
            for arg in proc.args.iter_mut() {
                if !written_to.contains(&arg.name) && !arg.is_array {
                    arg.is_in_only = true;
                }
            }
        }
    }
}

impl OptimizeInOutParameters {
    fn get_all_writes(
        &self,
        cmds: &Vec<IR>,
        ir_procs: &HashMap<String, ProcedureInfo>,
    ) -> HashSet<String> {
        let mut written: HashSet<String> = HashSet::new();
        for cmd in cmds {
            match cmd {
                IR::Mov { dest, .. }
                | IR::Add { dest, .. }
                | IR::Sub { dest, .. }
                | IR::Mul { dest, .. }
                | IR::Div { dest, .. }
                | IR::Mod { dest, .. }
                | IR::Read(dest) => {
                    if !dest.is_array() {
                        let base_name = dest.base_name();
                        written.insert(base_name.to_owned());
                    }
                }
                IR::ProcCall {
                    procedure,
                    arguments,
                } => {
                    let ir_proc = ir_procs.get(procedure).unwrap();
                    for (i, arg) in arguments.iter().enumerate() {
                        if arg.is_array() {
                            continue;
                        }
                        let arg_info = ir_proc.args.get(i).unwrap();
                        if !arg_info.is_in_only {
                            let base_name = arg.base_name();
                            written.insert(base_name.to_owned());
                        }
                    }
                }
                _ => {}
            }
        }
        return written;
    }
}
