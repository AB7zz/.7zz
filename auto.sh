#!/bin/bash


# lexer.cpp
g++ src/lexer.cpp -o src/lexer.exe
if [ $? -eq 0 ]; then
    echo "Running lexer..."
    ./src/lexer.exe
else
    echo "Compilation failed for lexer.cpp"
    exit 1
fi

# parser.cpp
# g++ parser.cpp -o parser
# if [ $? -eq 0 ]; then
#   echo "Running parser..."
#   ./parser
# else
#   echo "Compilation failed for parser.cpp"
#   exit 1
# fi