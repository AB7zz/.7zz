#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <cstring>
#include <iostream>
#include <stdio.h>

using namespace std;

class LexerError {
    public:
        void UnrecognizedChar(string str, int line, int pos);
        void InvalidIdentifier(string str, int line, int pos);
        void UnclosedPunc(char str);
};

extern LexerError lexerError;

#endif // LEXER_H