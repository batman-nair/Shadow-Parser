#include<bits/stdc++.h>
using namespace std;
#include "types.h"



class LR0Parser{
    ParseTableType parseTable;
    map< ProdType, int> StateMap;
    map< pair< int, char > , int> StateEdgeMap;
    vector<StateType> states;

    public :
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

            void parseGrammar(Grammar gr  ){
                  states.push_back( findClosure( gr[0], gr )  );

                  //Iterate through all the states
                  for(int stateno = 0; stateno<states.size();stateno++){
                    //Iterate through all the productions in a state
                      for(int pno=0; pno <states[stateno].size();pno++ ){
                              ProdType currentProduction = states[stateno][pno];

                              int dotPosition = currentProduction.second.find('.');
                              //If the dot hasn't reached the end
                              if(dotPosition < currentProduction.second.length() -1){
                                char nextSymbol  = currentProduction.second[dotPosition+1];
                                swap(currentProduction.second[dotPosition],currentProduction.second[dotPosition+1] );
                                //If this is an entriely new state
                                if(StateMap.find(currentProduction) == StateMap.end()){

                                  if(StateEdgeMap.find( make_pair(stateno,nextSymbol)) == StateEdgeMap.end()  ){
                                    states.push_back(findClosure(currentProduction,gr));
                                    StateEdgeMap[ make_pair(stateno,nextSymbol)  ] =   states.size()-1 ;
                                    StateMap[currentProduction] = states.size()-1;
                                  }
                                  else{
                                      Grammar additionalPro = findClosure(currentProduction,gr);
                                      int key = StateEdgeMap[ make_pair( stateno,nextSymbol  ) ];
                                      states[key ].insert(states[key].end(), additionalPro.begin(),additionalPro.end()  )    ;
                                  }
                                }
                                //If the new state is a duplicate
                                //Map to that state
                                else{
                                    StateEdgeMap[  make_pair(stateno,nextSymbol) ] = StateMap[currentProduction];
                              }
                      }
                  }
                }
            }

            void printTable(){

            }

            void printStates(){
                for(int i=0;i<states.size();i++){
                    cout<<"I"<<i<<endl;
                    for(int j=0;j<states[i].size();j++){
                        cout<<states[i][j].first<<" -> "<<states[i][j].second<<endl;
                    }
                    cout<<endl;
                }
            }
};
