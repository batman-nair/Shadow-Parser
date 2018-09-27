#pragma once
#include <map>
#include <vector>
#include <utility>
#include <set>
#include<string>
#include<algorithm>

class ParseRow{
      std::vector<std::string> row;
      public :
          //Useful in case of header row when we know all the elements
          //to be added into the header
          ParseRow();
          ParseRow(std::string stateNo, std::set<char> terminals, std::set<char> variables);

          ParseRow(int colsCount);
          std::vector<std::string> getRow();
          std::string& operator[](int index);

          int size();
          std::vector<std::string>::iterator find(std::string str);
          std::vector<std::string>::iterator begin();
};



class ParseTable{
      ParseRow tableHeader_;
      std::vector< ParseRow> tableContent_;

      public :
            ParseTable();
            void push(ParseRow row);
            void setHeader(ParseRow header);

            ParseRow& operator[](int stateNo);
            void printTable();
            std::string getMove(int stateNo, char symbol);

};
