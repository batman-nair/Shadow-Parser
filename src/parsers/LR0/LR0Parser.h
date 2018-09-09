#pragma once
#include "../../types.h"
#include "../parser.h"
#include <map>
#include <vector>
#include <utility>


typedef std::vector< ProdType > StateType;

class LR0Parser : public Parser {
    ParseTableType parseTable;
    std::map< ProdType, int> StateMap;
    std::map< std::pair< int, char > , int> StateEdgeMap;
    std::vector<StateType> states;

    Grammar findClosure(ProdType inputPro, Grammar productions);

    void addDot( Grammar &pr ){
        for(auto i = pr.begin(); i!=pr.end(); i++)
            (*i).second="."+(*i).second;
    }

    public:
        void parseGrammar(Grammar);
        void printStates();
};
