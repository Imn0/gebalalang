use std::collections::{HashMap, HashSet};

use super::ast::*;

pub trait OptimizationPass {
    fn optimize(&mut self, ast: &mut Ast);
}


pub struct ConstantFolding;

impl OptimizationPass for ConstantFolding {
    fn optimize(&mut self, ast: &mut Ast) {
        Self::optimize_main_block(&mut ast.main_block);
        for procedure in &mut ast.procedures {
            Self::optimize_commands(&mut procedure.commands);
        }
    }
}

impl ConstantFolding {
    fn optimize_main_block(block: &mut MainBlock) {
        Self::optimize_commands(&mut block.commands);
    }

    fn optimize_commands(commands: &mut Vec<Command>) {
        for command in commands.iter_mut() {
            match command {
                Command::Assignment { expression, .. } => {
                    *expression = Self::fold_expression(expression);
                }
                Command::If {
                    condition,
                    then_commands,
                    ..
                } => {
                    Self::optimize_commands(then_commands);
                    *condition = Self::fold_condition(condition);
                }
                Command::IfElse {
                    condition,
                    then_commands,
                    else_commands,
                    ..
                } => {
                    Self::optimize_commands(then_commands);
                    Self::optimize_commands(else_commands);
                    *condition = Self::fold_condition(condition);
                }
                Command::While {
                    condition,
                    commands: block_commands,
                    ..
                } => {
                    Self::optimize_commands(block_commands);
                    *condition = Self::fold_condition(condition);
                }
                Command::Repeat {
                    commands: block_commands,
                    condition,
                    ..
                } => {
                    Self::optimize_commands(block_commands);
                    *condition = Self::fold_condition(condition);
                }
                Command::For {
                    commands: block_commands,
                    ..
                } => {
                    Self::optimize_commands(block_commands);
                }
                _ => {}
            }
        }
    }

    fn fold_expression(expr: &Expression) -> Expression {
        match expr {
            Expression::Addition(Value::Number(a), Value::Number(b)) => {
                Expression::Value(Value::Number(a + b))
            }
            Expression::Subtraction(Value::Number(a), Value::Number(b)) => {
                Expression::Value(Value::Number(a - b))
            }
            Expression::Multiplication(Value::Number(a), Value::Number(b)) => {
                Expression::Value(Value::Number(a * b))
            }
            Expression::Division(Value::Number(a), Value::Number(b)) if *b != 0 => {
                Expression::Value(Value::Number(a / b))
            }
            Expression::Modulo(Value::Number(a), Value::Number(b)) if *b != 0 => {
                Expression::Value(Value::Number(a % b))
            }
            _ => expr.clone(),
        }
    }

    fn fold_condition(condition: &Condition) -> Condition {
        match condition {
            Condition::Equal(Value::Number(a), Value::Number(b)) => {
                if a == b {
                    Condition::Equal(Value::Number(1), Value::Number(1))
                } else {
                    Condition::Equal(Value::Number(0), Value::Number(1))
                }
            }
            Condition::NotEqual(Value::Number(a), Value::Number(b)) => {
                if a != b {
                    Condition::Equal(Value::Number(1), Value::Number(1))
                } else {
                    Condition::Equal(Value::Number(0), Value::Number(1))
                }
            }
            _ => condition.clone(),
        }
    }
}

pub struct DeadCodeElimination;

impl OptimizationPass for DeadCodeElimination {
    fn optimize(&mut self, ast: &mut Ast) {
        Self::optimize_main_block(&mut ast.main_block);
        let used_procedures: HashSet<String> = ast
            .procedures
            .iter()
            .filter(|proc| Self::is_procedure_used(proc, ast))
            .map(|proc| proc.name.clone())
            .collect();
        ast.procedures
            .retain(|proc| used_procedures.contains(&proc.name));

        for procedure in &mut ast.procedures {
            Self::optimize_commands(&mut procedure.commands);
        }
    }
}

impl DeadCodeElimination {
    fn optimize_main_block(block: &mut MainBlock) {
        Self::optimize_commands(&mut block.commands);
    }

    fn optimize_commands(commands: &mut Vec<Command>) {
        let mut i = 0;
        while i < commands.len() {
            match &commands[i] {
                Command::If { condition, .. } => {
                    if let Condition::Equal(Value::Number(a), Value::Number(b)) = condition {
                        if a != b {
                            commands.remove(i);
                            continue;
                        }
                    }
                }
                Command::IfElse {
                    condition,
                    then_commands,
                    else_commands,
                    ..
                } => {
                    if let Condition::Equal(Value::Number(a), Value::Number(b)) = condition {
                        if a == b {
                            let replacement = then_commands.clone();
                            commands.splice(i..=i, replacement);
                        } else {
                            let replacement = else_commands.clone();
                            commands.splice(i..=i, replacement);
                        }
                        continue;
                    }
                }
                Command::While { condition, .. } => {
                    if let Condition::Equal(Value::Number(a), Value::Number(b)) = condition {
                        if a != b {
                            commands.remove(i);
                            continue;
                        }
                    }
                }
                _ => {}
            }
            i += 1;
        }
    }

    fn is_procedure_used(procedure: &Procedure, ast: &Ast) -> bool {
        let mut used = false;

        Self::check_commands_for_procedure(&ast.main_block.commands, &procedure.name, &mut used);

        for proc in &ast.procedures {
            Self::check_commands_for_procedure(&proc.commands, &procedure.name, &mut used);
        }

        used
    }

    fn check_commands_for_procedure(commands: &[Command], proc_name: &str, used: &mut bool) {
        for command in commands {
            match command {
                Command::ProcedureCall {
                    proc_name: name, ..
                } if name == proc_name => {
                    *used = true;
                    return;
                }
                Command::If { then_commands, .. } => {
                    Self::check_commands_for_procedure(then_commands, proc_name, used);
                }
                Command::IfElse {
                    then_commands,
                    else_commands,
                    ..
                } => {
                    Self::check_commands_for_procedure(then_commands, proc_name, used);
                    Self::check_commands_for_procedure(else_commands, proc_name, used);
                }
                Command::While {
                    commands: block_commands,
                    ..
                } => {
                    Self::check_commands_for_procedure(block_commands, proc_name, used);
                }
                Command::Repeat {
                    commands: block_commands,
                    ..
                } => {
                    Self::check_commands_for_procedure(block_commands, proc_name, used);
                }
                Command::For {
                    commands: block_commands,
                    ..
                } => {
                    Self::check_commands_for_procedure(block_commands, proc_name, used);
                }
                _ => {}
            }
        }
    }
}

pub struct LoopOptimization;

impl OptimizationPass for LoopOptimization {
    fn optimize(&mut self, ast: &mut Ast) {
        Self::optimize_main_block(&mut ast.main_block);
        for procedure in &mut ast.procedures {
            Self::optimize_commands(&mut procedure.commands);
        }
    }
}

impl LoopOptimization {
    fn optimize_main_block(block: &mut MainBlock) {
        Self::optimize_commands(&mut block.commands);
    }

    fn optimize_commands(commands: &mut Vec<Command>) {
        let mut i = 0;
        while i < commands.len() {
            if let Command::While {
                condition: c1,
                commands: while_commands,
                location,
            } = &commands[i]
            {
                if let Condition::Equal(Value::Number(1), Value::Number(1)) = c1 {
                    if let Some(Command::If {
                        condition: break_condition,
                        then_commands,
                        location,
                    }) = while_commands.first()
                    {
                        if then_commands.len() == 1 {
                            let remaining_commands = while_commands[1..].to_vec();
                            commands[i] = Command::Repeat {
                                commands: remaining_commands,
                                condition: break_condition.clone(),
                                location: commands[i].get_location().clone(),
                            };
                        }
                    }
                }
            }
            i += 1;
        }
    }
}

trait GetLocation {
    fn get_location(&self) -> &(tree_sitter::Point, tree_sitter::Point);
}

impl GetLocation for Command {
    fn get_location(&self) -> &(tree_sitter::Point, tree_sitter::Point) {
        match self {
            Command::Assignment { location, .. } => location,
            Command::IfElse { location, .. } => location,
            Command::If { location, .. } => location,
            Command::While { location, .. } => location,
            Command::Repeat { location, .. } => location,
            Command::For { location, .. } => location,
            Command::ProcedureCall { location, .. } => location,
            Command::Read(id) => &id.location,
            Command::Write(Value::Identifier(id)) => &id.location,
            Command::Write(Value::Number(_)) => panic!("No location for number literals"),
            Command::HasEffect(ef) => &ef.location,
        }
    }
}

pub struct Optimizer {
    passes: Vec<Box<dyn OptimizationPass>>,
}

impl Optimizer {
    pub fn new() -> Self {
        Self {
            passes: vec![
                Box::new(ConstantFolding),
                Box::new(DeadCodeElimination),
                Box::new(LoopOptimization),
            ],
        }
    }

    pub fn optimize(&mut self, ast: &mut Ast) {
        for pass in &mut self.passes {
            pass.optimize(ast);
        }
    }
}
