#pragma once
#include "types.h"
#include <vector>
#include <string>
#include <set>

class GrammarFileReader {
    Grammar grammar_;
    std::set<char> terms_;
    std::set<char> vars_;
    char start_sym;

    GrammarFileReader();
    GrammarFileReader(std::string);

    void parseFile(std::string);
    void parseSymbols();

    void printGrammar();
    void printVariables();
    void printTerminals();

    bool isVariable(char var) {
       return (vars_.find(var) != vars_.end());
    }
    bool isTerminal(char term) {
       return (terms_.find(term) != terms_.end());
    }

    Grammar getGrammar() { return grammar_; }
    std::set<char> getTerminals() { return terms_; }
    std::set<char> getVariables() { return vars_; }
    char getStartSym() { return start_sym; }
};
