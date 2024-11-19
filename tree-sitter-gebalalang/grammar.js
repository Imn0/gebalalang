/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "gbl",

  rules: {
    program_all: $ => seq(repeat($.procedure), $.main),

    procedure: $ => seq('PROCEDURE', $.proc_head, 'IS', optional($.declarations), 'BEGIN', $.commands, 'END'),

    main: $ => seq('PROGRAM', 'IS', optional($.declarations) , 'BEGIN', optional($.commands), 'END'),

    commands: $ => repeat1($.command),

    command: $ => choice(
      seq($.identifier, ':=', $.expression, ';'),
      seq('IF', $.condition, 'THEN', $.commands, 'ELSE', $.commands, 'ENDIF'),
      seq('IF', $.condition, 'THEN', $.commands, 'ENDIF'),
      seq('WHILE', $.condition, 'DO', $.commands, 'ENDWHILE'),
      seq('REPEAT', $.commands, 'UNTIL', $.condition, ';'),
      seq('FOR', $.pidentifier, 'FROM', $.value, 'TO', $.value, 'DO', $.commands, 'ENDFOR'),
      seq('FOR', $.pidentifier, 'FROM', $.value, 'DOWNTO', $.value, 'DO', $.commands, 'ENDFOR'),
      seq($.proc_call, ';'),
      seq('READ', $.identifier, ';'),
      seq('WRITE', $.value, ';')
    ),

    proc_head: $ => seq($.pidentifier, '(', optional($.args_decl), ')'),

    proc_call: $ => seq($.pidentifier, '(', optional($.args), ')'),

    declarations: $ => seq(
      $.declaration,
      repeat(seq(',', $.declaration))
    ),

    declaration: $ => choice(
      $.pidentifier,
      seq($.pidentifier, '[', $.num, ':', $.num, ']')
    ),

    args_decl: $ => seq(
      choice($.pidentifier, seq('T', $.pidentifier)),
      repeat(seq(',', choice($.pidentifier, seq('T', $.pidentifier))))
    ),

    args: $ => seq(
      $.pidentifier,
      repeat(seq(',', $.pidentifier))
    ),

    expression: $ => choice(
      $.value,
      seq($.value, '+', $.value),
      seq($.value, '-', $.value),
      seq($.value, '*', $.value),
      seq($.value, '/', $.value),
      seq($.value, '%', $.value)
    ),

    condition: $ => choice(
      seq($.value, '=', $.value),
      seq($.value, '!=', $.value),
      seq($.value, '>', $.value),
      seq($.value, '<', $.value),
      seq($.value, '>=', $.value),
      seq($.value, '<=', $.value)
    ),

    value: $ => choice(
      $.num,
      $.identifier
    ),

    identifier: $ => choice(
      $.pidentifier,
      seq($.pidentifier, '[', $.pidentifier, ']'),
      seq($.pidentifier, '[', $.num, ']')
    ),

    comment: $ => /#.*/, 
    // Tokens and primitives
    pidentifier: $ => /[_a-z]+/,
    num: $ => /[-+]?\d+/

  },
  extras: $ => [$.comment, /[ \t\r\n]+/],
});