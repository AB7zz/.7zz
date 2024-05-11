#include "../h/parser.h"
#include "../h/emitter.h"

bool parser(vector<Token> tks){
    Keyword keyword;
    for (const Token& token : tks) {
        if(strcmp(token.key.c_str(), "key") == 0){
            keyword.toTarget(token.value);
        }
    }
    return true;
}