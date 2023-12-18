#pragma once 
#include "syntaxTree.hpp"
#include <vector>
#include <set>

class Parser
{
    private:
        unsigned int index;
        SyntaxTree* program();
        SyntaxTree* stmt_sequence();
        SyntaxTree* statement();
        SyntaxTree* if_stmt();
        SyntaxTree* repeat_stmt();
        SyntaxTree* assign_stmt();
        SyntaxTree* read_stmt();
        SyntaxTree* write_stmt();
        SyntaxTree* exp();
        SyntaxTree* comparison_op();
        SyntaxTree* simple_exp();
        SyntaxTree* addop();
        SyntaxTree* term();
        SyntaxTree* mulop();
        SyntaxTree* factor();
        void match(TokenType tokenType);

    public:
        SyntaxTree* syntaxTree = nullptr;
        std::vector<Token*>tokens;
        std::set<unsigned int>errors;
};