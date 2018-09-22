#pragma once
#include "types.h"
#include "grammar.h"
#include "parser.h"
#include <map>
#include <vector>
#include <utility>
#include <set>

typedef std::vector< ProdType > StateType;

class SLR1Parser : public Parser {
    std::map< ProdType, int> StateMap;
    std::map< std::pair< int, char > , int> StateEdgeMap;
    std::vector<StateType> states;

    Grammar findClosure(ProdType inputPro, Grammar productions);



    public:
        void parseGrammar(Grammar, std::set<char>, std::set<char>, std::map<char, std::set<char>>);
        void printStates();
        void buildTable(Grammar, std::set<char>, std::set<char>, std::map<char, std::set<char>>);
        void printTable();
};
