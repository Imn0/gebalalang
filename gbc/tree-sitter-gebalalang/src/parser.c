#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 126
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 66
#define ALIAS_COUNT 0
#define TOKEN_COUNT 46
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 26
#define MAX_ALIAS_SEQUENCE_LENGTH 9
#define PRODUCTION_ID_COUNT 41

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

enum ts_field_identifiers {
  field_argument = 1,
  field_arguments = 2,
  field_body = 3,
  field_command = 4,
  field_commands = 5,
  field_condition = 6,
  field_declaration = 7,
  field_declarations = 8,
  field_else_branch = 9,
  field_end = 10,
  field_expression = 11,
  field_header = 12,
  field_identifier = 13,
  field_index = 14,
  field_left = 15,
  field_main_program = 16,
  field_name = 17,
  field_number = 18,
  field_procedure_call = 19,
  field_procedures = 20,
  field_right = 21,
  field_start = 22,
  field_target = 23,
  field_then_branch = 24,
  field_value = 25,
  field_variable = 26,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_argument] = "argument",
  [field_arguments] = "arguments",
  [field_body] = "body",
  [field_command] = "command",
  [field_commands] = "commands",
  [field_condition] = "condition",
  [field_declaration] = "declaration",
  [field_declarations] = "declarations",
  [field_else_branch] = "else_branch",
  [field_end] = "end",
  [field_expression] = "expression",
  [field_header] = "header",
  [field_identifier] = "identifier",
  [field_index] = "index",
  [field_left] = "left",
  [field_main_program] = "main_program",
  [field_name] = "name",
  [field_number] = "number",
  [field_procedure_call] = "procedure_call",
  [field_procedures] = "procedures",
  [field_right] = "right",
  [field_start] = "start",
  [field_target] = "target",
  [field_then_branch] = "then_branch",
  [field_value] = "value",
  [field_variable] = "variable",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
  [3] = {.index = 3, .length = 1},
  [4] = {.index = 4, .length = 1},
  [5] = {.index = 5, .length = 1},
  [6] = {.index = 6, .length = 1},
  [7] = {.index = 7, .length = 1},
  [8] = {.index = 8, .length = 1},
  [9] = {.index = 9, .length = 2},
  [10] = {.index = 11, .length = 2},
  [11] = {.index = 13, .length = 2},
  [12] = {.index = 15, .length = 2},
  [13] = {.index = 17, .length = 1},
  [14] = {.index = 18, .length = 1},
  [15] = {.index = 19, .length = 1},
  [16] = {.index = 20, .length = 1},
  [17] = {.index = 21, .length = 2},
  [18] = {.index = 23, .length = 1},
  [19] = {.index = 24, .length = 1},
  [20] = {.index = 25, .length = 2},
  [21] = {.index = 27, .length = 3},
  [22] = {.index = 30, .length = 1},
  [23] = {.index = 31, .length = 2},
  [24] = {.index = 33, .length = 2},
  [25] = {.index = 35, .length = 2},
  [26] = {.index = 37, .length = 1},
  [27] = {.index = 38, .length = 1},
  [28] = {.index = 39, .length = 1},
  [29] = {.index = 40, .length = 2},
  [30] = {.index = 42, .length = 2},
  [31] = {.index = 44, .length = 3},
  [32] = {.index = 47, .length = 2},
  [33] = {.index = 49, .length = 2},
  [34] = {.index = 51, .length = 2},
  [35] = {.index = 53, .length = 2},
  [36] = {.index = 55, .length = 2},
  [37] = {.index = 57, .length = 2},
  [38] = {.index = 59, .length = 3},
  [39] = {.index = 62, .length = 3},
  [40] = {.index = 65, .length = 4},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_main_program, 0},
  [1] =
    {field_main_program, 1},
    {field_procedures, 0},
  [3] =
    {field_identifier, 0},
  [4] =
    {field_declaration, 0},
  [5] =
    {field_name, 0},
  [6] =
    {field_argument, 0},
  [7] =
    {field_command, 0},
  [8] =
    {field_command, 0, .inherited = true},
  [9] =
    {field_declaration, 0},
    {field_declaration, 1, .inherited = true},
  [11] =
    {field_argument, 0},
    {field_argument, 1},
  [13] =
    {field_argument, 0},
    {field_argument, 1, .inherited = true},
  [15] =
    {field_arguments, 2},
    {field_name, 0},
  [17] =
    {field_header, 1},
  [18] =
    {field_number, 0},
  [19] =
    {field_commands, 3},
  [20] =
    {field_procedure_call, 0},
  [21] =
    {field_command, 0, .inherited = true},
    {field_command, 1, .inherited = true},
  [23] =
    {field_declarations, 2},
  [24] =
    {field_declaration, 1},
  [25] =
    {field_declaration, 0, .inherited = true},
    {field_declaration, 1, .inherited = true},
  [27] =
    {field_argument, 0},
    {field_argument, 1},
    {field_argument, 2, .inherited = true},
  [30] =
    {field_argument, 1},
  [31] =
    {field_argument, 0, .inherited = true},
    {field_argument, 1, .inherited = true},
  [33] =
    {field_commands, 4},
    {field_header, 1},
  [35] =
    {field_declarations, 3},
    {field_header, 1},
  [37] =
    {field_target, 1},
  [38] =
    {field_value, 1},
  [39] =
    {field_value, 0},
  [40] =
    {field_commands, 4},
    {field_declarations, 2},
  [42] =
    {field_argument, 1},
    {field_argument, 2},
  [44] =
    {field_commands, 5},
    {field_declarations, 3},
    {field_header, 1},
  [47] =
    {field_left, 0},
    {field_right, 2},
  [49] =
    {field_index, 2},
    {field_name, 0},
  [51] =
    {field_expression, 2},
    {field_target, 0},
  [53] =
    {field_condition, 1},
    {field_then_branch, 3},
  [55] =
    {field_body, 3},
    {field_condition, 1},
  [57] =
    {field_body, 1},
    {field_condition, 3},
  [59] =
    {field_end, 4},
    {field_identifier, 0},
    {field_start, 2},
  [62] =
    {field_condition, 1},
    {field_else_branch, 5},
    {field_then_branch, 3},
  [65] =
    {field_body, 7},
    {field_end, 5},
    {field_start, 3},
    {field_variable, 1},
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
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 4,
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
  [69] = 69,
  [70] = 70,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 6,
  [76] = 7,
  [77] = 5,
  [78] = 71,
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
  [115] = 115,
  [116] = 116,
  [117] = 117,
  [118] = 118,
  [119] = 119,
  [120] = 120,
  [121] = 121,
  [122] = 122,
  [123] = 85,
  [124] = 124,
  [125] = 125,
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
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(136);
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
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(136);
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
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(136);
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
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(136);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(sym_word_token);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(135);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(sym_pidentifier);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(136);
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
  [7] = {.lex_state = 1},
  [8] = {.lex_state = 2},
  [9] = {.lex_state = 3},
  [10] = {.lex_state = 3},
  [11] = {.lex_state = 2},
  [12] = {.lex_state = 2},
  [13] = {.lex_state = 3},
  [14] = {.lex_state = 2},
  [15] = {.lex_state = 2},
  [16] = {.lex_state = 2},
  [17] = {.lex_state = 2},
  [18] = {.lex_state = 2},
  [19] = {.lex_state = 2},
  [20] = {.lex_state = 2},
  [21] = {.lex_state = 3},
  [22] = {.lex_state = 2},
  [23] = {.lex_state = 2},
  [24] = {.lex_state = 2},
  [25] = {.lex_state = 2},
  [26] = {.lex_state = 2},
  [27] = {.lex_state = 0},
  [28] = {.lex_state = 0},
  [29] = {.lex_state = 1},
  [30] = {.lex_state = 2},
  [31] = {.lex_state = 2},
  [32] = {.lex_state = 2},
  [33] = {.lex_state = 2},
  [34] = {.lex_state = 2},
  [35] = {.lex_state = 2},
  [36] = {.lex_state = 2},
  [37] = {.lex_state = 2},
  [38] = {.lex_state = 2},
  [39] = {.lex_state = 1},
  [40] = {.lex_state = 2},
  [41] = {.lex_state = 2},
  [42] = {.lex_state = 2},
  [43] = {.lex_state = 2},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 2},
  [46] = {.lex_state = 2},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 2},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 1},
  [55] = {.lex_state = 2},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 1},
  [58] = {.lex_state = 1},
  [59] = {.lex_state = 1},
  [60] = {.lex_state = 1},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 2},
  [63] = {.lex_state = 2},
  [64] = {.lex_state = 2},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 2},
  [67] = {.lex_state = 2},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 4},
  [70] = {.lex_state = 2},
  [71] = {.lex_state = 2},
  [72] = {.lex_state = 1},
  [73] = {.lex_state = 1},
  [74] = {.lex_state = 1},
  [75] = {.lex_state = 1},
  [76] = {.lex_state = 1},
  [77] = {.lex_state = 1},
  [78] = {.lex_state = 2},
  [79] = {.lex_state = 2},
  [80] = {.lex_state = 1},
  [81] = {.lex_state = 3},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 1},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 2},
  [88] = {.lex_state = 2},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 1},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 2},
  [94] = {.lex_state = 4},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 2},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 1},
  [100] = {.lex_state = 1},
  [101] = {.lex_state = 0},
  [102] = {.lex_state = 2},
  [103] = {.lex_state = 0},
  [104] = {.lex_state = 0},
  [105] = {.lex_state = 0},
  [106] = {.lex_state = 3},
  [107] = {.lex_state = 1},
  [108] = {.lex_state = 2},
  [109] = {.lex_state = 0},
  [110] = {.lex_state = 2},
  [111] = {.lex_state = 0},
  [112] = {.lex_state = 0},
  [113] = {.lex_state = 4},
  [114] = {.lex_state = 1},
  [115] = {.lex_state = 1},
  [116] = {.lex_state = 1},
  [117] = {.lex_state = 4},
  [118] = {.lex_state = 0},
  [119] = {.lex_state = 3},
  [120] = {.lex_state = 3},
  [121] = {.lex_state = 2},
  [122] = {.lex_state = 2},
  [123] = {.lex_state = 0},
  [124] = {.lex_state = 0},
  [125] = {.lex_state = 0},
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
    [sym_program_all] = STATE(118),
    [sym_procedure] = STATE(29),
    [sym_main] = STATE(101),
    [aux_sym_program_all_repeat1] = STATE(29),
    [anon_sym_PROCEDURE] = ACTIONS(5),
    [anon_sym_PROGRAM] = ACTIONS(7),
    [sym__comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 14,
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
    STATE(3), 1,
      aux_sym_commands_repeat1,
    STATE(12), 1,
      sym_command,
    STATE(96), 1,
      sym_proc_call,
    STATE(100), 1,
      sym_identifier,
    ACTIONS(13), 5,
      anon_sym_ELSE,
      anon_sym_ENDIF,
      anon_sym_ENDWHILE,
      anon_sym_UNTIL,
      anon_sym_ENDFOR,
  [47] = 14,
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
    STATE(3), 1,
      aux_sym_commands_repeat1,
    STATE(12), 1,
      sym_command,
    STATE(96), 1,
      sym_proc_call,
    STATE(100), 1,
      sym_identifier,
    ACTIONS(32), 5,
      anon_sym_ELSE,
      anon_sym_ENDIF,
      anon_sym_ENDWHILE,
      anon_sym_UNTIL,
      anon_sym_ENDFOR,
  [94] = 4,
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
  [119] = 3,
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
  [142] = 3,
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
  [164] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(68), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(66), 12,
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
  [186] = 3,
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
  [207] = 14,
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
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(12), 1,
      sym_command,
    STATE(96), 1,
      sym_proc_call,
    STATE(100), 1,
      sym_identifier,
    STATE(120), 1,
      sym_commands,
  [250] = 14,
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
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(12), 1,
      sym_command,
    STATE(96), 1,
      sym_proc_call,
    STATE(100), 1,
      sym_identifier,
    STATE(119), 1,
      sym_commands,
  [293] = 3,
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
  [314] = 3,
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
  [335] = 14,
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
    ACTIONS(86), 1,
      anon_sym_END,
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(12), 1,
      sym_command,
    STATE(81), 1,
      sym_commands,
    STATE(96), 1,
      sym_proc_call,
    STATE(100), 1,
      sym_identifier,
  [378] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(88), 1,
      anon_sym_END,
    ACTIONS(90), 12,
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
  [399] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(92), 1,
      anon_sym_END,
    ACTIONS(94), 12,
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
  [420] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(96), 1,
      anon_sym_END,
    ACTIONS(98), 12,
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
  [441] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(100), 1,
      anon_sym_END,
    ACTIONS(102), 12,
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
  [462] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(104), 1,
      anon_sym_END,
    ACTIONS(106), 12,
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
  [483] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(108), 1,
      anon_sym_END,
    ACTIONS(110), 12,
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
  [504] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(112), 1,
      anon_sym_END,
    ACTIONS(114), 12,
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
  [525] = 14,
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
    ACTIONS(116), 1,
      anon_sym_END,
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(12), 1,
      sym_command,
    STATE(96), 1,
      sym_proc_call,
    STATE(100), 1,
      sym_identifier,
    STATE(106), 1,
      sym_commands,
  [568] = 13,
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
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(12), 1,
      sym_command,
    STATE(87), 1,
      sym_commands,
    STATE(96), 1,
      sym_proc_call,
    STATE(100), 1,
      sym_identifier,
  [608] = 13,
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
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(12), 1,
      sym_command,
    STATE(69), 1,
      sym_commands,
    STATE(96), 1,
      sym_proc_call,
    STATE(100), 1,
      sym_identifier,
  [648] = 13,
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
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(12), 1,
      sym_command,
    STATE(94), 1,
      sym_commands,
    STATE(96), 1,
      sym_proc_call,
    STATE(100), 1,
      sym_identifier,
  [688] = 13,
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
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(12), 1,
      sym_command,
    STATE(96), 1,
      sym_proc_call,
    STATE(100), 1,
      sym_identifier,
    STATE(113), 1,
      sym_commands,
  [728] = 13,
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
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(12), 1,
      sym_command,
    STATE(96), 1,
      sym_proc_call,
    STATE(100), 1,
      sym_identifier,
    STATE(117), 1,
      sym_commands,
  [768] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(120), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(118), 4,
      anon_sym_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
  [782] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(122), 1,
      anon_sym_SEMI,
    ACTIONS(124), 5,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [796] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(5), 1,
      anon_sym_PROCEDURE,
    ACTIONS(7), 1,
      anon_sym_PROGRAM,
    STATE(124), 1,
      sym_main,
    STATE(39), 2,
      sym_procedure,
      aux_sym_program_all_repeat1,
  [813] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(126), 1,
      sym_pidentifier,
    ACTIONS(128), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(27), 1,
      sym_value,
    STATE(83), 1,
      sym_condition,
  [832] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(126), 1,
      sym_pidentifier,
    ACTIONS(128), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(28), 1,
      sym_value,
    STATE(86), 1,
      sym_expression,
  [851] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(126), 1,
      sym_pidentifier,
    ACTIONS(128), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(27), 1,
      sym_value,
    STATE(99), 1,
      sym_condition,
  [870] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(126), 1,
      sym_pidentifier,
    ACTIONS(128), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(27), 1,
      sym_value,
    STATE(95), 1,
      sym_condition,
  [889] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(126), 1,
      sym_pidentifier,
    ACTIONS(128), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(114), 1,
      sym_value,
  [905] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(130), 1,
      sym_pidentifier,
    ACTIONS(132), 1,
      sym_num,
    STATE(73), 1,
      sym_value,
    STATE(76), 1,
      sym_identifier,
  [921] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(126), 1,
      sym_pidentifier,
    ACTIONS(128), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(54), 1,
      sym_value,
  [937] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(126), 1,
      sym_pidentifier,
    ACTIONS(128), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(111), 1,
      sym_value,
  [953] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(134), 1,
      anon_sym_RPAREN,
    ACTIONS(136), 1,
      anon_sym_T,
    ACTIONS(138), 1,
      sym_pidentifier,
    STATE(104), 1,
      sym_args_decl,
  [969] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(140), 1,
      anon_sym_PROCEDURE,
    ACTIONS(143), 1,
      anon_sym_PROGRAM,
    STATE(39), 2,
      sym_procedure,
      aux_sym_program_all_repeat1,
  [983] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(145), 1,
      anon_sym_BEGIN,
    ACTIONS(147), 1,
      sym_pidentifier,
    STATE(45), 1,
      sym_declaration,
    STATE(122), 1,
      sym_declarations,
  [999] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(147), 1,
      sym_pidentifier,
    ACTIONS(149), 1,
      anon_sym_BEGIN,
    STATE(45), 1,
      sym_declaration,
    STATE(108), 1,
      sym_declarations,
  [1015] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(126), 1,
      sym_pidentifier,
    ACTIONS(128), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(92), 1,
      sym_value,
  [1031] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(153), 1,
      anon_sym_LBRACK,
    ACTIONS(151), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1042] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(155), 1,
      anon_sym_RPAREN,
    ACTIONS(157), 1,
      anon_sym_COMMA,
    STATE(49), 1,
      aux_sym_args_decl_repeat1,
  [1055] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(159), 1,
      anon_sym_BEGIN,
    ACTIONS(161), 1,
      anon_sym_COMMA,
    STATE(48), 1,
      aux_sym_declarations_repeat1,
  [1068] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(163), 1,
      anon_sym_BEGIN,
    ACTIONS(165), 1,
      anon_sym_COMMA,
    STATE(46), 1,
      aux_sym_declarations_repeat1,
  [1081] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(157), 1,
      anon_sym_COMMA,
    ACTIONS(168), 1,
      anon_sym_RPAREN,
    STATE(52), 1,
      aux_sym_args_decl_repeat1,
  [1094] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(161), 1,
      anon_sym_COMMA,
    ACTIONS(170), 1,
      anon_sym_BEGIN,
    STATE(46), 1,
      aux_sym_declarations_repeat1,
  [1107] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(172), 1,
      anon_sym_RPAREN,
    ACTIONS(174), 1,
      anon_sym_COMMA,
    STATE(49), 1,
      aux_sym_args_decl_repeat1,
  [1120] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(157), 1,
      anon_sym_COMMA,
    ACTIONS(177), 1,
      anon_sym_RPAREN,
    STATE(44), 1,
      aux_sym_args_decl_repeat1,
  [1133] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(179), 1,
      anon_sym_RPAREN,
    ACTIONS(181), 1,
      anon_sym_COMMA,
    STATE(53), 1,
      aux_sym_args_repeat1,
  [1146] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(157), 1,
      anon_sym_COMMA,
    ACTIONS(183), 1,
      anon_sym_RPAREN,
    STATE(49), 1,
      aux_sym_args_decl_repeat1,
  [1159] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(181), 1,
      anon_sym_COMMA,
    ACTIONS(185), 1,
      anon_sym_RPAREN,
    STATE(56), 1,
      aux_sym_args_repeat1,
  [1172] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(187), 3,
      anon_sym_SEMI,
      anon_sym_THEN,
      anon_sym_DO,
  [1181] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(189), 1,
      anon_sym_RPAREN,
    ACTIONS(191), 1,
      sym_pidentifier,
    STATE(84), 1,
      sym_args,
  [1194] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(193), 1,
      anon_sym_RPAREN,
    ACTIONS(195), 1,
      anon_sym_COMMA,
    STATE(56), 1,
      aux_sym_args_repeat1,
  [1207] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(52), 1,
      anon_sym_COLON_EQ,
    ACTIONS(54), 1,
      anon_sym_LBRACK,
    ACTIONS(198), 1,
      anon_sym_LPAREN,
  [1220] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(200), 1,
      anon_sym_LBRACK,
    ACTIONS(52), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1231] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(202), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1239] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(204), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1247] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(206), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1255] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(208), 1,
      anon_sym_T,
    ACTIONS(210), 1,
      sym_pidentifier,
  [1265] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(212), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1273] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(147), 1,
      sym_pidentifier,
    STATE(63), 1,
      sym_declaration,
  [1283] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(214), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1291] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(126), 1,
      sym_pidentifier,
    STATE(91), 1,
      sym_identifier,
  [1301] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(216), 1,
      sym_pidentifier,
    STATE(115), 1,
      sym_proc_head,
  [1311] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(218), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1319] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(220), 1,
      anon_sym_ELSE,
    ACTIONS(222), 1,
      anon_sym_ENDIF,
  [1329] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(224), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1337] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(226), 2,
      sym_pidentifier,
      sym_num,
  [1345] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(228), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1353] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(230), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1361] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(232), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1369] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(62), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1377] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(66), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1385] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(58), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1393] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(234), 2,
      sym_pidentifier,
      sym_num,
  [1401] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(236), 1,
      anon_sym_COLON,
  [1408] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(238), 1,
      anon_sym_IS,
  [1415] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(240), 1,
      anon_sym_END,
  [1422] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(242), 1,
      anon_sym_SEMI,
  [1429] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(244), 1,
      anon_sym_DO,
  [1436] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(246), 1,
      anon_sym_RPAREN,
  [1443] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(248), 1,
      anon_sym_RBRACK,
  [1450] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(250), 1,
      anon_sym_SEMI,
  [1457] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(252), 1,
      anon_sym_UNTIL,
  [1464] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(254), 1,
      sym_num,
  [1471] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(256), 1,
      ts_builtin_sym_end,
  [1478] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(258), 1,
      anon_sym_FROM,
  [1485] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(260), 1,
      anon_sym_SEMI,
  [1492] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(262), 1,
      anon_sym_SEMI,
  [1499] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(264), 1,
      sym_pidentifier,
  [1506] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(266), 1,
      anon_sym_ENDWHILE,
  [1513] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(268), 1,
      anon_sym_SEMI,
  [1520] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(270), 1,
      anon_sym_SEMI,
  [1527] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(272), 1,
      sym_pidentifier,
  [1534] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(274), 1,
      ts_builtin_sym_end,
  [1541] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(276), 1,
      anon_sym_THEN,
  [1548] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(278), 1,
      anon_sym_COLON_EQ,
  [1555] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(280), 1,
      ts_builtin_sym_end,
  [1562] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(282), 1,
      sym_num,
  [1569] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(284), 1,
      anon_sym_RBRACK,
  [1576] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(286), 1,
      anon_sym_RPAREN,
  [1583] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(288), 1,
      ts_builtin_sym_end,
  [1590] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(290), 1,
      anon_sym_END,
  [1597] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(292), 1,
      anon_sym_IS,
  [1604] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(294), 1,
      anon_sym_BEGIN,
  [1611] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(296), 1,
      ts_builtin_sym_end,
  [1618] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(298), 1,
      sym_pidentifier,
  [1625] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(300), 1,
      anon_sym_SEMI,
  [1632] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(302), 1,
      anon_sym_LPAREN,
  [1639] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(304), 1,
      anon_sym_ENDIF,
  [1646] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(306), 1,
      anon_sym_DO,
  [1653] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(308), 1,
      anon_sym_IS,
  [1660] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(310), 1,
      anon_sym_IS,
  [1667] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(312), 1,
      anon_sym_ENDFOR,
  [1674] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(314), 1,
      ts_builtin_sym_end,
  [1681] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(316), 1,
      anon_sym_END,
  [1688] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(318), 1,
      anon_sym_END,
  [1695] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(320), 1,
      sym_pidentifier,
  [1702] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(322), 1,
      anon_sym_BEGIN,
  [1709] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(324), 1,
      anon_sym_RBRACK,
  [1716] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(326), 1,
      ts_builtin_sym_end,
  [1723] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(328), 1,
      anon_sym_SEMI,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 47,
  [SMALL_STATE(4)] = 94,
  [SMALL_STATE(5)] = 119,
  [SMALL_STATE(6)] = 142,
  [SMALL_STATE(7)] = 164,
  [SMALL_STATE(8)] = 186,
  [SMALL_STATE(9)] = 207,
  [SMALL_STATE(10)] = 250,
  [SMALL_STATE(11)] = 293,
  [SMALL_STATE(12)] = 314,
  [SMALL_STATE(13)] = 335,
  [SMALL_STATE(14)] = 378,
  [SMALL_STATE(15)] = 399,
  [SMALL_STATE(16)] = 420,
  [SMALL_STATE(17)] = 441,
  [SMALL_STATE(18)] = 462,
  [SMALL_STATE(19)] = 483,
  [SMALL_STATE(20)] = 504,
  [SMALL_STATE(21)] = 525,
  [SMALL_STATE(22)] = 568,
  [SMALL_STATE(23)] = 608,
  [SMALL_STATE(24)] = 648,
  [SMALL_STATE(25)] = 688,
  [SMALL_STATE(26)] = 728,
  [SMALL_STATE(27)] = 768,
  [SMALL_STATE(28)] = 782,
  [SMALL_STATE(29)] = 796,
  [SMALL_STATE(30)] = 813,
  [SMALL_STATE(31)] = 832,
  [SMALL_STATE(32)] = 851,
  [SMALL_STATE(33)] = 870,
  [SMALL_STATE(34)] = 889,
  [SMALL_STATE(35)] = 905,
  [SMALL_STATE(36)] = 921,
  [SMALL_STATE(37)] = 937,
  [SMALL_STATE(38)] = 953,
  [SMALL_STATE(39)] = 969,
  [SMALL_STATE(40)] = 983,
  [SMALL_STATE(41)] = 999,
  [SMALL_STATE(42)] = 1015,
  [SMALL_STATE(43)] = 1031,
  [SMALL_STATE(44)] = 1042,
  [SMALL_STATE(45)] = 1055,
  [SMALL_STATE(46)] = 1068,
  [SMALL_STATE(47)] = 1081,
  [SMALL_STATE(48)] = 1094,
  [SMALL_STATE(49)] = 1107,
  [SMALL_STATE(50)] = 1120,
  [SMALL_STATE(51)] = 1133,
  [SMALL_STATE(52)] = 1146,
  [SMALL_STATE(53)] = 1159,
  [SMALL_STATE(54)] = 1172,
  [SMALL_STATE(55)] = 1181,
  [SMALL_STATE(56)] = 1194,
  [SMALL_STATE(57)] = 1207,
  [SMALL_STATE(58)] = 1220,
  [SMALL_STATE(59)] = 1231,
  [SMALL_STATE(60)] = 1239,
  [SMALL_STATE(61)] = 1247,
  [SMALL_STATE(62)] = 1255,
  [SMALL_STATE(63)] = 1265,
  [SMALL_STATE(64)] = 1273,
  [SMALL_STATE(65)] = 1283,
  [SMALL_STATE(66)] = 1291,
  [SMALL_STATE(67)] = 1301,
  [SMALL_STATE(68)] = 1311,
  [SMALL_STATE(69)] = 1319,
  [SMALL_STATE(70)] = 1329,
  [SMALL_STATE(71)] = 1337,
  [SMALL_STATE(72)] = 1345,
  [SMALL_STATE(73)] = 1353,
  [SMALL_STATE(74)] = 1361,
  [SMALL_STATE(75)] = 1369,
  [SMALL_STATE(76)] = 1377,
  [SMALL_STATE(77)] = 1385,
  [SMALL_STATE(78)] = 1393,
  [SMALL_STATE(79)] = 1401,
  [SMALL_STATE(80)] = 1408,
  [SMALL_STATE(81)] = 1415,
  [SMALL_STATE(82)] = 1422,
  [SMALL_STATE(83)] = 1429,
  [SMALL_STATE(84)] = 1436,
  [SMALL_STATE(85)] = 1443,
  [SMALL_STATE(86)] = 1450,
  [SMALL_STATE(87)] = 1457,
  [SMALL_STATE(88)] = 1464,
  [SMALL_STATE(89)] = 1471,
  [SMALL_STATE(90)] = 1478,
  [SMALL_STATE(91)] = 1485,
  [SMALL_STATE(92)] = 1492,
  [SMALL_STATE(93)] = 1499,
  [SMALL_STATE(94)] = 1506,
  [SMALL_STATE(95)] = 1513,
  [SMALL_STATE(96)] = 1520,
  [SMALL_STATE(97)] = 1527,
  [SMALL_STATE(98)] = 1534,
  [SMALL_STATE(99)] = 1541,
  [SMALL_STATE(100)] = 1548,
  [SMALL_STATE(101)] = 1555,
  [SMALL_STATE(102)] = 1562,
  [SMALL_STATE(103)] = 1569,
  [SMALL_STATE(104)] = 1576,
  [SMALL_STATE(105)] = 1583,
  [SMALL_STATE(106)] = 1590,
  [SMALL_STATE(107)] = 1597,
  [SMALL_STATE(108)] = 1604,
  [SMALL_STATE(109)] = 1611,
  [SMALL_STATE(110)] = 1618,
  [SMALL_STATE(111)] = 1625,
  [SMALL_STATE(112)] = 1632,
  [SMALL_STATE(113)] = 1639,
  [SMALL_STATE(114)] = 1646,
  [SMALL_STATE(115)] = 1653,
  [SMALL_STATE(116)] = 1660,
  [SMALL_STATE(117)] = 1667,
  [SMALL_STATE(118)] = 1674,
  [SMALL_STATE(119)] = 1681,
  [SMALL_STATE(120)] = 1688,
  [SMALL_STATE(121)] = 1695,
  [SMALL_STATE(122)] = 1702,
  [SMALL_STATE(123)] = 1709,
  [SMALL_STATE(124)] = 1716,
  [SMALL_STATE(125)] = 1723,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [9] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_commands, 1, 0, 8),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [13] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_commands, 1, 0, 8),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [27] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17),
  [29] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(32),
  [32] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17),
  [34] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(30),
  [37] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(22),
  [40] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(121),
  [43] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(66),
  [46] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(42),
  [49] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(57),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 1, 0, 5),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [56] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_identifier, 1, 0, 5),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 4, 0, 33),
  [60] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_identifier, 4, 0, 33),
  [62] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 1, 0, 14),
  [64] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_value, 1, 0, 14),
  [66] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 1, 0, 3),
  [68] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_value, 1, 0, 3),
  [70] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 9, 0, 40),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 9, 0, 40),
  [74] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [76] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [78] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 2, 0, 16),
  [80] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 2, 0, 16),
  [82] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_commands_repeat1, 1, 0, 7),
  [84] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 1, 0, 7),
  [86] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [88] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 3, 0, 26),
  [90] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3, 0, 26),
  [92] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 3, 0, 27),
  [94] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3, 0, 27),
  [96] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 5, 0, 35),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 5, 0, 35),
  [100] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 5, 0, 36),
  [102] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 5, 0, 36),
  [104] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 4, 0, 34),
  [106] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 4, 0, 34),
  [108] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 7, 0, 39),
  [110] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 7, 0, 39),
  [112] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 5, 0, 37),
  [114] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 5, 0, 37),
  [116] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [118] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [120] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [122] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 1, 0, 28),
  [124] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [126] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [128] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [130] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [134] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [140] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_all_repeat1, 2, 0, 0), SHIFT_REPEAT(67),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_program_all_repeat1, 2, 0, 0),
  [145] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [147] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [151] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declaration, 1, 0, 3),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [155] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 3, 0, 21),
  [157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [159] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declarations, 1, 0, 4),
  [161] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [163] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 20),
  [165] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 20), SHIFT_REPEAT(64),
  [168] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 1, 0, 6),
  [170] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declarations, 2, 0, 9),
  [172] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 23),
  [174] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 23), SHIFT_REPEAT(62),
  [177] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 2, 0, 10),
  [179] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args, 1, 0, 6),
  [181] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [183] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 2, 0, 11),
  [185] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args, 2, 0, 11),
  [187] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_condition, 3, 0, 32),
  [189] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [191] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [193] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 23),
  [195] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 23), SHIFT_REPEAT(97),
  [198] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [200] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [202] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 7, 0, 31),
  [204] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 5, 0, 13),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 22),
  [208] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [210] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [212] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 19),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 3, 0, 30),
  [216] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [218] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 22),
  [220] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [224] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declaration, 6, 0, 38),
  [226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [228] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 6, 0, 24),
  [230] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [232] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 6, 0, 25),
  [234] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [236] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [238] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_head, 3, 0, 5),
  [240] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_call, 3, 0, 5),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [252] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [254] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [256] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 6, 0, 29),
  [258] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [262] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [266] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [270] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [272] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [274] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 5, 0, 15),
  [276] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [280] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program_all, 1, 0, 1),
  [282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [284] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [286] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [288] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 5, 0, 18),
  [290] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [292] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [294] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [296] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 4, 0, 0),
  [298] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [300] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 3, 0, 32),
  [302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [304] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [306] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [308] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [310] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_head, 4, 0, 12),
  [312] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [314] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [316] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [318] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [320] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [324] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [326] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program_all, 2, 0, 2),
  [328] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_call, 4, 0, 12),
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
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
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
