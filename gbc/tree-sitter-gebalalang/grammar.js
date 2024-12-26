/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "gbl",
  word: $ => $.word_token,
  extras: $ => [$._comment, /[\s\t\n]+/],
  rules: {
    program_all: $ => seq(
      field('procedures', repeat($.procedure)),
      field('main_program', $.main)
    ),

    procedure: $ => seq(
      'PROCEDURE',
      field('header', $.proc_head),
      'IS',
      optional(field('declarations', $.declarations)),
      'BEGIN',
      optional(field('commands', $.commands)),
      'END'
    ),

    main: $ => seq(
      'PROGRAM',
      'IS',
      optional(field('declarations', $.declarations)),
      'BEGIN',
      optional(field('commands', $.commands)),
      'END'
    ),

    word: $ => $.word_token,
    
    commands: $ => repeat1(field('command', $.command)),

    command: $ => choice(
      seq(
        field('target', $.identifier),
        ':=',
        field('expression', $.expression),
        ';'
      ),
      seq(
        'IF',
        field('condition', $.condition),
        'THEN',
        field('then_branch', $.commands),
        'ELSE',
        field('else_branch', $.commands),
        'ENDIF'
      ),
      seq(
        'IF',
        field('condition', $.condition),
        'THEN',
        field('then_branch', $.commands),
        'ENDIF'
      ),
      seq(
        'WHILE',
        field('condition', $.condition),
        'DO',
        field('body', $.commands),
        'ENDWHILE'
      ),
      seq(
        'REPEAT',
        field('body', $.commands),
        'UNTIL',
        field('condition', $.condition),
        ';'
      ),
      seq(
        'FOR',
        field('variable', $.pidentifier),
        'FROM',
        field('start', $.value),
        'TO',
        field('end', $.value),
        'DO',
        field('body', $.commands),
        'ENDFOR'
      ),
      seq(
        'FOR',
        field('variable', $.pidentifier),
        'FROM',
        field('start', $.value),
        'DOWNTO',
        field('end', $.value),
        'DO',
        field('body', $.commands),
        'ENDFOR'
      ),
      seq(field('procedure_call', $.proc_call), ';'),
      seq('READ', field('target', $.identifier), ';'),
      seq('WRITE', field('value', $.value), ';')
    ),

    proc_head: $ => seq(
      field('name', $.pidentifier),
      '(',
      optional(field('arguments', $.args_decl)),
      ')'
    ),

    proc_call: $ => seq(
      field('name', $.pidentifier),
      '(',
      optional(field('arguments', $.args)),
      ')'
    ),

    declarations: $ => seq(
      field('declaration', $.declaration),
      repeat(seq(',', field('declaration', $.declaration)))
    ),

    declaration: $ => choice(
      field('identifier', $.pidentifier),
      seq(
        field('identifier', $.pidentifier),
        '[',
        field('start', $.num),
        ':',
        field('end', $.num),
        ']'
      )
    ),

    args_decl: $ => seq(
      field('argument', choice($.pidentifier, seq('T', $.pidentifier))),
      repeat(seq(',', field('argument', choice($.pidentifier, seq('T', $.pidentifier)))))
    ),

    args: $ => seq(
      field('argument', $.pidentifier),
      repeat(seq(',', field('argument', $.pidentifier)))
    ),

    expression: $ => choice(
      field('value', $.value),
      seq(field('left', $.value), '+', field('right', $.value)),
      seq(field('left', $.value), '-', field('right', $.value)),
      seq(field('left', $.value), '*', field('right', $.value)),
      seq(field('left', $.value), '/', field('right', $.value)),
      seq(field('left', $.value), '%', field('right', $.value))
    ),

    condition: $ => choice(
      seq(field('left', $.value), '=', field('right', $.value)),
      seq(field('left', $.value), '!=', field('right', $.value)),
      seq(field('left', $.value), '>', field('right', $.value)),
      seq(field('left', $.value), '<', field('right', $.value)),
      seq(field('left', $.value), '>=', field('right', $.value)),
      seq(field('left', $.value), '<=', field('right', $.value))
    ),

    value: $ => choice(
      field('number', $.num),
      field('identifier', $.identifier)
    ),

    identifier: $ => choice(
      field('name', $.pidentifier),
      seq(field('name', $.pidentifier), '[', field('index', $.pidentifier), ']'),
      seq(field('name', $.pidentifier), '[', field('index', $.num), ']')
    ),

    _comment: $ => /#.*/,
    
    // Tokens and primitives
    word_token: $ => /[_A-Z]+/,
    pidentifier: $ => /[_a-z]+/,
    num: $ => /[-+]?\d+/
  },
});
