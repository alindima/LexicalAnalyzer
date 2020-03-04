#include "../include/Analyzer.h"

using namespace std;

unordered_map<TokenType, string, hash<int>> Token::tokenTypeNames = {{Operator,"Operator"},
                                                                     {Comment, "Comment"},
                                                                     {Identifier, "Identifier"},
                                                                     {Keyword, "Keyword"},
                                                                     {Number, "Number"},
                                                                     {Semicolon, "Semicolon"},
                                                                     {Space, "Space"},
                                                                     {String, "String"},
                                                                     {Comma, "Comma"}};

vector<string> Token::values;

Token Analyzer::getToken() {
    auto tokenPair = dfa.parseToken();

    auto token = Token(tokenPair.second, tokenPair.first);

    if(isTokenTypeIgnorable(token.type)){
        return getToken();
    }

    if(isKeyword(token)){
        token.type = Keyword;
    }

    return token;
}
