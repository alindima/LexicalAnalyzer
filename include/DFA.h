#ifndef LEXICALANALYZER_DFA_H
#define LEXICALANALYZER_DFA_H

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_set>

using namespace std;

class DFA {
    ifstream* fin = nullptr;

    int currentState;

    map<pair<int, string>, int> transitions = {{{0, ";"},6}, {{0, "+"},4}, {{0, "*"},4},
                                             {{0, "("},4}, {{0, ")"},4}, {{0, "="},4},
                                             {{0, " "},5}, {{0, "\n"},5}, {{0, "/"},3}, {{0, "+"},4},
                                               {{0, "cif"},2}, {{0, "lit"},1},
                                               {{1, "lit"},1}, {{1, "cif"},1},
                                               {{2, "cif"},2}, {{3, "*"},8},
                                               {{5, " "},5}, {{5, "\n"},5}, {{8, "*"},9},
                                               {{8, "notstar"},8}, {{9, "notslash"},8},
                                               {{9, "/"},10}};

    unordered_set<int> finalStates = {1, 2, 3, 4, 5, 6, 10};

    void reset() {
        currentState = 0;
    }

public:
    DFA(string filename):currentState(0),fin(new ifstream(filename)) {}

    ~DFA() {
        fin->close();
        delete fin;
        fin= nullptr;
    }

    string parseToken() {
        char character;
        string token = "";

        while(*fin >> noskipws >> character){
            //cout<<character;


            if(transitions.count({currentState, string(1,character)})){
                token += character;
                currentState = transitions[{currentState, string(1,character)}];
            }else if(isdigit(character) && transitions.count({currentState, "cif"})) {
                token += character;
                currentState = transitions[{currentState, "cif"}];
            }else if(isalpha(character) && transitions.count({currentState, "lit"})){
                token += character;
                currentState = transitions[{currentState, "lit"}];
            }else if(character != '*' && transitions.count({currentState, "notstar"})){
                token += character;
                currentState = transitions[{currentState, "notstar"}];
            }else if(character != '/' && transitions.count({currentState, "notslash"})){
                token += character;
                currentState = transitions[{currentState, "notslash"}];
            }else{
                // the automaton is blocked
                fin->putback(character);

                if(finalStates.count(currentState)){
                    reset();
                    return token;
                }else {
                    reset();
                    return "Error";
                }
            }
        }


        if(finalStates.count(currentState)){
            reset();
            return token;
        }else {
            reset();
            return "Error";
        }
    }
};

#endif //LEXICALANALYZER_DFA_H
