#include "../h/emitter.h"

string Keyword::findTarget(string value){
    if (value == "num"){
        return "int";
    }else if (value == "imp"){
        return "#include";
    }else if (value == "out"){
        return "cout<<";
    }else if (value == "in"){
        return "cin>>";
    }else if (value == "ret"){
        return "return";
    }else if (value == "wh"){
        return "while(";
    }else if (value == "for"){
        return "for(";
    }else if (value == "end"){
        return "}";
    }else if (value == "str"){
        return "string";
    }else if (value == "bool"){
        return "bool";
    }else if (value == "or"){
        return "||";
    }else if (value == "and"){
        return "&&";
    }else if (value == "not"){
        return "!=";
    }else if (value == "if"){
        return "if(";
    }else{
        return value;
    }
}

void Keyword::toTarget(string value) {
    ofstream outputFile;
    outputFile.open("dummy.cpp", ios::app);

    string cpp = findTarget(value);

    if (outputFile.is_open()) {
        // outputFile << cpp <<" ";
        outputFile.close();
    } else {
        cerr<< "Unable to open file!"<<endl;
    }
}