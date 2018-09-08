#pragma once
#include <vector>
#include <utility>
#include <string>

typedef std::pair<char, std::string> ProdType;
typedef std::vector<ProdType> Grammar;
typedef std::pair<char, int> ParseCell;
typedef std::vector<ParseCell> ParseRow;
typedef std::vector<ParseRow> ParseTable;
