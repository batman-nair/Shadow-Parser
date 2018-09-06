#include<iostream>
#include<vector>
#include<iterator>
#include<set>

using namespace std;
#include "types.h"
#include "findclosure.h"


//Input is a a particular production
//Returns a Canonical state
//Function to find the closure state

// Grammar findClosure( ProdType inputPro, Grammar &productions ){
//
//   Grammar closure;
//   // Grammar productions;
//
//   string addedNterm="";
//
//   closure.push_back(inputPro);
//
//   for(auto itr=0;itr<closure.size();itr++){
//         int dotpos= closure[itr].second.find(".");
//         char symbol = closure[itr].second[dotpos+1];
//         if(isupper(symbol) && (addedNterm.find(symbol))==string::npos){
//                 for(auto jtr=productions.begin(); jtr!= productions.end(); jtr++){
//                     if((*jtr).first == symbol)
//                         closure.push_back(make_pair((*jtr).first,(*jtr).second));
//                 }
//
//                 addedNterm+=symbol;
//         }
//   }
//   return closure;
// }
//

vector<string> initializeGrammar(){
  RawGrammar g;
  g.push_back("S->AA");
  g.push_back("S->B");
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

  for(int i=0;i<productions.size();i++){
      ProdType str = productions[i];
      Grammar output =  findClosure(str, productions);

      for(auto itr=output.begin();itr!=output.end();itr++)
          cout<<(*itr).first<<"->"<<(*itr).second<<endl;
        cout<<endl;
    }


  return 0;
}
