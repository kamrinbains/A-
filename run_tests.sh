#!/bin/bash

# Colors for better readability
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Initialize counters
total_tests=0
passed_tests=0

# Check if a.out exists and is executable
if [ ! -x "./a.out" ]; then
    echo "Error: a.out not found or not executable in current directory"
    exit 1
fi

# Check if tests directory exists
if [ ! -d "./tests" ]; then
    echo "Error: tests directory not found"
    exit 1
fi

# Find all input files
input_files=$(find ./tests -name "*.in" | sort)

# If no input files found
if [ -z "$input_files" ]; then
    echo "No test input files found in ./tests"
    exit 1
fi

echo "Running tests..."
echo "--------------"

# Process each input file
for infile in $input_files; do
    total_tests=$((total_tests + 1))
    
    # Get the base filename without extension
    basename=$(basename "$infile" .in)
    
    # Construct the expected output filename
    expected_outfile="./tests/${basename}.out"
    
    # Check if expected output file exists
    if [ ! -f "$expected_outfile" ]; then
        echo -e "${RED}MISSING${NC}: Expected output file $expected_outfile not found"
        continue
    fi
    
    # Create a temporary file for the actual output
    temp_outfile=$(mktemp)
    
    # Run the program with input redirected from the input file
    # and capture the output to the temporary file
    ./a.out < "$infile" > "$temp_outfile"
    
    # Compare the actual output with the expected output
    # Use -w instead of -Z for macOS compatibility (ignores all whitespace)
    diff_result=$(diff -w "$temp_outfile" "$expected_outfile")
    
    if [ -z "$diff_result" ]; then
        echo -e "${GREEN}PASSED${NC}: Test $basename"
        passed_tests=$((passed_tests + 1))
    else
        echo -e "${RED}FAILED${NC}: Test $basename"
        echo "Differences:"
        echo "$diff_result"
    fi
    
    # Clean up the temporary file
    rm "$temp_outfile"
done

echo "--------------"
echo "Test summary: $passed_tests passed out of $total_tests total tests"

# Exit with status 0 if all tests passed, 1 otherwise
if [ "$passed_tests" -eq "$total_tests" ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed.${NC}"
    exit 1
fi
