// Everything comes together here

#include "types.h"
#include "grammar.h"
#include "parsers/parser.h"
#include "parsers/LR0/LR0Parser.h"


int main() {
    // Building the grammar
    GrammarFileReader gram("testgrammar.txt");
    gram.print();

    Parser *parser = new LR0Parser();
    parser->parseGrammar(gram.getGrammar());
    parser->printStates();

    // TODO : Building the ParseTable and checking


    return 0;
}

