#include "../h/errors/lexer.h"

void LexerError::UnrecognizedChar(string str, int line, int pos) {
    cerr << "Unrecognized character: " << str << " at line " << line << " and position " << pos << endl;
}

void LexerError::InvalidIdentifier(string str, int line, int pos) {
    cerr << "Invalid identifier: " << str << " at line " << line << " and position " << pos << endl;
}

void LexerError::UnclosedPunc(char str) {
    cerr << "Unclosed punctuation: " << str << endl;
}