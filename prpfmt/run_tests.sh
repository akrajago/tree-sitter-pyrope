#!/bin/bash

# This script is intended to be run from the 'tree-sitter-pyrope/prpfmt' directory,
# which is located under a main project root directory.

# The 'prpfmt' executable is expected to be in the project root directory.
# For example, if this script is at /root/tree-sitter-pyrope/prpfmt,
# the executable should be at /root as prpfmt.

# The test files are expected to be in the 'full_pyrope' directory in 'tree-sitter-pyrope'.

PRPFMT_EXECUTABLE="../.././prpfmt"
TEST_FILES_DIR="../full_pyrope"

# Check if prpfmt executable exists
if [ ! -f "$PRPFMT_EXECUTABLE" ]; then
    echo "Error: prpfmt executable not found at $PRPFMT_EXECUTABLE"
    echo "Please compile prpfmt and ensure it is located in the project root directory."
    exit 1
fi

# Check if test files directory exists
if [ ! -d "$TEST_FILES_DIR" ]; then
    echo "Error: Test files directory not found at $TEST_FILES_DIR"
    echo "Please ensure the 'full_pyrope' directory with test files is located at the expected path relative to this script."
    exit 1
fi

echo "Running prpfmt against files in $TEST_FILES_DIR:"
echo "--------------------------------------------------"

find "$TEST_FILES_DIR" -name "*.prp" | sort | while read -r file; do
    echo -n "Testing $file... "
    # Run prpfmt, redirecting stderr to /dev/null to avoid verbose output for expected errors
    "$PRPFMT_EXECUTABLE" "$file" > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo "SUCCESS"
    else
        echo "FAILURE"
    fi
done

echo "--------------------------------------------------"
echo "Test run complete."
