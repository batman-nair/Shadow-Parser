#pragma once
#include "types.h"
#include "parser.h"
#include <string>
#include "parsers/LR0Parser.h"
#include "parsers/SLR1Parser.h"
#include<iostream>

class ParserFactory{
  public :
    Parser* manufactureParser(std::string name){
          Parser *tmp;
          if(name == "SLR"){
              tmp = new SLR1Parser();
              std::cout<<"Making SLR ...\n";
          }
          else{
              tmp = new LR0Parser();
              std::cout<<"Making LR0 ...\n";
          }
          return tmp;
    }
};
