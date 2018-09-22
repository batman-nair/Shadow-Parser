#pragma once
#include <vector>
#include <utility>
#include <string>
#include <set>
#include <map>


typedef std::pair<char, std::string> ProdType;
typedef std::vector<ProdType> GrammarType;


class Grammar {

    typedef GrammarType::iterator iterator;
    typedef GrammarType::const_iterator const_iterator;
    typedef GrammarType::size_type size_type;

    GrammarType grammar_;
    std::set<char> terms_;
    std::set<char> vars_;
    char start_sym_;
    std::map<char, std::set<char>> firsts_;
    std::map<char, std::set<char>> follows_;

    void findFirsts(char non_term);
    void findFollows(char non_term);

    void findFirsts();
    void findFollows();

  public:
    Grammar(GrammarType gram)
        :grammar_(gram) { }
    Grammar()
        :grammar_() { }

    GrammarType getVector() { return grammar_; }
    void parseSymbols();

    void printGrammar();
    void printVariables();
    void printTerminals();
    void printFirsts();
    void printFollows();
    void print() {
        printGrammar();
        printVariables();
        printTerminals();
        printFirsts();
        printFollows();
    }

    bool isVariable(char var) {
        return (vars_.find(var) != vars_.end());
    }
    bool isTerminal(char term) {
        return (terms_.find(term) != terms_.end());
    }

    std::set<char> getTerminals() { parseSymbols(); return terms_; }
    std::set<char> getVariables() { parseSymbols(); return vars_; }
    std::set<char> getFirsts(char var) { findFirsts(); return firsts_[var]; }
    std::set<char> getFollows(char var) { findFollows(); return follows_[var]; }
    std::map<char, std::set<char>> getAllFollows() { findFollows(); return follows_; }
    char getStartSym() { parseSymbols(); return start_sym_; }


    // Vector Redirects
    void push_back(const ProdType &p) { return grammar_.push_back(p); }

    ProdType& operator[] (std::size_t n) { return grammar_[n]; }
    iterator begin() { return grammar_.begin(); }
    const_iterator begin() const { return grammar_.begin(); }
    iterator end() { return grammar_.end(); }
    const_iterator end() const { return grammar_.end(); }
    size_type size() const { return grammar_.size(); }
    iterator insert(iterator position, const ProdType& p) { return grammar_.insert(position, p); }
};
