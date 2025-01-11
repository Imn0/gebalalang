use crate::code_gen::ir::{IrOperand, IR};

use super::{ConstatFolding, Optimizer};

impl Optimizer for ConstatFolding {
    fn optimize(&self, prog: &mut crate::code_gen::IrProgram) -> Result<(), ()> {
        for proc in prog.procedures.values_mut().into_iter() {
            self.optimize_block(&mut proc.cmds);
        }

        self.optimize_block(&mut prog.main);

        Ok(())
    }
}

impl ConstatFolding {
    fn optimize_block(&self, block: &mut Vec<IR>) {
        let mut i = 0;

        while i < block.len() {
            match &mut block[i] {
                IR::Add { dest, left, right } => {
                    if let (IrOperand::Constant(l), IrOperand::Constant(r)) = (left, right) {
                        if let Some(res) = r.checked_add(*l) {
                            block[i] = IR::Mov {
                                dest: dest.clone(),
                                src: IrOperand::Constant(res),
                            }
                        }
                    }
                }
                IR::Sub { dest, left, right } => {
                    if let (IrOperand::Constant(l), IrOperand::Constant(r)) = (left, right) {
                        if let Some(res) = l.checked_sub(*r) {
                            block[i] = IR::Mov {
                                dest: dest.clone(),
                                src: IrOperand::Constant(res),
                            }
                        }
                    }
                }
                IR::Mul { dest, left, right } => {
                    if let (IrOperand::Constant(l), IrOperand::Constant(r)) = (left, right) {
                        if let Some(res) = r.checked_mul(*l) {
                            block[i] = IR::Mov {
                                dest: dest.clone(),
                                src: IrOperand::Constant(res),
                            }
                        }
                    }
                }
                IR::Div { dest, left, right } => {
                    if let (IrOperand::Constant(l), IrOperand::Constant(r)) = (left, right) {
                        if let (Some(div_res), _) = get_gebala_div_mod_result(*l, *r) {
                            block[i] = IR::Mov {
                                dest: dest.clone(),
                                src: IrOperand::Constant(div_res),
                            }
                        }
                    }
                }

                IR::Mod { dest, left, right } => {
                    if let (IrOperand::Constant(l), IrOperand::Constant(r)) = (left, right) {
                        if let (_, Some(mod_result)) = get_gebala_div_mod_result(*l, *r) {
                            block[i] = IR::Mov {
                                dest: dest.clone(),
                                src: IrOperand::Constant(mod_result),
                            }
                        }
                    }
                }
                _ => {
                    i += 1;
                    continue;
                }
            }

            i += 1;
        }
    }
}

fn get_gebala_div_mod_result(left: i64, right: i64) -> (Option<i64>, Option<i64>) {
    let left_128 = left as i128;
    let right_128 = right as i128;

    let (abs_left, abs_right) =
        if let (Some(l), Some(r)) = (left_128.checked_abs(), right_128.checked_abs()) {
            (l, r)
        } else {
            return (None, None);
        };

    let (checked_div_res, checked_mod_res) = if let (Some(l), Some(r)) = (
        abs_left.checked_div(abs_right),
        abs_left.checked_rem(abs_right),
    ) {
        (l, r)
    } else {
        return (None, None);
    };

    let true_res = match (left > 0, right > 0) {
        (true, true) => {
            let div_res: Option<i64> = checked_div_res.try_into().ok();
            let mod_res: Option<i64> = checked_mod_res.try_into().ok();
            (div_res, mod_res)
        }
        (true, false) => {
            let div_res: Option<i64> = (-1 - checked_div_res).try_into().ok();
            let mod_res: Option<i64> = (abs_right - checked_mod_res).try_into().ok();
            (div_res, mod_res)
        }
        (false, true) => {
            let div_res: Option<i64> = (-1 - checked_div_res).try_into().ok();
            let mod_res: Option<i64> = (checked_mod_res - abs_right).try_into().ok();
            (div_res, mod_res)
        }
        (false, false) => {
            let div_res: Option<i64> = checked_div_res.try_into().ok();
            let mod_res: Option<i64> = (-checked_mod_res).try_into().ok();
            (div_res, mod_res)
        }
    };

    return true_res;
}
