/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "gbl",
  word: $ => $.word_token,
  extras: $ => [$._comment, /[\s\t\n]+/],
  rules: {

    program_all: $ => seq(repeat($.procedure), $.main),

    procedure: $ => seq('PROCEDURE', $.proc_head, 'IS', optional($.declarations), 'BEGIN', optional($.commands), 'END'),

    main: $ => seq('PROGRAM', 'IS', optional($.declarations) , 'BEGIN', optional($.commands), 'END'),

    word: $ => $.word_token,
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

    _comment: $ => /#.*/, 
    // Tokens and primitives
    word_token: $ => /[_A-Z]+/,


    // evil 
    pidentifier: ($) => /[_a-z\u{1F300}-\u{1F6FF}\u{1F700}-\u{1F77F}\u{1F900}-\u{1F9FF}\u{1FA70}-\u{1FAFF}\u{2600}-\u{26FF}]+/u,

    // pidentifier: $ => /[_a-z]+/,
    num: $ => /[-+]?\d+/

  },

});