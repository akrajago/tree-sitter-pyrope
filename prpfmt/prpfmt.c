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
  // TODO: Implement formatting for assignment_or_declaration_statement
}

void print_control_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for control_statement
}

void print_declaration_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for declaration_statement
}

void print_enum_assignment_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for enum_assignment_statement
}

void print_expression_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for expression_statement
}

void print_for_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for for_statement
}

void print_function_call_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for function_call_statement
}

void print_impl_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for impl_statement
}

void print_import_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for import_statement
}

void print_lambda(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for lambda
}

void print_loop_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for loop_statement
}

void print_scope_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for scope_statement
}

void print_test_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for test_statement
}

void print_type_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for type_statement
}

void print_while_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for while_statement
}

void print_assignment(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for assignment
}

void print_enum_assignment(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for enum_assignment
}

void print_arg_item(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for arg_item
}

void print_arg_item_list(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for arg_item_list
}

void print_arg_list(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for arg_list
}

void print_array_type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for array_type
}

void print_assignment_delay(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for assignment_delay
}

void print_assignment_operator(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for assignment_operator
}

void print_attribute_item(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for attribute_item
}

void print_attribute_item_list(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for attribute_item_list
}

void print_attribute_list(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for attribute_list
}

void print_attributes(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for attributes
}

void print_binary_expression(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for binary_expression
}

void print_bit_select(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for bit_select
}

void print_bit_select_type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for bit_select_type
}

void print_bit_selection(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for bit_selection
}

void print_boolean_type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for boolean_type
}

void print_bounded_integer_type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for bounded_integer_type
}

void print_cassert_statement(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for cassert_statement
}

void print_comb_tok(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for comb_tok
}

void print_complex_identifier(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for complex_identifier
}

void print_complex_identifier_list(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for complex_identifier_list
}

void print_complex_string_literal(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for complex_string_literal
}

void print_constant(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for constant
}

void print_delay_tok(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for delay_tok
}

void print_description(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for description
}

void print_dot_expression(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for dot_expression
}

void print_dot_expression_type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for dot_expression_type
}

void print_enum_definition(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for enum_definition
}

void print_expression_list(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for expression_list
}

void print_expression_type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for expression_type
}

void print_flow_tok(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for flow_tok
}

void print_for_comprehension(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for for_comprehension
}

void print_func_def_verification(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for func_def_verification
}

void print_function_call_expression(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for function_call_expression
}

void print_function_call_type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for function_call_type
}

void print_function_definition(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for function_definition
}

void print_function_definition_decl(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for function_definition_decl
}

void print_identifier(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for identifier
}

void print_if_expression(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for if_expression
}

void print_lvalue_item(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for lvalue_item
}

void print_lvalue_list(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for lvalue_list
}

void print_match_expression(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for match_expression
}

void print_match_list(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for match_list
}

void print_match_operator(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for match_operator
}

void print_member_select(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for member_select
}

void print_member_selection(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for member_selection
}

void print_module_path(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for module_path
}

void print_optional_expression(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for optional_expression
}

void print_pipe_tok(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for pipe_tok
}

void print_primitive_type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for primitive_type
}

void print_range_type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for range_type
}

void print_ref_identifier(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for ref_identifier
}

void print_select(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for select
}

void print_select_options(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for select_options
}

void print_selection(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for selection
}

void print_sized_integer_type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for sized_integer_type
}

void print_stmt_list(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for stmt_list
}

void print_string_type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for string_type
}

void print_timed_identifier(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for timed_identifier
}

void print_tuple(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for tuple
}

void print_tuple_list(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for tuple_list
}

void print_tuple_sq(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for tuple_sq
}

void print_type_cast(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for type_cast
}

void print_type_or_identifier(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for type_or_identifier
}

void print_type_specification(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for type_specification
}

void print_type_type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for type_type
}

void print_typed_declaration(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for typed_declaration
}

void print_typed_identifier(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for typed_identifier
}

void print_typed_identifier_list(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for typed_identifier_list
}

void print_unary_expression(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for unary_expression
}

void print_unsized_integer_type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for unsized_integer_type
}

void print_var_or_let_or_reg(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for var_or_let_or_reg
}

void print_when_unless_cond(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for when_unless_cond
}

void print__binary_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _binary_number
}

void print__bool_literal(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _bool_literal
}

void print__decimal_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _decimal_number
}

void print__expression(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _expression
}

void print__expression_with_comprehension(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _expression_with_comprehension
}

void print__hex_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _hex_number
}

void print__neg_binary_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _neg_binary_number
}

void print__neg_decimal_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _neg_decimal_number
}

void print__neg_hex_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _neg_hex_number
}

void print__neg_octal_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _neg_octal_number
}

void print__neg_scaled_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _neg_scaled_number
}

void print__neg_simple_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _neg_simple_number
}

void print__neg_typed_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _neg_typed_number
}

void print__number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _number
}

void print__octal_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _octal_number
}

void print__restricted_expression(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _restricted_expression
}

void print__scaled_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _scaled_number
}

void print__semicolon(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _semicolon
}

void print__simple_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _simple_number
}

void print__simple_string_literal(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _simple_string_literal
}

void print__space(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _space
}

void print__string_literal(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _string_literal
}

void print__timing_sequence(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _timing_sequence
}

void print__tuple_item(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _tuple_item
}

void print__type(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _type
}

void print__typed_number(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _typed_number
}

void print__unknown_literal(TSNode node, const char *source_code, FILE *outfile) {
  // TODO: Implement formatting for _unknown_literal
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
