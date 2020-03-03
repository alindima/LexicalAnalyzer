#include <iostream>
#include "include/Analyzer.h"

using namespace std;

int main() {
    Analyzer analyzer("C:\\Users\\alin\\CLionProjects\\LexicalAnalyzer\\input\\test.txt");

    Token token;

    while((token = analyzer.getToken()).type != Error){
        if(token.value != " " && token.value != "\n"){
            cout<<token.value<<"\n";
        }
    }

    return 0;
}
