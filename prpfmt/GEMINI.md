# Project: Pyrope Tree-Sitter Formatter

## Project Overview
Read the project overview here:
@README.md

This project is using prpfmt.c as a starting point.

## Instructions
- Do not modify or delete any files not in this list:
```
prpfmt_new.c
prpfmt_new.h
```
- When compiling, navigate to `~/Desktop/Projects/capstone` and run: 
```shell
clang -I tree-sitter/lib/include tree-sitter-pyrope/prpfmt/prpfmt_new.c tree-sitter-pyrope/src/parser.c tree-sitter-pyrope/src/scanner.c tree-sitter/libtree-sitter.a -o prpfmt
```

## Coding Style
- No inline comments unless specifically asked.
- Indent = 2 spaces.
