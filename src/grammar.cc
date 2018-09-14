#include "grammar.h"
#include "types.h"
#include <iostream>
#include <vector>
#include <fstream>

GrammarFileReader::GrammarFileReader(std::string filename) {
    parseFile(filename);
    parseSymbols();
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

void GrammarFileReader::findFirsts() {
    for(char var: vars_) {
        if(firsts_[var].empty()){
            findFirsts(var);
        }
    }
}

void GrammarFileReader::findFirsts(char var) {

    // std::cout<<"Finding firsts of "<<var<<"\n";

    for(ProdType prod: grammar_) {
        // Find productions of the non terminal
        if(prod.first != var) {
            continue;
        }

        // std::cout<<"Processing production "<<prod.first<<"->"<<prod.second<<"\n";

        std::string rhs = prod.second;
        // Loop till a non terminal or no epsilon variable found
        for(char ch: rhs) {
            // If first char in production a non term, add it to firsts list
            if(!isupper(ch)) {
                firsts_[var].insert(ch);
                break;
            }
            else {
                // If char in prod is non terminal and whose firsts has no yet been found out
                // Find first for that non terminal if it is not itself
                if(firsts_[ch].empty() && var != ch) {
                    findFirsts(ch);
                }
                // If variable doesn't have epsilon, stop loop
                if(firsts_[ch].find('e') == firsts_[ch].end()) {
                    firsts_[var].insert(firsts_[ch].begin(), firsts_[ch].end());
                    break;
                }

                std::set<char> firsts_copy(firsts_[ch].begin(), firsts_[ch].end());

                // Remove epsilon from firsts if not the last variable
                // (epsilon not considered now so this is commented)
                // if(ch + 1 != rhs.end()) {
                //     firsts_copy.erase('e');
                // }

                // Append firsts of that variable
                firsts_[var].insert(firsts_copy.begin(), firsts_copy.end());
            }
        }
    }
}

void GrammarFileReader::printFirsts() {
    std::cout<<"Firsts list: \n";
    for(auto it = firsts_.begin(); it != firsts_.end(); ++it) {
        std::cout<<it->first<<" : ";
        for(char ch: it->second) {
            std::cout<<ch<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}
