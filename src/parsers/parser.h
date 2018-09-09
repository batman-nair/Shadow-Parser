#pragma once
#include "../types.h"

class Parser {
public:
    virtual void parseGrammar(Grammar) = 0;
    virtual void printStates() = 0;
};
