#include "../h/lexer.h"
#include "../h/errors/lexer.h"

bool isSpace(char ch)					
{
    if (ch == ' ')
    {
        return true;
    }
    return false;
}

bool isSemicolon(char ch)					
{
    if (ch == ';')
    {
        return true;
    }
    return false;
}

bool isPunctuator(char ch)					
{
    if (ch == ')' || ch == '(' || ch == ':' || ch == '"')
    {
        return true;
    }
    return false;
}

bool isUnrecognizedChar(char ch, int line, int pos)
{
    if (ch == '?' || ch == '!' || ch == '@' || ch == '#' || ch == '$' || ch == '^' || ch == '&' || ch == '<' || ch == '>' || ch == '=')
    {
        lexerError.UnrecognizedChar(&ch, 0, 0);
        exit(EXIT_FAILURE);
    }
    return false;
}

bool validIdentifier(char* str, int line, int pos)						
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isPunctuator(str[0]) == true)
    {
        lexerError.InvalidIdentifier(str, line, pos-1);
        exit(EXIT_FAILURE);
    }									
    int i, len = strlen(str);
    if (len == 1)
    {
        return true;
    }						
    else
    {
        for (i = 1 ; i < len ; i++)	
        {
            isUnrecognizedChar(str[i], line, pos);
            if (isPunctuator(str[i]))
            {
                return false;
            }
        }
    }
    return true;
}

bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/')
    {
       return true;
    }
    return false;
}

bool isKeyword(char *str)
{
    if (!strcmp(str, "imp") || !strcmp(str, "out")    || 
        !strcmp(str, "in")  || !strcmp(str, "if")     ||
        !strcmp(str, "ret") || !strcmp(str, "wh")     || 
        !strcmp(str, "for") || !strcmp(str, "end")    ||
        !strcmp(str, "num") || !strcmp(str, "str")    ||
        !strcmp(str, "bool")|| !strcmp(str, "or")     ||
        !strcmp(str, "and") || !strcmp(str, "not")    ||
        !strcmp(str, "is")  || !strcmp(str, "else")   ||
        !strcmp(str, "elif")|| !strcmp(str, "void")   ||
        !strcmp(str, "main")|| !strcmp(str, "<-")     ||
        !strcmp(str, "lt")|| !strcmp(str, "lte")      ||
        !strcmp(str, "gt")|| !strcmp(str, "gte")      
    )
    {
        return true;
    }
    else
    {
       return false;
    }
}

bool isNumber(char* str)
{
    int i, len = strlen(str),numOfDecimal = 0;
    if (len == 0)
    {
        return false;
    }
    for (i = 0 ; i < len ; i++)
    {
        if (numOfDecimal > 1 && str[i] == '.')
        {
            return false;
        } else if (numOfDecimal <= 1)
        {
            numOfDecimal++;
        }
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            {
                return false;
            }
    }
    return true;
}

char* subString(char* realStr, int l, int r)
{
    int i;

    char* str = (char*) malloc(sizeof(char) * (r - l + 2));

    for (i = l; i <= r; i++)
    {
        str[i - l] = realStr[i];
        str[r - l + 1] = '\0';
    }
    return str;
}

bool checkPunctuatorClosing(stack<char> punctuators, char ch)
{
    if (punctuators.empty())
    {
        return false;
    }

    char top = punctuators.top();

    if ( (top == '(' && ch == ')') || (top == ':' && ch == '}') || (top == '"' && ch == '"') )
    {
        punctuators.pop();
        return true;
    }
    return false;
}

vector<Token> lexer(char* str, int line, stack<char> punctuators)
{
    Token t;

    vector<Token> tokens;

    int left = 0, right = 0, len = strlen(str);

    while (len > 0 && right <= len && left <= right) {
        if (isSpace(str[right]) == false)
        {
            if(isPunctuator(str[right]) == true){
                t.key = "punc";
                t.value = str[right];
                tokens.push_back(t);
                punctuators.push(str[right]);
                left++;
            }
            right++;
        }

        
        if (isSpace(str[right]) == true && left == right)
        {
            right++;
            left = right;
        } 
        else if ((isSpace(str[right]) == true || checkPunctuatorClosing(punctuators, str[right]) || isPunctuator(str[right]) || right == len || isSemicolon(str[right]) == true) && (left != right || (right == len && left != right))) 			
        {
            char* sub = subString(str, left, right - 1);

            if (isKeyword(sub) == true)
            {
                t.key = "key";
                t.value = sub;
                tokens.push_back(t);
                if(strcmp(sub, "end") == 0){
                    punctuators.push('}');
                }
            }
            else if (isOperator(str[left]) == true)
            {
                t.key = "op";
                t.value = str[left];
                tokens.push_back(t);
            }
            else if (isNumber(sub) == true)
            {
                t.key = "num";
                t.value = sub;
                tokens.push_back(t);
            }
            else if (validIdentifier(sub, line, right) == true && isSpace(str[right - 1]) == false)
            {
                t.key = "id";
                t.value = sub;
                tokens.push_back(t);
            }
            else if (validIdentifier(sub, line, right) == false && isSpace(str[right - 1]) == false)
            {
                lexerError.InvalidIdentifier(sub, line, right);
                exit(EXIT_FAILURE);
            }
            left = right;
        }
    }
    
    return tokens;
}