#pragma once
#include "grammar.h"
#include "types.h"
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <set>

class Parser {
      protected:
          ParseTableType parseTable_;

          void augment( Grammar &pr ){
              pr.insert( pr.begin(), ProdType('Z',std::string(1,pr[0].first) ) );
              for(auto i = pr.begin(); i!=pr.end(); i++)
                  (*i).second="."+(*i).second;
          }

      public:
          static Parser* buildParser(std::string);


          virtual void parseGrammar(Grammar, std::set<char>, std::set<char>, std::map<char,std::set<char>> ) = 0;

          virtual void printStates() = 0;
          virtual void printTable() = 0;

          virtual ~Parser() { }
};
