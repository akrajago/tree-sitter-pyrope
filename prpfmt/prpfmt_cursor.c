#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree_sitter/api.h>

#include "prpfmt.h"

void print_tree(TSTree *tree, char *source_code, FILE *outfile) {
  // Get root and child info
  TSNode root_node = ts_tree_root_node(tree);
  uint32_t root_child_count = ts_node_child_count(root_node);

  // Iterate over the root's children
  for (uint32_t i = 0; i < root_child_count; i++) {
    TSNode child = ts_node_child(root_node, i);
    print_statement(child, source_code, outfile);
  }
}

void print_comment(TSNode node, const char *source_code, FILE *outfile) {
  uint32_t start_byte = ts_node_start_byte(node);

  char *node_text = get_node_text(node, source_code);
  if (node_text) {
    fprintf(outfile, "%s", node_text);
    free(node_text);
  }
}

void print_statement(TSNode node, const char *source_code, FILE *outfile) {
  // Check if comment
  if (ts_node_grammar_symbol(node) == sym_comment) {
    print_comment(node, source_code, outfile);
  } else {
    fprintf(outfile, "statement\n");
  }
}

void print_assignment_or_declaration_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "assignment_or_declaration_statement\n");
}

void print_control_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "control_statement\n");
}

void print_declaration_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "declaration_statement\n");
}

void print_enum_assignment_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "enum_assignment_statement\n");
}

void print_expression_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "expression_statement\n");
}

void print_for_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "for_statement\n");
}

void print_function_call_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "function_call_statement\n");
}

void print_impl_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "impl_statement\n");
}

void print_import_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "import_statement\n");
}

void print_lambda(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "lambda\n");
}

void print_loop_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "loop_statement\n");
}

void print_scope_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "scope_statement\n");
}

void print_test_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "test_statement\n");
}

void print_type_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "type_statement\n");
}

void print_while_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "while_statement\n");
}

void print_assignment(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "assignment\n");
}

void print_enum_assignment(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "enum_assignment\n");
}

void print_arg_item(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "arg_item\n");
}

void print_arg_item_list(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "arg_item_list\n");
}

void print_arg_list(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "arg_list\n");
}

void print_array_type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "array_type\n");
}

void print_assignment_delay(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "assignment_delay\n");
}

void print_assignment_operator(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "assignment_operator\n");
}

void print_attribute_item(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "attribute_item\n");
}

void print_attribute_item_list(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "attribute_item_list\n");
}

void print_attribute_list(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "attribute_list\n");
}

void print_attributes(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "attributes\n");
}

void print_binary_expression(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "binary_expression\n");
}

void print_bit_select(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "bit_select\n");
}

void print_bit_select_type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "bit_select_type\n");
}

void print_bit_selection(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "bit_selection\n");
}

void print_boolean_type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "boolean_type\n");
}

void print_bounded_integer_type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "bounded_integer_type\n");
}

void print_cassert_statement(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "cassert_statement\n");
}

void print_comb_tok(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "comb_tok\n");
}

void print_complex_identifier(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "complex_identifier\n");
}

void print_complex_identifier_list(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "complex_identifier_list\n");
}

void print_complex_string_literal(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "complex_string_literal\n");
}

void print_constant(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "constant\n");
}

void print_delay_tok(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "delay_tok\n");
}

void print_description(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "description\n");
}

void print_dot_expression(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "dot_expression\n");
}

void print_dot_expression_type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "dot_expression_type\n");
}

void print_enum_definition(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "enum_definition\n");
}

void print_expression_list(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "expression_list\n");
}

void print_expression_type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "expression_type\n");
}

void print_flow_tok(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "flow_tok\n");
}

void print_for_comprehension(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "for_comprehension\n");
}

void print_func_def_verification(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "func_def_verification\n");
}

void print_function_call_expression(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "function_call_expression\n");
}

void print_function_call_type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "function_call_type\n");
}

void print_function_definition(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "function_definition\n");
}

void print_function_definition_decl(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "function_definition_decl\n");
}

void print_identifier(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "identifier\n");
}

void print_if_expression(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "if_expression\n");
}

void print_lvalue_item(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "lvalue_item\n");
}

void print_lvalue_list(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "lvalue_list\n");
}

void print_match_expression(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "match_expression\n");
}

void print_match_list(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "match_list\n");
}

void print_match_operator(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "match_operator\n");
}

void print_member_select(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "member_select\n");
}

void print_member_selection(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "member_selection\n");
}

void print_module_path(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "module_path\n");
}

void print_optional_expression(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "optional_expression\n");
}

void print_pipe_tok(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "pipe_tok\n");
}

void print_primitive_type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "primitive_type\n");
}

void print_range_type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "range_type\n");
}

void print_ref_identifier(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "ref_identifier\n");
}

void print_select(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "select\n");
}

void print_select_options(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "select_options\n");
}

void print_selection(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "selection\n");
}

void print_sized_integer_type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "sized_integer_type\n");
}

void print_stmt_list(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "stmt_list\n");
}

void print_string_type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "string_type\n");
}

void print_timed_identifier(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "timed_identifier\n");
}

void print_tuple(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "tuple\n");
}

void print_tuple_list(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "tuple_list\n");
}

void print_tuple_sq(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "tuple_sq\n");
}

void print_type_cast(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "type_cast\n");
}

void print_type_or_identifier(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "type_or_identifier\n");
}

void print_type_specification(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "type_specification\n");
}

void print_type_type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "type_type\n");
}

void print_typed_declaration(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "typed_declaration\n");
}

void print_typed_identifier(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "typed_identifier\n");
}

void print_typed_identifier_list(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "typed_identifier_list\n");
}

void print_unary_expression(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "unary_expression\n");
}

void print_unsized_integer_type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "unsized_integer_type\n");
}

void print_var_or_let_or_reg(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "var_or_let_or_reg\n");
}

void print_when_unless_cond(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "when_unless_cond\n");
}

void print__binary_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_binary_number\n");
}

void print__bool_literal(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_bool_literal\n");
}

void print__decimal_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_decimal_number\n");
}

void print__expression(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_expression\n");
}

void print__expression_with_comprehension(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_expression_with_comprehension\n");
}

void print__hex_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_hex_number\n");
}

void print__neg_binary_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_neg_binary_number\n");
}

void print__neg_decimal_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_neg_decimal_number\n");
}

void print__neg_hex_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_neg_hex_number\n");
}

void print__neg_octal_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_neg_octal_number\n");
}

void print__neg_scaled_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_neg_scaled_number\n");
}

void print__neg_simple_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_neg_simple_number\n");
}

void print__neg_typed_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_neg_typed_number\n");
}

void print__number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_number\n");
}

void print__octal_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_octal_number\n");
}

void print__restricted_expression(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_restricted_expression\n");
}

void print__scaled_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_scaled_number\n");
}

void print__semicolon(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_semicolon\n");
}

void print__simple_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_simple_number\n");
}

void print__simple_string_literal(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_simple_string_literal\n");
}

void print__space(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_space\n");
}

void print__string_literal(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_string_literal\n");
}

void print__timing_sequence(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_timing_sequence\n");
}

void print__tuple_item(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_tuple_item\n");
}

void print__type(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_type\n");
}

void print__typed_number(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_typed_number\n");
}

void print__unknown_literal(TSNode node, const char *source_code, FILE *outfile) {
    fprintf(outfile, "_unknown_literal\n");
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
