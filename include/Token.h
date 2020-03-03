#ifndef LEXICALANALYZER_TOKEN_H
#define LEXICALANALYZER_TOKEN_H

#include <string>
#include "TokenType.h"

using namespace std;

struct Token {
    TokenType type;
    string value;

    Token(){}
    Token(TokenType type, string value): type(type), value(value){}
};

#endif //LEXICALANALYZER_TOKEN_H
