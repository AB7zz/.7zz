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
        if (value == "ret" || value == "out" || value == "in" || value == "num" || value == "str" || value == "bool" || value == "<-") {
            return true;
        }
    }
    return false;
}

bool nextlineKeyword(const vector<string>& values){
    for (const auto& value: values){
        if(value == "imp"){
            return true;
        }
    }
    return false;
}

bool specialKeyword(const vector<string>& values){
    for (const auto& value: values){
        if(value == "ret"){
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

    bool keyPresent = false, idPresent = false, puncPresent = false, funcPresent = false, assignmentPresent = false, specialPresent = false;

    for (const Token& token : tks) {
        cout<<token.key<<' '<<token.value<<endl;

        if (!specialPresent){
            specialPresent = specialKeyword(values);
        }

        if (token.key == "key"){
            keyPresent = true;
            if(token.value == "<-"){
                assignmentPresent = true;
            }
        }

        if ((!assignmentPresent) && token.key == "id" && idPresent == false){
            idPresent = true;
        }

        if((!assignmentPresent) && token.key == "punc" && puncPresent == false){
            puncPresent = true;
        }

        if (keyPresent && idPresent && puncPresent){
            funcPresent = true;
        }

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

    if ((!funcPresent || specialPresent) && semicolonKeyword(values)){
        ofstream outputFile;
        outputFile.open("output.cpp", ios::app);

        if (outputFile.is_open()) {
            outputFile << ";";
            outputFile.close();
        } else {
            cerr<< "Unable to open file!"<<endl;
        }
    }
    if(nextlineKeyword(values)){
        ofstream outputFile;
        outputFile.open("output.cpp", ios::app);

        if (outputFile.is_open()) {
            outputFile << endl;
            outputFile.close();
        } else {
            cerr<< "Unable to open file!"<<endl;
        }
    }
    return true;
}