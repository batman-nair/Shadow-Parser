// Everything comes together here

#include "types.h"
#include "grammar.h"
#include "parser.h"
#include "parsers/LR0Parser.h"


int main() {
    // Building the grammar
    GrammarFileReader gram("testgrammar.txt");
    gram.print();

    Parser *parser = new LR0Parser();
    parser->parseGrammar(gram.getGrammar(), gram.getTerminals(),gram.getVariables());
    parser->printStates();

    // TODO : Building the ParseTable and checking
    // parseGrammar() automatically calls buildTable()
    parser->printTable();
    return 0;
}
