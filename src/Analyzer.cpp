#include "../include/Analyzer.h"

using namespace std;

Token Analyzer::getToken() {
    string token = dfa.parseToken();
    TokenType type;

    if(token!="Error"){
        type = Ok;
    }else{
        type = Error;
    }

    return Token(type, token);
}
