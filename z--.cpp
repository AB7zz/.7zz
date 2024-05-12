#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <memory>
#include <cstdlib>
#include <chrono>
#include "h/lexer.h"
#include "h/parser.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    auto start = high_resolution_clock::now();
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

    // Lexer 
    for (const auto& line : lines) {
        char* lineStr = const_cast<char*>(line.c_str());
        vector<Token> tks = lexer(lineStr);
        allTokens.push_back(tks);
    }
    // Lexer

    // init file
    ofstream outputFile("dummy.cpp");

    if (outputFile.is_open()) {
        outputFile << "#include <iostream>" << endl;
        outputFile << "#include <string>" << endl;
        outputFile << "#include <vector>" << endl;
        outputFile << "#include <fstream>" << endl;
        outputFile << "#include <sstream>" << endl;
        outputFile << endl;

        outputFile << "using namespace std;" << endl;
        outputFile << endl;

        outputFile.close();
    } else {
        cerr << "Error: Unable to open dummy.cpp for writing." << endl;
    }
    // init file


    // Parser
    for (const auto& tks : allTokens) {
        parser(tks);
    }
    // Parser

    // Compile and execute
    system("g++ dummy.cpp -o dummy.exe");
    system("dummy.exe");
    // Compile and execute

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\nExecution Time: " << duration.count() << " microseconds" << endl;

    return 0;
}
