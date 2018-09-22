#pragma once
#include "grammar.h"
#include "types.h"
#include <vector>
#include <string>
#include <set>
#include <map>

class GrammarFileReader {
    Grammar grammar_;

    public:
        GrammarFileReader();
        GrammarFileReader(std::string);

        void parseFile(std::string);

        Grammar getGrammar() { return grammar_; }

        void print() { grammar_.print(); }
};
