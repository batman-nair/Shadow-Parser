#include "../../types.h"
#include "LR0Parser.h"
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <iostream>

Grammar LR0Parser::findClosure( ProdType inputPro, Grammar productions){
    Grammar closure;
    std::string addedNterm="";

    closure.push_back(inputPro);
    for(auto itr=0;itr<closure.size();itr++){
        int dotpos= closure[itr].second.find(".");
        char symbol = closure[itr].second[dotpos+1];
        if(isupper(symbol) && (addedNterm.find(symbol))==std::string::npos){
            for(auto jtr=productions.begin(); jtr!= productions.end(); jtr++){
                if((*jtr).first == symbol)
                    closure.push_back(std::make_pair((*jtr).first,(*jtr).second));
            }

            addedNterm+=symbol;
        }
    }
    return closure;
}

void LR0Parser::parseGrammar(Grammar gr){
    addDot(gr);

    states.push_back( findClosure( gr[0], gr )  );

    //iterate through all the states
    for(int stateno = 0; stateno<states.size();stateno++){
        //iterate through all the productions in a state
        for(int pno=0; pno <states[stateno].size();pno++ ){
            ProdType currentproduction = states[stateno][pno];

            int dotposition = currentproduction.second.find('.');
            //if the dot hasn't reached the end
            if(dotposition < currentproduction.second.length() -1){
                char nextsymbol  = currentproduction.second[dotposition+1];
                std::swap(currentproduction.second[dotposition],currentproduction.second[dotposition+1] );
                //if this is an entriely new state
                if(StateMap.find(currentproduction) == StateMap.end()){

                    if(StateEdgeMap.find( std::make_pair(stateno,nextsymbol)) == StateEdgeMap.end()  ){
                        states.push_back(findClosure(currentproduction,gr));
                        StateEdgeMap[ std::make_pair(stateno,nextsymbol)  ] =   states.size()-1 ;
                        StateMap[currentproduction] = states.size()-1;
                    }
                    else{
                        Grammar additionalpro = findClosure(currentproduction,gr);
                        int key = StateEdgeMap[ std::make_pair( stateno,nextsymbol  ) ];
                        states[key ].insert(states[key].end(), additionalpro.begin(),additionalpro.end()  )    ;
                    }
                }
                //if the new state is a duplicate
                //map to that state
                else{
                    StateEdgeMap[  std::make_pair(stateno,nextsymbol) ] = StateMap[currentproduction];
                }
            }
        }
    }
}

void LR0Parser::printStates(){
    for(int i=0;i<states.size();i++){
        std::cout<<"I"<<i<<std::endl;
        for(int j=0;j<states[i].size();j++){
            std::cout<<states[i][j].first<<" -> "<<states[i][j].second<<std::endl;
        }
        std::cout<<std::endl;
    }
}
