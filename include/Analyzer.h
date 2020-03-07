#ifndef LEXICALANALYZER_ANALYZER_H
#define LEXICALANALYZER_ANALYZER_H

#include <utility>
#include "Token.h"
#include "DFA.h"

using namespace std;

class Analyzer {
    DFA dfa;

    unordered_set<TokenType, hash<int>> ignorableTokens = {Comment, Space, Semicolon, Comma};
    unordered_set<string> keywords = {"int", "if", "for", "while", "do", "else", "float", "double", "return", "char"};

public:
    Analyzer(string filename):dfa(filename) {
        Token::values = vector<string>();
        Token::valueToIndex = unordered_map<string, int>();
    }

    Token getToken();

    bool isTokenTypeIgnorable(TokenType type){return ignorableTokens.count(type);}

    bool isKeyword(Token token){
        return token.type == Identifier && keywords.count(token.getValue());
    }
};

#endif //LEXICALANALYZER_ANALYZER_H
