#include<iostream>
#include<vector>
#include<iterator>
#include<set>

using namespace std;
#include "types.h"
// #include "findclosure.h"
#include "LR0.h"




vector<string> initializeGrammar(){
  RawGrammar g;
  g.push_back("S->E");
  g.push_back("E->E+(E)");
  g.push_back("E->i");
  return g;
}
//Convert Strings to Grammar
Grammar addProductions(RawGrammar grammar){
        Grammar productions;
        productions.push_back( make_pair('Z',grammar[0].substr(0,1)));
        for(int i=0; i<grammar.size();i++)
              productions.push_back( make_pair( grammar[i][0],grammar[i].substr(3) ));

        return productions;
}

void addDot( Grammar &pr ){
        for(auto i = pr.begin(); i!=pr.end(); i++)
                (*i).second="."+(*i).second;
}

int main(){
  RawGrammar gr = initializeGrammar();
  Grammar productions = addProductions(gr);


  addDot(productions);

  LR0Parser lr;
  lr.parseGrammar(productions);
  lr.printStates();


  return 0;
}
