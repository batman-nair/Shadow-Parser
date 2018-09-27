// Everything comes together here

#include "types.h"
#include "grammarFR.h"
#include "parser.h"
#include <iostream>
#include <utility>
#include <string>
#include <memory>

int main() {
    // Building the grammar
    GrammarFileReader gramFR("testgrammar.txt");
    Grammar gram = gramFR.getGrammar();
    gramFR.getGrammar().print();

    std::string input;
    std::cout<<"Choose which type of parser: ";
    std::cin>>input;
    // Creating from ParserFactory
    std::unique_ptr<Parser> parser( Parser::buildParser(input) );

    // parser->parseGrammar(gramFR.getGrammar(), gram.getTerminals(), gram.getVariables(), gram.getAllFollows());
    // parser->printStates();

    // TODO : Building the ParseTable and checking
    // parseGrammar() automatically calls buildTable()

    // parser->printTable();

    return 0;
}
