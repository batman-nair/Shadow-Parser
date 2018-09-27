#include "grammar.h"
#include "parsers/LR0Parser.h"
#include "parseTable.h"
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include <algorithm>
#include <climits>

Grammar LR0Parser::findClosure( ProdType inputPro, Grammar productions){
    Grammar closure;
    std::string addedNterm="";

    closure.push_back(inputPro);
    for(std::size_t itr=0;itr<closure.size();itr++){
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
    augment(gr);

    std::set<char> terminals = gr.getTerminals();
    std::set<char> variables = gr.getVariables();
    states.push_back( findClosure( gr[0], gr ).getVector()  );

    //iterate through all the states
    for(std::size_t stateno = 0; stateno<states.size();stateno++){
        //iterate through all the productions in a state
        for(std::size_t pno=0; pno <states[stateno].size();pno++ ){
            ProdType currentproduction = states[stateno][pno];

            std::size_t dotposition = currentproduction.second.find('.');
            //if the dot hasn't reached the end
            if(dotposition < currentproduction.second.length() -1){
                char nextsymbol  = currentproduction.second[dotposition+1];
                std::swap(currentproduction.second[dotposition],currentproduction.second[dotposition+1] );
                //if this is an entriely new state
                if(StateMap.find(currentproduction) == StateMap.end()){

                    if(StateEdgeMap.find( std::make_pair(stateno,nextsymbol)) == StateEdgeMap.end()  ){
                        states.push_back(findClosure(currentproduction,gr).getVector());
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
            //If its a final state
            else{
              //TODO change map
                  //If it's the augmented production

                  if(currentproduction.first == 'Z'){
                      StateEdgeMap[std::make_pair(stateno,'$') ] = INT_MIN;
                      //Accepting state
                  }
                  else{
                      ProdType tmp = currentproduction;
                      tmp.second ='.'+ tmp.second.substr(0, tmp.second.size() - 1);
                      StateEdgeMap[ std::make_pair(stateno,' ')]= -1 *  (std::find(gr.begin(), gr.end(), tmp) - gr.begin() );
                  }

            }
        }
    }

    buildTable(gr);
}

void LR0Parser::printStates(){
    for(std::size_t i=0;i<states.size();i++){
        std::cout<<"I"<<i<<std::endl;
        for(std::size_t j=0;j<states[i].size();j++){
            std::cout<<states[i][j].first<<" -> "<<states[i][j].second<<std::endl;
        }
        std::cout<<std::endl;
    }
}

void LR0Parser::buildTable(Grammar gr){
  ///   Takes a  grammar as argument instead
      std::set<char> terminals = gr.getTerminals();
      std::set<char> variables = gr.getVariables();
      int cols,i=0;
      cols = terminals.size() + variables.size() +1;

      ParseRow parseRow("State",terminals,variables);
      parseTable_.setHeader(parseRow);


    for(std::size_t i=0;i<states.size();i++){
        //NEW ///
        ParseRow tmpRow(cols);
        tmpRow[0] = "I" + std::to_string(i);
        //
        bool reduction =false;

        if(StateEdgeMap.find(std::make_pair(i,' ')) != StateEdgeMap.end()){
              reduction =true;
        }
        for(std::size_t j=1;j<parseRow.size();j++){
            //If theres isnt an entry
            if( StateEdgeMap.find( std::make_pair(i,parseRow[j][0]) ) == StateEdgeMap.end() );
                  // tmpRow[j]="";
            else{
                  int nextState = StateEdgeMap[ std::make_pair(i,parseRow[j][0]) ];
                  if(nextState == INT_MIN){
                      tmpRow[j] = "acc";
                  }
                  else{
                      //Whether it's a shift or reduce
                      std::string sOrR = terminals.find(parseRow[j][0]) != terminals.end()? "S" : "";
                      tmpRow[j]+= sOrR + std::to_string(nextState)+ ' ';
                  }
              }


        }
        //If reduction
        if(reduction){
          for(std::size_t j=1;j<=terminals.size();j++){
            tmpRow[j]+= 'r' + std::to_string(-1* StateEdgeMap[std::make_pair(i,' ') ] ) + ' ';
          }

        }
        //Can be replaced by parseTable.push(row);
        parseTable_.push(tmpRow);
    }

}


void LR0Parser::printTable(){
    parseTable_.printTable();
}
