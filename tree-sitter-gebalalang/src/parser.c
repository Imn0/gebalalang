#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 117
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
  sym__comment = 42,
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
  [sym__comment] = "_comment",
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
  [sym__comment] = sym__comment,
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
  [sym__comment] = {
    .visible = false,
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
  [57] = 56,
  [58] = 58,
  [59] = 5,
  [60] = 6,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
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
  [114] = 114,
  [115] = 80,
  [116] = 116,
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
          ('a' <= lookahead && lookahead <= 'z') ||
          (0x2600 <= lookahead && lookahead <= 0x26ff) ||
          (0x1f300 <= lookahead && lookahead <= 0x1f77f) ||
          (0x1f900 <= lookahead && lookahead <= 0x1f9ff) ||
          (0x1fa70 <= lookahead && lookahead <= 0x1faff)) ADVANCE(118);
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
          ('a' <= lookahead && lookahead <= 'z') ||
          (0x2600 <= lookahead && lookahead <= 0x26ff) ||
          (0x1f300 <= lookahead && lookahead <= 0x1f77f) ||
          (0x1f900 <= lookahead && lookahead <= 0x1f9ff) ||
          (0x1fa70 <= lookahead && lookahead <= 0x1faff)) ADVANCE(118);
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
          ('a' <= lookahead && lookahead <= 'z') ||
          (0x2600 <= lookahead && lookahead <= 0x26ff) ||
          (0x1f300 <= lookahead && lookahead <= 0x1f77f) ||
          (0x1f900 <= lookahead && lookahead <= 0x1f9ff) ||
          (0x1fa70 <= lookahead && lookahead <= 0x1faff)) ADVANCE(118);
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
      ACCEPT_TOKEN(sym__comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(117);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(sym_pidentifier);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          (0x2600 <= lookahead && lookahead <= 0x26ff) ||
          (0x1f300 <= lookahead && lookahead <= 0x1f77f) ||
          (0x1f900 <= lookahead && lookahead <= 0x1f9ff) ||
          (0x1fa70 <= lookahead && lookahead <= 0x1faff)) ADVANCE(118);
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
  [8] = {.lex_state = 1},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 1},
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
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 1},
  [51] = {.lex_state = 3},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 2},
  [57] = {.lex_state = 2},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 3},
  [60] = {.lex_state = 3},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 3},
  [65] = {.lex_state = 2},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 2},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 1},
  [74] = {.lex_state = 1},
  [75] = {.lex_state = 2},
  [76] = {.lex_state = 1},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 0},
  [82] = {.lex_state = 1},
  [83] = {.lex_state = 2},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 2},
  [90] = {.lex_state = 0},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 1},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 0},
  [102] = {.lex_state = 1},
  [103] = {.lex_state = 0},
  [104] = {.lex_state = 0},
  [105] = {.lex_state = 2},
  [106] = {.lex_state = 2},
  [107] = {.lex_state = 0},
  [108] = {.lex_state = 0},
  [109] = {.lex_state = 0},
  [110] = {.lex_state = 2},
  [111] = {.lex_state = 0},
  [112] = {.lex_state = 0},
  [113] = {.lex_state = 0},
  [114] = {.lex_state = 0},
  [115] = {.lex_state = 0},
  [116] = {.lex_state = 0},
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
    [sym__comment] = ACTIONS(3),
    [sym_pidentifier] = ACTIONS(1),
  },
  [1] = {
    [sym_program_all] = STATE(111),
    [sym_procedure] = STATE(26),
    [sym_main] = STATE(109),
    [aux_sym_program_all_repeat1] = STATE(26),
    [anon_sym_PROCEDURE] = ACTIONS(5),
    [anon_sym_PROGRAM] = ACTIONS(7),
    [sym__comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 13,
    ACTIONS(3), 1,
      sym__comment,
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
    STATE(76), 1,
      sym_identifier,
    STATE(78), 1,
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
      sym__comment,
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
    STATE(76), 1,
      sym_identifier,
    STATE(78), 1,
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
      sym__comment,
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
      sym__comment,
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
      sym__comment,
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
      sym__comment,
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
    STATE(76), 1,
      sym_identifier,
    STATE(78), 1,
      sym_proc_call,
    STATE(82), 1,
      sym_commands,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [201] = 13,
    ACTIONS(3), 1,
      sym__comment,
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
    ACTIONS(68), 1,
      anon_sym_END,
    STATE(76), 1,
      sym_identifier,
    STATE(78), 1,
      sym_proc_call,
    STATE(102), 1,
      sym_commands,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [242] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(70), 1,
      anon_sym_END,
    ACTIONS(72), 12,
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
  [263] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(74), 1,
      anon_sym_END,
    ACTIONS(76), 12,
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
  [284] = 13,
    ACTIONS(3), 1,
      sym__comment,
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
    ACTIONS(78), 1,
      anon_sym_END,
    STATE(74), 1,
      sym_commands,
    STATE(76), 1,
      sym_identifier,
    STATE(78), 1,
      sym_proc_call,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [325] = 3,
    ACTIONS(3), 1,
      sym__comment,
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
  [346] = 13,
    ACTIONS(3), 1,
      sym__comment,
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
    ACTIONS(84), 1,
      anon_sym_END,
    STATE(76), 1,
      sym_identifier,
    STATE(78), 1,
      sym_proc_call,
    STATE(94), 1,
      sym_commands,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [387] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(86), 1,
      anon_sym_END,
    ACTIONS(88), 12,
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
  [408] = 3,
    ACTIONS(3), 1,
      sym__comment,
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
  [429] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(94), 1,
      anon_sym_END,
    ACTIONS(96), 12,
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
  [450] = 12,
    ACTIONS(3), 1,
      sym__comment,
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
    STATE(76), 1,
      sym_identifier,
    STATE(78), 1,
      sym_proc_call,
    STATE(89), 1,
      sym_commands,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [488] = 12,
    ACTIONS(3), 1,
      sym__comment,
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
    STATE(76), 1,
      sym_identifier,
    STATE(78), 1,
      sym_proc_call,
    STATE(106), 1,
      sym_commands,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [526] = 12,
    ACTIONS(3), 1,
      sym__comment,
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
    STATE(65), 1,
      sym_commands,
    STATE(76), 1,
      sym_identifier,
    STATE(78), 1,
      sym_proc_call,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [564] = 12,
    ACTIONS(3), 1,
      sym__comment,
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
    STATE(76), 1,
      sym_identifier,
    STATE(78), 1,
      sym_proc_call,
    STATE(110), 1,
      sym_commands,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [602] = 12,
    ACTIONS(3), 1,
      sym__comment,
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
    STATE(76), 1,
      sym_identifier,
    STATE(78), 1,
      sym_proc_call,
    STATE(113), 1,
      sym_commands,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [640] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(100), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(98), 4,
      anon_sym_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
  [654] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(102), 1,
      anon_sym_SEMI,
    ACTIONS(104), 5,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [668] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    ACTIONS(108), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(22), 1,
      sym_value,
    STATE(90), 1,
      sym_condition,
  [687] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    ACTIONS(108), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(23), 1,
      sym_value,
    STATE(81), 1,
      sym_expression,
  [706] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(5), 1,
      anon_sym_PROCEDURE,
    ACTIONS(7), 1,
      anon_sym_PROGRAM,
    STATE(101), 1,
      sym_main,
    STATE(33), 2,
      sym_procedure,
      aux_sym_program_all_repeat1,
  [723] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    ACTIONS(108), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(22), 1,
      sym_value,
    STATE(73), 1,
      sym_condition,
  [742] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    ACTIONS(108), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(22), 1,
      sym_value,
    STATE(91), 1,
      sym_condition,
  [761] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(110), 1,
      anon_sym_RPAREN,
    ACTIONS(112), 1,
      anon_sym_T,
    ACTIONS(114), 1,
      sym_pidentifier,
    STATE(85), 1,
      sym_args_decl,
  [777] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    ACTIONS(108), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(104), 1,
      sym_value,
  [793] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    ACTIONS(108), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(107), 1,
      sym_value,
  [809] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(116), 1,
      anon_sym_BEGIN,
    ACTIONS(118), 1,
      sym_pidentifier,
    STATE(43), 1,
      sym_declaration,
    STATE(100), 1,
      sym_declarations,
  [825] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(120), 1,
      anon_sym_PROCEDURE,
    ACTIONS(123), 1,
      anon_sym_PROGRAM,
    STATE(33), 2,
      sym_procedure,
      aux_sym_program_all_repeat1,
  [839] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(125), 1,
      sym_pidentifier,
    ACTIONS(127), 1,
      sym_num,
    STATE(60), 1,
      sym_identifier,
    STATE(64), 1,
      sym_value,
  [855] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(118), 1,
      sym_pidentifier,
    ACTIONS(129), 1,
      anon_sym_BEGIN,
    STATE(43), 1,
      sym_declaration,
    STATE(87), 1,
      sym_declarations,
  [871] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    ACTIONS(108), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(86), 1,
      sym_value,
  [887] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    ACTIONS(108), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(50), 1,
      sym_value,
  [903] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(131), 1,
      anon_sym_RPAREN,
    ACTIONS(133), 1,
      anon_sym_COMMA,
    STATE(44), 1,
      aux_sym_args_decl_repeat1,
  [916] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(133), 1,
      anon_sym_COMMA,
    ACTIONS(135), 1,
      anon_sym_RPAREN,
    STATE(38), 1,
      aux_sym_args_decl_repeat1,
  [929] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(137), 1,
      anon_sym_BEGIN,
    ACTIONS(139), 1,
      anon_sym_COMMA,
    STATE(49), 1,
      aux_sym_declarations_repeat1,
  [942] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(131), 1,
      anon_sym_RPAREN,
    ACTIONS(133), 1,
      anon_sym_COMMA,
    STATE(45), 1,
      aux_sym_args_decl_repeat1,
  [955] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(52), 1,
      anon_sym_COLON_EQ,
    ACTIONS(54), 1,
      anon_sym_LBRACK,
    ACTIONS(141), 1,
      anon_sym_LPAREN,
  [968] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(139), 1,
      anon_sym_COMMA,
    ACTIONS(143), 1,
      anon_sym_BEGIN,
    STATE(40), 1,
      aux_sym_declarations_repeat1,
  [981] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(145), 1,
      anon_sym_RPAREN,
    ACTIONS(147), 1,
      anon_sym_COMMA,
    STATE(44), 1,
      aux_sym_args_decl_repeat1,
  [994] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(133), 1,
      anon_sym_COMMA,
    ACTIONS(150), 1,
      anon_sym_RPAREN,
    STATE(44), 1,
      aux_sym_args_decl_repeat1,
  [1007] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(154), 1,
      anon_sym_LBRACK,
    ACTIONS(152), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1018] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(156), 1,
      anon_sym_RPAREN,
    ACTIONS(158), 1,
      anon_sym_COMMA,
    STATE(53), 1,
      aux_sym_args_repeat1,
  [1031] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(160), 1,
      anon_sym_RPAREN,
    ACTIONS(162), 1,
      sym_pidentifier,
    STATE(79), 1,
      sym_args,
  [1044] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(164), 1,
      anon_sym_BEGIN,
    ACTIONS(166), 1,
      anon_sym_COMMA,
    STATE(49), 1,
      aux_sym_declarations_repeat1,
  [1057] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(169), 3,
      anon_sym_SEMI,
      anon_sym_THEN,
      anon_sym_DO,
  [1066] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(171), 1,
      anon_sym_LBRACK,
    ACTIONS(52), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1077] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(158), 1,
      anon_sym_COMMA,
    ACTIONS(173), 1,
      anon_sym_RPAREN,
    STATE(47), 1,
      aux_sym_args_repeat1,
  [1090] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(175), 1,
      anon_sym_RPAREN,
    ACTIONS(177), 1,
      anon_sym_COMMA,
    STATE(53), 1,
      aux_sym_args_repeat1,
  [1103] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    STATE(86), 1,
      sym_identifier,
  [1113] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(180), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1121] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(182), 2,
      sym_pidentifier,
      sym_num,
  [1129] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(184), 2,
      sym_pidentifier,
      sym_num,
  [1137] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(186), 1,
      sym_pidentifier,
    STATE(103), 1,
      sym_proc_head,
  [1147] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(58), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1155] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(62), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1163] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(188), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1171] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(175), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1179] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(164), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1187] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(190), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1195] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(192), 1,
      anon_sym_ELSE,
    ACTIONS(194), 1,
      anon_sym_ENDIF,
  [1205] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(196), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1213] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(145), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1221] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(118), 1,
      sym_pidentifier,
    STATE(63), 1,
      sym_declaration,
  [1231] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(198), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1239] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(200), 1,
      anon_sym_T,
    ACTIONS(202), 1,
      sym_pidentifier,
  [1249] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(204), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1257] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(206), 1,
      anon_sym_SEMI,
  [1264] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(208), 1,
      anon_sym_THEN,
  [1271] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(84), 1,
      anon_sym_END,
  [1278] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(210), 1,
      sym_num,
  [1285] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(212), 1,
      anon_sym_COLON_EQ,
  [1292] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(214), 1,
      anon_sym_SEMI,
  [1299] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(216), 1,
      anon_sym_SEMI,
  [1306] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(218), 1,
      anon_sym_RPAREN,
  [1313] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(220), 1,
      anon_sym_RBRACK,
  [1320] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(222), 1,
      anon_sym_SEMI,
  [1327] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(68), 1,
      anon_sym_END,
  [1334] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(224), 1,
      sym_num,
  [1341] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(226), 1,
      ts_builtin_sym_end,
  [1348] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(228), 1,
      anon_sym_RPAREN,
  [1355] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(230), 1,
      anon_sym_SEMI,
  [1362] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(232), 1,
      anon_sym_BEGIN,
  [1369] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(234), 1,
      sym_pidentifier,
  [1376] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(194), 1,
      anon_sym_ENDWHILE,
  [1383] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(194), 1,
      anon_sym_SEMI,
  [1390] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(236), 1,
      anon_sym_DO,
  [1397] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(238), 1,
      sym_pidentifier,
  [1404] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(240), 1,
      ts_builtin_sym_end,
  [1411] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(242), 1,
      anon_sym_END,
  [1418] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(244), 1,
      anon_sym_IS,
  [1425] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(246), 1,
      sym_pidentifier,
  [1432] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(248), 1,
      sym_pidentifier,
  [1439] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(250), 1,
      anon_sym_RBRACK,
  [1446] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(252), 1,
      anon_sym_IS,
  [1453] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(254), 1,
      anon_sym_BEGIN,
  [1460] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(256), 1,
      ts_builtin_sym_end,
  [1467] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(258), 1,
      anon_sym_END,
  [1474] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(260), 1,
      anon_sym_IS,
  [1481] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(262), 1,
      anon_sym_SEMI,
  [1488] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(264), 1,
      anon_sym_COLON,
  [1495] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(266), 1,
      anon_sym_ENDIF,
  [1502] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(268), 1,
      anon_sym_DO,
  [1509] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(270), 1,
      anon_sym_LPAREN,
  [1516] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(272), 1,
      ts_builtin_sym_end,
  [1523] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(274), 1,
      anon_sym_ENDFOR,
  [1530] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(276), 1,
      ts_builtin_sym_end,
  [1537] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(278), 1,
      anon_sym_IS,
  [1544] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(280), 1,
      anon_sym_UNTIL,
  [1551] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(282), 1,
      anon_sym_FROM,
  [1558] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(284), 1,
      anon_sym_RBRACK,
  [1565] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(286), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 45,
  [SMALL_STATE(4)] = 90,
  [SMALL_STATE(5)] = 115,
  [SMALL_STATE(6)] = 138,
  [SMALL_STATE(7)] = 160,
  [SMALL_STATE(8)] = 201,
  [SMALL_STATE(9)] = 242,
  [SMALL_STATE(10)] = 263,
  [SMALL_STATE(11)] = 284,
  [SMALL_STATE(12)] = 325,
  [SMALL_STATE(13)] = 346,
  [SMALL_STATE(14)] = 387,
  [SMALL_STATE(15)] = 408,
  [SMALL_STATE(16)] = 429,
  [SMALL_STATE(17)] = 450,
  [SMALL_STATE(18)] = 488,
  [SMALL_STATE(19)] = 526,
  [SMALL_STATE(20)] = 564,
  [SMALL_STATE(21)] = 602,
  [SMALL_STATE(22)] = 640,
  [SMALL_STATE(23)] = 654,
  [SMALL_STATE(24)] = 668,
  [SMALL_STATE(25)] = 687,
  [SMALL_STATE(26)] = 706,
  [SMALL_STATE(27)] = 723,
  [SMALL_STATE(28)] = 742,
  [SMALL_STATE(29)] = 761,
  [SMALL_STATE(30)] = 777,
  [SMALL_STATE(31)] = 793,
  [SMALL_STATE(32)] = 809,
  [SMALL_STATE(33)] = 825,
  [SMALL_STATE(34)] = 839,
  [SMALL_STATE(35)] = 855,
  [SMALL_STATE(36)] = 871,
  [SMALL_STATE(37)] = 887,
  [SMALL_STATE(38)] = 903,
  [SMALL_STATE(39)] = 916,
  [SMALL_STATE(40)] = 929,
  [SMALL_STATE(41)] = 942,
  [SMALL_STATE(42)] = 955,
  [SMALL_STATE(43)] = 968,
  [SMALL_STATE(44)] = 981,
  [SMALL_STATE(45)] = 994,
  [SMALL_STATE(46)] = 1007,
  [SMALL_STATE(47)] = 1018,
  [SMALL_STATE(48)] = 1031,
  [SMALL_STATE(49)] = 1044,
  [SMALL_STATE(50)] = 1057,
  [SMALL_STATE(51)] = 1066,
  [SMALL_STATE(52)] = 1077,
  [SMALL_STATE(53)] = 1090,
  [SMALL_STATE(54)] = 1103,
  [SMALL_STATE(55)] = 1113,
  [SMALL_STATE(56)] = 1121,
  [SMALL_STATE(57)] = 1129,
  [SMALL_STATE(58)] = 1137,
  [SMALL_STATE(59)] = 1147,
  [SMALL_STATE(60)] = 1155,
  [SMALL_STATE(61)] = 1163,
  [SMALL_STATE(62)] = 1171,
  [SMALL_STATE(63)] = 1179,
  [SMALL_STATE(64)] = 1187,
  [SMALL_STATE(65)] = 1195,
  [SMALL_STATE(66)] = 1205,
  [SMALL_STATE(67)] = 1213,
  [SMALL_STATE(68)] = 1221,
  [SMALL_STATE(69)] = 1231,
  [SMALL_STATE(70)] = 1239,
  [SMALL_STATE(71)] = 1249,
  [SMALL_STATE(72)] = 1257,
  [SMALL_STATE(73)] = 1264,
  [SMALL_STATE(74)] = 1271,
  [SMALL_STATE(75)] = 1278,
  [SMALL_STATE(76)] = 1285,
  [SMALL_STATE(77)] = 1292,
  [SMALL_STATE(78)] = 1299,
  [SMALL_STATE(79)] = 1306,
  [SMALL_STATE(80)] = 1313,
  [SMALL_STATE(81)] = 1320,
  [SMALL_STATE(82)] = 1327,
  [SMALL_STATE(83)] = 1334,
  [SMALL_STATE(84)] = 1341,
  [SMALL_STATE(85)] = 1348,
  [SMALL_STATE(86)] = 1355,
  [SMALL_STATE(87)] = 1362,
  [SMALL_STATE(88)] = 1369,
  [SMALL_STATE(89)] = 1376,
  [SMALL_STATE(90)] = 1383,
  [SMALL_STATE(91)] = 1390,
  [SMALL_STATE(92)] = 1397,
  [SMALL_STATE(93)] = 1404,
  [SMALL_STATE(94)] = 1411,
  [SMALL_STATE(95)] = 1418,
  [SMALL_STATE(96)] = 1425,
  [SMALL_STATE(97)] = 1432,
  [SMALL_STATE(98)] = 1439,
  [SMALL_STATE(99)] = 1446,
  [SMALL_STATE(100)] = 1453,
  [SMALL_STATE(101)] = 1460,
  [SMALL_STATE(102)] = 1467,
  [SMALL_STATE(103)] = 1474,
  [SMALL_STATE(104)] = 1481,
  [SMALL_STATE(105)] = 1488,
  [SMALL_STATE(106)] = 1495,
  [SMALL_STATE(107)] = 1502,
  [SMALL_STATE(108)] = 1509,
  [SMALL_STATE(109)] = 1516,
  [SMALL_STATE(110)] = 1523,
  [SMALL_STATE(111)] = 1530,
  [SMALL_STATE(112)] = 1537,
  [SMALL_STATE(113)] = 1544,
  [SMALL_STATE(114)] = 1551,
  [SMALL_STATE(115)] = 1558,
  [SMALL_STATE(116)] = 1565,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [9] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_commands, 1, 0, 0),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [13] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_commands, 1, 0, 0),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [27] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0),
  [29] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(27),
  [32] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0),
  [34] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(28),
  [37] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(21),
  [40] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(88),
  [43] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(54),
  [46] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(36),
  [49] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(42),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 1, 0, 0),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [56] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_identifier, 1, 0, 0),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 4, 0, 0),
  [60] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_identifier, 4, 0, 0),
  [62] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 1, 0, 0),
  [64] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_value, 1, 0, 0),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [68] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [70] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 3, 0, 0),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3, 0, 0),
  [74] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 9, 0, 0),
  [76] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 9, 0, 0),
  [78] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [80] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 5, 0, 0),
  [82] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 5, 0, 0),
  [84] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [86] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 2, 0, 0),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 2, 0, 0),
  [90] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 4, 0, 0),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 4, 0, 0),
  [94] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 7, 0, 0),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 7, 0, 0),
  [98] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [100] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [102] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 1, 0, 0),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [106] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [108] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [110] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [112] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [114] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [116] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [118] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [120] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_all_repeat1, 2, 0, 0), SHIFT_REPEAT(58),
  [123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_program_all_repeat1, 2, 0, 0),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [127] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [129] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 2, 0, 0),
  [133] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 1, 0, 0),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declarations, 2, 0, 0),
  [139] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [141] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declarations, 1, 0, 0),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 0),
  [147] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 0), SHIFT_REPEAT(70),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 3, 0, 0),
  [152] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declaration, 1, 0, 0),
  [154] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [156] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args, 2, 0, 0),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [162] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [164] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 0),
  [166] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 0), SHIFT_REPEAT(68),
  [169] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_condition, 3, 0, 0),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [173] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args, 1, 0, 0),
  [175] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 0),
  [177] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 0), SHIFT_REPEAT(92),
  [180] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 7, 0, 0),
  [182] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [184] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [186] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [188] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declaration, 6, 0, 0),
  [190] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [192] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [194] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [196] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 3, 0, 0),
  [198] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 6, 0, 0),
  [200] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [202] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [204] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 5, 0, 0),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_call, 4, 0, 0),
  [208] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [210] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [212] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_call, 3, 0, 0),
  [216] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [218] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [220] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [224] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [226] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 6, 0, 0),
  [228] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [230] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [232] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [234] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [236] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [238] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [240] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 4, 0, 0),
  [242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [244] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_head, 4, 0, 0),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [252] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_head, 3, 0, 0),
  [254] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [256] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program_all, 2, 0, 0),
  [258] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 3, 0, 0),
  [264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [266] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [270] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [272] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program_all, 1, 0, 0),
  [274] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [276] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [284] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [286] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 5, 0, 0),
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
