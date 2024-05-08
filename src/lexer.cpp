#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include "../h/common.h"

using namespace std;

bool isPunctuator(char ch)					
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
        ch == '&' || ch == '|')
    {
        return true;
    }
    return false;
}

bool validIdentifier(char* str)						
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isPunctuator(str[0]) == true)
    {
        return false;
    }									
    int i,len = strlen(str);
    if (len == 1)
    {
        return true;
    }						
    else
    {
        for (i = 1 ; i < len ; i++)	
        {
            if (isPunctuator(str[i]) == true)
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
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=' || ch == '|' || ch == '&')
    {
       return true;
    }
    return false;
}

bool isKeyword(char *str)
{
    if (!strcmp(str, "imp") || !strcmp(str, "out")    || 
        !strcmp(str, "in")  || !strcmp(str, "if")     ||
        !strcmp(str, "ret") || !strcmp(str, "fun")    ||
        !strcmp(str, "wh")  || !strcmp(str, "for")    ||
        !strcmp(str, "num") || !strcmp(str, "str")    ||
        !strcmp(str, "bool")
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


void parse(char* str)
{
    Token t;

    int left = 0, right = 0;
    int len = strlen(str);
    while (right <= len && left <= right) {
        if (isPunctuator(str[right]) == false)
        {
            right++;
        }

        if (isPunctuator(str[right]) == true && left == right)
        {
            if (isOperator(str[right]) == true)
            {
                t.key = "op";
                t.value = str[right];
                tokens.push_back(t);
                cout << t.key << ": " << t.value <<"\n";
            }
            right++;
            left = right;
        } 
        else if (isPunctuator(str[right]) == true && left != right || (right == len && left != right)) 			
        {
            char* sub = subString(str, left, right - 1);

            if (isKeyword(sub) == true)
            {
                t.key = "key";
                t.value = sub;
                tokens.push_back(t);
                cout << t.key << ": " << t.value <<"\n";
            }
            else if (isNumber(sub) == true)
            {
                t.key = "num";
                t.value = sub;
                tokens.push_back(t);
                cout << t.key << ": " << t.value <<"\n";
            }
            else if (validIdentifier(sub) == true && isPunctuator(str[right - 1]) == false)
            {
                t.key = "id";
                t.value = sub;
                tokens.push_back(t);
                cout << t.key << ": " << t.value <<"\n";
            }
            else if (validIdentifier(sub) == false && isPunctuator(str[right - 1]) == false)
            {
                cout<< sub <<" IS NOT A VALID IDENTIFIER\n";
            }
            left = right;
        }
    }
    return;
}

int main()
{
    char c[100] = "num c = 10 + 20";
    parse(c);
    return 0;
}