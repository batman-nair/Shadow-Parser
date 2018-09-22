#include "grammarFR.h"
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
    start_sym_ = grammar_.begin()->first;

    findFirsts();
    findFollows();
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

void GrammarFileReader::findFollows() {
	follows_[start_sym_].insert('$');
	findFollows(start_sym_);
	// Find follows for rest of variables
	for(char ch: vars_) {
		if(follows_[ch].empty()) {
			findFollows(ch);
		}
	}
}

void GrammarFileReader::findFollows(char non_term) {
	// cout<<"Finding follow of "<<non_term<<"\n";

	for(auto it = grammar_.begin(); it != grammar_.end(); ++it) {

		// finished is true when finding follow from this production is complete
		bool finished = true;
		auto ch = it->second.begin();

		// Skip variables till reqd non terminal
		for(;ch != it->second.end() ; ++ch) {
			if(*ch == non_term) {
				finished = false;
				break;
			}
		}
		++ch;

		for(;ch != it->second.end() && !finished; ++ch) {
			// If non terminal, just append to follow
			if(!isupper(*ch)) {
				follows_[non_term].insert(*ch);
				finished = true;
				break;
			}

            std::set<char> firsts_copy(firsts_[*ch]);
			// If char's firsts doesnt have epsilon follow search is over
			if(firsts_copy.find('e') == firsts_copy.end()) {
				follows_[non_term].insert(firsts_copy.begin(), firsts_copy.end());
				finished = true;
				break;
			}
			// Else next char has to be checked after appending firsts to follow
			firsts_copy.erase('e');
			follows_[non_term].insert(firsts_copy.begin(), firsts_copy.end());

		}


		// If end of production, follow same as follow of variable
		if(ch == it->second.end() && !finished) {
			// Find follow if it doesn't have
			if(follows_[it->first].empty()) {
				findFollows(it->first);
			}
			follows_[non_term].insert(follows_[it->first].begin(), follows_[it->first].end());
		}

	}
}


void GrammarFileReader::printFollows() {
    std::cout<<"Follows list: \n";
	for(auto it = follows_.begin(); it != follows_.end(); ++it) {
        std::cout<<it->first<<" : ";
		for(auto follows_it = it->second.begin(); follows_it != it->second.end(); ++follows_it) {
            std::cout<<*follows_it<<" ";
		}
        std::cout<<"\n";
	}
    std::cout<<"\n";

}
