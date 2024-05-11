#include <stack>
#include <string>
#include <cstring>
#include <iostream>
#include "common.h"

bool isSpace(char ch);

bool isPunctuator(char ch);

bool validIdentifier(char* str);

bool isOperator(char ch);

bool isKeyword(char *str);

bool isNumber(char* str);

char* subString(char* realStr, int l, int r);

bool checkPunctuatorClosing(stack<char> punctuators, char ch);

vector<Token> lexer(char* str);