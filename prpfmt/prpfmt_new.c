#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree_sitter/api.h>

#include "prpfmt_new.h"

int main(int argc, char **argv) {
  // Parse CLI arguments
  if (argc < 2) {
    printf("Argument of type file path expected:\n" 
           "    ./prpfmt <path_to_input_file>\n");
    return 1;
  }

  // Tree-sitter parser initialization
  TSLanguage *tree_sitter_pyrope();
  TSParser *parser = ts_parser_new();
  ts_parser_set_language(parser, tree_sitter_pyrope());

  // Parse the source code
  char *source_code = file_to_string(argv[1]);
  TSTree *tree =
      ts_parser_parse_string(parser, NULL, source_code, strlen(source_code));

  // Get the root node of the syntax tree
  TSNode root_node = ts_tree_root_node(tree);

  // Traverse the tree and print the original text of each node
  uint32_t last_printed_end = 0;
  traverse_and_print(root_node, source_code, &last_printed_end);

  // Free the memory
  free(source_code);
  ts_tree_delete(tree);
  ts_parser_delete(parser);

  return 0;
}

char *file_to_string(char *path) {
  char *buffer;
  FILE *fp = fopen(path, "r");

  // Attempt to open file
  if (!fp) {
    perror(path);
    exit(EXIT_FAILURE);
  }

  // Determine file size
  fseek(fp, 0L, SEEK_END);
  long l_size = ftell(fp);
  rewind(fp);

  // Allocate memory for file content
  buffer = malloc(l_size + 1);
  if (!buffer) {
    fclose(fp);
    fputs("Memory allocation failed", stderr);
    exit(EXIT_FAILURE);
  }

  // Read file content into buffer
  if (1 != fread(buffer, l_size, 1, fp)) {
    fclose(fp);
    free(buffer);
    fputs("File read failed", stderr);
    exit(EXIT_FAILURE);
  }

  buffer[l_size] = '\0';
  fclose(fp);

  return buffer;
}

// Extracts the text content of a given Tree-sitter node from the source code.
char *get_node_text(TSNode node, const char *source_code) {
  uint32_t start_byte = ts_node_start_byte(node);
  uint32_t end_byte = ts_node_end_byte(node);
  uint32_t length = end_byte - start_byte;

  char *text = (char *)malloc(length + 1);
  if (text == NULL) {
    perror("Failed to allocate memory for node text");
    return NULL;
  }
  strncpy(text, source_code + start_byte, length);
  text[length] = '\0';
  return text;
}

// Traverses the Tree-sitter syntax tree and prints the original text, including whitespace.
void traverse_and_print(TSNode node, const char *source_code,
                        uint32_t *last_printed_end) {
  // If it's a leaf node, print its text and any preceding whitespace.
  if (ts_node_child_count(node) == 0) {
    uint32_t start_byte = ts_node_start_byte(node);
    // Print whitespace between the last printed node and the current node.
    for (uint32_t i = *last_printed_end; i < start_byte; ++i) {
      printf("%c", source_code[i]);
    }

    char *node_text = get_node_text(node, source_code);
    if (node_text) {
      printf("%s", node_text);
      free(node_text);
    }
    // Update the end position of the last printed node.
    *last_printed_end = ts_node_end_byte(node);
  }

  // Use a tree cursor for efficient traversal of children.
  TSTreeCursor cursor = ts_tree_cursor_new(node);

  // Recursively traverse child nodes.
  if (ts_tree_cursor_goto_first_child(&cursor)) {
    do {
      TSNode current_child_node = ts_tree_cursor_current_node(&cursor);
      traverse_and_print(current_child_node, source_code, last_printed_end);
    } while (ts_tree_cursor_goto_next_sibling(&cursor));
  }

  ts_tree_cursor_delete(&cursor);
}
