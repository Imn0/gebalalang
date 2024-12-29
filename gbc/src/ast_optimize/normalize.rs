use std::mem::swap;

use crate::{
    ast::{Ast, Command, Expression, MainBlock, Value},
    program::Program,
};

use super::{Normalize, Optimization};

impl Optimization for Normalize {
    fn run(&mut self, prog: &mut Program) {
        self.normalize_ast(&mut prog.ast);
    }
}

impl Normalize {
    fn normalize_ast(&mut self, ast: &mut Ast) {
        self.normalize_main_bloc(&mut ast.main_block);
    }

    fn normalize_main_bloc(&mut self, main_bloc: &mut MainBlock) {
        self.normalize_commands(&mut main_bloc.commands);
    }

    fn normalize_commands(&mut self, cmds: &mut Vec<Command>) {
        for cmd in cmds.iter_mut() {
            self.normalize_command(cmd);
        }
    }

    fn normalize_command(&mut self, cmd: &mut Command) {
        match cmd {
            Command::Assignment { expression, .. } => match expression {
                Expression::Multiplication(l, r) => {
                    if let Value::Number(_) = l {
                        if let Value::Identifier(_) = r {
                            swap(l, r);
                        }
                    }
                }
                _ => {}
            },
            _ => {}
        }
    }
}
