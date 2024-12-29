use crate::ast::{Ast, Command, Condition, Location, MainBlock, Value};

#[test]
fn it_works() {
    let mut ast = Ast::default();

    ast.is_valid = true;
    ast.main_block = MainBlock::default();

    ast.main_block.commands = vec![Command::While {
        condition: Condition::Equal(Value::Number(1), Value::Number(1)),
        commands: vec![Command::Write(Value::Number(3))],
        location: Location::default(),
    }];

    println!("{:#?}", ast.main_block);
}
