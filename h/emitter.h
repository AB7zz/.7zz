#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Keyword {
    public:
        void toTarget(string value);
        string findTarget(string value);
};

class Identifier {
    public:
        void toTarget(string value);
};

class Operator {
    public:
        void toTarget(string value);
        string findTarget(string value);
};

class Punctuator {
    public:
        void toTarget(string value);
        string findTarget(string value);
};

class Number {
    public:
        void toTarget(string value);
};
