# Project: Pyrope Tree-Sitter Formatter

## Project Overview
Read the project overview here:
@README.md

This project is using `old_prpfmt.c` as a starting point.

## Instructions
- Do not modify or delete any files not in this list:
```
prpfmt.c
main.c
prpfmt.h
remove_indent.py
```
- When compiling, navigate to `~/Desktop/Projects/capstone` and run: 
```shell
clang -I tree-sitter/lib/include tree-sitter-pyrope/prpfmt/prpfmt.c tree-sitter-pyrope/prpfmt/main.c tree-sitter-pyrope/src/parser.c tree-sitter-pyrope/src/scanner.c tree-sitter/libtree-sitter.a -o prpfmt
```
Keep the executable in the capstone folder.
## Coding Style
- No inline comments unless specifically asked.
- Indent = 2 spaces.
