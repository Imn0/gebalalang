#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 116
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 65
#define ALIAS_COUNT 0
#define TOKEN_COUNT 45
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 9
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  anon_sym_PROCEDURE = 1,
  anon_sym_IS = 2,
  anon_sym_BEGIN = 3,
  anon_sym_END = 4,
  anon_sym_PROGRAM = 5,
  anon_sym_COLON_EQ = 6,
  anon_sym_SEMI = 7,
  anon_sym_IF = 8,
  anon_sym_THEN = 9,
  anon_sym_ELSE = 10,
  anon_sym_ENDIF = 11,
  anon_sym_WHILE = 12,
  anon_sym_DO = 13,
  anon_sym_ENDWHILE = 14,
  anon_sym_REPEAT = 15,
  anon_sym_UNTIL = 16,
  anon_sym_FOR = 17,
  anon_sym_FROM = 18,
  anon_sym_TO = 19,
  anon_sym_ENDFOR = 20,
  anon_sym_DOWNTO = 21,
  anon_sym_READ = 22,
  anon_sym_WRITE = 23,
  anon_sym_LPAREN = 24,
  anon_sym_RPAREN = 25,
  anon_sym_COMMA = 26,
  anon_sym_LBRACK = 27,
  anon_sym_COLON = 28,
  anon_sym_RBRACK = 29,
  anon_sym_T = 30,
  anon_sym_PLUS = 31,
  anon_sym_DASH = 32,
  anon_sym_STAR = 33,
  anon_sym_SLASH = 34,
  anon_sym_PERCENT = 35,
  anon_sym_EQ = 36,
  anon_sym_BANG_EQ = 37,
  anon_sym_GT = 38,
  anon_sym_LT = 39,
  anon_sym_GT_EQ = 40,
  anon_sym_LT_EQ = 41,
  sym_comment = 42,
  sym_pidentifier = 43,
  sym_num = 44,
  sym_program_all = 45,
  sym_procedure = 46,
  sym_main = 47,
  sym_commands = 48,
  sym_command = 49,
  sym_proc_head = 50,
  sym_proc_call = 51,
  sym_declarations = 52,
  sym_declaration = 53,
  sym_args_decl = 54,
  sym_args = 55,
  sym_expression = 56,
  sym_condition = 57,
  sym_value = 58,
  sym_identifier = 59,
  aux_sym_program_all_repeat1 = 60,
  aux_sym_commands_repeat1 = 61,
  aux_sym_declarations_repeat1 = 62,
  aux_sym_args_decl_repeat1 = 63,
  aux_sym_args_repeat1 = 64,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_PROCEDURE] = "PROCEDURE",
  [anon_sym_IS] = "IS",
  [anon_sym_BEGIN] = "BEGIN",
  [anon_sym_END] = "END",
  [anon_sym_PROGRAM] = "PROGRAM",
  [anon_sym_COLON_EQ] = ":=",
  [anon_sym_SEMI] = ";",
  [anon_sym_IF] = "IF",
  [anon_sym_THEN] = "THEN",
  [anon_sym_ELSE] = "ELSE",
  [anon_sym_ENDIF] = "ENDIF",
  [anon_sym_WHILE] = "WHILE",
  [anon_sym_DO] = "DO",
  [anon_sym_ENDWHILE] = "ENDWHILE",
  [anon_sym_REPEAT] = "REPEAT",
  [anon_sym_UNTIL] = "UNTIL",
  [anon_sym_FOR] = "FOR",
  [anon_sym_FROM] = "FROM",
  [anon_sym_TO] = "TO",
  [anon_sym_ENDFOR] = "ENDFOR",
  [anon_sym_DOWNTO] = "DOWNTO",
  [anon_sym_READ] = "READ",
  [anon_sym_WRITE] = "WRITE",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_COMMA] = ",",
  [anon_sym_LBRACK] = "[",
  [anon_sym_COLON] = ":",
  [anon_sym_RBRACK] = "]",
  [anon_sym_T] = "T",
  [anon_sym_PLUS] = "+",
  [anon_sym_DASH] = "-",
  [anon_sym_STAR] = "*",
  [anon_sym_SLASH] = "/",
  [anon_sym_PERCENT] = "%",
  [anon_sym_EQ] = "=",
  [anon_sym_BANG_EQ] = "!=",
  [anon_sym_GT] = ">",
  [anon_sym_LT] = "<",
  [anon_sym_GT_EQ] = ">=",
  [anon_sym_LT_EQ] = "<=",
  [sym_comment] = "comment",
  [sym_pidentifier] = "pidentifier",
  [sym_num] = "num",
  [sym_program_all] = "program_all",
  [sym_procedure] = "procedure",
  [sym_main] = "main",
  [sym_commands] = "commands",
  [sym_command] = "command",
  [sym_proc_head] = "proc_head",
  [sym_proc_call] = "proc_call",
  [sym_declarations] = "declarations",
  [sym_declaration] = "declaration",
  [sym_args_decl] = "args_decl",
  [sym_args] = "args",
  [sym_expression] = "expression",
  [sym_condition] = "condition",
  [sym_value] = "value",
  [sym_identifier] = "identifier",
  [aux_sym_program_all_repeat1] = "program_all_repeat1",
  [aux_sym_commands_repeat1] = "commands_repeat1",
  [aux_sym_declarations_repeat1] = "declarations_repeat1",
  [aux_sym_args_decl_repeat1] = "args_decl_repeat1",
  [aux_sym_args_repeat1] = "args_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_PROCEDURE] = anon_sym_PROCEDURE,
  [anon_sym_IS] = anon_sym_IS,
  [anon_sym_BEGIN] = anon_sym_BEGIN,
  [anon_sym_END] = anon_sym_END,
  [anon_sym_PROGRAM] = anon_sym_PROGRAM,
  [anon_sym_COLON_EQ] = anon_sym_COLON_EQ,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_IF] = anon_sym_IF,
  [anon_sym_THEN] = anon_sym_THEN,
  [anon_sym_ELSE] = anon_sym_ELSE,
  [anon_sym_ENDIF] = anon_sym_ENDIF,
  [anon_sym_WHILE] = anon_sym_WHILE,
  [anon_sym_DO] = anon_sym_DO,
  [anon_sym_ENDWHILE] = anon_sym_ENDWHILE,
  [anon_sym_REPEAT] = anon_sym_REPEAT,
  [anon_sym_UNTIL] = anon_sym_UNTIL,
  [anon_sym_FOR] = anon_sym_FOR,
  [anon_sym_FROM] = anon_sym_FROM,
  [anon_sym_TO] = anon_sym_TO,
  [anon_sym_ENDFOR] = anon_sym_ENDFOR,
  [anon_sym_DOWNTO] = anon_sym_DOWNTO,
  [anon_sym_READ] = anon_sym_READ,
  [anon_sym_WRITE] = anon_sym_WRITE,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [anon_sym_T] = anon_sym_T,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [anon_sym_PERCENT] = anon_sym_PERCENT,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_BANG_EQ] = anon_sym_BANG_EQ,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_GT_EQ] = anon_sym_GT_EQ,
  [anon_sym_LT_EQ] = anon_sym_LT_EQ,
  [sym_comment] = sym_comment,
  [sym_pidentifier] = sym_pidentifier,
  [sym_num] = sym_num,
  [sym_program_all] = sym_program_all,
  [sym_procedure] = sym_procedure,
  [sym_main] = sym_main,
  [sym_commands] = sym_commands,
  [sym_command] = sym_command,
  [sym_proc_head] = sym_proc_head,
  [sym_proc_call] = sym_proc_call,
  [sym_declarations] = sym_declarations,
  [sym_declaration] = sym_declaration,
  [sym_args_decl] = sym_args_decl,
  [sym_args] = sym_args,
  [sym_expression] = sym_expression,
  [sym_condition] = sym_condition,
  [sym_value] = sym_value,
  [sym_identifier] = sym_identifier,
  [aux_sym_program_all_repeat1] = aux_sym_program_all_repeat1,
  [aux_sym_commands_repeat1] = aux_sym_commands_repeat1,
  [aux_sym_declarations_repeat1] = aux_sym_declarations_repeat1,
  [aux_sym_args_decl_repeat1] = aux_sym_args_decl_repeat1,
  [aux_sym_args_repeat1] = aux_sym_args_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_PROCEDURE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_IS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BEGIN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_END] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PROGRAM] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_IF] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_THEN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ELSE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ENDIF] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_WHILE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DO] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ENDWHILE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_REPEAT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_UNTIL] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_FOR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_FROM] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_TO] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ENDFOR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOWNTO] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_READ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_WRITE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_T] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PERCENT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_EQ] = {
    .visible = true,
    .named = false,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_pidentifier] = {
    .visible = true,
    .named = true,
  },
  [sym_num] = {
    .visible = true,
    .named = true,
  },
  [sym_program_all] = {
    .visible = true,
    .named = true,
  },
  [sym_procedure] = {
    .visible = true,
    .named = true,
  },
  [sym_main] = {
    .visible = true,
    .named = true,
  },
  [sym_commands] = {
    .visible = true,
    .named = true,
  },
  [sym_command] = {
    .visible = true,
    .named = true,
  },
  [sym_proc_head] = {
    .visible = true,
    .named = true,
  },
  [sym_proc_call] = {
    .visible = true,
    .named = true,
  },
  [sym_declarations] = {
    .visible = true,
    .named = true,
  },
  [sym_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_args_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_args] = {
    .visible = true,
    .named = true,
  },
  [sym_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_condition] = {
    .visible = true,
    .named = true,
  },
  [sym_value] = {
    .visible = true,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_program_all_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_commands_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_declarations_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_args_decl_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_args_repeat1] = {
    .visible = false,
    .named = false,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 4,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 5,
  [59] = 6,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 56,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
  [83] = 83,
  [84] = 84,
  [85] = 85,
  [86] = 86,
  [87] = 87,
  [88] = 88,
  [89] = 89,
  [90] = 90,
  [91] = 91,
  [92] = 92,
  [93] = 93,
  [94] = 94,
  [95] = 95,
  [96] = 96,
  [97] = 97,
  [98] = 98,
  [99] = 99,
  [100] = 100,
  [101] = 101,
  [102] = 102,
  [103] = 103,
  [104] = 104,
  [105] = 105,
  [106] = 106,
  [107] = 107,
  [108] = 108,
  [109] = 109,
  [110] = 110,
  [111] = 111,
  [112] = 112,
  [113] = 113,
  [114] = 81,
  [115] = 115,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(72);
      ADVANCE_MAP(
        '!', 4,
        '#', 117,
        '%', 110,
        '(', 97,
        ')', 98,
        '*', 108,
        '+', 106,
        ',', 99,
        '-', 107,
        '/', 109,
        ':', 102,
        ';', 80,
        '<', 114,
        '=', 111,
        '>', 113,
        'B', 15,
        'D', 50,
        'E', 38,
        'F', 57,
        'I', 26,
        'P', 62,
        'R', 16,
        'T', 105,
        'U', 45,
        'W', 30,
        '[', 100,
        ']', 103,
      );
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(118);
      END_STATE();
    case 1:
      ADVANCE_MAP(
        '!', 4,
        '#', 117,
        '%', 110,
        '(', 97,
        '*', 108,
        '+', 106,
        '-', 107,
        '/', 109,
        ':', 5,
        ';', 80,
        '<', 114,
        '=', 111,
        '>', 113,
        'D', 50,
        'E', 48,
        'F', 56,
        'I', 25,
        'R', 16,
        'T', 31,
        'W', 30,
        '[', 100,
      );
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(1);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(118);
      END_STATE();
    case 2:
      if (lookahead == '#') ADVANCE(117);
      if (lookahead == ')') ADVANCE(98);
      if (lookahead == ':') ADVANCE(101);
      if (lookahead == 'E') ADVANCE(39);
      if (lookahead == 'T') ADVANCE(104);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(71);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(119);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(118);
      END_STATE();
    case 3:
      if (lookahead == '#') ADVANCE(117);
      if (lookahead == 'D') ADVANCE(54);
      if (lookahead == 'T') ADVANCE(51);
      if (lookahead == '[') ADVANCE(100);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(3);
      END_STATE();
    case 4:
      if (lookahead == '=') ADVANCE(112);
      END_STATE();
    case 5:
      if (lookahead == '=') ADVANCE(79);
      END_STATE();
    case 6:
      if (lookahead == 'A') ADVANCE(11);
      if (lookahead == 'P') ADVANCE(18);
      END_STATE();
    case 7:
      if (lookahead == 'A') ADVANCE(44);
      END_STATE();
    case 8:
      if (lookahead == 'A') ADVANCE(65);
      END_STATE();
    case 9:
      if (lookahead == 'C') ADVANCE(24);
      if (lookahead == 'G') ADVANCE(61);
      END_STATE();
    case 10:
      if (lookahead == 'D') ADVANCE(77);
      END_STATE();
    case 11:
      if (lookahead == 'D') ADVANCE(95);
      END_STATE();
    case 12:
      if (lookahead == 'D') ADVANCE(69);
      END_STATE();
    case 13:
      if (lookahead == 'D') ADVANCE(76);
      END_STATE();
    case 14:
      if (lookahead == 'D') ADVANCE(28);
      END_STATE();
    case 15:
      if (lookahead == 'E') ADVANCE(29);
      END_STATE();
    case 16:
      if (lookahead == 'E') ADVANCE(6);
      END_STATE();
    case 17:
      if (lookahead == 'E') ADVANCE(83);
      END_STATE();
    case 18:
      if (lookahead == 'E') ADVANCE(8);
      END_STATE();
    case 19:
      if (lookahead == 'E') ADVANCE(85);
      END_STATE();
    case 20:
      if (lookahead == 'E') ADVANCE(96);
      END_STATE();
    case 21:
      if (lookahead == 'E') ADVANCE(87);
      END_STATE();
    case 22:
      if (lookahead == 'E') ADVANCE(73);
      END_STATE();
    case 23:
      if (lookahead == 'E') ADVANCE(46);
      END_STATE();
    case 24:
      if (lookahead == 'E') ADVANCE(12);
      END_STATE();
    case 25:
      if (lookahead == 'F') ADVANCE(81);
      END_STATE();
    case 26:
      if (lookahead == 'F') ADVANCE(81);
      if (lookahead == 'S') ADVANCE(74);
      END_STATE();
    case 27:
      if (lookahead == 'F') ADVANCE(84);
      END_STATE();
    case 28:
      if (lookahead == 'F') ADVANCE(58);
      if (lookahead == 'I') ADVANCE(27);
      if (lookahead == 'W') ADVANCE(32);
      END_STATE();
    case 29:
      if (lookahead == 'G') ADVANCE(36);
      END_STATE();
    case 30:
      if (lookahead == 'H') ADVANCE(33);
      if (lookahead == 'R') ADVANCE(34);
      END_STATE();
    case 31:
      if (lookahead == 'H') ADVANCE(23);
      END_STATE();
    case 32:
      if (lookahead == 'H') ADVANCE(37);
      END_STATE();
    case 33:
      if (lookahead == 'I') ADVANCE(41);
      END_STATE();
    case 34:
      if (lookahead == 'I') ADVANCE(66);
      END_STATE();
    case 35:
      if (lookahead == 'I') ADVANCE(40);
      END_STATE();
    case 36:
      if (lookahead == 'I') ADVANCE(47);
      END_STATE();
    case 37:
      if (lookahead == 'I') ADVANCE(42);
      END_STATE();
    case 38:
      if (lookahead == 'L') ADVANCE(64);
      if (lookahead == 'N') ADVANCE(10);
      END_STATE();
    case 39:
      if (lookahead == 'L') ADVANCE(64);
      if (lookahead == 'N') ADVANCE(14);
      END_STATE();
    case 40:
      if (lookahead == 'L') ADVANCE(89);
      END_STATE();
    case 41:
      if (lookahead == 'L') ADVANCE(19);
      END_STATE();
    case 42:
      if (lookahead == 'L') ADVANCE(21);
      END_STATE();
    case 43:
      if (lookahead == 'M') ADVANCE(91);
      END_STATE();
    case 44:
      if (lookahead == 'M') ADVANCE(78);
      END_STATE();
    case 45:
      if (lookahead == 'N') ADVANCE(68);
      END_STATE();
    case 46:
      if (lookahead == 'N') ADVANCE(82);
      END_STATE();
    case 47:
      if (lookahead == 'N') ADVANCE(75);
      END_STATE();
    case 48:
      if (lookahead == 'N') ADVANCE(13);
      END_STATE();
    case 49:
      if (lookahead == 'N') ADVANCE(67);
      END_STATE();
    case 50:
      if (lookahead == 'O') ADVANCE(86);
      END_STATE();
    case 51:
      if (lookahead == 'O') ADVANCE(92);
      END_STATE();
    case 52:
      if (lookahead == 'O') ADVANCE(43);
      END_STATE();
    case 53:
      if (lookahead == 'O') ADVANCE(9);
      END_STATE();
    case 54:
      if (lookahead == 'O') ADVANCE(70);
      END_STATE();
    case 55:
      if (lookahead == 'O') ADVANCE(94);
      END_STATE();
    case 56:
      if (lookahead == 'O') ADVANCE(59);
      END_STATE();
    case 57:
      if (lookahead == 'O') ADVANCE(59);
      if (lookahead == 'R') ADVANCE(52);
      END_STATE();
    case 58:
      if (lookahead == 'O') ADVANCE(60);
      END_STATE();
    case 59:
      if (lookahead == 'R') ADVANCE(90);
      END_STATE();
    case 60:
      if (lookahead == 'R') ADVANCE(93);
      END_STATE();
    case 61:
      if (lookahead == 'R') ADVANCE(7);
      END_STATE();
    case 62:
      if (lookahead == 'R') ADVANCE(53);
      END_STATE();
    case 63:
      if (lookahead == 'R') ADVANCE(22);
      END_STATE();
    case 64:
      if (lookahead == 'S') ADVANCE(17);
      END_STATE();
    case 65:
      if (lookahead == 'T') ADVANCE(88);
      END_STATE();
    case 66:
      if (lookahead == 'T') ADVANCE(20);
      END_STATE();
    case 67:
      if (lookahead == 'T') ADVANCE(55);
      END_STATE();
    case 68:
      if (lookahead == 'T') ADVANCE(35);
      END_STATE();
    case 69:
      if (lookahead == 'U') ADVANCE(63);
      END_STATE();
    case 70:
      if (lookahead == 'W') ADVANCE(49);
      END_STATE();
    case 71:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(119);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_PROCEDURE);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_IS);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_BEGIN);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_END);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_END);
      if (lookahead == 'F') ADVANCE(58);
      if (lookahead == 'I') ADVANCE(27);
      if (lookahead == 'W') ADVANCE(32);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_PROGRAM);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_COLON_EQ);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_IF);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_THEN);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_ELSE);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_ENDIF);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(anon_sym_WHILE);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(anon_sym_DO);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(anon_sym_ENDWHILE);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(anon_sym_REPEAT);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(anon_sym_UNTIL);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(anon_sym_FOR);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(anon_sym_FROM);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(anon_sym_TO);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(anon_sym_ENDFOR);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(anon_sym_DOWNTO);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(anon_sym_READ);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_WRITE);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(anon_sym_COLON);
      if (lookahead == '=') ADVANCE(79);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(anon_sym_T);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(anon_sym_T);
      if (lookahead == 'H') ADVANCE(23);
      if (lookahead == 'O') ADVANCE(92);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(anon_sym_PERCENT);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(115);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(116);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(117);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(sym_pidentifier);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(118);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(sym_num);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(119);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 1},
  [5] = {.lex_state = 1},
  [6] = {.lex_state = 1},
  [7] = {.lex_state = 1},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 1},
  [14] = {.lex_state = 0},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 0},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 0},
  [24] = {.lex_state = 2},
  [25] = {.lex_state = 2},
  [26] = {.lex_state = 0},
  [27] = {.lex_state = 2},
  [28] = {.lex_state = 2},
  [29] = {.lex_state = 2},
  [30] = {.lex_state = 2},
  [31] = {.lex_state = 2},
  [32] = {.lex_state = 0},
  [33] = {.lex_state = 0},
  [34] = {.lex_state = 2},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 2},
  [37] = {.lex_state = 2},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 1},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 1},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 3},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 2},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 3},
  [59] = {.lex_state = 3},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 3},
  [64] = {.lex_state = 2},
  [65] = {.lex_state = 2},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 2},
  [71] = {.lex_state = 1},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 1},
  [74] = {.lex_state = 1},
  [75] = {.lex_state = 0},
  [76] = {.lex_state = 2},
  [77] = {.lex_state = 1},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 0},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 1},
  [84] = {.lex_state = 2},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 2},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 0},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 0},
  [102] = {.lex_state = 0},
  [103] = {.lex_state = 0},
  [104] = {.lex_state = 1},
  [105] = {.lex_state = 2},
  [106] = {.lex_state = 0},
  [107] = {.lex_state = 0},
  [108] = {.lex_state = 0},
  [109] = {.lex_state = 2},
  [110] = {.lex_state = 0},
  [111] = {.lex_state = 0},
  [112] = {.lex_state = 2},
  [113] = {.lex_state = 0},
  [114] = {.lex_state = 0},
  [115] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_PROCEDURE] = ACTIONS(1),
    [anon_sym_IS] = ACTIONS(1),
    [anon_sym_BEGIN] = ACTIONS(1),
    [anon_sym_END] = ACTIONS(1),
    [anon_sym_PROGRAM] = ACTIONS(1),
    [anon_sym_COLON_EQ] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_IF] = ACTIONS(1),
    [anon_sym_THEN] = ACTIONS(1),
    [anon_sym_ELSE] = ACTIONS(1),
    [anon_sym_ENDIF] = ACTIONS(1),
    [anon_sym_WHILE] = ACTIONS(1),
    [anon_sym_DO] = ACTIONS(1),
    [anon_sym_ENDWHILE] = ACTIONS(1),
    [anon_sym_REPEAT] = ACTIONS(1),
    [anon_sym_UNTIL] = ACTIONS(1),
    [anon_sym_FOR] = ACTIONS(1),
    [anon_sym_FROM] = ACTIONS(1),
    [anon_sym_TO] = ACTIONS(1),
    [anon_sym_ENDFOR] = ACTIONS(1),
    [anon_sym_READ] = ACTIONS(1),
    [anon_sym_WRITE] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [anon_sym_T] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_PERCENT] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_BANG_EQ] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_GT_EQ] = ACTIONS(1),
    [anon_sym_LT_EQ] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
    [sym_pidentifier] = ACTIONS(1),
  },
  [1] = {
    [sym_program_all] = STATE(110),
    [sym_procedure] = STATE(26),
    [sym_main] = STATE(108),
    [aux_sym_program_all_repeat1] = STATE(26),
    [anon_sym_PROCEDURE] = ACTIONS(5),
    [anon_sym_PROGRAM] = ACTIONS(7),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 13,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(9), 1,
      anon_sym_END,
    ACTIONS(11), 1,
      anon_sym_IF,
    ACTIONS(15), 1,
      anon_sym_WHILE,
    ACTIONS(17), 1,
      anon_sym_REPEAT,
    ACTIONS(19), 1,
      anon_sym_FOR,
    ACTIONS(21), 1,
      anon_sym_READ,
    ACTIONS(23), 1,
      anon_sym_WRITE,
    ACTIONS(25), 1,
      sym_pidentifier,
    STATE(77), 1,
      sym_identifier,
    STATE(79), 1,
      sym_proc_call,
    STATE(3), 2,
      sym_command,
      aux_sym_commands_repeat1,
    ACTIONS(13), 5,
      anon_sym_ELSE,
      anon_sym_ENDIF,
      anon_sym_ENDWHILE,
      anon_sym_UNTIL,
      anon_sym_ENDFOR,
  [45] = 13,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(27), 1,
      anon_sym_END,
    ACTIONS(29), 1,
      anon_sym_IF,
    ACTIONS(34), 1,
      anon_sym_WHILE,
    ACTIONS(37), 1,
      anon_sym_REPEAT,
    ACTIONS(40), 1,
      anon_sym_FOR,
    ACTIONS(43), 1,
      anon_sym_READ,
    ACTIONS(46), 1,
      anon_sym_WRITE,
    ACTIONS(49), 1,
      sym_pidentifier,
    STATE(77), 1,
      sym_identifier,
    STATE(79), 1,
      sym_proc_call,
    STATE(3), 2,
      sym_command,
      aux_sym_commands_repeat1,
    ACTIONS(32), 5,
      anon_sym_ELSE,
      anon_sym_ENDIF,
      anon_sym_ENDWHILE,
      anon_sym_UNTIL,
      anon_sym_ENDFOR,
  [90] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(54), 1,
      anon_sym_LBRACK,
    ACTIONS(56), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(52), 12,
      anon_sym_SEMI,
      anon_sym_THEN,
      anon_sym_DO,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
  [115] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(60), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(58), 13,
      anon_sym_COLON_EQ,
      anon_sym_SEMI,
      anon_sym_THEN,
      anon_sym_DO,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
  [138] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(64), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(62), 12,
      anon_sym_SEMI,
      anon_sym_THEN,
      anon_sym_DO,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
  [160] = 13,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_IF,
    ACTIONS(15), 1,
      anon_sym_WHILE,
    ACTIONS(17), 1,
      anon_sym_REPEAT,
    ACTIONS(19), 1,
      anon_sym_FOR,
    ACTIONS(21), 1,
      anon_sym_READ,
    ACTIONS(23), 1,
      anon_sym_WRITE,
    ACTIONS(25), 1,
      sym_pidentifier,
    ACTIONS(66), 1,
      anon_sym_END,
    STATE(77), 1,
      sym_identifier,
    STATE(79), 1,
      sym_proc_call,
    STATE(83), 1,
      sym_commands,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [201] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(68), 1,
      anon_sym_END,
    ACTIONS(70), 12,
      anon_sym_IF,
      anon_sym_ELSE,
      anon_sym_ENDIF,
      anon_sym_WHILE,
      anon_sym_ENDWHILE,
      anon_sym_REPEAT,
      anon_sym_UNTIL,
      anon_sym_FOR,
      anon_sym_ENDFOR,
      anon_sym_READ,
      anon_sym_WRITE,
      sym_pidentifier,
  [222] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(72), 1,
      anon_sym_END,
    ACTIONS(74), 12,
      anon_sym_IF,
      anon_sym_ELSE,
      anon_sym_ENDIF,
      anon_sym_WHILE,
      anon_sym_ENDWHILE,
      anon_sym_REPEAT,
      anon_sym_UNTIL,
      anon_sym_FOR,
      anon_sym_ENDFOR,
      anon_sym_READ,
      anon_sym_WRITE,
      sym_pidentifier,
  [243] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(76), 1,
      anon_sym_END,
    ACTIONS(78), 12,
      anon_sym_IF,
      anon_sym_ELSE,
      anon_sym_ENDIF,
      anon_sym_WHILE,
      anon_sym_ENDWHILE,
      anon_sym_REPEAT,
      anon_sym_UNTIL,
      anon_sym_FOR,
      anon_sym_ENDFOR,
      anon_sym_READ,
      anon_sym_WRITE,
      sym_pidentifier,
  [264] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(80), 1,
      anon_sym_END,
    ACTIONS(82), 12,
      anon_sym_IF,
      anon_sym_ELSE,
      anon_sym_ENDIF,
      anon_sym_WHILE,
      anon_sym_ENDWHILE,
      anon_sym_REPEAT,
      anon_sym_UNTIL,
      anon_sym_FOR,
      anon_sym_ENDFOR,
      anon_sym_READ,
      anon_sym_WRITE,
      sym_pidentifier,
  [285] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(84), 1,
      anon_sym_END,
    ACTIONS(86), 12,
      anon_sym_IF,
      anon_sym_ELSE,
      anon_sym_ENDIF,
      anon_sym_WHILE,
      anon_sym_ENDWHILE,
      anon_sym_REPEAT,
      anon_sym_UNTIL,
      anon_sym_FOR,
      anon_sym_ENDFOR,
      anon_sym_READ,
      anon_sym_WRITE,
      sym_pidentifier,
  [306] = 13,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_IF,
    ACTIONS(15), 1,
      anon_sym_WHILE,
    ACTIONS(17), 1,
      anon_sym_REPEAT,
    ACTIONS(19), 1,
      anon_sym_FOR,
    ACTIONS(21), 1,
      anon_sym_READ,
    ACTIONS(23), 1,
      anon_sym_WRITE,
    ACTIONS(25), 1,
      sym_pidentifier,
    ACTIONS(88), 1,
      anon_sym_END,
    STATE(77), 1,
      sym_identifier,
    STATE(79), 1,
      sym_proc_call,
    STATE(104), 1,
      sym_commands,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [347] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(90), 1,
      anon_sym_END,
    ACTIONS(92), 12,
      anon_sym_IF,
      anon_sym_ELSE,
      anon_sym_ENDIF,
      anon_sym_WHILE,
      anon_sym_ENDWHILE,
      anon_sym_REPEAT,
      anon_sym_UNTIL,
      anon_sym_FOR,
      anon_sym_ENDFOR,
      anon_sym_READ,
      anon_sym_WRITE,
      sym_pidentifier,
  [368] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_IF,
    ACTIONS(15), 1,
      anon_sym_WHILE,
    ACTIONS(17), 1,
      anon_sym_REPEAT,
    ACTIONS(19), 1,
      anon_sym_FOR,
    ACTIONS(21), 1,
      anon_sym_READ,
    ACTIONS(23), 1,
      anon_sym_WRITE,
    ACTIONS(25), 1,
      sym_pidentifier,
    STATE(64), 1,
      sym_commands,
    STATE(77), 1,
      sym_identifier,
    STATE(79), 1,
      sym_proc_call,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [406] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_IF,
    ACTIONS(15), 1,
      anon_sym_WHILE,
    ACTIONS(17), 1,
      anon_sym_REPEAT,
    ACTIONS(19), 1,
      anon_sym_FOR,
    ACTIONS(21), 1,
      anon_sym_READ,
    ACTIONS(23), 1,
      anon_sym_WRITE,
    ACTIONS(25), 1,
      sym_pidentifier,
    STATE(77), 1,
      sym_identifier,
    STATE(79), 1,
      sym_proc_call,
    STATE(105), 1,
      sym_commands,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [444] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_IF,
    ACTIONS(15), 1,
      anon_sym_WHILE,
    ACTIONS(17), 1,
      anon_sym_REPEAT,
    ACTIONS(19), 1,
      anon_sym_FOR,
    ACTIONS(21), 1,
      anon_sym_READ,
    ACTIONS(23), 1,
      anon_sym_WRITE,
    ACTIONS(25), 1,
      sym_pidentifier,
    STATE(77), 1,
      sym_identifier,
    STATE(79), 1,
      sym_proc_call,
    STATE(88), 1,
      sym_commands,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [482] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_IF,
    ACTIONS(15), 1,
      anon_sym_WHILE,
    ACTIONS(17), 1,
      anon_sym_REPEAT,
    ACTIONS(19), 1,
      anon_sym_FOR,
    ACTIONS(21), 1,
      anon_sym_READ,
    ACTIONS(23), 1,
      anon_sym_WRITE,
    ACTIONS(25), 1,
      sym_pidentifier,
    STATE(74), 1,
      sym_commands,
    STATE(77), 1,
      sym_identifier,
    STATE(79), 1,
      sym_proc_call,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [520] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_IF,
    ACTIONS(15), 1,
      anon_sym_WHILE,
    ACTIONS(17), 1,
      anon_sym_REPEAT,
    ACTIONS(19), 1,
      anon_sym_FOR,
    ACTIONS(21), 1,
      anon_sym_READ,
    ACTIONS(23), 1,
      anon_sym_WRITE,
    ACTIONS(25), 1,
      sym_pidentifier,
    STATE(77), 1,
      sym_identifier,
    STATE(79), 1,
      sym_proc_call,
    STATE(109), 1,
      sym_commands,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [558] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_IF,
    ACTIONS(15), 1,
      anon_sym_WHILE,
    ACTIONS(17), 1,
      anon_sym_REPEAT,
    ACTIONS(19), 1,
      anon_sym_FOR,
    ACTIONS(21), 1,
      anon_sym_READ,
    ACTIONS(23), 1,
      anon_sym_WRITE,
    ACTIONS(25), 1,
      sym_pidentifier,
    STATE(71), 1,
      sym_commands,
    STATE(77), 1,
      sym_identifier,
    STATE(79), 1,
      sym_proc_call,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [596] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_IF,
    ACTIONS(15), 1,
      anon_sym_WHILE,
    ACTIONS(17), 1,
      anon_sym_REPEAT,
    ACTIONS(19), 1,
      anon_sym_FOR,
    ACTIONS(21), 1,
      anon_sym_READ,
    ACTIONS(23), 1,
      anon_sym_WRITE,
    ACTIONS(25), 1,
      sym_pidentifier,
    STATE(77), 1,
      sym_identifier,
    STATE(79), 1,
      sym_proc_call,
    STATE(101), 1,
      sym_commands,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [634] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(96), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(94), 4,
      anon_sym_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
  [648] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(98), 1,
      anon_sym_SEMI,
    ACTIONS(100), 5,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [662] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      sym_pidentifier,
    ACTIONS(104), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(22), 1,
      sym_value,
    STATE(89), 1,
      sym_condition,
  [681] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      sym_pidentifier,
    ACTIONS(104), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(23), 1,
      sym_value,
    STATE(82), 1,
      sym_expression,
  [700] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(5), 1,
      anon_sym_PROCEDURE,
    ACTIONS(7), 1,
      anon_sym_PROGRAM,
    STATE(100), 1,
      sym_main,
    STATE(33), 2,
      sym_procedure,
      aux_sym_program_all_repeat1,
  [717] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      sym_pidentifier,
    ACTIONS(104), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(22), 1,
      sym_value,
    STATE(73), 1,
      sym_condition,
  [736] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      sym_pidentifier,
    ACTIONS(104), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(22), 1,
      sym_value,
    STATE(90), 1,
      sym_condition,
  [755] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(106), 1,
      anon_sym_RPAREN,
    ACTIONS(108), 1,
      anon_sym_T,
    ACTIONS(110), 1,
      sym_pidentifier,
    STATE(95), 1,
      sym_args_decl,
  [771] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      sym_pidentifier,
    ACTIONS(104), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(103), 1,
      sym_value,
  [787] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      sym_pidentifier,
    ACTIONS(104), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(106), 1,
      sym_value,
  [803] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 1,
      anon_sym_BEGIN,
    ACTIONS(114), 1,
      sym_pidentifier,
    STATE(43), 1,
      sym_declaration,
    STATE(99), 1,
      sym_declarations,
  [819] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(116), 1,
      anon_sym_PROCEDURE,
    ACTIONS(119), 1,
      anon_sym_PROGRAM,
    STATE(33), 2,
      sym_procedure,
      aux_sym_program_all_repeat1,
  [833] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(121), 1,
      sym_pidentifier,
    ACTIONS(123), 1,
      sym_num,
    STATE(59), 1,
      sym_identifier,
    STATE(63), 1,
      sym_value,
  [849] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(114), 1,
      sym_pidentifier,
    ACTIONS(125), 1,
      anon_sym_BEGIN,
    STATE(43), 1,
      sym_declaration,
    STATE(72), 1,
      sym_declarations,
  [865] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      sym_pidentifier,
    ACTIONS(104), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(115), 1,
      sym_value,
  [881] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      sym_pidentifier,
    ACTIONS(104), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(49), 1,
      sym_value,
  [897] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(127), 1,
      anon_sym_RPAREN,
    ACTIONS(129), 1,
      anon_sym_COMMA,
    STATE(44), 1,
      aux_sym_args_decl_repeat1,
  [910] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(129), 1,
      anon_sym_COMMA,
    ACTIONS(131), 1,
      anon_sym_RPAREN,
    STATE(38), 1,
      aux_sym_args_decl_repeat1,
  [923] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(133), 1,
      anon_sym_BEGIN,
    ACTIONS(135), 1,
      anon_sym_COMMA,
    STATE(50), 1,
      aux_sym_declarations_repeat1,
  [936] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(127), 1,
      anon_sym_RPAREN,
    ACTIONS(129), 1,
      anon_sym_COMMA,
    STATE(48), 1,
      aux_sym_args_decl_repeat1,
  [949] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(52), 1,
      anon_sym_COLON_EQ,
    ACTIONS(54), 1,
      anon_sym_LBRACK,
    ACTIONS(137), 1,
      anon_sym_LPAREN,
  [962] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(135), 1,
      anon_sym_COMMA,
    ACTIONS(139), 1,
      anon_sym_BEGIN,
    STATE(40), 1,
      aux_sym_declarations_repeat1,
  [975] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(141), 1,
      anon_sym_RPAREN,
    ACTIONS(143), 1,
      anon_sym_COMMA,
    STATE(44), 1,
      aux_sym_args_decl_repeat1,
  [988] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(148), 1,
      anon_sym_LBRACK,
    ACTIONS(146), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [999] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(150), 1,
      anon_sym_RPAREN,
    ACTIONS(152), 1,
      anon_sym_COMMA,
    STATE(53), 1,
      aux_sym_args_repeat1,
  [1012] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(154), 1,
      anon_sym_RPAREN,
    ACTIONS(156), 1,
      sym_pidentifier,
    STATE(80), 1,
      sym_args,
  [1025] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(129), 1,
      anon_sym_COMMA,
    ACTIONS(158), 1,
      anon_sym_RPAREN,
    STATE(44), 1,
      aux_sym_args_decl_repeat1,
  [1038] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(160), 3,
      anon_sym_SEMI,
      anon_sym_THEN,
      anon_sym_DO,
  [1047] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(162), 1,
      anon_sym_BEGIN,
    ACTIONS(164), 1,
      anon_sym_COMMA,
    STATE(50), 1,
      aux_sym_declarations_repeat1,
  [1060] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 1,
      anon_sym_LBRACK,
    ACTIONS(52), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1071] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(152), 1,
      anon_sym_COMMA,
    ACTIONS(169), 1,
      anon_sym_RPAREN,
    STATE(46), 1,
      aux_sym_args_repeat1,
  [1084] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(171), 1,
      anon_sym_RPAREN,
    ACTIONS(173), 1,
      anon_sym_COMMA,
    STATE(53), 1,
      aux_sym_args_repeat1,
  [1097] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      sym_pidentifier,
    STATE(115), 1,
      sym_identifier,
  [1107] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(176), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1115] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(178), 2,
      sym_pidentifier,
      sym_num,
  [1123] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(180), 1,
      sym_pidentifier,
    STATE(102), 1,
      sym_proc_head,
  [1133] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(58), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1141] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(62), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1149] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(182), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1157] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(171), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1165] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(162), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1173] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(184), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1181] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(186), 1,
      anon_sym_ELSE,
    ACTIONS(188), 1,
      anon_sym_ENDIF,
  [1191] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(190), 1,
      anon_sym_T,
    ACTIONS(192), 1,
      sym_pidentifier,
  [1201] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(141), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1209] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(114), 1,
      sym_pidentifier,
    STATE(62), 1,
      sym_declaration,
  [1219] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(194), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1227] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(196), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1235] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(198), 2,
      sym_pidentifier,
      sym_num,
  [1243] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(200), 1,
      anon_sym_END,
  [1250] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(202), 1,
      anon_sym_BEGIN,
  [1257] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(204), 1,
      anon_sym_THEN,
  [1264] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(206), 1,
      anon_sym_END,
  [1271] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(208), 1,
      anon_sym_IS,
  [1278] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(210), 1,
      sym_num,
  [1285] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(212), 1,
      anon_sym_COLON_EQ,
  [1292] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(214), 1,
      anon_sym_SEMI,
  [1299] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(216), 1,
      anon_sym_SEMI,
  [1306] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(218), 1,
      anon_sym_RPAREN,
  [1313] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(220), 1,
      anon_sym_RBRACK,
  [1320] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(222), 1,
      anon_sym_SEMI,
  [1327] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(88), 1,
      anon_sym_END,
  [1334] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      sym_num,
  [1341] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(226), 1,
      ts_builtin_sym_end,
  [1348] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(228), 1,
      ts_builtin_sym_end,
  [1355] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(230), 1,
      sym_pidentifier,
  [1362] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(188), 1,
      anon_sym_ENDWHILE,
  [1369] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(188), 1,
      anon_sym_SEMI,
  [1376] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(232), 1,
      anon_sym_DO,
  [1383] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(234), 1,
      sym_pidentifier,
  [1390] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(236), 1,
      ts_builtin_sym_end,
  [1397] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(238), 1,
      anon_sym_SEMI,
  [1404] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(240), 1,
      sym_pidentifier,
  [1411] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_RPAREN,
  [1418] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(244), 1,
      sym_pidentifier,
  [1425] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(246), 1,
      anon_sym_RBRACK,
  [1432] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(248), 1,
      anon_sym_IS,
  [1439] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(250), 1,
      anon_sym_BEGIN,
  [1446] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(252), 1,
      ts_builtin_sym_end,
  [1453] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(254), 1,
      anon_sym_UNTIL,
  [1460] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(256), 1,
      anon_sym_IS,
  [1467] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(258), 1,
      anon_sym_SEMI,
  [1474] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(260), 1,
      anon_sym_END,
  [1481] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      anon_sym_ENDIF,
  [1488] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(264), 1,
      anon_sym_DO,
  [1495] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(266), 1,
      anon_sym_LPAREN,
  [1502] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(268), 1,
      ts_builtin_sym_end,
  [1509] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(270), 1,
      anon_sym_ENDFOR,
  [1516] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      ts_builtin_sym_end,
  [1523] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(274), 1,
      anon_sym_IS,
  [1530] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(276), 1,
      anon_sym_COLON,
  [1537] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(278), 1,
      anon_sym_FROM,
  [1544] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(280), 1,
      anon_sym_RBRACK,
  [1551] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(282), 1,
      anon_sym_SEMI,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 45,
  [SMALL_STATE(4)] = 90,
  [SMALL_STATE(5)] = 115,
  [SMALL_STATE(6)] = 138,
  [SMALL_STATE(7)] = 160,
  [SMALL_STATE(8)] = 201,
  [SMALL_STATE(9)] = 222,
  [SMALL_STATE(10)] = 243,
  [SMALL_STATE(11)] = 264,
  [SMALL_STATE(12)] = 285,
  [SMALL_STATE(13)] = 306,
  [SMALL_STATE(14)] = 347,
  [SMALL_STATE(15)] = 368,
  [SMALL_STATE(16)] = 406,
  [SMALL_STATE(17)] = 444,
  [SMALL_STATE(18)] = 482,
  [SMALL_STATE(19)] = 520,
  [SMALL_STATE(20)] = 558,
  [SMALL_STATE(21)] = 596,
  [SMALL_STATE(22)] = 634,
  [SMALL_STATE(23)] = 648,
  [SMALL_STATE(24)] = 662,
  [SMALL_STATE(25)] = 681,
  [SMALL_STATE(26)] = 700,
  [SMALL_STATE(27)] = 717,
  [SMALL_STATE(28)] = 736,
  [SMALL_STATE(29)] = 755,
  [SMALL_STATE(30)] = 771,
  [SMALL_STATE(31)] = 787,
  [SMALL_STATE(32)] = 803,
  [SMALL_STATE(33)] = 819,
  [SMALL_STATE(34)] = 833,
  [SMALL_STATE(35)] = 849,
  [SMALL_STATE(36)] = 865,
  [SMALL_STATE(37)] = 881,
  [SMALL_STATE(38)] = 897,
  [SMALL_STATE(39)] = 910,
  [SMALL_STATE(40)] = 923,
  [SMALL_STATE(41)] = 936,
  [SMALL_STATE(42)] = 949,
  [SMALL_STATE(43)] = 962,
  [SMALL_STATE(44)] = 975,
  [SMALL_STATE(45)] = 988,
  [SMALL_STATE(46)] = 999,
  [SMALL_STATE(47)] = 1012,
  [SMALL_STATE(48)] = 1025,
  [SMALL_STATE(49)] = 1038,
  [SMALL_STATE(50)] = 1047,
  [SMALL_STATE(51)] = 1060,
  [SMALL_STATE(52)] = 1071,
  [SMALL_STATE(53)] = 1084,
  [SMALL_STATE(54)] = 1097,
  [SMALL_STATE(55)] = 1107,
  [SMALL_STATE(56)] = 1115,
  [SMALL_STATE(57)] = 1123,
  [SMALL_STATE(58)] = 1133,
  [SMALL_STATE(59)] = 1141,
  [SMALL_STATE(60)] = 1149,
  [SMALL_STATE(61)] = 1157,
  [SMALL_STATE(62)] = 1165,
  [SMALL_STATE(63)] = 1173,
  [SMALL_STATE(64)] = 1181,
  [SMALL_STATE(65)] = 1191,
  [SMALL_STATE(66)] = 1201,
  [SMALL_STATE(67)] = 1209,
  [SMALL_STATE(68)] = 1219,
  [SMALL_STATE(69)] = 1227,
  [SMALL_STATE(70)] = 1235,
  [SMALL_STATE(71)] = 1243,
  [SMALL_STATE(72)] = 1250,
  [SMALL_STATE(73)] = 1257,
  [SMALL_STATE(74)] = 1264,
  [SMALL_STATE(75)] = 1271,
  [SMALL_STATE(76)] = 1278,
  [SMALL_STATE(77)] = 1285,
  [SMALL_STATE(78)] = 1292,
  [SMALL_STATE(79)] = 1299,
  [SMALL_STATE(80)] = 1306,
  [SMALL_STATE(81)] = 1313,
  [SMALL_STATE(82)] = 1320,
  [SMALL_STATE(83)] = 1327,
  [SMALL_STATE(84)] = 1334,
  [SMALL_STATE(85)] = 1341,
  [SMALL_STATE(86)] = 1348,
  [SMALL_STATE(87)] = 1355,
  [SMALL_STATE(88)] = 1362,
  [SMALL_STATE(89)] = 1369,
  [SMALL_STATE(90)] = 1376,
  [SMALL_STATE(91)] = 1383,
  [SMALL_STATE(92)] = 1390,
  [SMALL_STATE(93)] = 1397,
  [SMALL_STATE(94)] = 1404,
  [SMALL_STATE(95)] = 1411,
  [SMALL_STATE(96)] = 1418,
  [SMALL_STATE(97)] = 1425,
  [SMALL_STATE(98)] = 1432,
  [SMALL_STATE(99)] = 1439,
  [SMALL_STATE(100)] = 1446,
  [SMALL_STATE(101)] = 1453,
  [SMALL_STATE(102)] = 1460,
  [SMALL_STATE(103)] = 1467,
  [SMALL_STATE(104)] = 1474,
  [SMALL_STATE(105)] = 1481,
  [SMALL_STATE(106)] = 1488,
  [SMALL_STATE(107)] = 1495,
  [SMALL_STATE(108)] = 1502,
  [SMALL_STATE(109)] = 1509,
  [SMALL_STATE(110)] = 1516,
  [SMALL_STATE(111)] = 1523,
  [SMALL_STATE(112)] = 1530,
  [SMALL_STATE(113)] = 1537,
  [SMALL_STATE(114)] = 1544,
  [SMALL_STATE(115)] = 1551,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [9] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_commands, 1, 0, 0),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [13] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_commands, 1, 0, 0),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [27] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0),
  [29] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(27),
  [32] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0),
  [34] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(28),
  [37] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(21),
  [40] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(87),
  [43] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(54),
  [46] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(36),
  [49] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(42),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 1, 0, 0),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [56] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_identifier, 1, 0, 0),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 4, 0, 0),
  [60] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_identifier, 4, 0, 0),
  [62] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 1, 0, 0),
  [64] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_value, 1, 0, 0),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [68] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 9, 0, 0),
  [70] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 9, 0, 0),
  [72] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 3, 0, 0),
  [74] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3, 0, 0),
  [76] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 7, 0, 0),
  [78] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 7, 0, 0),
  [80] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 4, 0, 0),
  [82] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 4, 0, 0),
  [84] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 5, 0, 0),
  [86] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 5, 0, 0),
  [88] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [90] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 2, 0, 0),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 2, 0, 0),
  [94] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [96] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 1, 0, 0),
  [100] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [102] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [106] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [108] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [110] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [112] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [114] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [116] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_all_repeat1, 2, 0, 0), SHIFT_REPEAT(57),
  [119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_program_all_repeat1, 2, 0, 0),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [127] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 2, 0, 0),
  [129] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 1, 0, 0),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declarations, 2, 0, 0),
  [135] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [137] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declarations, 1, 0, 0),
  [141] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 0),
  [143] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 0), SHIFT_REPEAT(65),
  [146] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declaration, 1, 0, 0),
  [148] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args, 2, 0, 0),
  [152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [154] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [158] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 3, 0, 0),
  [160] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_condition, 3, 0, 0),
  [162] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 0),
  [164] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 0), SHIFT_REPEAT(67),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [169] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args, 1, 0, 0),
  [171] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 0),
  [173] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 0), SHIFT_REPEAT(91),
  [176] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 7, 0, 0),
  [178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [180] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [182] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declaration, 6, 0, 0),
  [184] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [186] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [190] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [192] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [194] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 6, 0, 0),
  [196] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 3, 0, 0),
  [198] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [200] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [202] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [204] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [206] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [208] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_head, 4, 0, 0),
  [210] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [212] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_call, 3, 0, 0),
  [216] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [218] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [220] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [224] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [226] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 6, 0, 0),
  [228] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 5, 0, 0),
  [230] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [232] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [234] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [236] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 4, 0, 0),
  [238] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_call, 4, 0, 0),
  [240] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [248] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_head, 3, 0, 0),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [252] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program_all, 2, 0, 0),
  [254] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [256] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [258] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 3, 0, 0),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [262] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [266] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [268] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program_all, 1, 0, 0),
  [270] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [272] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [274] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [276] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_gbl(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
