#include <string>
#include <cstring>
#include <iostream>
#include <stdio.h>

using namespace std;

class ParserError {
    public:
        void SyntaxError(string str, int line, int pos);
        void NameError(string str, int line, int pos);
};
