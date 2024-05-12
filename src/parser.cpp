#include "../h/parser.h"
#include "../h/emitter.h"

enum State {
    key,
    num,
    id,
    op,
    punc
};

State stringToState(const string& str) {
    if (str == "key") return key;
    else if (str == "num") return num;
    else if (str == "id") return id;
    else if (str == "op") return op;
    else if (str == "punc") return punc;
    else return key;
}

bool semicolonKeyword(const vector<string>& values) {
    for (const auto& value : values) {
        if (value == "ret" || value == "out" || value == "in") {
            return true;
        }
    }
    return false;
}

bool parser(vector<Token> tks){
    Keyword keyword;
    Number number;
    Identifier identifier;
    Operator op;
    Punctuator punc;

    vector<string> values;

    for (const Token& token : tks) {
        State state = stringToState(token.key);
        switch (state){
            case 0:
                keyword.toTarget(token.value);
                values.push_back(token.value);
                break;
            case 1:
                number.toTarget(token.value);
                break;
            case 2:
                identifier.toTarget(token.value);
                break;
            case 3:
                op.toTarget(token.value);
                break;
            case 4:
                punc.toTarget(token.value);
                break;
        }
    }

    if (semicolonKeyword(values)){
        ofstream outputFile;
        outputFile.open("dummy.cpp", ios::app);

        if (outputFile.is_open()) {
            outputFile << ";";
            outputFile.close();
        } else {
            cerr<< "Unable to open file!"<<endl;
        }
    }
    return true;
}