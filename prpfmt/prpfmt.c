#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree_sitter/api.h>

#include "prpfmt.h"

void print_tree(TSTree *tree, char *source_code, FILE *outfile) {
  // Get root and child info
  TSNode root_node = ts_tree_root_node(tree);
  uint32_t last_printed_end = 0;
  uint32_t root_child_count = ts_node_child_count(root_node);

  // Iterate over the root's children
  for (uint32_t i = 0; i < root_child_count; i++) {
    TSNode child = ts_node_child(root_node, i);
    print_statement(child, source_code, &last_printed_end, outfile);
  }
}

void print_statement(TSNode node, const char *source_code, uint32_t *last_printed_end, FILE *outfile) {
  format_node_recursive(node, source_code, last_printed_end, outfile);
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

void format_node_recursive(TSNode node, const char *source_code,
                        uint32_t *last_printed_end, FILE *outfile) {
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
