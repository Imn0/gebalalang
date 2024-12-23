#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 117
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 66
#define ALIAS_COUNT 0
#define TOKEN_COUNT 46
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 9
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  sym_word_token = 1,
  anon_sym_PROCEDURE = 2,
  anon_sym_IS = 3,
  anon_sym_BEGIN = 4,
  anon_sym_END = 5,
  anon_sym_PROGRAM = 6,
  anon_sym_COLON_EQ = 7,
  anon_sym_SEMI = 8,
  anon_sym_IF = 9,
  anon_sym_THEN = 10,
  anon_sym_ELSE = 11,
  anon_sym_ENDIF = 12,
  anon_sym_WHILE = 13,
  anon_sym_DO = 14,
  anon_sym_ENDWHILE = 15,
  anon_sym_REPEAT = 16,
  anon_sym_UNTIL = 17,
  anon_sym_FOR = 18,
  anon_sym_FROM = 19,
  anon_sym_TO = 20,
  anon_sym_ENDFOR = 21,
  anon_sym_DOWNTO = 22,
  anon_sym_READ = 23,
  anon_sym_WRITE = 24,
  anon_sym_LPAREN = 25,
  anon_sym_RPAREN = 26,
  anon_sym_COMMA = 27,
  anon_sym_LBRACK = 28,
  anon_sym_COLON = 29,
  anon_sym_RBRACK = 30,
  anon_sym_T = 31,
  anon_sym_PLUS = 32,
  anon_sym_DASH = 33,
  anon_sym_STAR = 34,
  anon_sym_SLASH = 35,
  anon_sym_PERCENT = 36,
  anon_sym_EQ = 37,
  anon_sym_BANG_EQ = 38,
  anon_sym_GT = 39,
  anon_sym_LT = 40,
  anon_sym_GT_EQ = 41,
  anon_sym_LT_EQ = 42,
  sym__comment = 43,
  sym_pidentifier = 44,
  sym_num = 45,
  sym_program_all = 46,
  sym_procedure = 47,
  sym_main = 48,
  sym_commands = 49,
  sym_command = 50,
  sym_proc_head = 51,
  sym_proc_call = 52,
  sym_declarations = 53,
  sym_declaration = 54,
  sym_args_decl = 55,
  sym_args = 56,
  sym_expression = 57,
  sym_condition = 58,
  sym_value = 59,
  sym_identifier = 60,
  aux_sym_program_all_repeat1 = 61,
  aux_sym_commands_repeat1 = 62,
  aux_sym_declarations_repeat1 = 63,
  aux_sym_args_decl_repeat1 = 64,
  aux_sym_args_repeat1 = 65,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_word_token] = "word_token",
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
  [sym_word_token] = sym_word_token,
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
  [sym_word_token] = {
    .visible = true,
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
  [51] = 51,
  [52] = 52,
  [53] = 4,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 6,
  [70] = 5,
  [71] = 55,
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
  [114] = 79,
  [115] = 115,
  [116] = 116,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(48);
      ADVANCE_MAP(
        '!', 5,
        '#', 98,
        '%', 91,
        '(', 78,
        ')', 79,
        '*', 89,
        '+', 87,
        ',', 80,
        '-', 88,
        '/', 90,
        ':', 83,
        ';', 55,
        '<', 95,
        '=', 92,
        '>', 94,
        'B', 103,
        'E', 120,
        'F', 126,
        'I', 110,
        'R', 104,
        'T', 86,
        'U', 124,
        'W', 113,
        '[', 81,
        ']', 84,
        '_', 134,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(135);
      if (('a' <= lookahead && lookahead <= 'z') ||
          (0x2600 <= lookahead && lookahead <= 0x26ff) ||
          (0x1f300 <= lookahead && lookahead <= 0x1f77f) ||
          (0x1f900 <= lookahead && lookahead <= 0x1f9ff) ||
          (0x1fa70 <= lookahead && lookahead <= 0x1faff)) ADVANCE(136);
      END_STATE();
    case 1:
      ADVANCE_MAP(
        '!', 5,
        '#', 98,
        '%', 91,
        '(', 78,
        '*', 89,
        '+', 87,
        '-', 88,
        '/', 90,
        ':', 6,
        ';', 55,
        '<', 95,
        '=', 92,
        '>', 94,
        '[', 81,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(1);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 2:
      ADVANCE_MAP(
        '#', 98,
        ')', 79,
        ',', 80,
        ':', 82,
        'B', 13,
        'E', 31,
        'F', 39,
        'I', 20,
        'R', 14,
        'T', 85,
        'U', 36,
        'W', 24,
        '[', 81,
        '+', 47,
        '-', 47,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(2);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(137);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          (0x2600 <= lookahead && lookahead <= 0x26ff) ||
          (0x1f300 <= lookahead && lookahead <= 0x1f77f) ||
          (0x1f900 <= lookahead && lookahead <= 0x1f9ff) ||
          (0x1fa70 <= lookahead && lookahead <= 0x1faff)) ADVANCE(136);
      END_STATE();
    case 3:
      if (lookahead == '#') ADVANCE(98);
      if (lookahead == 'E') ADVANCE(38);
      if (lookahead == 'F') ADVANCE(39);
      if (lookahead == 'I') ADVANCE(20);
      if (lookahead == 'R') ADVANCE(14);
      if (lookahead == 'W') ADVANCE(24);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(3);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          (0x2600 <= lookahead && lookahead <= 0x26ff) ||
          (0x1f300 <= lookahead && lookahead <= 0x1f77f) ||
          (0x1f900 <= lookahead && lookahead <= 0x1f9ff) ||
          (0x1fa70 <= lookahead && lookahead <= 0x1faff)) ADVANCE(136);
      END_STATE();
    case 4:
      if (lookahead == '#') ADVANCE(98);
      if (lookahead == 'E') ADVANCE(32);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(4);
      END_STATE();
    case 5:
      if (lookahead == '=') ADVANCE(93);
      END_STATE();
    case 6:
      if (lookahead == '=') ADVANCE(54);
      END_STATE();
    case 7:
      if (lookahead == 'A') ADVANCE(10);
      if (lookahead == 'P') ADVANCE(16);
      END_STATE();
    case 8:
      if (lookahead == 'A') ADVANCE(44);
      END_STATE();
    case 9:
      if (lookahead == 'D') ADVANCE(53);
      END_STATE();
    case 10:
      if (lookahead == 'D') ADVANCE(74);
      END_STATE();
    case 11:
      if (lookahead == 'D') ADVANCE(51);
      END_STATE();
    case 12:
      if (lookahead == 'D') ADVANCE(22);
      END_STATE();
    case 13:
      if (lookahead == 'E') ADVANCE(23);
      END_STATE();
    case 14:
      if (lookahead == 'E') ADVANCE(7);
      END_STATE();
    case 15:
      if (lookahead == 'E') ADVANCE(58);
      END_STATE();
    case 16:
      if (lookahead == 'E') ADVANCE(8);
      END_STATE();
    case 17:
      if (lookahead == 'E') ADVANCE(62);
      END_STATE();
    case 18:
      if (lookahead == 'E') ADVANCE(76);
      END_STATE();
    case 19:
      if (lookahead == 'E') ADVANCE(64);
      END_STATE();
    case 20:
      if (lookahead == 'F') ADVANCE(56);
      END_STATE();
    case 21:
      if (lookahead == 'F') ADVANCE(60);
      END_STATE();
    case 22:
      if (lookahead == 'F') ADVANCE(40);
      if (lookahead == 'I') ADVANCE(21);
      if (lookahead == 'W') ADVANCE(25);
      END_STATE();
    case 23:
      if (lookahead == 'G') ADVANCE(27);
      END_STATE();
    case 24:
      if (lookahead == 'H') ADVANCE(26);
      if (lookahead == 'R') ADVANCE(28);
      END_STATE();
    case 25:
      if (lookahead == 'H') ADVANCE(30);
      END_STATE();
    case 26:
      if (lookahead == 'I') ADVANCE(34);
      END_STATE();
    case 27:
      if (lookahead == 'I') ADVANCE(37);
      END_STATE();
    case 28:
      if (lookahead == 'I') ADVANCE(45);
      END_STATE();
    case 29:
      if (lookahead == 'I') ADVANCE(33);
      END_STATE();
    case 30:
      if (lookahead == 'I') ADVANCE(35);
      END_STATE();
    case 31:
      if (lookahead == 'L') ADVANCE(43);
      if (lookahead == 'N') ADVANCE(9);
      END_STATE();
    case 32:
      if (lookahead == 'L') ADVANCE(43);
      if (lookahead == 'N') ADVANCE(12);
      END_STATE();
    case 33:
      if (lookahead == 'L') ADVANCE(68);
      END_STATE();
    case 34:
      if (lookahead == 'L') ADVANCE(17);
      END_STATE();
    case 35:
      if (lookahead == 'L') ADVANCE(19);
      END_STATE();
    case 36:
      if (lookahead == 'N') ADVANCE(46);
      END_STATE();
    case 37:
      if (lookahead == 'N') ADVANCE(49);
      END_STATE();
    case 38:
      if (lookahead == 'N') ADVANCE(11);
      END_STATE();
    case 39:
      if (lookahead == 'O') ADVANCE(41);
      END_STATE();
    case 40:
      if (lookahead == 'O') ADVANCE(42);
      END_STATE();
    case 41:
      if (lookahead == 'R') ADVANCE(70);
      END_STATE();
    case 42:
      if (lookahead == 'R') ADVANCE(72);
      END_STATE();
    case 43:
      if (lookahead == 'S') ADVANCE(15);
      END_STATE();
    case 44:
      if (lookahead == 'T') ADVANCE(66);
      END_STATE();
    case 45:
      if (lookahead == 'T') ADVANCE(18);
      END_STATE();
    case 46:
      if (lookahead == 'T') ADVANCE(29);
      END_STATE();
    case 47:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(137);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(anon_sym_BEGIN);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(anon_sym_BEGIN);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_END);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(anon_sym_END);
      if (lookahead == 'F') ADVANCE(127);
      if (lookahead == 'I') ADVANCE(111);
      if (lookahead == 'W') ADVANCE(114);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(anon_sym_END);
      if (lookahead == 'F') ADVANCE(40);
      if (lookahead == 'I') ADVANCE(21);
      if (lookahead == 'W') ADVANCE(25);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_COLON_EQ);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(anon_sym_IF);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(anon_sym_IF);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(anon_sym_ELSE);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(anon_sym_ELSE);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(anon_sym_ENDIF);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_ENDIF);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(anon_sym_WHILE);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(anon_sym_WHILE);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(anon_sym_ENDWHILE);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(anon_sym_ENDWHILE);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_REPEAT);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_REPEAT);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_UNTIL);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_UNTIL);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_FOR);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_FOR);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_ENDFOR);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_ENDFOR);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_READ);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_READ);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_WRITE);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_WRITE);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_COLON);
      if (lookahead == '=') ADVANCE(54);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(anon_sym_T);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(anon_sym_T);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(anon_sym_PERCENT);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(96);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(97);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(sym__comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(98);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'A') ADVANCE(102);
      if (lookahead == 'P') ADVANCE(106);
      if (('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'A') ADVANCE(131);
      if (('B' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'D') ADVANCE(52);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'D') ADVANCE(75);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'E') ADVANCE(112);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'E') ADVANCE(99);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'E') ADVANCE(59);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'E') ADVANCE(100);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'E') ADVANCE(63);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'E') ADVANCE(77);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'E') ADVANCE(65);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'F') ADVANCE(57);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'F') ADVANCE(61);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'G') ADVANCE(116);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'H') ADVANCE(115);
      if (lookahead == 'R') ADVANCE(117);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'H') ADVANCE(119);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'I') ADVANCE(122);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'I') ADVANCE(125);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'I') ADVANCE(132);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'I') ADVANCE(121);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'I') ADVANCE(123);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'L') ADVANCE(130);
      if (lookahead == 'N') ADVANCE(101);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'L') ADVANCE(69);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'L') ADVANCE(107);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'L') ADVANCE(109);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'N') ADVANCE(133);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'N') ADVANCE(50);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'O') ADVANCE(128);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'O') ADVANCE(129);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'R') ADVANCE(71);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'R') ADVANCE(73);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'S') ADVANCE(105);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'T') ADVANCE(67);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'T') ADVANCE(108);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == 'T') ADVANCE(118);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(sym_word_token);
      if (lookahead == '_') ADVANCE(134);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(135);
      if (('a' <= lookahead && lookahead <= 'z') ||
          (0x2600 <= lookahead && lookahead <= 0x26ff) ||
          (0x1f300 <= lookahead && lookahead <= 0x1f77f) ||
          (0x1f900 <= lookahead && lookahead <= 0x1f9ff) ||
          (0x1fa70 <= lookahead && lookahead <= 0x1faff)) ADVANCE(136);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(sym_word_token);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(sym_pidentifier);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z') ||
          (0x2600 <= lookahead && lookahead <= 0x26ff) ||
          (0x1f300 <= lookahead && lookahead <= 0x1f77f) ||
          (0x1f900 <= lookahead && lookahead <= 0x1f9ff) ||
          (0x1fa70 <= lookahead && lookahead <= 0x1faff)) ADVANCE(136);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(sym_num);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(137);
      END_STATE();
    default:
      return false;
  }
}

static bool ts_lex_keywords(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (lookahead == 'D') ADVANCE(1);
      if (lookahead == 'F') ADVANCE(2);
      if (lookahead == 'I') ADVANCE(3);
      if (lookahead == 'P') ADVANCE(4);
      if (lookahead == 'T') ADVANCE(5);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      END_STATE();
    case 1:
      if (lookahead == 'O') ADVANCE(6);
      END_STATE();
    case 2:
      if (lookahead == 'R') ADVANCE(7);
      END_STATE();
    case 3:
      if (lookahead == 'S') ADVANCE(8);
      END_STATE();
    case 4:
      if (lookahead == 'R') ADVANCE(9);
      END_STATE();
    case 5:
      if (lookahead == 'H') ADVANCE(10);
      if (lookahead == 'O') ADVANCE(11);
      END_STATE();
    case 6:
      ACCEPT_TOKEN(anon_sym_DO);
      if (lookahead == 'W') ADVANCE(12);
      END_STATE();
    case 7:
      if (lookahead == 'O') ADVANCE(13);
      END_STATE();
    case 8:
      ACCEPT_TOKEN(anon_sym_IS);
      END_STATE();
    case 9:
      if (lookahead == 'O') ADVANCE(14);
      END_STATE();
    case 10:
      if (lookahead == 'E') ADVANCE(15);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(anon_sym_TO);
      END_STATE();
    case 12:
      if (lookahead == 'N') ADVANCE(16);
      END_STATE();
    case 13:
      if (lookahead == 'M') ADVANCE(17);
      END_STATE();
    case 14:
      if (lookahead == 'C') ADVANCE(18);
      if (lookahead == 'G') ADVANCE(19);
      END_STATE();
    case 15:
      if (lookahead == 'N') ADVANCE(20);
      END_STATE();
    case 16:
      if (lookahead == 'T') ADVANCE(21);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(anon_sym_FROM);
      END_STATE();
    case 18:
      if (lookahead == 'E') ADVANCE(22);
      END_STATE();
    case 19:
      if (lookahead == 'R') ADVANCE(23);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_THEN);
      END_STATE();
    case 21:
      if (lookahead == 'O') ADVANCE(24);
      END_STATE();
    case 22:
      if (lookahead == 'D') ADVANCE(25);
      END_STATE();
    case 23:
      if (lookahead == 'A') ADVANCE(26);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_DOWNTO);
      END_STATE();
    case 25:
      if (lookahead == 'U') ADVANCE(27);
      END_STATE();
    case 26:
      if (lookahead == 'M') ADVANCE(28);
      END_STATE();
    case 27:
      if (lookahead == 'R') ADVANCE(29);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_PROGRAM);
      END_STATE();
    case 29:
      if (lookahead == 'E') ADVANCE(30);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_PROCEDURE);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 1},
  [2] = {.lex_state = 2},
  [3] = {.lex_state = 2},
  [4] = {.lex_state = 1},
  [5] = {.lex_state = 1},
  [6] = {.lex_state = 1},
  [7] = {.lex_state = 2},
  [8] = {.lex_state = 3},
  [9] = {.lex_state = 3},
  [10] = {.lex_state = 3},
  [11] = {.lex_state = 3},
  [12] = {.lex_state = 2},
  [13] = {.lex_state = 2},
  [14] = {.lex_state = 2},
  [15] = {.lex_state = 2},
  [16] = {.lex_state = 2},
  [17] = {.lex_state = 2},
  [18] = {.lex_state = 2},
  [19] = {.lex_state = 2},
  [20] = {.lex_state = 2},
  [21] = {.lex_state = 2},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 0},
  [24] = {.lex_state = 1},
  [25] = {.lex_state = 2},
  [26] = {.lex_state = 2},
  [27] = {.lex_state = 2},
  [28] = {.lex_state = 2},
  [29] = {.lex_state = 2},
  [30] = {.lex_state = 1},
  [31] = {.lex_state = 2},
  [32] = {.lex_state = 2},
  [33] = {.lex_state = 2},
  [34] = {.lex_state = 2},
  [35] = {.lex_state = 2},
  [36] = {.lex_state = 2},
  [37] = {.lex_state = 2},
  [38] = {.lex_state = 2},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 2},
  [42] = {.lex_state = 1},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 2},
  [45] = {.lex_state = 1},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 2},
  [51] = {.lex_state = 2},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 1},
  [54] = {.lex_state = 2},
  [55] = {.lex_state = 2},
  [56] = {.lex_state = 2},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 1},
  [59] = {.lex_state = 2},
  [60] = {.lex_state = 2},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 1},
  [63] = {.lex_state = 4},
  [64] = {.lex_state = 1},
  [65] = {.lex_state = 1},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 2},
  [68] = {.lex_state = 2},
  [69] = {.lex_state = 1},
  [70] = {.lex_state = 1},
  [71] = {.lex_state = 2},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 1},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 2},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 2},
  [82] = {.lex_state = 2},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 3},
  [85] = {.lex_state = 1},
  [86] = {.lex_state = 2},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 4},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 3},
  [91] = {.lex_state = 2},
  [92] = {.lex_state = 2},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 2},
  [95] = {.lex_state = 3},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 2},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 1},
  [101] = {.lex_state = 0},
  [102] = {.lex_state = 0},
  [103] = {.lex_state = 0},
  [104] = {.lex_state = 2},
  [105] = {.lex_state = 4},
  [106] = {.lex_state = 1},
  [107] = {.lex_state = 1},
  [108] = {.lex_state = 2},
  [109] = {.lex_state = 4},
  [110] = {.lex_state = 1},
  [111] = {.lex_state = 0},
  [112] = {.lex_state = 3},
  [113] = {.lex_state = 1},
  [114] = {.lex_state = 0},
  [115] = {.lex_state = 1},
  [116] = {.lex_state = 1},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_word_token] = ACTIONS(1),
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
    [anon_sym_DOWNTO] = ACTIONS(1),
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
    [sym_program_all] = STATE(96),
    [sym_procedure] = STATE(24),
    [sym_main] = STATE(102),
    [aux_sym_program_all_repeat1] = STATE(24),
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
    STATE(103), 1,
      sym_proc_call,
    STATE(113), 1,
      sym_identifier,
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
    STATE(103), 1,
      sym_proc_call,
    STATE(113), 1,
      sym_identifier,
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
  [160] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(66), 1,
      anon_sym_END,
    ACTIONS(68), 12,
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
  [181] = 13,
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
    ACTIONS(70), 1,
      anon_sym_END,
    STATE(95), 1,
      sym_commands,
    STATE(103), 1,
      sym_proc_call,
    STATE(113), 1,
      sym_identifier,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [222] = 13,
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
    ACTIONS(72), 1,
      anon_sym_END,
    STATE(84), 1,
      sym_commands,
    STATE(103), 1,
      sym_proc_call,
    STATE(113), 1,
      sym_identifier,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [263] = 13,
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
    ACTIONS(74), 1,
      anon_sym_END,
    STATE(103), 1,
      sym_proc_call,
    STATE(112), 1,
      sym_commands,
    STATE(113), 1,
      sym_identifier,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [304] = 13,
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
    ACTIONS(76), 1,
      anon_sym_END,
    STATE(90), 1,
      sym_commands,
    STATE(103), 1,
      sym_proc_call,
    STATE(113), 1,
      sym_identifier,
    STATE(2), 2,
      sym_command,
      aux_sym_commands_repeat1,
  [345] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(78), 1,
      anon_sym_END,
    ACTIONS(80), 12,
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
  [366] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(82), 1,
      anon_sym_END,
    ACTIONS(84), 12,
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
    STATE(103), 1,
      sym_proc_call,
    STATE(108), 1,
      sym_commands,
    STATE(113), 1,
      sym_identifier,
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
    STATE(63), 1,
      sym_commands,
    STATE(103), 1,
      sym_proc_call,
    STATE(113), 1,
      sym_identifier,
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
    STATE(103), 1,
      sym_proc_call,
    STATE(105), 1,
      sym_commands,
    STATE(113), 1,
      sym_identifier,
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
    STATE(88), 1,
      sym_commands,
    STATE(103), 1,
      sym_proc_call,
    STATE(113), 1,
      sym_identifier,
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
    STATE(103), 1,
      sym_proc_call,
    STATE(109), 1,
      sym_commands,
    STATE(113), 1,
      sym_identifier,
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
  [668] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(5), 1,
      anon_sym_PROCEDURE,
    ACTIONS(7), 1,
      anon_sym_PROGRAM,
    STATE(77), 1,
      sym_main,
    STATE(30), 2,
      sym_procedure,
      aux_sym_program_all_repeat1,
  [685] = 6,
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
    STATE(100), 1,
      sym_condition,
  [704] = 6,
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
    STATE(107), 1,
      sym_condition,
  [723] = 6,
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
    STATE(80), 1,
      sym_expression,
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
    STATE(89), 1,
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
    STATE(87), 1,
      sym_args_decl,
  [777] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(116), 1,
      anon_sym_PROCEDURE,
    ACTIONS(119), 1,
      anon_sym_PROGRAM,
    STATE(30), 2,
      sym_procedure,
      aux_sym_program_all_repeat1,
  [791] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    ACTIONS(108), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(45), 1,
      sym_value,
  [807] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    ACTIONS(108), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(111), 1,
      sym_value,
  [823] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(121), 1,
      sym_pidentifier,
    ACTIONS(123), 1,
      sym_num,
    STATE(64), 1,
      sym_value,
    STATE(69), 1,
      sym_identifier,
  [839] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(125), 1,
      anon_sym_BEGIN,
    ACTIONS(127), 1,
      sym_pidentifier,
    STATE(51), 1,
      sym_declaration,
    STATE(98), 1,
      sym_declarations,
  [855] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    ACTIONS(108), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(106), 1,
      sym_value,
  [871] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    ACTIONS(108), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(72), 1,
      sym_value,
  [887] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(127), 1,
      sym_pidentifier,
    ACTIONS(129), 1,
      anon_sym_BEGIN,
    STATE(51), 1,
      sym_declaration,
    STATE(86), 1,
      sym_declarations,
  [903] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(131), 1,
      anon_sym_RPAREN,
    ACTIONS(133), 1,
      sym_pidentifier,
    STATE(78), 1,
      sym_args,
  [916] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(135), 1,
      anon_sym_RPAREN,
    ACTIONS(137), 1,
      anon_sym_COMMA,
    STATE(39), 1,
      aux_sym_args_decl_repeat1,
  [929] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(140), 1,
      anon_sym_RPAREN,
    ACTIONS(142), 1,
      anon_sym_COMMA,
    STATE(39), 1,
      aux_sym_args_decl_repeat1,
  [942] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(144), 1,
      anon_sym_BEGIN,
    ACTIONS(146), 1,
      anon_sym_COMMA,
    STATE(41), 1,
      aux_sym_declarations_repeat1,
  [955] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(52), 1,
      anon_sym_COLON_EQ,
    ACTIONS(54), 1,
      anon_sym_LBRACK,
    ACTIONS(149), 1,
      anon_sym_LPAREN,
  [968] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(151), 1,
      anon_sym_RPAREN,
    ACTIONS(153), 1,
      anon_sym_COMMA,
    STATE(49), 1,
      aux_sym_args_repeat1,
  [981] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(155), 1,
      anon_sym_BEGIN,
    ACTIONS(157), 1,
      anon_sym_COMMA,
    STATE(41), 1,
      aux_sym_declarations_repeat1,
  [994] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(159), 3,
      anon_sym_SEMI,
      anon_sym_THEN,
      anon_sym_DO,
  [1003] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(142), 1,
      anon_sym_COMMA,
    ACTIONS(161), 1,
      anon_sym_RPAREN,
    STATE(40), 1,
      aux_sym_args_decl_repeat1,
  [1016] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(142), 1,
      anon_sym_COMMA,
    ACTIONS(161), 1,
      anon_sym_RPAREN,
    STATE(39), 1,
      aux_sym_args_decl_repeat1,
  [1029] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(153), 1,
      anon_sym_COMMA,
    ACTIONS(163), 1,
      anon_sym_RPAREN,
    STATE(43), 1,
      aux_sym_args_repeat1,
  [1042] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(165), 1,
      anon_sym_RPAREN,
    ACTIONS(167), 1,
      anon_sym_COMMA,
    STATE(49), 1,
      aux_sym_args_repeat1,
  [1055] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(172), 1,
      anon_sym_LBRACK,
    ACTIONS(170), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1066] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(157), 1,
      anon_sym_COMMA,
    ACTIONS(174), 1,
      anon_sym_BEGIN,
    STATE(44), 1,
      aux_sym_declarations_repeat1,
  [1079] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(142), 1,
      anon_sym_COMMA,
    ACTIONS(176), 1,
      anon_sym_RPAREN,
    STATE(47), 1,
      aux_sym_args_decl_repeat1,
  [1092] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(178), 1,
      anon_sym_LBRACK,
    ACTIONS(52), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1103] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(144), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1111] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(180), 2,
      sym_pidentifier,
      sym_num,
  [1119] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(106), 1,
      sym_pidentifier,
    STATE(111), 1,
      sym_identifier,
  [1129] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(135), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1137] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(182), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1145] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(127), 1,
      sym_pidentifier,
    STATE(54), 1,
      sym_declaration,
  [1155] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(184), 1,
      anon_sym_T,
    ACTIONS(186), 1,
      sym_pidentifier,
  [1165] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(188), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1173] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(190), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1181] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(192), 1,
      anon_sym_ELSE,
    ACTIONS(194), 1,
      anon_sym_ENDIF,
  [1191] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(196), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1199] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(198), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1207] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(165), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1215] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(200), 1,
      sym_pidentifier,
    STATE(85), 1,
      sym_proc_head,
  [1225] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(202), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1233] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(62), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1241] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(58), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1249] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(204), 2,
      sym_pidentifier,
      sym_num,
  [1257] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(206), 1,
      anon_sym_SEMI,
  [1264] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(208), 1,
      anon_sym_IS,
  [1271] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(210), 1,
      ts_builtin_sym_end,
  [1278] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(212), 1,
      sym_pidentifier,
  [1285] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(214), 1,
      anon_sym_SEMI,
  [1292] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(216), 1,
      ts_builtin_sym_end,
  [1299] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(218), 1,
      anon_sym_RPAREN,
  [1306] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(220), 1,
      anon_sym_RBRACK,
  [1313] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(222), 1,
      anon_sym_SEMI,
  [1320] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(224), 1,
      anon_sym_COLON,
  [1327] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(226), 1,
      sym_num,
  [1334] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(228), 1,
      ts_builtin_sym_end,
  [1341] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(230), 1,
      anon_sym_END,
  [1348] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(232), 1,
      anon_sym_IS,
  [1355] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(234), 1,
      anon_sym_BEGIN,
  [1362] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(236), 1,
      anon_sym_RPAREN,
  [1369] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(194), 1,
      anon_sym_ENDWHILE,
  [1376] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(194), 1,
      anon_sym_SEMI,
  [1383] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(72), 1,
      anon_sym_END,
  [1390] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(238), 1,
      sym_pidentifier,
  [1397] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(240), 1,
      sym_num,
  [1404] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(242), 1,
      anon_sym_SEMI,
  [1411] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(244), 1,
      sym_pidentifier,
  [1418] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(74), 1,
      anon_sym_END,
  [1425] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(246), 1,
      ts_builtin_sym_end,
  [1432] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(248), 1,
      anon_sym_RBRACK,
  [1439] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(250), 1,
      anon_sym_BEGIN,
  [1446] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(252), 1,
      ts_builtin_sym_end,
  [1453] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(254), 1,
      anon_sym_THEN,
  [1460] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(256), 1,
      anon_sym_LPAREN,
  [1467] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(258), 1,
      ts_builtin_sym_end,
  [1474] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(260), 1,
      anon_sym_SEMI,
  [1481] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(262), 1,
      sym_pidentifier,
  [1488] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(264), 1,
      anon_sym_ENDIF,
  [1495] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(266), 1,
      anon_sym_DO,
  [1502] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(268), 1,
      anon_sym_DO,
  [1509] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(270), 1,
      anon_sym_UNTIL,
  [1516] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(272), 1,
      anon_sym_ENDFOR,
  [1523] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(274), 1,
      anon_sym_FROM,
  [1530] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(276), 1,
      anon_sym_SEMI,
  [1537] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(278), 1,
      anon_sym_END,
  [1544] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(280), 1,
      anon_sym_COLON_EQ,
  [1551] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(282), 1,
      anon_sym_RBRACK,
  [1558] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(284), 1,
      anon_sym_IS,
  [1565] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(286), 1,
      anon_sym_IS,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 45,
  [SMALL_STATE(4)] = 90,
  [SMALL_STATE(5)] = 115,
  [SMALL_STATE(6)] = 138,
  [SMALL_STATE(7)] = 160,
  [SMALL_STATE(8)] = 181,
  [SMALL_STATE(9)] = 222,
  [SMALL_STATE(10)] = 263,
  [SMALL_STATE(11)] = 304,
  [SMALL_STATE(12)] = 345,
  [SMALL_STATE(13)] = 366,
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
  [SMALL_STATE(25)] = 685,
  [SMALL_STATE(26)] = 704,
  [SMALL_STATE(27)] = 723,
  [SMALL_STATE(28)] = 742,
  [SMALL_STATE(29)] = 761,
  [SMALL_STATE(30)] = 777,
  [SMALL_STATE(31)] = 791,
  [SMALL_STATE(32)] = 807,
  [SMALL_STATE(33)] = 823,
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
  [SMALL_STATE(46)] = 1003,
  [SMALL_STATE(47)] = 1016,
  [SMALL_STATE(48)] = 1029,
  [SMALL_STATE(49)] = 1042,
  [SMALL_STATE(50)] = 1055,
  [SMALL_STATE(51)] = 1066,
  [SMALL_STATE(52)] = 1079,
  [SMALL_STATE(53)] = 1092,
  [SMALL_STATE(54)] = 1103,
  [SMALL_STATE(55)] = 1111,
  [SMALL_STATE(56)] = 1119,
  [SMALL_STATE(57)] = 1129,
  [SMALL_STATE(58)] = 1137,
  [SMALL_STATE(59)] = 1145,
  [SMALL_STATE(60)] = 1155,
  [SMALL_STATE(61)] = 1165,
  [SMALL_STATE(62)] = 1173,
  [SMALL_STATE(63)] = 1181,
  [SMALL_STATE(64)] = 1191,
  [SMALL_STATE(65)] = 1199,
  [SMALL_STATE(66)] = 1207,
  [SMALL_STATE(67)] = 1215,
  [SMALL_STATE(68)] = 1225,
  [SMALL_STATE(69)] = 1233,
  [SMALL_STATE(70)] = 1241,
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
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [9] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_commands, 1, 0, 0),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [13] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_commands, 1, 0, 0),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [27] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0),
  [29] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(25),
  [32] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0),
  [34] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(26),
  [37] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(17),
  [40] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(104),
  [43] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(56),
  [46] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(32),
  [49] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 0), SHIFT_REPEAT(42),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 1, 0, 0),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [56] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_identifier, 1, 0, 0),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 4, 0, 0),
  [60] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_identifier, 4, 0, 0),
  [62] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 1, 0, 0),
  [64] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_value, 1, 0, 0),
  [66] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 9, 0, 0),
  [68] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 9, 0, 0),
  [70] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [72] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [74] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [76] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [78] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 2, 0, 0),
  [80] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 2, 0, 0),
  [82] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 5, 0, 0),
  [84] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 5, 0, 0),
  [86] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 3, 0, 0),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3, 0, 0),
  [90] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 4, 0, 0),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 4, 0, 0),
  [94] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 7, 0, 0),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 7, 0, 0),
  [98] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [100] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [102] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 1, 0, 0),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [106] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [108] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [110] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [112] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [114] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [116] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_all_repeat1, 2, 0, 0), SHIFT_REPEAT(67),
  [119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_program_all_repeat1, 2, 0, 0),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [127] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [129] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [131] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [133] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 0),
  [137] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 0), SHIFT_REPEAT(60),
  [140] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 3, 0, 0),
  [142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [144] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 0),
  [146] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 0), SHIFT_REPEAT(59),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [151] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args, 2, 0, 0),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [155] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declarations, 2, 0, 0),
  [157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [159] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_condition, 3, 0, 0),
  [161] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 2, 0, 0),
  [163] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args, 1, 0, 0),
  [165] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 0),
  [167] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 0), SHIFT_REPEAT(91),
  [170] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declaration, 1, 0, 0),
  [172] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [174] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declarations, 1, 0, 0),
  [176] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 1, 0, 0),
  [178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [180] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [182] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 6, 0, 0),
  [184] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [186] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [188] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 3, 0, 0),
  [190] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 7, 0, 0),
  [192] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [194] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [196] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [198] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 5, 0, 0),
  [200] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [202] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declaration, 6, 0, 0),
  [204] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 3, 0, 0),
  [208] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_head, 3, 0, 0),
  [210] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 5, 0, 0),
  [212] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_call, 3, 0, 0),
  [216] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program_all, 2, 0, 0),
  [218] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [220] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [224] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [228] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 6, 0, 0),
  [230] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [232] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [234] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [236] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [238] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [240] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_call, 4, 0, 0),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [246] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [252] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 4, 0, 0),
  [254] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [256] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [258] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program_all, 1, 0, 0),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [262] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [266] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [270] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [272] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [274] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [276] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [284] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [286] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_head, 4, 0, 0),
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
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_word_token,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
