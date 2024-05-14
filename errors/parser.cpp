#include "../h/errors/parser.h"

void ParserError::SyntaxError(string str, int line, int pos) {
    cerr << "Syntax error: " << str << " at line " << line << " and position " << pos << endl;
}

void ParserError::NameError(string str, int line, int pos) {
    cerr << "Name error: " << str << " at line " << line << " and position " << pos << endl;
}