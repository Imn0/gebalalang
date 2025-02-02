use super::gvm_ext::{GVMe, GVMeCompileContext, GVMeProc, LabelIdx};

#[allow(non_camel_case_types)]
pub enum BUILTINS {
    MUL,
    DIV_MOD,
    MOD,
}
impl BUILTINS {
    pub fn to_name(&self) -> &'static str {
        match self {
            BUILTINS::MUL => "__BUILTIN_MUL",
            BUILTINS::DIV_MOD => "__BUILTIN_DIV_MOD",
            BUILTINS::MOD => "__BUILTIN_MOD",
        }
    }
}

impl<'a> GVMeCompileContext<'a> {
    /// BUILTIN PROCEDURES !!!!
    pub fn generate_mul_procedure_stub(&mut self) -> GVMeProc {
        let proc_name = BUILTINS::MUL.to_name();

        let mut args = vec![];
        args.push(
            self.memory
                .allocate_in_arg("arg1", &proc_name)
                .memory_address,
        );
        args.push(
            self.memory
                .allocate_in_arg("arg2", &proc_name)
                .memory_address,
        );
        args.push(
            self.memory
                .allocate_in_arg("rtn", &proc_name)
                .memory_address,
        );

        self.memory.allocate_in_arg("last_arg1", &proc_name);
        self.memory.allocate_in_arg("last_arg2", &proc_name);

        self.next_available_label += 1;
        GVMeProc {
            label: LabelIdx(self.next_available_label - 1),
            return_address: self.memory.allocate_proc_return(&proc_name),
            args: args,
            do_inline: false,
            arg_names: vec![
                "arg1".to_owned(),
                "arg2".to_owned(),
                "rtn".to_owned(),
                "last_arg1".to_owned(),
                "last_arg2".to_owned(),
            ],
        }
    }

    pub fn generate_mod_procedure_stub(&mut self) -> GVMeProc {
        let proc_name = BUILTINS::MOD.to_name();

        let mut args = vec![];
        args.push(
            self.memory
                .allocate_in_arg("arg1", &proc_name)
                .memory_address,
        );
        args.push(
            self.memory
                .allocate_in_arg("arg2", &proc_name)
                .memory_address,
        );
        args.push(
            self.memory
                .allocate_in_arg("rtn", &proc_name)
                .memory_address,
        );

        self.next_available_label += 1;
        GVMeProc {
            label: LabelIdx(self.next_available_label - 1),
            return_address: self.memory.allocate_proc_return(&proc_name),
            args: args,
            do_inline: false,
            arg_names: vec!["arg1".to_owned(), "arg2".to_owned(), "rtn".to_owned()],
        }
    }

    pub fn generate_div_mod_procedure_stub(&mut self) -> GVMeProc {
        let proc_name = BUILTINS::DIV_MOD.to_name();

        let mut args = vec![];
        args.push(
            self.memory
                .allocate_in_arg("arg1", &proc_name)
                .memory_address,
        );
        args.push(
            self.memory
                .allocate_in_arg("arg2", &proc_name)
                .memory_address,
        );
        args.push(
            self.memory
                .allocate_in_arg("dividend", &proc_name)
                .memory_address,
        );
        args.push(
            self.memory
                .allocate_in_arg("divisor", &proc_name)
                .memory_address,
        );

        args.push(
            self.memory
                .allocate_in_arg("last_arg1", &proc_name)
                .memory_address,
        );
        args.push(
            self.memory
                .allocate_in_arg("last_arg2", &proc_name)
                .memory_address,
        );

        self.next_available_label += 1;

        GVMeProc {
            label: LabelIdx(self.next_available_label - 1),
            return_address: self.memory.allocate_proc_return(&proc_name),
            args: args,
            do_inline: false,
            arg_names: vec![
                "arg1".to_owned(),
                "arg2".to_owned(),
                "dividend".to_owned(),
                "divisor".to_owned(),
                "last_arg1".to_owned(),
                "last_arg2".to_owned(),
            ],
        }
    }

    pub fn compile_mul_builtin(&mut self) {
        let proc_info = self
            .proc_info
            .get(BUILTINS::MUL.to_name())
            .cloned()
            .unwrap();
        self.buff.push(GVMe::lbl {
            idx: proc_info.label.clone(),
            name: BUILTINS::MUL.to_name().to_owned(),
        });
        let arg1 = proc_info.args[0];
        let arg2 = proc_info.args[1];
        let res_rtn = proc_info.args[2];

        let last_arg1 = self
            .memory
            .get_base_loc("last_arg1", &BUILTINS::MUL.to_name())
            .memory_address;

        let last_arg2 = self
            .memory
            .get_base_loc("last_arg2", &BUILTINS::MUL.to_name())
            .memory_address;

        let zero = 0;
        let one = 1;
        let m_one = -1;

        let loop_end_lbl = self.next_label();
        let loop_start_lbl = self.next_label();

        let skip_add = self.next_label();

        let sign_flag = self
            .memory
            .allocate_var("sign_flag", BUILTINS::MUL.to_name())
            .memory_address;
        let arg1_op = self
            .memory
            .allocate_var("arg1_op", BUILTINS::MUL.to_name())
            .memory_address;
        let arg2_op = self
            .memory
            .allocate_var("arg2_op", BUILTINS::MUL.to_name())
            .memory_address;
        let res = self
            .memory
            .allocate_var("res", BUILTINS::MUL.to_name())
            .memory_address;
        let arg_1_pos = self.next_label();
        let arg_2_pos = self.next_label();

        self.const_in_acc(&one);
        self.buff.push(GVMe::STORE(sign_flag));

        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::jpos(arg_1_pos.clone()));

        self.const_in_acc(&m_one);
        self.buff.push(GVMe::STORE(sign_flag));
        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(arg1));
        self.buff.push(GVMe::STORE(arg1));

        self.buff.push(GVMe::lbl {
            idx: arg_1_pos,
            name: format!(""),
        });

        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::jpos(arg_2_pos.clone()));

        self.const_in_acc(&zero);

        self.buff.push(GVMe::SUB(sign_flag));
        self.buff.push(GVMe::STORE(sign_flag));
        self.const_in_acc(&zero);

        self.buff.push(GVMe::SUB(arg2));
        self.buff.push(GVMe::STORE(arg2));

        self.buff.push(GVMe::lbl {
            idx: arg_2_pos,
            name: format!(""),
        });
        //TODO VVVVVV
        // SWAP ARGS SO THE SMALLER ONE IS FIRST
        let tmp = self.last_mem_slot - 2;
        let dont_swap = self.next_label();
        self.buff.push(GVMe::SUB(arg1));
        self.buff.push(GVMe::jpos(dont_swap));
        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::STORE(tmp));
        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::STORE(arg1));
        self.buff.push(GVMe::LOAD(tmp));
        self.buff.push(GVMe::STORE(arg2));
        self.buff.push(GVMe::lbl {
            idx: dont_swap,
            name: format!(""),
        });
        if self.mul_call_count > 3 {
            // CHECK IF LAST ARGS ARE THE SAME
            let _skip = self.next_label();
            self.buff.push(GVMe::LOAD(arg2));
            self.buff.push(GVMe::SUB(last_arg2));
            self.buff.push(GVMe::jnz(_skip));
            self.buff.push(GVMe::LOAD(arg1));
            self.buff.push(GVMe::SUB(last_arg1));
            self.buff.push(GVMe::jz(loop_end_lbl));

            self.buff.push(GVMe::lbl {
                idx: _skip,
                name: "".to_owned(),
            });
        }

        // STORE CURRENT ARGS TO LAST ARGS

        self.const_in_acc(&zero);
        self.buff.push(GVMe::STORE(res));
        self.buff.push(GVMe::LOAD(arg2));
        if self.mul_call_count > 3 {
            self.buff.push(GVMe::STORE(last_arg2));
        }
        self.buff.push(GVMe::STORE(arg2_op));
        self.buff.push(GVMe::LOAD(arg1));

        if self.mul_call_count > 3 {
            self.buff.push(GVMe::STORE(last_arg1));
        }
        self.buff.push(GVMe::STORE(arg1_op));
        // CARRY ON
        self.buff.push(GVMe::LOAD(arg1_op));
        self.buff.push(GVMe::lbl {
            idx: loop_start_lbl.clone(),
            name: format!(""),
        });
        self.buff.push(GVMe::jz(loop_end_lbl.clone()));

        self.buff.push(GVMe::HALF);
        self.buff.push(GVMe::ADD(0));
        self.buff.push(GVMe::SUB(arg1_op));

        self.buff.push(GVMe::jz(skip_add.clone()));
        self.buff.push(GVMe::LOAD(arg1_op));
        self.buff.push(GVMe::LOAD(res));
        self.buff.push(GVMe::ADD(arg2_op));
        self.buff.push(GVMe::STORE(res));
        self.buff.push(GVMe::lbl {
            idx: skip_add,
            name: format!(""),
        });

        self.buff.push(GVMe::LOAD(arg2_op));
        self.buff.push(GVMe::ADD(arg2_op));
        self.buff.push(GVMe::STORE(arg2_op));

        self.buff.push(GVMe::LOAD(arg1_op));
        self.buff.push(GVMe::HALF);
        self.buff.push(GVMe::STORE(arg1_op));

        self.buff.push(GVMe::lbl_jump(loop_start_lbl));
        self.buff.push(GVMe::lbl {
            idx: loop_end_lbl,
            name: format!(""),
        });
        let is_pos = self.next_label();

        let skip = self.next_label();

        self.buff.push(GVMe::LOAD(sign_flag));
        self.buff.push(GVMe::jpos(is_pos.clone()));

        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(res));
        self.buff.push(GVMe::lbl_jump(skip.clone()));

        self.buff.push(GVMe::lbl {
            idx: is_pos,
            name: format!(""),
        });
        self.buff.push(GVMe::LOAD(res));
        self.buff.push(GVMe::lbl {
            idx: skip,
            name: format!(""),
        });
        self.buff.push(GVMe::STORE(res_rtn));

        self.buff.push(GVMe::RTRN(proc_info.return_address));
    }

    pub fn compile_div_mod_builtin(&mut self) {
        let proc_info = self
            .proc_info
            .get(BUILTINS::DIV_MOD.to_name())
            .cloned()
            .unwrap();
        self.buff.push(GVMe::lbl {
            idx: proc_info.label.clone(),
            name: BUILTINS::DIV_MOD.to_name().to_owned(),
        });

        let arg1 = proc_info.args[0];
        let arg2 = proc_info.args[1];
        let div_res_rtn = proc_info.args[2];
        let mod_res_rtn = proc_info.args[3];
        let last_arg1 = proc_info.args[4];
        let last_arg2 = proc_info.args[5];

        let zero = 0;
        let one = 1;
        let m_one = -1;
        let arg1_positive = self
            .memory
            .allocate_var("arg1_positive", BUILTINS::DIV_MOD.to_name())
            .memory_address;
        let arg2_positive = self
            .memory
            .allocate_var("arg2_positive", BUILTINS::DIV_MOD.to_name())
            .memory_address;

        let power_of_two = self
            .memory
            .allocate_var("power_of_two", BUILTINS::DIV_MOD.to_name())
            .memory_address;

        let arg2_cpy = self
            .memory
            .allocate_var("arg2_cpy", BUILTINS::DIV_MOD.to_name())
            .memory_address;

        let div_res = self
            .memory
            .allocate_var("div_res", BUILTINS::DIV_MOD.to_name())
            .memory_address;
        let mod_res = self
            .memory
            .allocate_var("mod_res", BUILTINS::DIV_MOD.to_name())
            .memory_address;
        let sign_flag = self
            .memory
            .allocate_var("sign_flag", BUILTINS::DIV_MOD.to_name())
            .memory_address;

        let arg_1_pos = self.next_label();
        let arg_2_pos = self.next_label();
        let arg_2_zero = self.next_label();
        // if b == 0
        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::jnz(arg_2_zero));
        self.const_in_acc(&zero);
        self.buff.push(GVMe::STORE(div_res_rtn));
        self.buff.push(GVMe::STORE(mod_res_rtn));
        self.buff.push(GVMe::RTRN(proc_info.return_address));
        self.buff.push(GVMe::lbl {
            idx: arg_2_zero,
            name: format!(""),
        });

        // sign = 1, mod_sign = 1
        self.const_in_acc(&one);
        self.buff.push(GVMe::STORE(arg1_positive));
        self.buff.push(GVMe::STORE(arg2_positive));
        self.buff.push(GVMe::STORE(sign_flag));

        // if arg1 < 0
        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::jpos(arg_1_pos.clone()));

        self.const_in_acc(&m_one);
        self.buff.push(GVMe::STORE(arg1_positive));
        self.buff.push(GVMe::STORE(sign_flag));
        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(arg1));
        self.buff.push(GVMe::STORE(arg1));

        self.buff.push(GVMe::lbl {
            idx: arg_1_pos,
            name: format!(""),
        });

        // if arg2 < 0
        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::jpos(arg_2_pos.clone()));

        self.const_in_acc(&m_one);
        self.buff.push(GVMe::STORE(arg2_positive));

        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(sign_flag));
        self.buff.push(GVMe::STORE(sign_flag));
        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(arg2));
        self.buff.push(GVMe::STORE(arg2));

        self.buff.push(GVMe::lbl {
            idx: arg_2_pos,
            name: format!(""),
        });
        self.buff.push(GVMe::STORE(arg2_cpy));

        //TODO VVVVVV
        let loop2_end = self.next_label();

        if self.mod_div_call_count > 1 {
            let skip = self.next_label();
            // CHECK IF LAST ARGS ARE THE SAME
            self.buff.push(GVMe::LOAD(arg2));
            self.buff.push(GVMe::SUB(last_arg2));
            self.buff.push(GVMe::jnz(skip));
            self.buff.push(GVMe::LOAD(arg1));
            self.buff.push(GVMe::SUB(last_arg1));
            self.buff.push(GVMe::jz(loop2_end));

            self.buff.push(GVMe::lbl {
                idx: skip,
                name: "".to_owned(),
            });
            // STORE CURRENT ARGS TO LAST ARGS
            self.buff.push(GVMe::LOAD(arg2));
            self.buff.push(GVMe::STORE(last_arg2));
            self.buff.push(GVMe::LOAD(arg1));
            self.buff.push(GVMe::STORE(last_arg1));
        }
        // CARRY ON

        self.const_in_acc(&zero);
        self.buff.push(GVMe::STORE(div_res));

        self.const_in_acc(&one);
        self.buff.push(GVMe::STORE(power_of_two));

        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::STORE(mod_res));

        /*
        while arg2 - arg1 < 0:
            arg2 += arg2
            power_of_two += power_of_two
        */
        let loop1_start = self.next_label();
        let loop_exit1 = self.next_label();
        self.buff.push(GVMe::lbl {
            idx: loop1_start.clone(),
            name: format!(""),
        });
        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::SUB(mod_res));
        self.buff.push(GVMe::jpos(loop_exit1.clone()));
        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::ADD(arg2));
        self.buff.push(GVMe::STORE(arg2));

        self.buff.push(GVMe::LOAD(power_of_two));
        self.buff.push(GVMe::ADD(power_of_two));
        self.buff.push(GVMe::STORE(power_of_two));

        self.buff.push(GVMe::lbl_jump(loop1_start));
        self.buff.push(GVMe::lbl {
            idx: loop_exit1,
            name: format!(""),
        });

        /*
        while !power_of_two <= 0:
            if arg1 - arg2 >= 0 :
                arg1 -= arg2
                quotient += power_of_two

            arg2 = arg2 // 2
            power_of_two = power_of_two // 2
        */
        let loop2_start = self.next_label();
        let inner_if_fail = self.next_label();

        self.buff.push(GVMe::lbl {
            idx: loop2_start.clone(),
            name: format!(""),
        });
        self.buff.push(GVMe::LOAD(power_of_two));
        self.buff.push(GVMe::jnegz(loop2_end.clone()));

        self.buff.push(GVMe::LOAD(mod_res));
        self.buff.push(GVMe::SUB(arg2));
        self.buff.push(GVMe::jneg(inner_if_fail.clone()));
        self.buff.push(GVMe::LOAD(mod_res));
        self.buff.push(GVMe::SUB(arg2));
        self.buff.push(GVMe::STORE(mod_res));

        self.buff.push(GVMe::LOAD(div_res));
        self.buff.push(GVMe::ADD(power_of_two));
        self.buff.push(GVMe::STORE(div_res));

        self.buff.push(GVMe::lbl {
            idx: inner_if_fail,
            name: format!(""),
        });

        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::HALF);
        self.buff.push(GVMe::STORE(arg2));

        self.buff.push(GVMe::LOAD(power_of_two));
        self.buff.push(GVMe::HALF);
        self.buff.push(GVMe::STORE(power_of_two));

        self.buff.push(GVMe::lbl_jump(loop2_start));
        self.buff.push(GVMe::lbl {
            idx: loop2_end,
            name: format!(""),
        });

        // what if r == 0 ?????
        let fix_mod = self.next_label();
        let skip_sign = self.next_label();
        self.buff.push(GVMe::LOAD(mod_res));
        self.buff.push(GVMe::jnz(fix_mod));
        self.buff.push(GVMe::STORE(mod_res_rtn));

        self.buff.push(GVMe::LOAD(sign_flag));
        self.buff.push(GVMe::jpos(skip_sign));

        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(div_res));
        self.buff.push(GVMe::STORE(div_res));

        self.buff.push(GVMe::lbl {
            idx: skip_sign,
            name: format!(""),
        });
        self.buff.push(GVMe::LOAD(div_res));
        self.buff.push(GVMe::STORE(div_res_rtn));

        self.buff.push(GVMe::RTRN(proc_info.return_address));

        self.buff.push(GVMe::lbl {
            idx: fix_mod,
            name: "".to_owned(),
        });

        // arg1 positive
        let arg1_is_in_fact_negative = self.next_label();
        self.buff.push(GVMe::LOAD(arg1_positive));
        self.buff.push(GVMe::jneg(arg1_is_in_fact_negative));

        // arg1 pos, arg2 pos
        let arg1_pos_and_arg2_negative = self.next_label();
        self.buff.push(GVMe::LOAD(arg2_positive));
        self.buff.push(GVMe::jneg(arg1_pos_and_arg2_negative));
        // x>0 y>0 -> nothing
        self.buff.push(GVMe::LOAD(mod_res));
        self.buff.push(GVMe::STORE(mod_res_rtn));
        self.buff.push(GVMe::LOAD(div_res));
        self.buff.push(GVMe::STORE(div_res_rtn));
        self.buff.push(GVMe::RTRN(proc_info.return_address));

        // arg1 pos, arg2 neg
        self.buff.push(GVMe::lbl {
            idx: arg1_pos_and_arg2_negative,
            name: format!(""),
        });

        // x>0 y<0 -> q = -1 - q and r = r - y
        self.const_in_acc(&m_one);
        self.buff.push(GVMe::SUB(div_res));
        self.buff.push(GVMe::STORE(div_res_rtn));
        self.buff.push(GVMe::LOAD(mod_res));
        self.buff.push(GVMe::SUB(arg2_cpy));
        self.buff.push(GVMe::STORE(mod_res_rtn));
        self.buff.push(GVMe::RTRN(proc_info.return_address));

        // arg1 negative
        self.buff.push(GVMe::lbl {
            idx: arg1_is_in_fact_negative,
            name: format!(""),
        });

        let arg1_neg_and_arg2_neg = self.next_label();
        self.buff.push(GVMe::LOAD(arg2_positive));
        self.buff.push(GVMe::jneg(arg1_neg_and_arg2_neg));
        // x<0 y>0 -> q = -1 - q and r = y - r
        self.const_in_acc(&m_one);
        self.buff.push(GVMe::SUB(div_res));
        self.buff.push(GVMe::STORE(div_res_rtn));
        self.buff.push(GVMe::LOAD(arg2_cpy));
        self.buff.push(GVMe::SUB(mod_res));
        self.buff.push(GVMe::STORE(mod_res_rtn));
        self.buff.push(GVMe::RTRN(proc_info.return_address));

        self.buff.push(GVMe::lbl {
            idx: arg1_neg_and_arg2_neg,
            name: format!(""),
        });
        // x<0 y<0 -> r = -r
        self.buff.push(GVMe::LOAD(div_res));
        self.buff.push(GVMe::STORE(div_res_rtn));
        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(mod_res));
        self.buff.push(GVMe::STORE(mod_res_rtn));

        self.buff.push(GVMe::RTRN(proc_info.return_address));
    }

    pub fn compile_mod_builtin(&mut self) {
        let proc_info = self
            .proc_info
            .get(BUILTINS::MOD.to_name())
            .cloned()
            .unwrap();
        self.buff.push(GVMe::lbl {
            idx: proc_info.label.clone(),
            name: BUILTINS::MOD.to_name().to_owned(),
        });

        let arg1 = proc_info.args[0];
        let arg2 = proc_info.args[1];
        let mod_res_rtn = proc_info.args[2];

        let zero = 0;
        let one = 1;
        let m_one = -1;
        let arg1_positive = self
            .memory
            .allocate_var("arg1_positive", BUILTINS::DIV_MOD.to_name())
            .memory_address;
        let arg2_positive = self
            .memory
            .allocate_var("arg2_positive", BUILTINS::DIV_MOD.to_name())
            .memory_address;

        let power_of_two = self
            .memory
            .allocate_var("power_of_two", BUILTINS::DIV_MOD.to_name())
            .memory_address;

        let arg2_cpy = self
            .memory
            .allocate_var("arg2_cpy", BUILTINS::DIV_MOD.to_name())
            .memory_address;

        
        let mod_res = self
            .memory
            .allocate_var("mod_res", BUILTINS::DIV_MOD.to_name())
            .memory_address;
        let sign_flag = self
            .memory
            .allocate_var("sign_flag", BUILTINS::DIV_MOD.to_name())
            .memory_address;

        let arg_1_pos = self.next_label();
        let arg_2_pos = self.next_label();
        let arg_2_zero = self.next_label();
        // if b == 0
        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::jnz(arg_2_zero.clone()));
        self.const_in_acc(&zero);
        self.buff.push(GVMe::STORE(mod_res_rtn));
        self.buff.push(GVMe::RTRN(proc_info.return_address));
        self.buff.push(GVMe::lbl {
            idx: arg_2_zero,
            name: format!(""),
        });

        // sign = 1, mod_sign = 1
        self.const_in_acc(&one);
        self.buff.push(GVMe::STORE(arg1_positive));
        self.buff.push(GVMe::STORE(arg2_positive));
        self.buff.push(GVMe::STORE(sign_flag));

        // if arg1 < 0
        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::jpos(arg_1_pos.clone()));

        self.const_in_acc(&m_one);
        self.buff.push(GVMe::STORE(arg1_positive));
        self.buff.push(GVMe::STORE(sign_flag));
        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(arg1));
        self.buff.push(GVMe::STORE(arg1));

        self.buff.push(GVMe::lbl {
            idx: arg_1_pos,
            name: format!(""),
        });

        // if arg2 < 0
        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::jpos(arg_2_pos.clone()));

        self.const_in_acc(&m_one);
        self.buff.push(GVMe::STORE(arg2_positive));

        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(sign_flag));
        self.buff.push(GVMe::STORE(sign_flag));
        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(arg2));
        self.buff.push(GVMe::STORE(arg2));

        self.buff.push(GVMe::lbl {
            idx: arg_2_pos,
            name: format!(""),
        });
        self.buff.push(GVMe::STORE(arg2_cpy));

        //TODO VVVVVV
        let loop2_end = self.next_label();


        self.const_in_acc(&one);
        self.buff.push(GVMe::STORE(power_of_two));

        self.buff.push(GVMe::LOAD(arg1));
        self.buff.push(GVMe::STORE(mod_res));

        /*
        while arg2 - arg1 < 0:
            arg2 += arg2
            power_of_two += power_of_two
        */
        let loop1_start = self.next_label();
        let loop_exit1 = self.next_label();
        self.buff.push(GVMe::lbl {
            idx: loop1_start.clone(),
            name: format!(""),
        });
        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::SUB(mod_res));
        self.buff.push(GVMe::jpos(loop_exit1.clone()));
        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::ADD(arg2));
        self.buff.push(GVMe::STORE(arg2));

        self.buff.push(GVMe::LOAD(power_of_two));
        self.buff.push(GVMe::ADD(power_of_two));
        self.buff.push(GVMe::STORE(power_of_two));

        self.buff.push(GVMe::lbl_jump(loop1_start));
        self.buff.push(GVMe::lbl {
            idx: loop_exit1,
            name: format!(""),
        });

        /*
        while !power_of_two <= 0:
            if arg1 - arg2 >= 0 :
                arg1 -= arg2
                quotient += power_of_two

            arg2 = arg2 // 2
            power_of_two = power_of_two // 2
        */
        let loop2_start = self.next_label();
        let inner_if_fail = self.next_label();

        self.buff.push(GVMe::lbl {
            idx: loop2_start.clone(),
            name: format!(""),
        });
        self.buff.push(GVMe::LOAD(power_of_two));
        self.buff.push(GVMe::jnegz(loop2_end.clone()));

        self.buff.push(GVMe::LOAD(mod_res));
        self.buff.push(GVMe::SUB(arg2));
        self.buff.push(GVMe::jneg(inner_if_fail.clone()));
        self.buff.push(GVMe::LOAD(mod_res));
        self.buff.push(GVMe::SUB(arg2));
        self.buff.push(GVMe::STORE(mod_res));


        self.buff.push(GVMe::lbl {
            idx: inner_if_fail,
            name: format!(""),
        });

        self.buff.push(GVMe::LOAD(arg2));
        self.buff.push(GVMe::HALF);
        self.buff.push(GVMe::STORE(arg2));

        self.buff.push(GVMe::LOAD(power_of_two));
        self.buff.push(GVMe::HALF);
        self.buff.push(GVMe::STORE(power_of_two));

        self.buff.push(GVMe::lbl_jump(loop2_start));
        self.buff.push(GVMe::lbl {
            idx: loop2_end,
            name: format!(""),
        });

        // what if r == 0 ?????
        let fix_mod = self.next_label();
        self.buff.push(GVMe::LOAD(mod_res));
        self.buff.push(GVMe::jnz(fix_mod));
        self.buff.push(GVMe::STORE(mod_res_rtn));
        self.buff.push(GVMe::RTRN(proc_info.return_address));

        self.buff.push(GVMe::lbl {
            idx: fix_mod,
            name: "".to_owned(),
        });

        // arg1 positive
        let arg1_is_in_fact_negative = self.next_label();
        self.buff.push(GVMe::LOAD(arg1_positive));
        self.buff.push(GVMe::jneg(arg1_is_in_fact_negative));

        // arg1 pos, arg2 pos
        let arg1_pos_and_arg2_negative = self.next_label();
        self.buff.push(GVMe::LOAD(arg2_positive));
        self.buff.push(GVMe::jneg(arg1_pos_and_arg2_negative));
        // x>0 y>0 -> nothing
        self.buff.push(GVMe::LOAD(mod_res));
        self.buff.push(GVMe::STORE(mod_res_rtn));
        self.buff.push(GVMe::RTRN(proc_info.return_address));

        // arg1 pos, arg2 neg
        self.buff.push(GVMe::lbl {
            idx: arg1_pos_and_arg2_negative,
            name: format!(""),
        });

        // x>0 y<0 -> q = -1 - q and r = r - y
        self.const_in_acc(&m_one);
        self.buff.push(GVMe::LOAD(mod_res));
        self.buff.push(GVMe::SUB(arg2_cpy));
        self.buff.push(GVMe::STORE(mod_res_rtn));
        self.buff.push(GVMe::RTRN(proc_info.return_address));

        // arg1 negative
        self.buff.push(GVMe::lbl {
            idx: arg1_is_in_fact_negative,
            name: format!(""),
        });

        let arg1_neg_and_arg2_neg = self.next_label();
        self.buff.push(GVMe::LOAD(arg2_positive));
        self.buff.push(GVMe::jneg(arg1_neg_and_arg2_neg));
        // x<0 y>0 -> q = -1 - q and r = y - r
        self.buff.push(GVMe::LOAD(arg2_cpy));
        self.buff.push(GVMe::SUB(mod_res));
        self.buff.push(GVMe::STORE(mod_res_rtn));
        self.buff.push(GVMe::RTRN(proc_info.return_address));

        self.buff.push(GVMe::lbl {
            idx: arg1_neg_and_arg2_neg,
            name: format!(""),
        });
        // x<0 y<0 -> r = -r
        self.const_in_acc(&zero);
        self.buff.push(GVMe::SUB(mod_res));
        self.buff.push(GVMe::STORE(mod_res_rtn));

        self.buff.push(GVMe::RTRN(proc_info.return_address));
    }
}
