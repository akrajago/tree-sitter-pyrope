#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree_sitter/api.h>

#include "prpfmt.h"

void print_indent(PrpfmtState *st) {
  for (int i = 0; i < st->indent_level * st->indent_size; i++) {
    fprintf(st->outfile, " ");
  }
}

void print_tree(TSTree *tree, PrpfmtState *st) {
  // Get root and child info
  TSNode root_node = ts_tree_root_node(tree);
  uint32_t root_child_count = ts_node_child_count(root_node);

  // Iterate over the root's children
  for (uint32_t i = 0; i < root_child_count; i++) {
    TSNode child = ts_node_child(root_node, i);
    print_statement(child, st);
  }
}

void print_comment_inline(TSNode node, PrpfmtState *st) {
  char *node_text = get_node_text(node, st->source_code);
  if (node_text) {
    fprintf(st->outfile, " %s", node_text);
    free(node_text);
  }
}

void print_comment_newline(TSNode node, PrpfmtState *st) {
  char *node_text = get_node_text(node, st->source_code);
  if (node_text) {
    print_indent(st);
    fprintf(st->outfile, "%s\n", node_text);
    free(node_text);
  }
}

void print_statement(TSNode node, PrpfmtState *st) {
  if (ts_node_grammar_symbol(node) == sym_comment) {
    print_comment_newline(node, st);
    return;
  }

  uint32_t child_count = ts_node_child_count(node);
  for (uint32_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    TSSymbol symbol = ts_node_grammar_symbol(child);

    if (i == 0 && symbol != sym_scope_statement) {
      print_indent(st);
    }

    switch (symbol) {
      case sym_assignment_or_declaration_statement:
        print_assignment_or_declaration_statement(child, st);
        break;
      case sym_control_statement:
        print_control_statement(child, st);
        break;
      case sym_declaration_statement:
        print_declaration_statement(child, st);
        break;
      case sym_enum_assignment_statement:
        print_enum_assignment_statement(child, st);
        break;
      case sym_expression_statement:
        print_expression_statement(child, st);
        break;
      case sym_for_statement:
        print_for_statement(child, st);
        break;
      case sym_function_call_statement:
        print_function_call_statement(child, st);
        break;
      case sym_impl_statement:
        print_impl_statement(child, st);
        break;
      case sym_import_statement:
        print_import_statement(child, st);
        break;
      case sym_lambda:
        print_lambda(child, st);
        break;
      case sym_loop_statement:
        print_loop_statement(child, st);
        break;
      case sym_scope_statement:
        print_scope_statement(child, st);
        break;
      case sym_test_statement:
        print_test_statement(child, st);
        break;
      case sym_type_statement:
        print_type_statement(child, st);
        break;
      case sym_while_statement:
        print_while_statement(child, st);
        break;
      case sym_comment:
        print_comment_inline(child, st);
        break;
    }
  }
  fprintf(st->outfile, "\n");
}

void print_assignment_or_declaration_statement(TSNode node, PrpfmtState *st) {
  uint32_t child_count = ts_node_child_count(node);
  for (uint32_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    TSSymbol symbol = ts_node_grammar_symbol(child);

    switch (symbol) {
      case sym_assignment:
        print_assignment(child, st);
        break;
      case sym_when_unless_cond:
      case anon_sym_SEMI:
      case sym__automatic_semicolon:
        print__semicolon(child, st);
        break;
      case sym_comment:
        print_comment_inline(child, st);
        break;
    }
  }
}

void print_control_statement(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "control_statement\n");
}

void print_declaration_statement(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "declaration_statement\n");
}

void print_enum_assignment_statement(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "enum_assignment_statement\n");
}

void print_expression_statement(TSNode node, PrpfmtState *st) {
  uint32_t child_count = ts_node_child_count(node);

  for (uint32_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    TSSymbol symbol = ts_node_grammar_symbol(child);

    switch (symbol) {
      case sym_for_comprehension:
        print_for_comprehension(child, st);
        break;
      case sym_when_unless_cond:
      case anon_sym_SEMI:
      case sym__automatic_semicolon:
        print__semicolon(child, st);
        break;
      case sym_comment:
        print_comment_inline(child, st);
        break;
      default:
        print__expression(child, st);
        break;
    }
  }
}

void print_for_statement(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "for_statement\n");
}

void print_function_call_statement(TSNode node, PrpfmtState *st) {
  uint32_t child_count = ts_node_child_count(node);
  for (uint32_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    TSSymbol symbol = ts_node_grammar_symbol(child);
    const char *field_name = ts_node_field_name_for_child(node, i);

    if (field_name) {
      if (strcmp(field_name, "function") == 0) {
        print_complex_identifier(child, st);
        continue;
      }
      if (strcmp(field_name, "argument") == 0) {
        fprintf(st->outfile, " ");
        print_expression_list(child, st);
        continue;
      }
    }

    if (symbol == sym_when_unless_cond || symbol == anon_sym_SEMI || symbol == sym__automatic_semicolon) {
      print__semicolon(child, st);
    }

    if (symbol == sym_comment) {
      print_comment_inline(child, st);
    }
  }
}

void print_impl_statement(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "impl_statement\n");
}

void print_import_statement(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "import_statement\n");
}

void print_lambda(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "lambda\n");
}

void print_loop_statement(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "loop_statement\n");
}

void print_scope_statement(TSNode node, PrpfmtState *st) {
  uint32_t child_count = ts_node_child_count(node);
  for (uint32_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    TSSymbol symbol = ts_node_grammar_symbol(child);

    switch (symbol) {
      case anon_sym_LBRACE:
        fprintf(st->outfile, "{\n");
        st->indent_level++;
        break;
      case sym_statement:
        print_statement(child, st);
        break;
      case anon_sym_RBRACE:
        st->indent_level--;
        print_indent(st);
        fprintf(st->outfile, "}");
        break;
      case sym_comment:
        print_comment_inline(child, st);
        break;
    }
  }
}

void print_test_statement(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "test_statement\n");
}

void print_type_statement(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "type_statement\n");
}

void print_while_statement(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "while_statement\n");
}

void print_assignment(TSNode node, PrpfmtState *st) {
  uint32_t child_count = ts_node_child_count(node);
  for (uint32_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    TSSymbol symbol = ts_node_grammar_symbol(child);
    const char *field_name = ts_node_field_name_for_child(node, i);

    if (field_name) {
      if (strcmp(field_name, "decl") == 0) {
        print_var_or_let_or_reg(child, st);
        fprintf(st->outfile, " ");
        continue;
      }
      if (strcmp(field_name, "lvalue") == 0) {
        if (symbol == sym_lvalue_list) {
          print_lvalue_list(child, st);
        } else if (symbol == sym_typed_identifier) {
          print_typed_identifier(child, st);
        } else if (symbol == sym_complex_identifier) {
          print_complex_identifier(child, st);
        }
        continue;
      }
      if (strcmp(field_name, "type") == 0) {
        print_type_cast(child, st);
        continue;
      }
      if (strcmp(field_name, "operator") == 0) {
        fprintf(st->outfile, " ");
        print_assignment_operator(child, st);
        fprintf(st->outfile, " ");
        continue;
      }
      if (strcmp(field_name, "delay") == 0) {
        print_assignment_delay(child, st);
        continue;
      }
      if (strcmp(field_name, "rvalue") == 0) {
        if (symbol == sym_enum_definition) {
          print_enum_definition(child, st);
        } else if (symbol == sym_ref_identifier) {
          print_ref_identifier(child, st);
        } else {
          print__expression_with_comprehension(child, st);
        }
        continue;
      }
    }

    // Handle literals/structural tokens
    switch (symbol) {
      case anon_sym_LPAREN: fprintf(st->outfile, "("); break;
      case anon_sym_RPAREN: fprintf(st->outfile, ")"); break;
      case sym_comment: print_comment_inline(child, st); break;
    }
  }
}

void print_enum_assignment(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "enum_assignment\n");
}

void print_arg_item(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "arg_item\n");
}

void print_arg_item_list(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "arg_item_list\n");
}

void print_arg_list(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "arg_list\n");
}

void print_array_type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "array_type\n");
}

void print_assignment_delay(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "assignment_delay\n");
}

void print_assignment_operator(TSNode node, PrpfmtState *st) {
  char *text = get_node_text(node, st->source_code);
  if (text) {
    fprintf(st->outfile, "%s", text);
    free(text);
  }
}

void print_attribute_item(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "attribute_item\n");
}

void print_attribute_item_list(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "attribute_item_list\n");
}

void print_attribute_list(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "attribute_list\n");
}

void print_attributes(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "attributes\n");
}

void print_binary_expression(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "binary_expression\n");
}

void print_bit_select(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "bit_select\n");
}

void print_bit_select_type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "bit_select_type\n");
}

void print_bit_selection(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "bit_selection\n");
}

void print_boolean_type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "boolean_type\n");
}

void print_bounded_integer_type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "bounded_integer_type\n");
}

void print_cassert_statement(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "cassert_statement\n");
}

void print_comb_tok(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "comb_tok\n");
}

void print_complex_identifier(TSNode node, PrpfmtState *st) {
  uint32_t child_count = ts_node_child_count(node);
  for (uint32_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    TSSymbol symbol = ts_node_grammar_symbol(child);

    switch (symbol) {
      case sym_identifier:
        print_identifier(child, st);
        break;
      case sym_dot_expression:
        print_dot_expression(child, st);
        break;
      case sym_selection:
        print_selection(child, st);
        break;
      case sym_timed_identifier:
        print_timed_identifier(child, st);
        break;
      case sym_comment:
        print_comment_inline(child, st);
        break;
      default:
        // If child is a token, print it
        if (ts_node_child_count(child) == 0) {
          char *text = get_node_text(child, st->source_code);
          if (text) {
            fprintf(st->outfile, "%s", text);
            free(text);
          }
        }
        break;
    }
  }
}

void print_complex_identifier_list(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "complex_identifier_list\n");
}

void print_complex_string_literal(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "complex_string_literal\n");
}

void print_constant(TSNode node, PrpfmtState *st) {
  char *text = get_node_text(node, st->source_code);
  if (text) {
    fprintf(st->outfile, "%s", text);
    free(text);
  }
}

void print_delay_tok(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "delay_tok\n");
}

void print_description(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "description\n");
}

void print_dot_expression(TSNode node, PrpfmtState *st) {
  uint32_t child_count = ts_node_child_count(node);
  for (uint32_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    TSSymbol symbol = ts_node_grammar_symbol(child);

    if (symbol == anon_sym_DOT) {
      fprintf(st->outfile, ".");
    } else if (symbol == sym_identifier) {
      print_identifier(child, st);
    } else if (symbol == sym_constant) {
      print_constant(child, st);
    } else {
      print__restricted_expression(child, st);
    }
  }
}

void print_dot_expression_type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "dot_expression_type\n");
}

void print_enum_definition(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "enum_definition\n");
}

void print_expression_list(TSNode node, PrpfmtState *st) {
  uint32_t child_count = ts_node_child_count(node);
  for (uint32_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    TSSymbol symbol = ts_node_grammar_symbol(child);
    
    if (symbol == anon_sym_COMMA) {
      fprintf(st->outfile, ", ");
    } else if (symbol == sym_comment) {
      print_comment_inline(child, st);
    } else {
      print__expression(child, st);
    }
  }
}

void print_expression_type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "expression_type\n");
}

void print_flow_tok(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "flow_tok\n");
}

void print_for_comprehension(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "for_comprehension\n");
}

void print_func_def_verification(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "func_def_verification\n");
}

void print_function_call_expression(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "function_call_expression\n");
}

void print_function_call_type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "function_call_type\n");
}

void print_function_definition(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "function_definition\n");
}

void print_function_definition_decl(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "function_definition_decl\n");
}

void print_identifier(TSNode node, PrpfmtState *st) {
  char *text = get_node_text(node, st->source_code);
  if (text) {
    fprintf(st->outfile, "%s", text);
    free(text);
  }
}

void print_if_expression(TSNode node, PrpfmtState *st) {
  uint32_t child_count = ts_node_child_count(node);
  for (uint32_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    TSSymbol symbol = ts_node_grammar_symbol(child);
    const char *field_name = ts_node_field_name_for_child(node, i);

    if (field_name && strcmp(field_name, "condition") == 0) {
      fprintf(st->outfile, " ");
      print__expression(child, st);
      continue;
    }

    switch (symbol) {
      case anon_sym_unique:
        fprintf(st->outfile, "unique ");
        break;
      case anon_sym_if:
        fprintf(st->outfile, "if");
        break;
      case sym_stmt_list:
        fprintf(st->outfile, " ");
        print_stmt_list(child, st);
        break;
      case anon_sym_SEMI:
        fprintf(st->outfile, " ;");
        break;
      case sym_scope_statement:
        fprintf(st->outfile, " ");
        print_scope_statement(child, st);
        break;
      case anon_sym_elif:
        fprintf(st->outfile, " elif");
        break;
      case anon_sym_else:
        fprintf(st->outfile, " else");
        break;
      case sym_comment:
        print_comment_inline(child, st);
        break;
    }
  }
}

void print_lvalue_item(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "lvalue_item\n");
}

void print_lvalue_list(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "lvalue_list\n");
}

void print_match_expression(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "match_expression\n");
}

void print_match_list(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "match_list\n");
}

void print_match_operator(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "match_operator\n");
}

void print_member_select(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "member_select\n");
}

void print_member_selection(TSNode node, PrpfmtState *st) {
  uint32_t child_count = ts_node_child_count(node);
  for (uint32_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    TSSymbol symbol = ts_node_grammar_symbol(child);

    if (symbol == sym_member_select) {
      print_member_select(child, st);
    } else {
      print__restricted_expression(child, st);
    }
  }
}

void print_module_path(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "module_path\n");
}

void print_optional_expression(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "optional_expression\n");
}

void print_pipe_tok(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "pipe_tok\n");
}

void print_primitive_type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "primitive_type\n");
}

void print_range_type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "range_type\n");
}

void print_ref_identifier(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "ref_identifier\n");
}

void print_select(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "select\n");
}

void print_select_options(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "select_options\n");
}

void print_selection(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "selection\n");
}

void print_sized_integer_type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "sized_integer_type\n");
}

void print_stmt_list(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "stmt_list\n");
}

void print_string_type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "string_type\n");
}

void print_timed_identifier(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "timed_identifier\n");
}

void print_tuple(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "tuple\n");
}

void print_tuple_list(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "tuple_list\n");
}

void print_tuple_sq(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "tuple_sq\n");
}

void print_type_cast(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "type_cast\n");
}

void print_type_or_identifier(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "type_or_identifier\n");
}

void print_type_specification(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "type_specification\n");
}

void print_type_type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "type_type\n");
}

void print_typed_declaration(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "typed_declaration\n");
}

void print_typed_identifier(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "typed_identifier\n");
}

void print_typed_identifier_list(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "typed_identifier_list\n");
}

void print_unary_expression(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "unary_expression\n");
}

void print_unsized_integer_type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "unsized_integer_type\n");
}

void print_var_or_let_or_reg(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "var_or_let_or_reg\n");
}

void print_when_unless_cond(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "when_unless_cond\n");
}

void print__binary_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_binary_number\n");
}

void print__bool_literal(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_bool_literal\n");
}

void print__decimal_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_decimal_number\n");
}

void print__expression(TSNode node, PrpfmtState *st) {
  TSSymbol symbol = ts_node_grammar_symbol(node);

  switch (symbol) {
    case sym_binary_expression:
      print_binary_expression(node, st);
      break;
    case sym_if_expression:
      print_if_expression(node, st);
      break;
    case sym_match_expression:
      print_match_expression(node, st);
      break;
    case sym_type_specification:
      print_type_specification(node, st);
      break;
    case sym_unary_expression:
      print_unary_expression(node, st);
      break;
    case sym_complex_identifier:
    case sym_constant:
    case sym_function_call_expression:
    case sym_lambda:
    case sym_tuple:
    case sym_optional_expression:
    case sym__restricted_expression:
    default:
      print__restricted_expression(node, st);
      break;
  }
}

void print__expression_with_comprehension(TSNode node, PrpfmtState *st) {
  TSSymbol symbol = ts_node_grammar_symbol(node);
  if (symbol == sym_for_comprehension) {
    print_for_comprehension(node, st);
  } else {
    print__expression(node, st);
  }
}

void print__hex_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_hex_number\n");
}

void print__neg_binary_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_neg_binary_number\n");
}

void print__neg_decimal_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_neg_decimal_number\n");
}

void print__neg_hex_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_neg_hex_number\n");
}

void print__neg_octal_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_neg_octal_number\n");
}

void print__neg_scaled_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_neg_scaled_number\n");
}

void print__neg_simple_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_neg_simple_number\n");
}

void print__neg_typed_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_neg_typed_number\n");
}

void print__number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_number\n");
}

void print__octal_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_octal_number\n");
}

void print__restricted_expression(TSNode node, PrpfmtState *st) {
  TSSymbol symbol = ts_node_grammar_symbol(node);

  switch (symbol) {
    case sym_complex_identifier:
      print_complex_identifier(node, st);
      break;
    case sym_constant:
      print_constant(node, st);
      break;
    case sym_function_call_expression:
      print_function_call_expression(node, st);
      break;
    case sym_lambda:
      print_lambda(node, st);
      break;
    case sym_tuple:
      print_tuple(node, st);
      break;
    case sym_optional_expression:
      print_optional_expression(node, st);
      break;
    case sym_if_expression:
      print_if_expression(node, st);
      break;
    case sym_match_expression:
      print_match_expression(node, st);
      break;
    default:
      // Fallback: print node text if it's a leaf or we don't have a specific handler
      if (ts_node_child_count(node) == 0) {
        char *text = get_node_text(node, st->source_code);
        if (text) {
          fprintf(st->outfile, "%s", text);
          free(text);
        }
      }
      break;
  }
}

void print__scaled_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_scaled_number\n");
}

void print__semicolon(TSNode node, PrpfmtState *st) {
  TSSymbol symbol = ts_node_grammar_symbol(node);

  switch (symbol) {
    case anon_sym_SEMI:
      fprintf(st->outfile, " ;");
      break;
    case sym_when_unless_cond:
      fprintf(st->outfile, " ");
      print_when_unless_cond(node, st);
      break;
  }
}

void print__simple_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_simple_number\n");
}

void print__simple_string_literal(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_simple_string_literal\n");
}

void print__space(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_space\n");
}

void print__string_literal(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_string_literal\n");
}

void print__timing_sequence(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_timing_sequence\n");
}

void print__tuple_item(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_tuple_item\n");
}

void print__type(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_type\n");
}

void print__typed_number(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_typed_number\n");
}

void print__unknown_literal(TSNode node, PrpfmtState *st) {
    fprintf(st->outfile, "_unknown_literal\n");
}


char *get_node_text(TSNode node, const char *source_code) {
  // Get byte position of text in original code
  uint32_t start_byte = ts_node_start_byte(node);
  uint32_t end_byte = ts_node_end_byte(node);
  uint32_t length = end_byte - start_byte;

  // Allocate memory for node text
  char *text = (char *) malloc(length + 1);
  if (text == NULL) {
    perror("Failed to allocate memory for node text");
    return NULL;
  }

  // Retrieve original text
  strncpy(text, source_code + start_byte, length);
  text[length] = '\0';

  return text;
}

void format_node_recursive(TSNode node, const char *source_code, uint32_t *last_printed_end, FILE *outfile) {
  // Only print if leaf node
  if (ts_node_child_count(node) == 0) {
    uint32_t start_byte = ts_node_start_byte(node);
    // Preserve whitespace between last printed node and current node
    for (uint32_t i = *last_printed_end; i < start_byte; ++i) {
      fprintf(outfile, "%c", source_code[i]);
    }

    // Get node text and update node pointer
    char *node_text = get_node_text(node, source_code);
    if (node_text) {
      fprintf(outfile, "%s", node_text);
      free(node_text);
    }
    *last_printed_end = ts_node_end_byte(node);
  }

  TSTreeCursor cursor = ts_tree_cursor_new(node);

  // Recursively traverse child nodes
  if (ts_tree_cursor_goto_first_child(&cursor)) {
    do {
      TSNode current_child_node = ts_tree_cursor_current_node(&cursor);
      format_node_recursive(current_child_node, source_code, last_printed_end,
                         outfile);
    } while (ts_tree_cursor_goto_next_sibling(&cursor));
  }

  ts_tree_cursor_delete(&cursor);
}

// Helper for test_print_all_nodes
void test_print_all_nodes_recursive(TSNode node, const char *source_code, int indent_level) {
  for (int i = 0; i < indent_level; ++i) {
    printf("  ");
  }
  printf("Node Type: %s\n", ts_node_type(node));

  uint32_t child_count = ts_node_child_count(node);
  for (uint32_t i = 0; i < child_count; ++i) {
    TSNode child = ts_node_child(node, i);
    test_print_all_nodes_recursive(child, source_code, indent_level + 1);
  }
}

// Test function to print all nodes
void test_print_all_nodes(TSTree *tree, const char *source_code) {
  TSNode root_node = ts_tree_root_node(tree);
  test_print_all_nodes_recursive(root_node, source_code, 0);
}
