#include "parseTable.h"
#include <map>
#include <vector>
#include <utility>
#include <set>
#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <cctype>
#include "grammar.h"

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

std::size_t ParseRow::size(){
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
    for(std::size_t i=0;i<tableHeader_.size();i++)
        std::cout<<tableHeader_[i]<<"\t";
    std::cout<<"\n";
    for(std::size_t i=0;i<tableContent_.size();i++){
          for(std::size_t j=0;j<tableContent_[i].size();j++)
              std::cout<<tableContent_[i][j]<<"\t";
          std::cout<<"\n";
    }
}

std::string ParseTable::getMove(int stateNo, char symbol){
        return tableContent_[stateNo][tableHeader_.find(std::string(1,symbol)) - tableHeader_.begin() ];
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

bool ParseTable::checkString(std::string str, Grammar gram) {
    str.append("$");
    std::stack<std::string> input_stack;
    input_stack.push("0");

    while(true) {

            int state_no = stoi(input_stack.top());
            char input_char = str[0];

            std::string action = getMove(state_no, input_char);

            switch(action[0]) {
                case 'S':
                    input_stack.push(std::to_string(str[0]));
                    str.erase(str.begin());
                    input_stack.push(action.substr(1));

                    break;
                case 'r':
                    {
                        int production_no = stoi(action.substr(1));
                        int size_of_production = gram[production_no-1].second.size();
                        for(int i = 0; i < size_of_production*2; ++i) {
                            input_stack.pop();
                        }

                        // Push reduced prod var

                        input_stack.push(std::string(1, gram[production_no-1].first));

                        std::string top_variable = input_stack.top();
                        input_stack.pop();
                        int top_state_num = stoi(input_stack.top());
                        std::string new_state_num = getMove(top_state_num, top_variable[0]);
                        input_stack.push(top_variable);
                        input_stack.push(new_state_num);
                    }
                    break;

                case 'a':
                    return true;
                default:
                    return false;

        }

    }
    return false;
}

