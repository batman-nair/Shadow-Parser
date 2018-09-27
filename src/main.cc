// Everything comes together here

#include "types.h"
#include "grammarFR.h"
#include "parser.h"
#include <iostream>
#include <utility>
#include <string>
#include <memory>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout<<"./shadow-parser <parser-type> <input-string>"<<std::endl;
        std::cout<<"Example: ./shadow-parser SLR \"i+i\""<<std::endl;
        return 0;
    }

    std::string parser_name(argv[1]), input_string(argv[2]);

    // Building the grammar
    GrammarFileReader gramFR("testgrammar.txt");
    Grammar gram = gramFR.getGrammar();
    gramFR.getGrammar().print();

    // Creating from ParserFactory
    std::unique_ptr<Parser> parser(Parser::buildParser(parser_name));

    parser->parseGrammar(gramFR.getGrammar());

    parser->printTable();
    if(parser->checkString(input_string, gramFR.getGrammar())) {
        std::cout<<"\nInput string is accepted"<<std::endl;
    }

    return 0;
}
