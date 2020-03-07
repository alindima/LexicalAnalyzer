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
        if(valueToIndex.count(value)){
           valuePos = valueToIndex[value];
        }else{
            values.push_back(value);
            valuePos = values.size()-1;
            valueToIndex[value] = valuePos;
        }
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
    static unordered_map<string, int> valueToIndex;

    friend class Analyzer;
};

#endif //LEXICALANALYZER_TOKEN_H
