#pragma once
#include "grammar.h"
#include "parser.h"
#include <map>
#include <vector>
#include <utility>
#include <set>

typedef std::vector< ProdType > StateType;

class LR0Parser : public Parser {
    std::map< ProdType, int> StateMap;
    std::map< std::pair< int, char > , int> StateEdgeMap;
    std::vector<StateType> states;

    Grammar findClosure(ProdType inputPro, Grammar productions);



    public:
        void parseGrammar(Grammar);
        void printStates();
        void buildTable(Grammar);
        void printTable();
};
