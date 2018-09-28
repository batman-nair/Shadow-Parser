#include "grammarFR.h"
#include <iostream>
#include <vector>
#include <fstream>

GrammarFileReader::GrammarFileReader(std::string filename) {
    parseFile(filename);
}

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
