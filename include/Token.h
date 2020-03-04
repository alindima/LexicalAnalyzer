#ifndef LEXICALANALYZER_TOKEN_H
#define LEXICALANALYZER_TOKEN_H

#include <string>
#include <vector>
#include <unordered_map>
#include "TokenType.h"

using namespace std;

struct Token {
    TokenType type;


    Token(){}
    Token(TokenType type, string value): type(type){
        values.push_back(value);
        valuePos = values.size()-1;
    }

    string getTokenTypeAsString(){
        return tokenTypeNames[type];
    }

    string getValue(){
        return values[valuePos];
    }

private:
    int valuePos;

    static unordered_map<TokenType, string, hash<int>> tokenTypeNames;
    static vector<string> values;

    friend class Analyzer;
};

#endif //LEXICALANALYZER_TOKEN_H
