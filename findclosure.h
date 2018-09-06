#include<vector>
#include<iterator>
using namespace std;
#include "types.h";
Grammar findClosure( ProdType inputPro, Grammar productions){

  Grammar closure;
  string addedNterm="";

  closure.push_back(inputPro);
  for(auto itr=0;itr<closure.size();itr++){
        int dotpos= closure[itr].second.find(".");
        char symbol = closure[itr].second[dotpos+1];
        if(isupper(symbol) && (addedNterm.find(symbol))==string::npos){
                for(auto jtr=productions.begin(); jtr!= productions.end(); jtr++){
                    if((*jtr).first == symbol)
                        closure.push_back(make_pair((*jtr).first,(*jtr).second));
                }

                addedNterm+=symbol;
        }
  }
  return closure;
}
