/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "gbl",
  word: ($) => $.word_token,
  extras: ($) => [$._comment, /[\s\t\n]+/],
  rules: {
    program_all: ($) =>
      seq(
        optional(field("procedures", $.procedures)),
        field("main_program", $.main)
      ),

    procedures: ($) => field("procedure", repeat1($.procedure)),

    procedure: ($) =>
      seq(
        "PROCEDURE",
        field("header", $.proc_head),
        "IS",
        optional(field("declarations", $.declarations)),
        "BEGIN",
        optional(field("commands", $.commands)),
        "END"
      ),

    main: ($) =>
      seq(
        "PROGRAM",
        "IS",
        optional(field("declarations", $.declarations)),
        "BEGIN",
        optional(field("commands", $.commands)),
        "END"
      ),

    word: ($) => $.word_token,

    commands: ($) => repeat1(field("command", $.command)),

    command: ($) =>
      choice(
        // Assignment command
        prec(
          1,
          seq(
            alias(
              seq(
                field("target", $.identifier),
                ":=",
                field("expression", $.expression),
                ";"
              ),
              "assignment_command"
            )
          )
        ),

        // If-Then-Else command
        prec(
          1,
          seq(
            alias(
              seq(
                "IF",
                field("condition", $.condition),
                "THEN",
                optional(field("then_branch", $.commands)),
                "ELSE",
                optional(field("else_branch", $.commands)),
                "ENDIF"
              ),
              "if_else_command"
            )
          )
        ),

        // If-Then command
        prec(
          1,
          seq(
            alias(
              seq(
                "IF",
                field("condition", $.condition),
                "THEN",
                optional(field("then_branch", $.commands)),
                "ENDIF"
              ),
              "if_command"
            )
          )
        ),

        // While command
        prec(
          1,
          seq(
            alias(
              seq(
                "WHILE",
                field("condition", $.condition),
                "DO",
                optional(field("body", $.commands)),
                "ENDWHILE"
              ),
              "while_command"
            )
          )
        ),

        // Repeat-Until command
        prec(
          1,
          seq(
            alias(
              seq(
                "REPEAT",
                optional(field("body", $.commands)),
                "UNTIL",
                field("condition", $.condition),
                ";"
              ),
              "repeat_until_command"
            )
          )
        ),

        // For-To command
        prec(
          1,
          seq(
            alias(
              seq(
                "FOR",
                field("variable", $.pidentifier),
                "FROM",
                field("start", $.value),
                "TO",
                field("end", $.value),
                "DO",
                optional(field("body", $.commands)),
                "ENDFOR"
              ),
              "for_to_command"
            )
          )
        ),

        // For-Downto command
        prec(
          1,
          seq(
            alias(
              seq(
                "FOR",
                field("variable", $.pidentifier),
                "FROM",
                field("start", $.value),
                "DOWNTO",
                field("end", $.value),
                "DO",
                optional(field("body", $.commands)),
                "ENDFOR"
              ),
              "for_downto_command"
            )
          )
        ),

        // Procedure call command
        prec(
          1,
          seq(
            alias(
              seq(field("procedure_call", $.proc_call), ";"),
              "procedure_call_command"
            )
          )
        ),

        // Read command
        prec(
          1,
          seq(
            alias(
              seq("READ", field("target", $.identifier), ";"),
              "read_command"
            )
          )
        ),

        // Write command
        prec(
          1,
          seq(
            alias(seq("WRITE", field("value", $.value), ";"), "write_command")
          )
        )
      ),

    proc_head: ($) =>
      seq(
        field("name", $.pidentifier),
        "(",
        optional(field("arguments", $.args_decl)),
        ")"
      ),

    proc_call: ($) =>
      seq(
        field("name", $.pidentifier),
        "(",
        optional(field("arguments", $.args)),
        ")"
      ),

    declarations: ($) =>
      seq(
        field("declaration", $.declaration),
        repeat(seq(",", field("declaration", $.declaration)))
      ),

    declaration: ($) =>
      choice(
        field("identifier", $.pidentifier),
        seq(
          field("identifier", $.pidentifier),
          "[",
          field("start", $.num),
          ":",
          field("end", $.num),
          "]"
        )
      ),

    args_decl: ($) =>
      seq(
        field("argument", $.arg_decl),
        repeat(seq(",", field("argument", $.arg_decl)))
      ),

    arg_decl: ($) =>
      choice(
        seq(field("name", $.pidentifier)),
        seq(field("T", "T"), field("name", $.pidentifier))
      ),

    args: ($) =>
      seq(
        field("argument", $.pidentifier),
        repeat(seq(",", field("argument", $.pidentifier)))
      ),

    expression: ($) =>
      choice(
        field("value", $.value),
        seq(field("left", $.value), field("op", "+"), field("right", $.value)),
        seq(field("left", $.value), field("op", "-"), field("right", $.value)),
        seq(field("left", $.value), field("op", "*"), field("right", $.value)),
        seq(field("left", $.value), field("op", "/"), field("right", $.value)),
        seq(field("left", $.value), field("op", "%"), field("right", $.value))
      ),

    condition: ($) =>
      choice(
        seq(field("left", $.value), field("op", "="), field("right", $.value)),
        seq(field("left", $.value), field("op", "!="), field("right", $.value)),
        seq(field("left", $.value), field("op", ">"), field("right", $.value)),
        seq(field("left", $.value), field("op", "<"), field("right", $.value)),
        seq(field("left", $.value), field("op", ">="), field("right", $.value)),
        seq(field("left", $.value), field("op", "<="), field("right", $.value))
      ),

    value: ($) =>
      choice(field("number", $.num), field("identifier", $.identifier)),

    identifier: ($) =>
      choice(
        field("name", $.pidentifier),
        seq(
          field("name", $.pidentifier),
          "[",
          field("index", $.pidentifier),
          "]"
        ),
        seq(field("name", $.pidentifier), "[", field("index", $.num), "]")
      ),

    _comment: ($) => /#.*/,

    // Tokens and primitives
    word_token: ($) => /[_A-Z]+/,
    pidentifier: ($) => /[_a-z]+/,
    num: ($) => /[-+]?\d+/,
  },
});
