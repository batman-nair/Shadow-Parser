#include "grammar.h"
#include "types.h"
#include <iostream>
#include <vector>
#include <fstream>

void GrammarFileReader::parseFile(std::string filename) {
    std::ifstream grammar_file(filename);

    if(!grammar_file.is_open()) {
        std::cout<<"Error opening grammar file: "<<filename<<std::endl;
    }

    for(std::string line; std::getline(grammar_file, line);) {
        char lhs = line[0];
        std::string rhs = line.substr(3);

        ProdType prod(lhs, rhs);

        grammar_.push_back(prod);
    }
}

void GrammarFileReader::parseSymbols() {
    // Parsing Variables in the grammar
    for(ProdType prod: grammar_) {
        vars_.insert(prod.first);
    }

    // Parsing Terminals in the grammar
    for(ProdType prod: grammar_) {
        for(char ch: prod.second) {
            if(!isupper(ch)) {
                terms_.insert(ch);
            }
        }
    }
    // Remove epsilon and add end character $
    terms_.erase('e');
    terms_.insert('$');

    // Setting the start symbol in the grammar
	// Start symbol is first non terminal production in grammar
    start_sym = grammar_.begin()->first;
}

void GrammarFileReader::printGrammar() {
    std::cout<<"Grammar: "<<std::endl;
    for(ProdType prod: grammar_) {
        std::cout<<prod.first<<"->"<<prod.second<<std::endl;
    }
}

void GrammarFileReader::printVariables() {
    std::cout<<"Variables in the grammar: ";
    for(char ch: vars_) {
        std::cout<<ch<<" ";
    }
    std::cout<<std::endl;
}

void GrammarFileReader::printTerminals() {
    std::cout<<"Terminals in the grammar: ";
    for(char ch: terms_) {
        std::cout<<ch<<" ";
    }
    std::cout<<std::endl;
}
