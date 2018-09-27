#include "parseTable.h"
#include <map>
#include <vector>
#include <utility>
#include <set>
#include<iostream>
#include<string>
#include<algorithm>
ParseRow::ParseRow(){

}
ParseRow::ParseRow(std::string stateNo, std::set<char> terminals, std::set<char> variables){
                row.push_back(stateNo);
                for(auto itr : terminals)
                    row.push_back( std::string(1,itr) );
                for(auto itr : variables)
                    row.push_back(std::string(1,itr));
}

ParseRow::ParseRow(int colsCount){
      row.resize(colsCount);
}
std::vector<std::string>::iterator ParseRow::begin(){
      return row.begin();
}


std::vector<std::string>::iterator ParseRow::find(std::string str){
      return std::find(row.begin(),row.end(),str);
}

std::vector<std::string>  ParseRow::getRow(){
      return row;
}
std::string& ParseRow::operator[](int index){
      return row[index];
}

int ParseRow::size(){
      return row.size();
}

ParseTable::ParseTable(){

}

void ParseTable::push(ParseRow row){
      tableContent_.push_back(row);
}

void ParseTable::setHeader(ParseRow header){
    tableHeader_ = header;
}

ParseRow& ParseTable:: operator[](int stateNo){
      return tableContent_[stateNo];
}

void ParseTable::printTable(){
    for(int i=0;i<tableHeader_.size();i++)
        std::cout<<tableHeader_[i]<<"\t";
    std::cout<<"\n";
    for(int i=0;i<tableContent_.size();i++){
          for(int j=0;j<tableContent_[i].size();j++)
              std::cout<<tableContent_[i][j]<<"\t";
          std::cout<<"\n";
    }
}

std::string ParseTable::getMove(int stateNo, char symbol){
        return tableContent_[stateNo][tableHeader_.find(std::string(1,symbol)) - tableHeader_.begin() ];
}
