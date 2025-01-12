#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 142
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 68
#define ALIAS_COUNT 1
#define TOKEN_COUNT 46
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 29
#define MAX_ALIAS_SEQUENCE_LENGTH 9
#define PRODUCTION_ID_COUNT 49

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
  sym_procedures = 47,
  sym_procedure = 48,
  sym_main = 49,
  sym_commands = 50,
  sym_command = 51,
  sym_proc_head = 52,
  sym_proc_call = 53,
  sym_declarations = 54,
  sym_declaration = 55,
  sym_args_decl = 56,
  sym_arg_decl = 57,
  sym_args = 58,
  sym_expression = 59,
  sym_condition = 60,
  sym_value = 61,
  sym_identifier = 62,
  aux_sym_procedures_repeat1 = 63,
  aux_sym_commands_repeat1 = 64,
  aux_sym_declarations_repeat1 = 65,
  aux_sym_args_decl_repeat1 = 66,
  aux_sym_args_repeat1 = 67,
  anon_alias_sym_if_command = 68,
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
  [anon_sym_SEMI] = "repeat_until_command",
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
  [sym_procedures] = "procedures",
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
  [aux_sym_procedures_repeat1] = "procedures_repeat1",
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
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_IF] = anon_sym_IF,
  [anon_sym_THEN] = anon_sym_IF,
  [anon_sym_ELSE] = anon_sym_IF,
  [anon_sym_ENDIF] = anon_sym_IF,
  [anon_sym_WHILE] = anon_sym_WHILE,
  [anon_sym_DO] = anon_sym_WHILE,
  [anon_sym_ENDWHILE] = anon_sym_WHILE,
  [anon_sym_REPEAT] = anon_sym_SEMI,
  [anon_sym_UNTIL] = anon_sym_SEMI,
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
  [sym_procedures] = sym_procedures,
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
  [aux_sym_procedures_repeat1] = aux_sym_procedures_repeat1,
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
  [sym_procedures] = {
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
  [aux_sym_procedures_repeat1] = {
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
  field_procedure = 21,
  field_procedure_call = 22,
  field_procedures = 23,
  field_right = 24,
  field_start = 25,
  field_target = 26,
  field_then_branch = 27,
  field_value = 28,
  field_variable = 29,
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
  [field_procedure] = "procedure",
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
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 2},
  [4] = {.index = 4, .length = 1},
  [5] = {.index = 5, .length = 1},
  [6] = {.index = 6, .length = 1},
  [7] = {.index = 7, .length = 1},
  [8] = {.index = 8, .length = 1},
  [9] = {.index = 9, .length = 1},
  [10] = {.index = 10, .length = 2},
  [11] = {.index = 12, .length = 2},
  [12] = {.index = 14, .length = 2},
  [13] = {.index = 16, .length = 2},
  [14] = {.index = 18, .length = 1},
  [15] = {.index = 19, .length = 1},
  [16] = {.index = 20, .length = 1},
  [17] = {.index = 21, .length = 1},
  [18] = {.index = 22, .length = 2},
  [19] = {.index = 24, .length = 1},
  [20] = {.index = 25, .length = 1},
  [21] = {.index = 26, .length = 2},
  [22] = {.index = 28, .length = 1},
  [23] = {.index = 29, .length = 2},
  [24] = {.index = 31, .length = 2},
  [25] = {.index = 33, .length = 2},
  [26] = {.index = 35, .length = 1},
  [27] = {.index = 36, .length = 1},
  [28] = {.index = 37, .length = 1},
  [29] = {.index = 38, .length = 2},
  [30] = {.index = 40, .length = 3},
  [31] = {.index = 43, .length = 1},
  [32] = {.index = 44, .length = 3},
  [33] = {.index = 43, .length = 1},
  [34] = {.index = 47, .length = 1},
  [35] = {.index = 48, .length = 2},
  [36] = {.index = 50, .length = 2},
  [37] = {.index = 43, .length = 1},
  [38] = {.index = 52, .length = 2},
  [39] = {.index = 54, .length = 2},
  [40] = {.index = 56, .length = 2},
  [41] = {.index = 58, .length = 3},
  [42] = {.index = 61, .length = 2},
  [43] = {.index = 52, .length = 2},
  [44] = {.index = 63, .length = 3},
  [45] = {.index = 66, .length = 3},
  [46] = {.index = 66, .length = 3},
  [47] = {.index = 69, .length = 4},
  [48] = {.index = 69, .length = 4},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_main_program, 0},
  [1] =
    {field_procedure, 0},
  [2] =
    {field_main_program, 1},
    {field_procedures, 0},
  [4] =
    {field_identifier, 0},
  [5] =
    {field_declaration, 0},
  [6] =
    {field_name, 0},
  [7] =
    {field_argument, 0},
  [8] =
    {field_command, 0},
  [9] =
    {field_command, 0, .inherited = true},
  [10] =
    {field_declaration, 0},
    {field_declaration, 1, .inherited = true},
  [12] =
    {field_T, 0},
    {field_name, 1},
  [14] =
    {field_arguments, 2},
    {field_name, 0},
  [16] =
    {field_argument, 0},
    {field_argument, 1, .inherited = true},
  [18] =
    {field_header, 1},
  [19] =
    {field_number, 0},
  [20] =
    {field_commands, 3},
  [21] =
    {field_procedure_call, 0},
  [22] =
    {field_command, 0, .inherited = true},
    {field_command, 1, .inherited = true},
  [24] =
    {field_declarations, 2},
  [25] =
    {field_declaration, 1},
  [26] =
    {field_declaration, 0, .inherited = true},
    {field_declaration, 1, .inherited = true},
  [28] =
    {field_argument, 1},
  [29] =
    {field_argument, 0, .inherited = true},
    {field_argument, 1, .inherited = true},
  [31] =
    {field_commands, 4},
    {field_header, 1},
  [33] =
    {field_declarations, 3},
    {field_header, 1},
  [35] =
    {field_target, 1},
  [36] =
    {field_value, 1},
  [37] =
    {field_value, 0},
  [38] =
    {field_commands, 4},
    {field_declarations, 2},
  [40] =
    {field_commands, 5},
    {field_declarations, 3},
    {field_header, 1},
  [43] =
    {field_condition, 1},
  [44] =
    {field_left, 0},
    {field_op, 1},
    {field_right, 2},
  [47] =
    {field_condition, 2},
  [48] =
    {field_index, 2},
    {field_name, 0},
  [50] =
    {field_expression, 2},
    {field_target, 0},
  [52] =
    {field_condition, 1},
    {field_then_branch, 3},
  [54] =
    {field_body, 3},
    {field_condition, 1},
  [56] =
    {field_body, 1},
    {field_condition, 3},
  [58] =
    {field_end, 4},
    {field_identifier, 0},
    {field_start, 2},
  [61] =
    {field_condition, 1},
    {field_else_branch, 4},
  [63] =
    {field_condition, 1},
    {field_else_branch, 5},
    {field_then_branch, 3},
  [66] =
    {field_end, 5},
    {field_start, 3},
    {field_variable, 1},
  [69] =
    {field_body, 7},
    {field_end, 5},
    {field_start, 3},
    {field_variable, 1},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
  [17] = {
    [1] = sym_proc_call,
  },
  [26] = {
    [1] = anon_sym_READ,
    [2] = anon_sym_READ,
  },
  [27] = {
    [1] = anon_sym_WRITE,
    [2] = anon_sym_WRITE,
  },
  [31] = {
    [0] = anon_alias_sym_if_command,
    [1] = anon_alias_sym_if_command,
    [2] = anon_alias_sym_if_command,
    [3] = anon_alias_sym_if_command,
  },
  [33] = {
    [1] = anon_sym_WHILE,
    [3] = anon_sym_WHILE,
  },
  [34] = {
    [1] = anon_sym_SEMI,
    [2] = anon_sym_SEMI,
    [3] = anon_sym_SEMI,
  },
  [36] = {
    [0] = anon_sym_COLON_EQ,
    [3] = anon_sym_COLON_EQ,
  },
  [37] = {
    [3] = anon_sym_IF,
    [4] = anon_sym_IF,
  },
  [38] = {
    [0] = anon_alias_sym_if_command,
    [1] = anon_alias_sym_if_command,
    [2] = anon_alias_sym_if_command,
    [3] = anon_alias_sym_if_command,
    [4] = anon_alias_sym_if_command,
  },
  [39] = {
    [1] = anon_sym_WHILE,
    [3] = anon_sym_WHILE,
  },
  [40] = {
    [1] = anon_sym_SEMI,
    [2] = anon_sym_SEMI,
    [3] = anon_sym_SEMI,
  },
  [42] = {
    [3] = anon_sym_IF,
    [4] = anon_sym_IF,
    [5] = anon_sym_IF,
  },
  [43] = {
    [3] = anon_sym_IF,
    [4] = anon_sym_IF,
    [5] = anon_sym_IF,
  },
  [44] = {
    [3] = anon_sym_IF,
    [4] = anon_sym_IF,
    [5] = anon_sym_IF,
  },
  [45] = {
    [1] = anon_sym_FOR,
    [3] = anon_sym_FOR,
    [5] = anon_sym_FOR,
    [6] = anon_sym_FOR,
    [7] = anon_sym_FOR,
  },
  [46] = {
    [0] = anon_sym_DOWNTO,
    [1] = anon_sym_DOWNTO,
    [2] = anon_sym_DOWNTO,
    [3] = anon_sym_DOWNTO,
    [5] = anon_sym_DOWNTO,
    [6] = anon_sym_DOWNTO,
    [7] = anon_sym_DOWNTO,
  },
  [47] = {
    [1] = anon_sym_FOR,
    [3] = anon_sym_FOR,
    [5] = anon_sym_FOR,
    [6] = anon_sym_FOR,
    [7] = anon_sym_FOR,
  },
  [48] = {
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
    anon_sym_SEMI,
    anon_sym_WHILE,
  sym_condition, 4,
    anon_sym_IF,
    anon_alias_sym_if_command,
    anon_sym_SEMI,
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
  [66] = 4,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 5,
  [77] = 77,
  [78] = 7,
  [79] = 8,
  [80] = 80,
  [81] = 81,
  [82] = 73,
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
  [127] = 127,
  [128] = 128,
  [129] = 129,
  [130] = 130,
  [131] = 131,
  [132] = 132,
  [133] = 133,
  [134] = 134,
  [135] = 135,
  [136] = 136,
  [137] = 137,
  [138] = 138,
  [139] = 139,
  [140] = 95,
  [141] = 141,
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
      if (lookahead == 'F') ADVANCE(39);
      if (lookahead == 'I') ADVANCE(20);
      if (lookahead == 'R') ADVANCE(14);
      if (lookahead == 'W') ADVANCE(24);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(4);
      if (lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(136);
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
      if (lookahead == 'D') ADVANCE(22);
      END_STATE();
    case 12:
      if (lookahead == 'D') ADVANCE(51);
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
      if (lookahead == 'N') ADVANCE(11);
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
      if (lookahead == 'N') ADVANCE(12);
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
  [6] = {.lex_state = 4},
  [7] = {.lex_state = 1},
  [8] = {.lex_state = 1},
  [9] = {.lex_state = 2},
  [10] = {.lex_state = 3},
  [11] = {.lex_state = 2},
  [12] = {.lex_state = 2},
  [13] = {.lex_state = 2},
  [14] = {.lex_state = 2},
  [15] = {.lex_state = 3},
  [16] = {.lex_state = 2},
  [17] = {.lex_state = 2},
  [18] = {.lex_state = 4},
  [19] = {.lex_state = 2},
  [20] = {.lex_state = 2},
  [21] = {.lex_state = 2},
  [22] = {.lex_state = 2},
  [23] = {.lex_state = 4},
  [24] = {.lex_state = 3},
  [25] = {.lex_state = 2},
  [26] = {.lex_state = 2},
  [27] = {.lex_state = 4},
  [28] = {.lex_state = 3},
  [29] = {.lex_state = 2},
  [30] = {.lex_state = 2},
  [31] = {.lex_state = 4},
  [32] = {.lex_state = 2},
  [33] = {.lex_state = 2},
  [34] = {.lex_state = 2},
  [35] = {.lex_state = 2},
  [36] = {.lex_state = 4},
  [37] = {.lex_state = 2},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 2},
  [41] = {.lex_state = 2},
  [42] = {.lex_state = 2},
  [43] = {.lex_state = 2},
  [44] = {.lex_state = 2},
  [45] = {.lex_state = 2},
  [46] = {.lex_state = 2},
  [47] = {.lex_state = 2},
  [48] = {.lex_state = 1},
  [49] = {.lex_state = 2},
  [50] = {.lex_state = 2},
  [51] = {.lex_state = 2},
  [52] = {.lex_state = 1},
  [53] = {.lex_state = 2},
  [54] = {.lex_state = 2},
  [55] = {.lex_state = 2},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 1},
  [60] = {.lex_state = 2},
  [61] = {.lex_state = 2},
  [62] = {.lex_state = 2},
  [63] = {.lex_state = 2},
  [64] = {.lex_state = 2},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 1},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 1},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 2},
  [71] = {.lex_state = 2},
  [72] = {.lex_state = 2},
  [73] = {.lex_state = 2},
  [74] = {.lex_state = 1},
  [75] = {.lex_state = 1},
  [76] = {.lex_state = 1},
  [77] = {.lex_state = 2},
  [78] = {.lex_state = 1},
  [79] = {.lex_state = 1},
  [80] = {.lex_state = 1},
  [81] = {.lex_state = 2},
  [82] = {.lex_state = 2},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 2},
  [86] = {.lex_state = 1},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 4},
  [90] = {.lex_state = 1},
  [91] = {.lex_state = 1},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 2},
  [98] = {.lex_state = 2},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 1},
  [101] = {.lex_state = 1},
  [102] = {.lex_state = 3},
  [103] = {.lex_state = 4},
  [104] = {.lex_state = 1},
  [105] = {.lex_state = 0},
  [106] = {.lex_state = 2},
  [107] = {.lex_state = 2},
  [108] = {.lex_state = 1},
  [109] = {.lex_state = 0},
  [110] = {.lex_state = 0},
  [111] = {.lex_state = 4},
  [112] = {.lex_state = 3},
  [113] = {.lex_state = 3},
  [114] = {.lex_state = 2},
  [115] = {.lex_state = 0},
  [116] = {.lex_state = 2},
  [117] = {.lex_state = 1},
  [118] = {.lex_state = 0},
  [119] = {.lex_state = 0},
  [120] = {.lex_state = 0},
  [121] = {.lex_state = 0},
  [122] = {.lex_state = 2},
  [123] = {.lex_state = 1},
  [124] = {.lex_state = 4},
  [125] = {.lex_state = 1},
  [126] = {.lex_state = 1},
  [127] = {.lex_state = 2},
  [128] = {.lex_state = 0},
  [129] = {.lex_state = 1},
  [130] = {.lex_state = 0},
  [131] = {.lex_state = 4},
  [132] = {.lex_state = 0},
  [133] = {.lex_state = 4},
  [134] = {.lex_state = 0},
  [135] = {.lex_state = 0},
  [136] = {.lex_state = 1},
  [137] = {.lex_state = 0},
  [138] = {.lex_state = 2},
  [139] = {.lex_state = 0},
  [140] = {.lex_state = 0},
  [141] = {.lex_state = 3},
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
    [sym_program_all] = STATE(135),
    [sym_procedures] = STATE(80),
    [sym_procedure] = STATE(52),
    [sym_main] = STATE(132),
    [aux_sym_procedures_repeat1] = STATE(52),
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
    STATE(108), 1,
      sym_identifier,
    STATE(110), 1,
      sym_proc_call,
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
    STATE(108), 1,
      sym_identifier,
    STATE(110), 1,
      sym_proc_call,
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
  [142] = 15,
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
    ACTIONS(62), 1,
      anon_sym_ELSE,
    ACTIONS(64), 1,
      anon_sym_ENDIF,
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(9), 1,
      sym_command,
    STATE(89), 1,
      sym_commands,
    STATE(108), 1,
      sym_identifier,
    STATE(110), 1,
      sym_proc_call,
  [188] = 3,
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
  [210] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(72), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(70), 12,
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
  [232] = 3,
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
  [253] = 14,
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
    STATE(108), 1,
      sym_identifier,
    STATE(110), 1,
      sym_proc_call,
    STATE(113), 1,
      sym_commands,
  [296] = 3,
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
  [317] = 3,
    ACTIONS(3), 1,
      sym__comment,
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
  [338] = 3,
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
  [359] = 3,
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
  [380] = 14,
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
    ACTIONS(96), 1,
      anon_sym_END,
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(9), 1,
      sym_command,
    STATE(108), 1,
      sym_identifier,
    STATE(110), 1,
      sym_proc_call,
    STATE(112), 1,
      sym_commands,
  [423] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(98), 1,
      anon_sym_END,
    ACTIONS(100), 12,
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
  [444] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(102), 1,
      anon_sym_END,
    ACTIONS(104), 12,
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
  [465] = 14,
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
    ACTIONS(106), 1,
      anon_sym_ENDWHILE,
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(9), 1,
      sym_command,
    STATE(103), 1,
      sym_commands,
    STATE(108), 1,
      sym_identifier,
    STATE(110), 1,
      sym_proc_call,
  [508] = 3,
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
  [529] = 3,
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
  [550] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(116), 1,
      anon_sym_END,
    ACTIONS(118), 12,
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
  [571] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(120), 1,
      anon_sym_END,
    ACTIONS(122), 12,
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
  [592] = 14,
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
    ACTIONS(124), 1,
      anon_sym_ENDIF,
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(9), 1,
      sym_command,
    STATE(108), 1,
      sym_identifier,
    STATE(110), 1,
      sym_proc_call,
    STATE(111), 1,
      sym_commands,
  [635] = 14,
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
    ACTIONS(126), 1,
      anon_sym_END,
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(9), 1,
      sym_command,
    STATE(102), 1,
      sym_commands,
    STATE(108), 1,
      sym_identifier,
    STATE(110), 1,
      sym_proc_call,
  [678] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(128), 1,
      anon_sym_END,
    ACTIONS(130), 12,
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
  [699] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(132), 1,
      anon_sym_END,
    ACTIONS(134), 12,
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
  [720] = 14,
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
    ACTIONS(136), 1,
      anon_sym_ENDFOR,
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(9), 1,
      sym_command,
    STATE(108), 1,
      sym_identifier,
    STATE(110), 1,
      sym_proc_call,
    STATE(133), 1,
      sym_commands,
  [763] = 14,
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
    ACTIONS(138), 1,
      anon_sym_END,
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(9), 1,
      sym_command,
    STATE(108), 1,
      sym_identifier,
    STATE(110), 1,
      sym_proc_call,
    STATE(141), 1,
      sym_commands,
  [806] = 14,
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
    ACTIONS(140), 1,
      anon_sym_UNTIL,
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(9), 1,
      sym_command,
    STATE(97), 1,
      sym_commands,
    STATE(108), 1,
      sym_identifier,
    STATE(110), 1,
      sym_proc_call,
  [849] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(142), 1,
      anon_sym_END,
    ACTIONS(144), 12,
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
  [870] = 14,
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
    ACTIONS(146), 1,
      anon_sym_ENDIF,
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(9), 1,
      sym_command,
    STATE(108), 1,
      sym_identifier,
    STATE(110), 1,
      sym_proc_call,
    STATE(124), 1,
      sym_commands,
  [913] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(148), 1,
      anon_sym_END,
    ACTIONS(150), 12,
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
  [934] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(152), 1,
      anon_sym_END,
    ACTIONS(154), 12,
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
  [955] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(156), 1,
      anon_sym_END,
    ACTIONS(158), 12,
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
  [976] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(160), 1,
      anon_sym_END,
    ACTIONS(162), 12,
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
  [997] = 14,
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
    ACTIONS(164), 1,
      anon_sym_ENDFOR,
    STATE(2), 1,
      aux_sym_commands_repeat1,
    STATE(9), 1,
      sym_command,
    STATE(108), 1,
      sym_identifier,
    STATE(110), 1,
      sym_proc_call,
    STATE(131), 1,
      sym_commands,
  [1040] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(166), 1,
      anon_sym_END,
    ACTIONS(168), 12,
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
  [1061] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(170), 1,
      anon_sym_SEMI,
    ACTIONS(172), 5,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [1075] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(176), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(174), 4,
      anon_sym_EQ,
      anon_sym_BANG_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
  [1089] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(178), 1,
      sym_pidentifier,
    ACTIONS(180), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(39), 1,
      sym_value,
    STATE(100), 1,
      sym_condition,
  [1108] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(182), 1,
      anon_sym_RPAREN,
    ACTIONS(184), 1,
      anon_sym_T,
    ACTIONS(186), 1,
      sym_pidentifier,
    STATE(67), 1,
      sym_arg_decl,
    STATE(93), 1,
      sym_args_decl,
  [1127] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(178), 1,
      sym_pidentifier,
    ACTIONS(180), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(38), 1,
      sym_value,
    STATE(96), 1,
      sym_expression,
  [1146] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(178), 1,
      sym_pidentifier,
    ACTIONS(180), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(39), 1,
      sym_value,
    STATE(105), 1,
      sym_condition,
  [1165] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(178), 1,
      sym_pidentifier,
    ACTIONS(180), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(39), 1,
      sym_value,
    STATE(137), 1,
      sym_condition,
  [1184] = 6,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(178), 1,
      sym_pidentifier,
    ACTIONS(180), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(39), 1,
      sym_value,
    STATE(101), 1,
      sym_condition,
  [1203] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(178), 1,
      sym_pidentifier,
    ACTIONS(180), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(125), 1,
      sym_value,
  [1219] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(178), 1,
      sym_pidentifier,
    ACTIONS(180), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(126), 1,
      sym_value,
  [1235] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(188), 1,
      anon_sym_PROCEDURE,
    ACTIONS(191), 1,
      anon_sym_PROGRAM,
    STATE(48), 2,
      sym_procedure,
      aux_sym_procedures_repeat1,
  [1249] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(193), 1,
      anon_sym_BEGIN,
    ACTIONS(195), 1,
      sym_pidentifier,
    STATE(63), 1,
      sym_declaration,
    STATE(127), 1,
      sym_declarations,
  [1265] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(178), 1,
      sym_pidentifier,
    ACTIONS(180), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(68), 1,
      sym_value,
  [1281] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(178), 1,
      sym_pidentifier,
    ACTIONS(180), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(121), 1,
      sym_value,
  [1297] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(5), 1,
      anon_sym_PROCEDURE,
    ACTIONS(197), 1,
      anon_sym_PROGRAM,
    STATE(48), 2,
      sym_procedure,
      aux_sym_procedures_repeat1,
  [1311] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(195), 1,
      sym_pidentifier,
    ACTIONS(199), 1,
      anon_sym_BEGIN,
    STATE(63), 1,
      sym_declaration,
    STATE(116), 1,
      sym_declarations,
  [1327] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(201), 1,
      sym_pidentifier,
    ACTIONS(203), 1,
      sym_num,
    STATE(78), 1,
      sym_identifier,
    STATE(90), 1,
      sym_value,
  [1343] = 5,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(178), 1,
      sym_pidentifier,
    ACTIONS(180), 1,
      sym_num,
    STATE(7), 1,
      sym_identifier,
    STATE(120), 1,
      sym_value,
  [1359] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(205), 1,
      anon_sym_RPAREN,
    ACTIONS(207), 1,
      anon_sym_COMMA,
    STATE(56), 1,
      aux_sym_args_repeat1,
  [1372] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(210), 1,
      anon_sym_RPAREN,
    ACTIONS(212), 1,
      anon_sym_COMMA,
    STATE(57), 1,
      aux_sym_args_decl_repeat1,
  [1385] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(215), 1,
      anon_sym_RPAREN,
    ACTIONS(217), 1,
      anon_sym_COMMA,
    STATE(65), 1,
      aux_sym_args_repeat1,
  [1398] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(52), 1,
      anon_sym_COLON_EQ,
    ACTIONS(54), 1,
      anon_sym_LBRACK,
    ACTIONS(219), 1,
      anon_sym_LPAREN,
  [1411] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(184), 1,
      anon_sym_T,
    ACTIONS(186), 1,
      sym_pidentifier,
    STATE(88), 1,
      sym_arg_decl,
  [1424] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(221), 1,
      anon_sym_RPAREN,
    ACTIONS(223), 1,
      sym_pidentifier,
    STATE(94), 1,
      sym_args,
  [1437] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(225), 1,
      anon_sym_BEGIN,
    ACTIONS(227), 1,
      anon_sym_COMMA,
    STATE(70), 1,
      aux_sym_declarations_repeat1,
  [1450] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(227), 1,
      anon_sym_COMMA,
    ACTIONS(229), 1,
      anon_sym_BEGIN,
    STATE(62), 1,
      aux_sym_declarations_repeat1,
  [1463] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(233), 1,
      anon_sym_LBRACK,
    ACTIONS(231), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1474] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(217), 1,
      anon_sym_COMMA,
    ACTIONS(235), 1,
      anon_sym_RPAREN,
    STATE(56), 1,
      aux_sym_args_repeat1,
  [1487] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(237), 1,
      anon_sym_LBRACK,
    ACTIONS(52), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1498] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(239), 1,
      anon_sym_RPAREN,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    STATE(69), 1,
      aux_sym_args_decl_repeat1,
  [1511] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(243), 3,
      anon_sym_SEMI,
      anon_sym_THEN,
      anon_sym_DO,
  [1520] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(245), 1,
      anon_sym_RPAREN,
    STATE(57), 1,
      aux_sym_args_decl_repeat1,
  [1533] = 4,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(247), 1,
      anon_sym_BEGIN,
    ACTIONS(249), 1,
      anon_sym_COMMA,
    STATE(70), 1,
      aux_sym_declarations_repeat1,
  [1546] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(252), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1554] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(195), 1,
      sym_pidentifier,
    STATE(71), 1,
      sym_declaration,
  [1564] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(254), 2,
      sym_pidentifier,
      sym_num,
  [1572] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(256), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1580] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(258), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1588] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(58), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1596] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(260), 1,
      sym_pidentifier,
    STATE(129), 1,
      sym_proc_head,
  [1606] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(66), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1614] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(70), 2,
      anon_sym_TO,
      anon_sym_DOWNTO,
  [1622] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(7), 1,
      anon_sym_PROGRAM,
    STATE(128), 1,
      sym_main,
  [1632] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(262), 2,
      anon_sym_BEGIN,
      anon_sym_COMMA,
  [1640] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(264), 2,
      sym_pidentifier,
      sym_num,
  [1648] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(266), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1656] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(268), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1664] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(178), 1,
      sym_pidentifier,
    STATE(119), 1,
      sym_identifier,
  [1674] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(270), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1682] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(272), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1690] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(274), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [1698] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(276), 1,
      anon_sym_ELSE,
    ACTIONS(278), 1,
      anon_sym_ENDIF,
  [1708] = 3,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(280), 1,
      anon_sym_TO,
    ACTIONS(282), 1,
      anon_sym_DOWNTO,
  [1718] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(284), 2,
      anon_sym_PROCEDURE,
      anon_sym_PROGRAM,
  [1726] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(286), 1,
      anon_sym_SEMI,
  [1733] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(288), 1,
      anon_sym_RPAREN,
  [1740] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(290), 1,
      anon_sym_RPAREN,
  [1747] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(292), 1,
      anon_sym_RBRACK,
  [1754] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(294), 1,
      anon_sym_SEMI,
  [1761] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(296), 1,
      anon_sym_UNTIL,
  [1768] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(298), 1,
      sym_num,
  [1775] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(300), 1,
      ts_builtin_sym_end,
  [1782] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(302), 1,
      anon_sym_DO,
  [1789] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(304), 1,
      anon_sym_THEN,
  [1796] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(306), 1,
      anon_sym_END,
  [1803] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(308), 1,
      anon_sym_ENDWHILE,
  [1810] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(310), 1,
      anon_sym_IS,
  [1817] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(312), 1,
      anon_sym_SEMI,
  [1824] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(314), 1,
      sym_pidentifier,
  [1831] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(316), 1,
      sym_num,
  [1838] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(318), 1,
      anon_sym_COLON_EQ,
  [1845] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(320), 1,
      anon_sym_RBRACK,
  [1852] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(322), 1,
      anon_sym_SEMI,
  [1859] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(324), 1,
      anon_sym_ENDIF,
  [1866] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(326), 1,
      anon_sym_END,
  [1873] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(328), 1,
      anon_sym_END,
  [1880] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(330), 1,
      sym_pidentifier,
  [1887] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(332), 1,
      ts_builtin_sym_end,
  [1894] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(334), 1,
      anon_sym_BEGIN,
  [1901] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(336), 1,
      anon_sym_FROM,
  [1908] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(338), 1,
      anon_sym_SEMI,
  [1915] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(340), 1,
      anon_sym_SEMI,
  [1922] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(342), 1,
      anon_sym_SEMI,
  [1929] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(344), 1,
      anon_sym_SEMI,
  [1936] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(346), 1,
      sym_pidentifier,
  [1943] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(348), 1,
      anon_sym_IS,
  [1950] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(350), 1,
      anon_sym_ENDIF,
  [1957] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(352), 1,
      anon_sym_DO,
  [1964] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(354), 1,
      anon_sym_DO,
  [1971] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(356), 1,
      anon_sym_BEGIN,
  [1978] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(358), 1,
      ts_builtin_sym_end,
  [1985] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(360), 1,
      anon_sym_IS,
  [1992] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(362), 1,
      anon_sym_LPAREN,
  [1999] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(364), 1,
      anon_sym_ENDFOR,
  [2006] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(366), 1,
      ts_builtin_sym_end,
  [2013] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(368), 1,
      anon_sym_ENDFOR,
  [2020] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(370), 1,
      ts_builtin_sym_end,
  [2027] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(372), 1,
      ts_builtin_sym_end,
  [2034] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(374), 1,
      anon_sym_IS,
  [2041] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(376), 1,
      anon_sym_SEMI,
  [2048] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(378), 1,
      anon_sym_COLON,
  [2055] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(380), 1,
      ts_builtin_sym_end,
  [2062] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(382), 1,
      anon_sym_RBRACK,
  [2069] = 2,
    ACTIONS(3), 1,
      sym__comment,
    ACTIONS(384), 1,
      anon_sym_END,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 47,
  [SMALL_STATE(4)] = 94,
  [SMALL_STATE(5)] = 119,
  [SMALL_STATE(6)] = 142,
  [SMALL_STATE(7)] = 188,
  [SMALL_STATE(8)] = 210,
  [SMALL_STATE(9)] = 232,
  [SMALL_STATE(10)] = 253,
  [SMALL_STATE(11)] = 296,
  [SMALL_STATE(12)] = 317,
  [SMALL_STATE(13)] = 338,
  [SMALL_STATE(14)] = 359,
  [SMALL_STATE(15)] = 380,
  [SMALL_STATE(16)] = 423,
  [SMALL_STATE(17)] = 444,
  [SMALL_STATE(18)] = 465,
  [SMALL_STATE(19)] = 508,
  [SMALL_STATE(20)] = 529,
  [SMALL_STATE(21)] = 550,
  [SMALL_STATE(22)] = 571,
  [SMALL_STATE(23)] = 592,
  [SMALL_STATE(24)] = 635,
  [SMALL_STATE(25)] = 678,
  [SMALL_STATE(26)] = 699,
  [SMALL_STATE(27)] = 720,
  [SMALL_STATE(28)] = 763,
  [SMALL_STATE(29)] = 806,
  [SMALL_STATE(30)] = 849,
  [SMALL_STATE(31)] = 870,
  [SMALL_STATE(32)] = 913,
  [SMALL_STATE(33)] = 934,
  [SMALL_STATE(34)] = 955,
  [SMALL_STATE(35)] = 976,
  [SMALL_STATE(36)] = 997,
  [SMALL_STATE(37)] = 1040,
  [SMALL_STATE(38)] = 1061,
  [SMALL_STATE(39)] = 1075,
  [SMALL_STATE(40)] = 1089,
  [SMALL_STATE(41)] = 1108,
  [SMALL_STATE(42)] = 1127,
  [SMALL_STATE(43)] = 1146,
  [SMALL_STATE(44)] = 1165,
  [SMALL_STATE(45)] = 1184,
  [SMALL_STATE(46)] = 1203,
  [SMALL_STATE(47)] = 1219,
  [SMALL_STATE(48)] = 1235,
  [SMALL_STATE(49)] = 1249,
  [SMALL_STATE(50)] = 1265,
  [SMALL_STATE(51)] = 1281,
  [SMALL_STATE(52)] = 1297,
  [SMALL_STATE(53)] = 1311,
  [SMALL_STATE(54)] = 1327,
  [SMALL_STATE(55)] = 1343,
  [SMALL_STATE(56)] = 1359,
  [SMALL_STATE(57)] = 1372,
  [SMALL_STATE(58)] = 1385,
  [SMALL_STATE(59)] = 1398,
  [SMALL_STATE(60)] = 1411,
  [SMALL_STATE(61)] = 1424,
  [SMALL_STATE(62)] = 1437,
  [SMALL_STATE(63)] = 1450,
  [SMALL_STATE(64)] = 1463,
  [SMALL_STATE(65)] = 1474,
  [SMALL_STATE(66)] = 1487,
  [SMALL_STATE(67)] = 1498,
  [SMALL_STATE(68)] = 1511,
  [SMALL_STATE(69)] = 1520,
  [SMALL_STATE(70)] = 1533,
  [SMALL_STATE(71)] = 1546,
  [SMALL_STATE(72)] = 1554,
  [SMALL_STATE(73)] = 1564,
  [SMALL_STATE(74)] = 1572,
  [SMALL_STATE(75)] = 1580,
  [SMALL_STATE(76)] = 1588,
  [SMALL_STATE(77)] = 1596,
  [SMALL_STATE(78)] = 1606,
  [SMALL_STATE(79)] = 1614,
  [SMALL_STATE(80)] = 1622,
  [SMALL_STATE(81)] = 1632,
  [SMALL_STATE(82)] = 1640,
  [SMALL_STATE(83)] = 1648,
  [SMALL_STATE(84)] = 1656,
  [SMALL_STATE(85)] = 1664,
  [SMALL_STATE(86)] = 1674,
  [SMALL_STATE(87)] = 1682,
  [SMALL_STATE(88)] = 1690,
  [SMALL_STATE(89)] = 1698,
  [SMALL_STATE(90)] = 1708,
  [SMALL_STATE(91)] = 1718,
  [SMALL_STATE(92)] = 1726,
  [SMALL_STATE(93)] = 1733,
  [SMALL_STATE(94)] = 1740,
  [SMALL_STATE(95)] = 1747,
  [SMALL_STATE(96)] = 1754,
  [SMALL_STATE(97)] = 1761,
  [SMALL_STATE(98)] = 1768,
  [SMALL_STATE(99)] = 1775,
  [SMALL_STATE(100)] = 1782,
  [SMALL_STATE(101)] = 1789,
  [SMALL_STATE(102)] = 1796,
  [SMALL_STATE(103)] = 1803,
  [SMALL_STATE(104)] = 1810,
  [SMALL_STATE(105)] = 1817,
  [SMALL_STATE(106)] = 1824,
  [SMALL_STATE(107)] = 1831,
  [SMALL_STATE(108)] = 1838,
  [SMALL_STATE(109)] = 1845,
  [SMALL_STATE(110)] = 1852,
  [SMALL_STATE(111)] = 1859,
  [SMALL_STATE(112)] = 1866,
  [SMALL_STATE(113)] = 1873,
  [SMALL_STATE(114)] = 1880,
  [SMALL_STATE(115)] = 1887,
  [SMALL_STATE(116)] = 1894,
  [SMALL_STATE(117)] = 1901,
  [SMALL_STATE(118)] = 1908,
  [SMALL_STATE(119)] = 1915,
  [SMALL_STATE(120)] = 1922,
  [SMALL_STATE(121)] = 1929,
  [SMALL_STATE(122)] = 1936,
  [SMALL_STATE(123)] = 1943,
  [SMALL_STATE(124)] = 1950,
  [SMALL_STATE(125)] = 1957,
  [SMALL_STATE(126)] = 1964,
  [SMALL_STATE(127)] = 1971,
  [SMALL_STATE(128)] = 1978,
  [SMALL_STATE(129)] = 1985,
  [SMALL_STATE(130)] = 1992,
  [SMALL_STATE(131)] = 1999,
  [SMALL_STATE(132)] = 2006,
  [SMALL_STATE(133)] = 2013,
  [SMALL_STATE(134)] = 2020,
  [SMALL_STATE(135)] = 2027,
  [SMALL_STATE(136)] = 2034,
  [SMALL_STATE(137)] = 2041,
  [SMALL_STATE(138)] = 2048,
  [SMALL_STATE(139)] = 2055,
  [SMALL_STATE(140)] = 2062,
  [SMALL_STATE(141)] = 2069,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(136),
  [9] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_commands, 1, 0, 9),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [13] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_commands, 1, 0, 9),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [27] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 18),
  [29] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 18), SHIFT_REPEAT(45),
  [32] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 18),
  [34] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 18), SHIFT_REPEAT(40),
  [37] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 18), SHIFT_REPEAT(29),
  [40] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 18), SHIFT_REPEAT(114),
  [43] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 18), SHIFT_REPEAT(85),
  [46] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 18), SHIFT_REPEAT(51),
  [49] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 2, 0, 18), SHIFT_REPEAT(59),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 1, 0, 6),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [56] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_identifier, 1, 0, 6),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_identifier, 4, 0, 35),
  [60] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_identifier, 4, 0, 35),
  [62] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [64] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [66] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 1, 0, 4),
  [68] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_value, 1, 0, 4),
  [70] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 1, 0, 15),
  [72] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_value, 1, 0, 15),
  [74] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_commands_repeat1, 1, 0, 8),
  [76] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_commands_repeat1, 1, 0, 8),
  [78] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [80] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 7, 0, 44),
  [82] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 7, 0, 44),
  [84] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 9, 0, 48),
  [86] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 9, 0, 48),
  [88] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 9, 0, 47),
  [90] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 9, 0, 47),
  [92] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 8, 0, 46),
  [94] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 8, 0, 46),
  [96] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [98] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 2, 0, 17),
  [100] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 2, 0, 17),
  [102] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 6, 0, 43),
  [104] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 6, 0, 43),
  [106] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [108] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 6, 0, 42),
  [110] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 6, 0, 42),
  [112] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 3, 0, 26),
  [114] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3, 0, 26),
  [116] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 3, 0, 27),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3, 0, 27),
  [120] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 8, 0, 45),
  [122] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 8, 0, 45),
  [124] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [126] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [128] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 5, 0, 40),
  [130] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 5, 0, 40),
  [132] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 5, 0, 39),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 5, 0, 39),
  [136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [142] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 5, 0, 38),
  [144] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 5, 0, 38),
  [146] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [148] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 4, 0, 31),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 4, 0, 31),
  [152] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 4, 0, 33),
  [154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 4, 0, 33),
  [156] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 5, 0, 37),
  [158] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 5, 0, 37),
  [160] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 4, 0, 34),
  [162] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 4, 0, 34),
  [164] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [166] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 4, 0, 36),
  [168] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 4, 0, 36),
  [170] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 1, 0, 28),
  [172] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [174] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [176] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [180] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [182] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [184] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [186] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [188] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_procedures_repeat1, 2, 0, 0), SHIFT_REPEAT(77),
  [191] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_procedures_repeat1, 2, 0, 0),
  [193] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [195] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [197] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedures, 1, 0, 2),
  [199] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [201] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [203] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [205] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 23),
  [207] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 23), SHIFT_REPEAT(106),
  [210] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 23),
  [212] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 23), SHIFT_REPEAT(60),
  [215] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args, 1, 0, 7),
  [217] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [219] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [221] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [223] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [225] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declarations, 2, 0, 10),
  [227] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [229] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declarations, 1, 0, 5),
  [231] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declaration, 1, 0, 4),
  [233] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [235] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args, 2, 0, 13),
  [237] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [239] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 1, 0, 7),
  [241] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [243] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_condition, 3, 0, 32),
  [245] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_args_decl, 2, 0, 13),
  [247] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 21),
  [249] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 21), SHIFT_REPEAT(72),
  [252] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_declarations_repeat1, 2, 0, 20),
  [254] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [256] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 6, 0, 24),
  [258] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 6, 0, 25),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declaration, 6, 0, 41),
  [264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [266] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arg_decl, 1, 0, 6),
  [268] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_repeat1, 2, 0, 22),
  [270] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 7, 0, 30),
  [272] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arg_decl, 2, 0, 11),
  [274] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_args_decl_repeat1, 2, 0, 22),
  [276] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [284] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_procedure, 5, 0, 14),
  [286] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_call, 4, 0, 12),
  [288] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [290] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [292] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [294] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [296] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [298] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [300] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 6, 0, 29),
  [302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [304] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [306] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [308] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [310] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_head, 4, 0, 12),
  [312] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [314] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [316] = {.entry = {.count = 1, .reusable = true}}, SHIFT(138),
  [318] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [320] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [324] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [326] = {.entry = {.count = 1, .reusable = true}}, SHIFT(134),
  [328] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [330] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [332] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 4, 0, 0),
  [334] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [336] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [338] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_call, 3, 0, 6),
  [340] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [342] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 3, 0, 32),
  [344] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [346] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [348] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_proc_head, 3, 0, 6),
  [350] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [352] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [354] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [356] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [358] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program_all, 2, 0, 3),
  [360] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [362] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [364] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [366] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program_all, 1, 0, 1),
  [368] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [370] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 5, 0, 16),
  [372] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [374] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [376] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [378] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [380] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_main, 5, 0, 19),
  [382] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [384] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
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
