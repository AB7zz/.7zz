#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include "h/lexer.h"

using namespace std;

vector<Token> lexer(char* str);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ab7 filename" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    vector<string> lines;

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    vector<vector<Token>> allTokens;

    for (const auto& line : lines) {
        char* lineStr = const_cast<char*>(line.c_str());
        vector<Token> tks = lexer(lineStr);
        allTokens.push_back(tks);
    }

    for (const auto& tks : allTokens) {
        for (const Token& token : tks) {
            cout << token.key << ": " << token.value << endl;
        }
        cout << "End of line" << endl;
    }

    return 0;
}
