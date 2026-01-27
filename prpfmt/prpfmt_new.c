#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree_sitter/api.h>

// Forward declaration of the tree-sitter-pyrope language function
TSLanguage *tree_sitter_pyrope();
char *file_to_string(char *path);

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Argument of type file path expected\n");
    return 1;
  }

  char *source_code = file_to_string(argv[1]);

  // Boilerplate for tree-sitter parser initialization
  TSParser *parser = ts_parser_new();
  ts_parser_set_language(parser, tree_sitter_pyrope());

  // Parsing the source code
  TSTree *tree =
      ts_parser_parse_string(parser, NULL, source_code, strlen(source_code));

  // Get the root node of the syntax tree
  TSNode root_node = ts_tree_root_node(tree);

  // Convert the root node to a string representation for printing
  char *string = ts_node_string(root_node);
  printf("Syntax tree: %s\n", string);

  // Free the memory
  free(string);
  free(source_code);
  ts_tree_delete(tree);
  ts_parser_delete(parser);

  return 0;
}

char *file_to_string(char *path) {
  char *buffer;

  FILE *fp = fopen(path, "r");
  if (!fp)
    perror(path), exit(EXIT_FAILURE);

  fseek(fp, 0L, SEEK_END);
  long l_size = ftell(fp);
  rewind(fp);

  buffer = malloc(l_size + 1);
  if (!buffer)
    fclose(fp), fputs("Memory allocation fails", stderr), exit(1);

  if (1 != fread(buffer, l_size, 1, fp))
    fclose(fp), free(buffer), fputs("Read fails", stderr), exit(1);

  fclose(fp);
  return buffer;
}
