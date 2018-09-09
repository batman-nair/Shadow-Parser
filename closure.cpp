#include<iostream>
#include<vector>
#include<iterator>
#include<set>

using namespace std;
#include "types.h"
// #include "findclosure.h"
#include "parse.h"




vector<string> initializeGrammar(){
  RawGrammar g;
  g.push_back("S->AA");
  g.push_back("S->AB");
  g.push_back("B->a");
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

  parseGrammar(productions);
  // for(int i=0;i<productions.size();i++){
  //     ProdType str = productions[i];
  //     Grammar output =  findClosure(str, productions);
  //
  //     for(auto itr=output.begin();itr!=output.end();itr++)
  //         cout<<(*itr).first<<"->"<<(*itr).second<<endl;
  //       cout<<endl;
  //   }


  return 0;
}
