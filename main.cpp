#include <iostream>
#include "include/Analyzer.h"

using namespace std;

int main(int argc, char** argv) {
    Analyzer analyzer("C:\\Users\\alin\\CLionProjects\\LexicalAnalyzer\\input\\test.txt");

    Token token;

    while((token = analyzer.getToken()).type != Error && token.type != EndOfFile){
        cout<<token.getTokenTypeAsString()<<" "<<token.getValue()<<"\n";
    }

    if(token.type == Error){
        cout<<token.getValue()<<"\n";
    }

    return 0;
}
