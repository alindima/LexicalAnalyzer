#include <fstream>
#include "include/Analyzer.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc != 2){
        cout<<"This program needs 1 argument: absolute path to input file\n";

        return 0;
    }

    Analyzer analyzer(argv[1]);

    ofstream fout("analysis.txt");

    Token token;

    while((token = analyzer.getToken()).type != Error && token.type != EndOfFile){
        fout<<token.getTokenTypeAsString()<<" "<<token.getValue()<<"\n";
    }

    if(token.type == Error){
        fout<<token.getValue()<<"\n";
    }

    fout.close();

    return 0;
}
