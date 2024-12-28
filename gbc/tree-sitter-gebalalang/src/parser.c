#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 129
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 67
#define ALIAS_COUNT 1
#define TOKEN_COUNT 46
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 28
#define MAX_ALIAS_SEQUENCE_LENGTH 9
#define PRODUCTION_ID_COUNT 40

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
  sym_arg_decl = 56,
  sym_args = 57,
  sym_expression = 58,
  sym_condition = 59,
  sym_value = 60,
  sym_identifier = 61,
  aux_sym_program_all_repeat1 = 62,
  aux_sym_commands_repeat1 = 63,
  aux_sym_declarations_repeat1 = 64,
  aux_sym_args_decl_repeat1 = 65,
  aux_sym_args_repeat1 = 66,
  anon_alias_sym_if_command = 67,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_word_token] = "word_token",
  [anon_sym_PROCEDURE] = "PROCEDURE",
  [anon_sym_IS] = "IS",
  [anon_sym_BEGIN] = "BEGIN",
  [anon_sym_END] = "END",
  [anon_sym_PROGRAM] = "PROGRAM",
  [anon_sym_COLON_EQ] = "assignment_command",
  [anon_sym_SEMI] = "assignment_command",
  [anon_sym_IF] = "if_else_command",
  [anon_sym_THEN] = "if_else_command",
  [anon_sym_ELSE] = "if_else_command",
  [anon_sym_ENDIF] = "if_else_command",
  [anon_sym_WHILE] = "while_command",
  [anon_sym_DO] = "while_command",
  [anon_sym_ENDWHILE] = "while_command",
  [anon_sym_REPEAT] = "repeat_until_command",
  [anon_sym_UNTIL] = "repeat_until_command",
  [anon_sym_FOR] = "for_to_command",
  [anon_sym_FROM] = "for_to_command",
  [anon_sym_TO] = "for_to_command",
  [anon_sym_ENDFOR] = "for_to_command",
  [anon_sym_DOWNTO] = "for_downto_command",
  [anon_sym_READ] = "read_command",
  [anon_sym_WRITE] = "write_command",
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
  [sym_proc_call] = "procedure_call_command",
  [sym_declarations] = "declarations",
  [sym_declaration] = "declaration",
  [sym_args_decl] = "args_decl",
  [sym_arg_decl] = "arg_decl",
  [sym_args] = "args",
  [sym_expression] = "assignment_command",
  [sym_condition] = "if_else_command",
  [sym_value] = "value",
  [sym_identifier] = "identifier",
  [aux_sym_program_all_repeat1] = "program_all_repeat1",
  [aux_sym_commands_repeat1] = "commands_repeat1",
  [aux_sym_declarations_repeat1] = "declarations_repeat1",
  [aux_sym_args_decl_repeat1] = "args_decl_repeat1",
  [aux_sym_args_repeat1] = "args_repeat1",
  [anon_alias_sym_if_command] = "if_command",
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
  [anon_sym_SEMI] = anon_sym_COLON_EQ,
  [anon_sym_IF] = anon_sym_IF,
  [anon_sym_THEN] = anon_sym_IF,
  [anon_sym_ELSE] = anon_sym_IF,
  [anon_sym_ENDIF] = anon_sym_IF,
  [anon_sym_WHILE] = anon_sym_WHILE,
  [anon_sym_DO] = anon_sym_WHILE,
  [anon_sym_ENDWHILE] = anon_sym_WHILE,
  [anon_sym_REPEAT] = anon_sym_REPEAT,
  [anon_sym_UNTIL] = anon_sym_REPEAT,
  [anon_sym_FOR] = anon_sym_FOR,
  [anon_sym_FROM] = anon_sym_FOR,
  [anon_sym_TO] = anon_sym_FOR,
  [anon_sym_ENDFOR] = anon_sym_FOR,
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
  [sym_arg_decl] = sym_arg_decl,
  [sym_args] = sym_args,
  [sym_expression] = anon_sym_COLON_EQ,
  [sym_condition] = anon_sym_IF,
  [sym_value] = sym_value,
  [sym_identifier] = sym_identifier,
  [aux_sym_program_all_repeat1] = aux_sym_program_all_repeat1,
  [aux_sym_commands_repeat1] = aux_sym_commands_repeat1,
  [aux_sym_declarations_repeat1] = aux_sym_declarations_repeat1,
  [aux_sym_args_decl_repeat1] = aux_sym_args_decl_repeat1,
  [aux_sym_args_repeat1] = aux_sym_args_repeat1,
  [anon_alias_sym_if_command] = anon_alias_sym_if_command,
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
    .named = false,
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
  [sym_arg_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_args] = {
    .visible = true,
    .named = true,
  },
  [sym_expression] = {
    .visible = true,
    .named = false,
  },
  [sym_condition] = {
    .visible = true,
    .named = false,
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
  [anon_alias_sym_if_command] = {
    .visible = true,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_T = 1,
  field_argument = 2,
  field_arguments = 3,
  field_body = 4,
  field_command = 5,
  field_commands = 6,
  field_condition = 7,
  field_declaration = 8,
  field_declarations = 9,
  field_else_branch = 10,
  field_end = 11,
  field_expression = 12,
  field_header = 13,
  field_identifier = 14,
  field_index = 15,
  field_left = 16,
  field_main_program = 17,
  field_name = 18,
  field_number = 19,
  field_op = 20,
  field_procedure_call = 21,
  field_procedures = 22,
  field_right = 23,
  field_start = 24,
  field_target = 25,
  field_then_branch = 26,
  field_value = 27,
  field_variable = 28,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_T] = "T",
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
  [field_op] = "op",
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
  [21] = {.index = 27, .length = 1},
  [22] = {.index = 28, .length = 2},
  [23] = {.index = 30, .length = 2},
  [24] = {.index = 32, .length = 2},
  [25] = {.index = 34, .length = 1},
  [26] = {.index = 35, .length = 1},
  [27] = {.index = 36, .length = 1},
  [28] = {.index = 37, .length = 2},
  [29] = {.index = 39, .length = 3},
  [30] = {.index = 42, .length = 3},
  [31] = {.index = 45, .length = 2},
  [32] = {.index = 47, .length = 2},
  [33] = {.index = 49, .length = 2},
  [34] = {.index = 51, .length = 2},
  [35] = {.index = 53, .length = 2},
  [36] = {.index = 55, .length = 3},
  [37] = {.index = 58, .length = 3},
  [38] = {.index = 61, .length = 4},
  [39] = {.index = 61, .length = 4},
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
    {field_T, 0},
    {field_name, 1},
  [13] =
    {field_arguments, 2},
    {field_name, 0},
  [15] =
    {field_argument, 0},
    {field_argument, 1, .inherited = true},
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
    {field_argument, 1},
  [28] =
    {field_argument, 0, .inherited = true},
    {field_argument, 1, .inherited = true},
  [30] =
    {field_commands, 4},
    {field_header, 1},
  [32] =
    {field_declarations, 3},
    {field_header, 1},
  [34] =
    {field_target, 1},
  [35] =
    {field_value, 1},
  [36] =
    {field_value, 0},
  [37] =
    {field_commands, 4},
    {field_declarations, 2},
  [39] =
    {field_commands, 5},
    {field_declarations, 3},
    {field_header, 1},
  [42] =
    {field_left, 0},
    {field_op, 1},
    {field_right, 2},
  [45] =
    {field_index, 2},
    {field_name, 0},
  [47] =
    {field_expression, 2},
    {field_target, 0},
  [49] =
    {field_condition, 1},
    {field_then_branch, 3},
  [51] =
    {field_body, 3},
    {field_condition, 1},
  [53] =
    {field_body, 1},
    {field_condition, 3},
  [55] =
    {field_end, 4},
    {field_identifier, 0},
    {field_start, 2},
  [58] =
    {field_condition, 1},
    {field_else_branch, 5},
    {field_then_branch, 3},
  [61] =
    {field_body, 7},
    {field_end, 5},
    {field_start, 3},
    {field_variable, 1},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
  [16] = {
    [1] = sym_proc_call,
  },
  [25] = {
    [1] = anon_sym_READ,
    [2] = anon_sym_READ,
  },
  [26] = {
    [1] = anon_sym_WRITE,
    [2] = anon_sym_WRITE,
  },
  [32] = {
    [0] = anon_sym_COLON_EQ,
  },
  [33] = {
    [0] = anon_alias_sym_if_command,
    [1] = anon_alias_sym_if_command,
    [2] = anon_alias_sym_if_command,
    [3] = anon_alias_sym_if_command,
    [4] = anon_alias_sym_if_command,
  },
  [34] = {
    [1] = anon_sym_WHILE,
    [3] = anon_sym_WHILE,
  },
  [35] = {
    [1] = anon_sym_REPEAT,
    [3] = anon_sym_REPEAT,
    [4] = anon_sym_REPEAT,
  },
  [37] = {
    [3] = anon_sym_IF,
    [5] = anon_sym_IF,
  },
  [38] = {
    [1] = anon_sym_FOR,
    [3] = anon_sym_FOR,
    [5] = anon_sym_FOR,
    [6] = anon_sym_FOR,
    [7] = anon_sym_FOR,
  },
  [39] = {
    [0] = anon_sym_DOWNTO,
    [1] = anon_sym_DOWNTO,
    [2] = anon_sym_DOWNTO,
    [3] = anon_sym_DOWNTO,
    [5] = anon_sym_DOWNTO,
    [6] = anon_sym_DOWNTO,
    [7] = anon_sym_DOWNTO,
    [8] = anon_sym_DOWNTO,
  },
};

static const uint16_t ts_non_terminal_alias_map[] = {
  sym_commands, 7,
    sym_commands,
    anon_alias_sym_if_command,
    anon_sym_DOWNTO,
    anon_sym_FOR,
    anon_sym_IF,
    anon_sym_REPEAT,
    anon_sym_WHILE,
  sym_condition, 4,
    anon_sym_IF,
    anon_alias_sym_if_command,
    anon_sym_REPEAT,
    anon_sym_WHILE,
  sym_value, 4,
    sym_value,
    anon_sym_DOWNTO,
    anon_sym_FOR,
    anon_sym_WRITE,
  sym_identifier, 3,
    sym_identifier,
    anon_sym_COLON_EQ,
    anon_sym_READ,
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
  [55] = 4,
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
  [67] = 7,
  [68] = 68,
  [69] = 6,
  [70] = 70,
  [71] = 5,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 61,
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
  [115] = 115,
  [116] = 116,
  [117] = 117,
  [118] = 118,
  [119] = 119,
  [120] = 120,
  [121] = 121,
  [122] = 122,
  [123] = 123,
  [124] = 124,
  [125] = 125,
  [126] = 126,
  [127] = 86,
  [128] = 128,
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
  [9] = {.lex_state = 2},
  [10] = {.lex_state = 3},
  [11] = {.lex_state = 2},
  [12] = {.lex_state = 3},
  [13] = {.lex_state = 3},
  [14] = {.lex_state = 2},
  [15] = {.lex_state = 2},
  [16] = {.lex_state = 2},
  [17] = {.lex_state = 2},
  [18] = {.lex_state = 2},
  [19] = {.lex_state = 3},
  [20] = {.lex_state = 2},
  [21] = {.lex_state = 2},
  [22] = {.lex_state = 2},
  [23] = {.lex_state = 2},
  [24] = {.lex_state = 2},
  [25] = {.lex_state = 2},
  [26] = {.lex_state = 2},
  [27] = {.lex_state = 2},
  [28] = {.lex_state = 2},
  [29] = {.lex_state = 0},
  [30] = {.lex_state = 0},
  [31] = {.lex_state = 2},
  [32] = {.lex_state = 2},
  [33] = {.lex_state = 2},
  [34] = {.lex_state = 1},
  [35] = {.lex_state = 2},
  [36] = {.lex_state = 2},
  [37] = {.lex_state = 2},
  [38] = {.lex_state = 2},
  [39] = {.lex_state = 2},
  [40] = {.lex_state = 2},
  [41] = {.lex_state = 2},
  [42] = {.lex_state = 1},
  [43] = {.lex_state = 2},
  [44] = {.lex_state = 2},
  [45] = {.lex_state = 2},
  [46] = {.lex_state = 1},
  [47] = {.lex_state = 2},
  [48] = {.lex_state = 1},
  [49] = {.lex_state = 2},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 2},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 1},
  [56] = {.lex_state = 2},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 2},
  [60] = {.lex_state = 2},
  [61] = {.lex_state = 2},
  [62] = {.lex_state = 2},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 2},
  [65] = {.lex_state = 2},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 1},
  [68] = {.lex_state = 2},
  [69] = {.lex_state = 1},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 1},
  [72] = {.lex_state = 1},
  [73] = {.lex_state = 1},
  [74] = {.lex_state = 1},
  [75] = {.lex_state = 1},
  [76] = {.lex_state = 2},
  [77] = {.lex_state = 4},
  [78] = {.lex_state = 1},
  [79] = {.lex_state = 2},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 2},
  [82] = {.lex_state = 1},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 2},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 1},
  [91] = {.lex_state = 3},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 4},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 1},
  [96] = {.lex_state = 2},
  [97] = {.lex_state = 2},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 3},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 3},
  [102] = {.lex_state = 0},
  [103] = {.lex_state = 2},
  [104] = {.lex_state = 2},
  [105] = {.lex_state = 0},
  [106] = {.lex_state = 2},
  [107] = {.lex_state = 2},
  [108] = {.lex_state = 0},
  [109] = {.lex_state = 0},
  [110] = {.lex_state = 0},
  [111] = {.lex_state = 0},
  [112] = {.lex_state = 0},
  [113] = {.lex_state = 4},
  [114] = {.lex_state = 1},
  [115] = {.lex_state = 1},
  [116] = {.lex_state = 1},
  [117] = {.lex_state = 0},
  [118] = {.lex_state = 0},
  [119] = {.lex_state = 4},
  [120] = {.lex_state = 4},
  [121] = {.lex_state = 0},
  [122] = {.lex_state = 1},
  [123] = {.lex_state = 1},
  [124] = {.lex_state = 2},
  [125] = {.lex_state = 1},
  [126] = {.lex_state = 1},
  [127] = {.lex_state = 0},
  [128] = {.lex_state = 3},
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
    [sym_program_all] = STATE(121),
    [sym_procedure] = STATE(34),
    [sym_main] = STATE(118),
    [aux_sym_program_all_repeat1] = STATE(34),
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
    STATE(9), 1,
      sym_command,
    STATE(92), 1,
      sym_proc_call,
    STATE(95), 1,
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
    STATE(9), 1,
      sym_command,
    STATE(92), 1,
      sym_proc_call,
    STATE(95), 1,
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
  [207] = 3,
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
  [228] = 14,
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
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(9), 1,
      sym_command,
    STATE(92), 1,
      sym_proc_call,
    STATE(95), 1,
      sym_identifier,
    STATE(99), 1,
      sym_commands,
  [271] = 3,
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
  [292] = 14,
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
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(9), 1,
      sym_command,
    STATE(92), 1,
      sym_proc_call,
    STATE(95), 1,
      sym_identifier,
    STATE(101), 1,
      sym_commands,
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
    STATE(9), 1,
      sym_command,
    STATE(91), 1,
      sym_commands,
    STATE(92), 1,
      sym_proc_call,
    STATE(95), 1,
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
  [483] = 14,
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
    ACTIONS(108), 1,
      anon_sym_END,
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(9), 1,
      sym_command,
    STATE(92), 1,
      sym_proc_call,
    STATE(95), 1,
      sym_identifier,
    STATE(128), 1,
      sym_commands,
  [526] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(110), 1,
      anon_sym_END,
    ACTIONS(112), 12,
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
  [547] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(114), 1,
      anon_sym_END,
    ACTIONS(116), 12,
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
  [568] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(118), 1,
      anon_sym_END,
    ACTIONS(120), 12,
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
  [589] = 13,
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
    STATE(9), 1,
      sym_command,
    STATE(92), 1,
      sym_proc_call,
    STATE(95), 1,
      sym_identifier,
    STATE(119), 1,
      sym_commands,
  [629] = 13,
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
    STATE(9), 1,
      sym_command,
    STATE(92), 1,
      sym_proc_call,
    STATE(95), 1,
      sym_identifier,
    STATE(113), 1,
      sym_commands,
  [669] = 13,
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
    STATE(9), 1,
      sym_command,
    STATE(77), 1,
      sym_commands,
    STATE(92), 1,
      sym_proc_call,
    STATE(95), 1,
      sym_identifier,
  [709] = 13,
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
    STATE(9), 1,
      sym_command,
    STATE(92), 1,
      sym_proc_call,
    STATE(95), 1,
      sym_identifier,
    STATE(120), 1,
      sym_commands,
  [749] = 13,
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
    STATE(9), 1,
      sym_command,
    STATE(92), 1,
      sym_proc_call,
    STATE(95), 1,
      sym_identifier,
    STATE(124), 1,
      sym_commands,
  [789] = 13,
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
    STATE(9), 1,
      sym_command,
    STATE(92), 1,
      sym_proc_call,
    STATE(93), 1,
      sym_commands,
    STATE(95), 1,
      sym_identifier,
  [829] = 3,
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
  [843] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(128), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(126), 4,
      anon_sym_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
  [857] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(130), 1,
      sym_pidentifier,
    ACTIONS(132), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(30), 1,
      sym_value,
    STATE(94), 1,
      sym_condition,
  [876] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(130), 1,
      sym_pidentifier,
    ACTIONS(132), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(30), 1,
      sym_value,
    STATE(125), 1,
      sym_condition,
  [895] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(130), 1,
      sym_pidentifier,
    ACTIONS(132), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(30), 1,
      sym_value,
    STATE(126), 1,
      sym_condition,
  [914] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(5), 1,
      anon_sym_PROCEDURE,
    ACTIONS(7), 1,
      anon_sym_PROGRAM,
    STATE(108), 1,
      sym_main,
    STATE(42), 2,
      sym_procedure,
      aux_sym_program_all_repeat1,
  [931] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(134), 1,
      anon_sym_RPAREN,
    ACTIONS(136), 1,
      anon_sym_T,
    ACTIONS(138), 1,
      sym_pidentifier,
    STATE(54), 1,
      sym_arg_decl,
    STATE(100), 1,
      sym_args_decl,
  [950] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(130), 1,
      sym_pidentifier,
    ACTIONS(132), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(29), 1,
      sym_value,
    STATE(87), 1,
      sym_expression,
  [969] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(130), 1,
      sym_pidentifier,
    ACTIONS(132), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(110), 1,
      sym_value,
  [985] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(140), 1,
      sym_pidentifier,
    ACTIONS(142), 1,
      sym_num,
    STATE(69), 1,
      sym_identifier,
    STATE(75), 1,
      sym_value,
  [1001] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(130), 1,
      sym_pidentifier,
    ACTIONS(132), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(48), 1,
      sym_value,
  [1017] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(130), 1,
      sym_pidentifier,
    ACTIONS(132), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(111), 1,
      sym_value,
  [1033] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(144), 1,
      anon_sym_BEGIN,
    ACTIONS(146), 1,
      sym_pidentifier,
    STATE(56), 1,
      sym_declaration,
    STATE(81), 1,
      sym_declarations,
  [1049] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(148), 1,
      anon_sym_PROCEDURE,
    ACTIONS(151), 1,
      anon_sym_PROGRAM,
    STATE(42), 2,
      sym_procedure,
      aux_sym_program_all_repeat1,
  [1063] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(130), 1,
      sym_pidentifier,
    ACTIONS(132), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(114), 1,
      sym_value,
  [1079] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(146), 1,
      sym_pidentifier,
    ACTIONS(153), 1,
      anon_sym_BEGIN,
    STATE(56), 1,
      sym_declaration,
    STATE(106), 1,
      sym_declarations,
  [1095] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(130), 1,
      sym_pidentifier,
    ACTIONS(132), 1,
      sym_num,
    STATE(6), 1,
      sym_identifier,
    STATE(115), 1,
      sym_value,
  [1111] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(52), 1,
      anon_sym_COLON_EQ,
    ACTIONS(54), 1,
      anon_sym_LBRACK,
    ACTIONS(155), 1,
      anon_sym_LPAREN,
  [1124] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(157), 1,
      anon_sym_BEGIN,
    ACTIONS(159), 1,
      anon_sym_COMMA,
    STATE(53), 1,
      aux_sym_declarations_repeat1,
  [1137] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(161), 3,
      anon_sym_SEMI,
      anon_sym_THEN,
      anon_sym_DO,
  [1146] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(136), 1,
      anon_sym_T,
    ACTIONS(138), 1,
      sym_pidentifier,
    STATE(70), 1,
      sym_arg_decl,
  [1159] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(163), 1,
      anon_sym_RPAREN,
    ACTIONS(165), 1,
      anon_sym_COMMA,
    STATE(52), 1,
      aux_sym_args_decl_repeat1,
  [1172] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(167), 1,
      anon_sym_RPAREN,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    STATE(57), 1,
      aux_sym_args_repeat1,
  [1185] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(171), 1,
      anon_sym_RPAREN,
    ACTIONS(173), 1,
      anon_sym_COMMA,
    STATE(52), 1,
      aux_sym_args_decl_repeat1,
  [1198] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(176), 1,
      anon_sym_BEGIN,
    ACTIONS(178), 1,
      anon_sym_COMMA,
    STATE(53), 1,
      aux_sym_declarations_repeat1,
  [1211] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(165), 1,
      anon_sym_COMMA,
    ACTIONS(181), 1,
      anon_sym_RPAREN,
    STATE(50), 1,
      aux_sym_args_decl_repeat1,
  [1224] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(183), 1,
      anon_sym_LBRACK,
    ACTIONS(52), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1235] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(159), 1,
      anon_sym_COMMA,
    ACTIONS(185), 1,
      anon_sym_BEGIN,
    STATE(47), 1,
      aux_sym_declarations_repeat1,
  [1248] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(187), 1,
      anon_sym_RPAREN,
    ACTIONS(189), 1,
      anon_sym_COMMA,
    STATE(57), 1,
      aux_sym_args_repeat1,
  [1261] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    ACTIONS(192), 1,
      anon_sym_RPAREN,
    STATE(51), 1,
      aux_sym_args_repeat1,
  [1274] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(194), 1,
      anon_sym_RPAREN,
    ACTIONS(196), 1,
      sym_pidentifier,
    STATE(85), 1,
      sym_args,
  [1287] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(200), 1,
      anon_sym_LBRACK,
    ACTIONS(198), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1298] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(202), 2,
      sym_pidentifier,
      sym_num,
  [1306] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(204), 1,
      sym_pidentifier,
    STATE(116), 1,
      sym_proc_head,
  [1316] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(206), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1324] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(146), 1,
      sym_pidentifier,
    STATE(68), 1,
      sym_declaration,
  [1334] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(208), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1342] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(210), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1350] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(66), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1358] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(212), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1366] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(62), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1374] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(214), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1382] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(58), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1390] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(216), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1398] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(218), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1406] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(220), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1414] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(222), 1,
      anon_sym_TO,
    ACTIONS(224), 1,
      anon_sym_DOWNTO,
  [1424] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(226), 2,
      sym_pidentifier,
      sym_num,
  [1432] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(228), 1,
      anon_sym_ELSE,
    ACTIONS(230), 1,
      anon_sym_ENDIF,
  [1442] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(232), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1450] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(130), 1,
      sym_pidentifier,
    STATE(112), 1,
      sym_identifier,
  [1460] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(234), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1468] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(236), 1,
      anon_sym_BEGIN,
  [1475] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(238), 1,
      anon_sym_IS,
  [1482] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(240), 1,
      ts_builtin_sym_end,
  [1489] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(242), 1,
      anon_sym_SEMI,
  [1496] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(244), 1,
      anon_sym_RPAREN,
  [1503] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(246), 1,
      anon_sym_RBRACK,
  [1510] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(248), 1,
      anon_sym_SEMI,
  [1517] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(250), 1,
      sym_num,
  [1524] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(252), 1,
      ts_builtin_sym_end,
  [1531] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(254), 1,
      anon_sym_IS,
  [1538] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(256), 1,
      anon_sym_END,
  [1545] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(258), 1,
      anon_sym_SEMI,
  [1552] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(260), 1,
      anon_sym_ENDWHILE,
  [1559] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(262), 1,
      anon_sym_SEMI,
  [1566] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(264), 1,
      anon_sym_COLON_EQ,
  [1573] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(266), 1,
      sym_pidentifier,
  [1580] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(268), 1,
      sym_num,
  [1587] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(270), 1,
      anon_sym_SEMI,
  [1594] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(272), 1,
      anon_sym_END,
  [1601] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(274), 1,
      anon_sym_RPAREN,
  [1608] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(276), 1,
      anon_sym_END,
  [1615] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(278), 1,
      anon_sym_RBRACK,
  [1622] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(280), 1,
      sym_pidentifier,
  [1629] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(282), 1,
      sym_pidentifier,
  [1636] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(284), 1,
      ts_builtin_sym_end,
  [1643] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(286), 1,
      anon_sym_BEGIN,
  [1650] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(288), 1,
      anon_sym_COLON,
  [1657] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(290), 1,
      ts_builtin_sym_end,
  [1664] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(292), 1,
      ts_builtin_sym_end,
  [1671] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(294), 1,
      anon_sym_SEMI,
  [1678] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(296), 1,
      anon_sym_SEMI,
  [1685] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(298), 1,
      anon_sym_SEMI,
  [1692] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(300), 1,
      anon_sym_ENDIF,
  [1699] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(302), 1,
      anon_sym_DO,
  [1706] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(304), 1,
      anon_sym_DO,
  [1713] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(306), 1,
      anon_sym_IS,
  [1720] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(308), 1,
      anon_sym_LPAREN,
  [1727] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(310), 1,
      ts_builtin_sym_end,
  [1734] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(312), 1,
      anon_sym_ENDFOR,
  [1741] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(314), 1,
      anon_sym_ENDFOR,
  [1748] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(316), 1,
      ts_builtin_sym_end,
  [1755] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(318), 1,
      anon_sym_IS,
  [1762] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(320), 1,
      anon_sym_FROM,
  [1769] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(322), 1,
      anon_sym_UNTIL,
  [1776] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(324), 1,
      anon_sym_DO,
  [1783] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(326), 1,
      anon_sym_THEN,
  [1790] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(328), 1,
      anon_sym_RBRACK,
  [1797] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(330), 1,
      anon_sym_END,
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
  [SMALL_STATE(10)] = 228,
  [SMALL_STATE(11)] = 271,
  [SMALL_STATE(12)] = 292,
  [SMALL_STATE(13)] = 335,
  [SMALL_STATE(14)] = 378,
  [SMALL_STATE(15)] = 399,
  [SMALL_STATE(16)] = 420,
  [SMALL_STATE(17)] = 441,
  [SMALL_STATE(18)] = 462,
  [SMALL_STATE(19)] = 483,
  [SMALL_STATE(20)] = 526,
  [SMALL_STATE(21)] = 547,
  [SMALL_STATE(22)] = 568,
  [SMALL_STATE(23)] = 589,
  [SMALL_STATE(24)] = 629,
  [SMALL_STATE(25)] = 669,
  [SMALL_STATE(26)] = 709,
  [SMALL_STATE(27)] = 749,
  [SMALL_STATE(28)] = 789,
  [SMALL_STATE(29)] = 829,
  [SMALL_STATE(30)] = 843,
  [SMALL_STATE(31)] = 857,
  [SMALL_STATE(32)] = 876,
  [SMALL_STATE(33)] = 895,
  [SMALL_STATE(34)] = 914,
  [SMALL_STATE(35)] = 931,
  [SMALL_STATE(36)] = 950,
  [SMALL_STATE(37)] = 969,
  [SMALL_STATE(38)] = 985,
  [SMALL_STATE(39)] = 1001,
  [SMALL_STATE(40)] = 1017,
  [SMALL_STATE(41)] = 1033,
  [SMALL_STATE(42)] = 1049,
  [SMALL_STATE(43)] = 1063,
  [SMALL_STATE(44)] = 1079,
  [SMALL_STATE(45)] = 1095,
  [SMALL_STATE(46)] = 1111,
  [SMALL_STATE(47)] = 1124,
  [SMALL_STATE(48)] = 1137,
  [SMALL_STATE(49)] = 1146,
  [SMALL_STATE(50)] = 1159,
  [SMALL_STATE(51)] = 1172,
  [SMALL_STATE(52)] = 1185,
  [SMALL_STATE(53)] = 1198,
  [SMALL_STATE(54)] = 1211,
  [SMALL_STATE(55)] = 1224,
  [SMALL_STATE(56)] = 1235,
  [SMALL_STATE(57)] = 1248,
  [SMALL_STATE(58)] = 1261,
  [SMALL_STATE(59)] = 1274,
  [SMALL_STATE(60)] = 1287,
  [SMALL_STATE(61)] = 1298,
  [SMALL_STATE(62)] = 1306,
  [SMALL_STATE(63)] = 1316,
  [SMALL_STATE(64)] = 1324,
  [SMALL_STATE(65)] = 1334,
  [SMALL_STATE(66)] = 1342,
  [SMALL_STATE(67)] = 1350,
  [SMALL_STATE(68)] = 1358,
  [SMALL_STATE(69)] = 1366,
  [SMALL_STATE(70)] = 1374,
  [SMALL_STATE(71)] = 1382,
  [SMALL_STATE(72)] = 1390,
  [SMALL_STATE(73)] = 1398,
  [SMALL_STATE(74)] = 1406,
  [SMALL_STATE(75)] = 1414,
  [SMALL_STATE(76)] = 1424,
  [SMALL_STATE(77)] = 1432,
  [SMALL_STATE(78)] = 1442,
  [SMALL_STATE(79)] = 1450,
  [SMALL_STATE(80)] = 1460,
  [SMALL_STATE(81)] = 1468,
  [SMALL_STATE(82)] = 1475,
  [SMALL_STATE(83)] = 1482,
  [SMALL_STATE(84)] = 1489,
  [SMALL_STATE(85)] = 1496,
  [SMALL_STATE(86)] = 1503,
  [SMALL_STATE(87)] = 1510,
  [SMALL_STATE(88)] = 1517,
  [SMALL_STATE(89)] = 1524,
  [SMALL_STATE(90)] = 1531,
  [SMALL_STATE(91)] = 1538,
  [SMALL_STATE(92)] = 1545,
  [SMALL_STATE(93)] = 1552,
  [SMALL_STATE(94)] = 1559,
  [SMALL_STATE(95)] = 1566,
  [SMALL_STATE(96)] = 1573,
  [SMALL_STATE(97)] = 1580,
  [SMALL_STATE(98)] = 1587,
  [SMALL_STATE(99)] = 1594,
  [SMALL_STATE(100)] = 1601,
  [SMALL_STATE(101)] = 1608,
  [SMALL_STATE(102)] = 1615,
  [SMALL_STATE(103)] = 1622,
  [SMALL_STATE(104)] = 1629,
  [SMALL_STATE(105)] = 1636,
  [SMALL_STATE(106)] = 1643,
  [SMALL_STATE(107)] = 1650,
  [SMALL_STATE(108)] = 1657,
  [SMALL_STATE(109)] = 1664,
  [SMALL_STATE(110)] = 1671,
  [SMALL_STATE(111)] = 1678,
  [SMALL_STATE(112)] = 1685,
  [SMALL_STATE(113)] = 1692,
  [SMALL_STATE(114)] = 1699,
  [SMALL_STATE(115)] = 1706,
  [SMALL_STATE(116)] = 1713,
  [SMALL_STATE(117)] = 1720,
  [SMALL_STATE(118)] = 1727,
  [SMALL_STATE(119)] = 1734,
  [SMALL_STATE(120)] = 1741,
  [SMALL_STATE(121)] = 1748,
  [SMALL_STATE(122)] = 1755,
  [SMALL_STATE(123)] = 1762,
  [SMALL_STATE(124)] = 1769,
  [SMALL_STATE(125)] = 1776,
  [SMALL_STATE(126)] = 1783,
  [SMALL_STATE(127)] = 1790,
  [SMALL_STATE(128)] = 1797,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [9] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_commands, 1, 0, 8),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [13] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_commands, 1, 0, 8),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [27] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17),
  [29] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(33),
  [32] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17),
  [34] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(32),
  [37] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(27),
  [40] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(104),
  [43] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(79),
  [46] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(37),
  [49] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 17), SHIFT_REPEAT(46),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 1, 0, 5),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [56] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_identifier, 1, 0, 5),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 4, 0, 31),
  [60] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_identifier, 4, 0, 31),
  [62] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 1, 0, 3),
  [64] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_value, 1, 0, 3),
  [66] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 1, 0, 14),
  [68] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_value, 1, 0, 14),
  [70] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 7, 0, 37),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 7, 0, 37),
  [74] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_commands_repeat1, 1, 0, 7),
  [76] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 1, 0, 7),
  [78] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [80] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 2, 0, 16),
  [82] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 2, 0, 16),
  [84] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [86] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [88] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 5, 0, 35),
  [90] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 5, 0, 35),
  [92] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 5, 0, 34),
  [94] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 5, 0, 34),
  [96] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 5, 0, 33),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 5, 0, 33),
  [100] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 4, 0, 32),
  [102] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 4, 0, 32),
  [104] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 9, 0, 39),
  [106] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 9, 0, 39),
  [108] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [110] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 3, 0, 26),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3, 0, 26),
  [114] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 3, 0, 25),
  [116] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3, 0, 25),
  [118] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 9, 0, 38),
  [120] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 9, 0, 38),
  [122] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 1, 0, 27),
  [124] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [126] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [128] = {.entry = {.count = 1, .reusable = false}}, SHIFT(39),
  [130] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [134] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [146] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [148] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_all_repeat1, 2, 0, 0), SHIFT_REPEAT(62),
  [151] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_program_all_repeat1, 2, 0, 0),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [157] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declarations, 2, 0, 9),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [161] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_condition, 3, 0, 30),
  [163] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 2, 0, 12),
  [165] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [167] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args, 2, 0, 12),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [171] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 22),
  [173] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 22), SHIFT_REPEAT(49),
  [176] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 20),
  [178] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 20), SHIFT_REPEAT(64),
  [181] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 1, 0, 6),
  [183] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [185] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declarations, 1, 0, 4),
  [187] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 22),
  [189] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 22), SHIFT_REPEAT(96),
  [192] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args, 1, 0, 6),
  [194] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [196] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [198] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declaration, 1, 0, 3),
  [200] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [202] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [204] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 21),
  [208] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declaration, 6, 0, 36),
  [210] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arg_decl, 1, 0, 5),
  [212] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 19),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 21),
  [216] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 6, 0, 23),
  [218] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 6, 0, 24),
  [220] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 5, 0, 13),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [224] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [228] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [230] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [232] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 7, 0, 29),
  [234] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arg_decl, 2, 0, 10),
  [236] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [238] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_head, 3, 0, 5),
  [240] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 4, 0, 0),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_call, 3, 0, 5),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [252] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 6, 0, 28),
  [254] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_head, 4, 0, 11),
  [256] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [258] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [262] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [266] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [270] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_call, 4, 0, 11),
  [272] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [274] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [276] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [284] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 5, 0, 18),
  [286] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [288] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [290] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program_all, 2, 0, 2),
  [292] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 5, 0, 15),
  [294] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [296] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 3, 0, 30),
  [298] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [300] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [304] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [306] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [308] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [310] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program_all, 1, 0, 1),
  [312] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [314] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [316] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [318] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [320] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [324] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [326] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [328] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [330] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
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
