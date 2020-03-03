#ifndef LEXICALANALYZER_ANALYZER_H
#define LEXICALANALYZER_ANALYZER_H

#include <utility>
#include "Token.h"
#include "DFA.h"

using namespace std;

class Analyzer {
    DFA dfa;

public:
    Analyzer(string filename):dfa(filename) {
    }

    Token getToken();
};

#endif //LEXICALANALYZER_ANALYZER_H
