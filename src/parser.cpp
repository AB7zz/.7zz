#include <iostream>
#include <vector>
#include <string>
#include "../h/common.h"

int pos = 0; // Token position

bool match(const std::string& expected) {
    if (tokens[pos] == expected) {
        pos++;
        return true;
    }
    return false;
}

void expression();
void term();
void factor();

void assignment_statement() {
    if (match("key") && match(":") && match("num")) {
        std::string id = tokens[pos++];
        if (match("=")) {
            expression();
            // Handle assignment
        }
    }
}

void expression() {
    term();
    while (match("+") || match("-")) {
        term();
        // Handle operation
    }
}

void term() {
    factor();
    while (match("*") || match("/")) {
        factor();
        // Handle operation
    }
}

void factor() {
    if (match("num")) {
        // Handle number
    } else if (match("(")) {
        expression();
        match(")");
    }
}