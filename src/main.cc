// Everything comes together here

#include "types.h"
#include "grammar.h"
#include "parser.h"
#include "ParserFactory.h"
#include<iostream>
#include<utility>
#include<string>


int main() {
    // Building the grammar
    GrammarFileReader gram("testgrammar.txt");

    ParserFactory factory;
    std::cout<<"Choose which type of parser\n";
    std::string input;
    std::cin>>input;
    //Made a parser Factory
    Parser *parser = factory.manufactureParser(input);

    gram.print();
    parser->parseGrammar(gram.getGrammar(), gram.getTerminals(),gram.getVariables(),gram.getAllFollows() );
    parser->printStates();

    // TODO : Building the ParseTable and checking
    // parseGrammar() automatically calls buildTable()
    parser->printTable();
    return 0;
}
