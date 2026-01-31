#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree_sitter/api.h>

#include "prpfmt.h"

void print_help() {
  printf("Usage: ./prpfmt <input_file> [-o <output_file>]\n");
  printf("       ./prpfmt [-h | --help]\n\n");
  printf("Options:\n");
  printf("  -o <output_file>  Specify an output file. If not provided, output to stdout.\n");
  printf("  -h, --help        Display this help message.\n");
}

int main(int argc, char **argv) {
  // Check if input file provided
  if (argc < 2) {
    fprintf(stderr, "Error: Input file path is required.\n");
    print_help();
    exit(1);
  }

  // Parse for -h option
  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    print_help();
    return 0;
  }
  
  char *infile_path = argv[1];
  char *outfile_path = NULL;

  // Parse for -o option
  for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "-o") == 0) {
      if (i + 1 < argc) {
        outfile_path = argv[i + 1];
        i++;
      } else {
        fprintf(stderr, "Error: -o requires an output file path.\n");
        print_help();
        exit(1);
      }
    } else {
      fprintf(stderr, "Error: Invalid argument '%s'.\n", argv[i]);
      print_help();
      exit(1);
    }
  }
  
  // Set output file
  FILE *outfile = stdout;
  if (outfile_path) {
    outfile = fopen(outfile_path, "w");
    if (!outfile) {
      perror("Error opening output file");
      exit(1);
    }
  }

  // Tree-sitter parser initialization
  TSLanguage *tree_sitter_pyrope();
  TSParser *parser = ts_parser_new();
  if (!ts_parser_set_language(parser, tree_sitter_pyrope())) {
    fprintf(stderr, "Error: the language was generated with an "
                    "incompatible version of the tree-sitter CLI.\n");
  }

  // Parse the source code
  char *source_code = file_to_string(infile_path);
  TSTree *tree =
      ts_parser_parse_string(parser, NULL, source_code, strlen(source_code));

  // Get the root node of the syntax tree
  TSNode root_node = ts_tree_root_node(tree);

  // Traverse the tree and print the original text of each node
  uint32_t last_printed_end = 0;
  traverse_and_print(root_node, source_code, &last_printed_end, outfile);

  // Free the memory
  free(source_code);
  ts_tree_delete(tree);
  ts_parser_delete(parser);

  if (outfile != stdout) {
    fclose(outfile);
  }

  return 0;
}

char *file_to_string(char *infile) {
  char *buffer;
  FILE *fp = fopen(infile, "r");

  // Attempt to open file
  if (!fp) {
    perror(infile);
    exit(1);
  }

  // Determine file size
  fseek(fp, 0L, SEEK_END);
  long l_size = ftell(fp);
  rewind(fp);

  // Allocate memory for file content
  buffer = malloc(l_size + 1);
  if (!buffer) {
    fclose(fp);
    fprintf(stderr, "Memory allocation failed");
    exit(1);
  }

  // Read file content into buffer
  if (fread(buffer, l_size, 1, fp) != 1) {
    fclose(fp);
    free(buffer);
    fprintf(stderr, "File read failed");
    exit(1);
  }

  buffer[l_size] = '\0';
  fclose(fp);

  return buffer;
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

void traverse_and_print(TSNode node, const char *source_code,
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
      traverse_and_print(current_child_node, source_code, last_printed_end,
                         outfile);
    } while (ts_tree_cursor_goto_next_sibling(&cursor));
  }

  ts_tree_cursor_delete(&cursor);
}
