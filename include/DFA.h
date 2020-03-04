#ifndef LEXICALANALYZER_DFA_H
#define LEXICALANALYZER_DFA_H

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class DFA {
    ifstream* fin = nullptr;

    int currentState;

    int position = 0;

    map<pair<int, string>, int> transitions = {{{0, ";"},6}, {{0, ","},15},
                                               {{0, "\""},11}, {{0, "'"},13}, {{0, "+"},4}, {{0, "*"},4},
                                             {{0, "("},4},{{0, "["},4},{{0, "]"},4}, {{0, "{"},4},
                                               {{0, "}"},4},{{0, "&"},4},{{0, "|"},4},{{0, ")"},4}, {{0, "="},4},
                                             {{0, " "},5}, {{0, "\n"},5}, {{0, "/"},3}, {{0, "+"},4},
                                               {{0, "cif"},2}, {{0, "lit"},1},
                                               {{1, "lit"},1}, {{1, "cif"},1},
                                               {{2, "cif"},2}, {{3, "*"},8}, {{3, "/"},7},
                                               {{5, " "},5}, {{5, "\n"},5}, {{8, "*"},9},
                                               {{8, "notstar"},8}, {{9, "notslash"},8},
                                               {{9, "/"},10}, {{7, "notnewline"},7},
                                               {{11, "not\""},11}, {{11, "\""},12},
                                               {{13, "not'"},13}, {{13, "'"},14}};

    unordered_set<int> finalStates = {1, 2, 4, 5, 6, 7, 10, 12, 14, 15};

    // maps from final states to token types
    unordered_map<int, TokenType> tokenTypes = {{1, Identifier}, {2, Number}, {4, Operator},
                                                {5, Space}, {6, Semicolon}, {10, Comment},
                                                {7, Comment}, {12, String}, {14, String}, {15, Comma}};

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

    pair<string, TokenType> parseToken() {
        char character;
        string token = "";

        while(*fin >> noskipws >> character){
            position++;

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
            }else if(character != '\n' && transitions.count({currentState, "notnewline"})){
                token += character;
                currentState = transitions[{currentState, "notnewline"}];
            }else if(character != '"' && transitions.count({currentState, "not\""})){
                token += character;
                currentState = transitions[{currentState, "not\""}];
            }else if(character != '\'' && transitions.count({currentState, "not'"})){
                token += character;
                currentState = transitions[{currentState, "not'"}];
            }else{
                // the automaton is blocked
                fin->putback(character);
                position--;

                if(finalStates.count(currentState)){
                    int state = currentState;
                    reset();
                    return {token, tokenTypes[state]};
                }else {
                    reset();
                    return {"Error at position " + to_string(position), Error};
                }
            }
        }

        if(finalStates.count(currentState)){
            int state = currentState;
            reset();
            return {token, tokenTypes[state]};
        }else {
            reset();
            return {"",EndOfFile};
        }
    }
};

#endif //LEXICALANALYZER_DFA_H
