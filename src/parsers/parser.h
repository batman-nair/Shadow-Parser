#pragma once
#include "../types.h"
#include<vector>
#include<string>
#include<utility>
#include<map>
class Parser {
public:
    virtual void parseGrammar(Grammar) = 0;
    virtual void printStates() = 0;

    void augment( Grammar &pr ){
        pr.vector::insert( pr.begin(), std::make_pair('Z',std::string(1,pr[0].first) ) );
        for(auto i = pr.begin(); i!=pr.end(); i++)
            (*i).second="."+(*i).second;
    }
};
