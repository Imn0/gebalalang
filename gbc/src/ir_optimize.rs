use std::{
    collections::{HashMap, HashSet},
    process::{Command, Stdio},
    thread,
    time::{Duration, Instant},
};

use crate::{
    code_gen::{
        ir::{IrOperand, IR},
        IrProgram, ProcedureInfo,
    },
    program::Program,
    targets::{Compile, PythonTarget},
};

trait Optimizer {
    fn optimize(&self, ir_prog: &mut IrProgram);
}

struct RemoveTailingOperations;
struct ConstantFolding;
struct RemoveUnusedProcedures;
struct OptimizeInOutParameters;
struct NoReadInstructions;

impl Program {
    pub fn ir_optimize(&mut self) -> Result<(), ()> {
        let optimization_passes: Vec<Box<dyn Optimizer>> = vec![
            Box::new(RemoveTailingOperations),
            Box::new(RemoveUnusedProcedures),
            Box::new(ConstantFolding),
            Box::new(NoReadInstructions),
            Box::new(OptimizeInOutParameters),
            Box::new(OptimizeInOutParameters),
            Box::new(OptimizeInOutParameters),
            Box::new(OptimizeInOutParameters),
        ];

        for optimization_pass in optimization_passes {
            optimization_pass.optimize(&mut self.ir_program);
        }

        return Ok(());
    }
}

impl Optimizer for NoReadInstructions {
    fn optimize(&self, prog: &mut IrProgram) {
        let mut h = self.has_reads(&prog.main);
        for proc in &prog.procedures {
            if self.has_reads(&proc.1.cmds) {
                h = true;
            }
        }

        if h {
            return;
        }

        let target = PythonTarget;
        let mut prog_cpy = Program::default();
        prog_cpy.ir_program = prog.clone();
        let r = target.compile(&mut prog_cpy);
        let code = match r {
            Ok(cmd) => cmd,
            Err(_) => return,
        };
        let code_str = String::from_utf8_lossy(&code).to_string();
        let mut python_run = Command::new("python3")
            .arg("-c")
            .arg(code_str)
            .stdout(Stdio::piped())
            .stderr(Stdio::piped())
            .spawn()
            .expect("Failed to start process");

        let timeout = Duration::new(0, 650000000);
        let start_time = Instant::now();

        loop {
            if python_run.try_wait().unwrap().is_some() {
                break;
            }

            if start_time.elapsed() >= timeout {
                python_run.kill().expect("Failed to kill process");
                return;
            }

            thread::sleep(Duration::from_millis(50));
        }
        if !python_run.wait().unwrap().success() {
            return;
        }

        let output =
            String::from_utf8_lossy(&python_run.wait_with_output().unwrap().stdout).to_string();
        let mut valid = true;
        let output: Vec<i64> = output
            .lines()
            .map(|c| {
                c.parse().unwrap_or_else(|_| {
                    valid = false;
                    99
                })
            })
            .collect();

        if !valid {
            return;
        }

        let new_main: Vec<IR> = output
            .iter()
            .map(|num| IR::Write(IrOperand::Constant(*num)))
            .collect();

        prog.main = new_main;
    }
}

impl NoReadInstructions {
    fn has_reads(&self, commands: &Vec<IR>) -> bool {
        for op in commands {
            match op {
                IR::Read(_) => {
                    return true;
                }
                _ => {}
            }
        }
        return false;
    }
}

impl Optimizer for RemoveUnusedProcedures {
    fn optimize(&self, prog: &mut IrProgram) {
        let mut compiled_procs: HashSet<String> = HashSet::new();

        let mut to_compile = self.get_calls(&prog.main);

        for _ in 0..prog.procedures.len() {
            let left_to_compile: Vec<String> =
                to_compile.difference(&compiled_procs).cloned().collect();

            if left_to_compile.len() == 0 {
                break;
            }

            for name in left_to_compile {
                let proc = prog.procedures.get(&name).unwrap();
                compiled_procs.insert(name);
                let new_calls = self.get_calls(&proc.cmds);
                to_compile.extend(new_calls);
            }
        }

        prog.procedures = prog
            .procedures
            .iter()
            .filter(|p| {
                if compiled_procs.contains(p.0) {
                    true
                } else {
                    false
                }
            })
            .map(|(k, v)| (k.clone(), v.clone()))
            .collect();
    }
}

impl RemoveUnusedProcedures {
    fn get_calls(&self, ir: &Vec<IR>) -> HashSet<String> {
        let mut calls: HashSet<String> = HashSet::new();
        ir.iter().for_each(|op| match op {
            IR::ProcCall { procedure, .. } => {
                calls.insert(procedure.clone());
            }
            _ => {}
        });

        return calls;
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
