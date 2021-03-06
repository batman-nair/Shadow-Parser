#include "parser.h"
#include "parsers/LR0Parser.h"
#include "parsers/SLR1Parser.h"
#include <iostream>
#include <string>
#include <stack>

Parser* Parser::buildParser(std::string str) {
    if (str == "SLR") {
        std::cout<<"Making SLR ...\n";
        return new SLR1Parser();
    }
    else {
        std::cout<<"Making LR ...\n";
        return new LR0Parser();
    }
}

