#pragma once

#include "scanner.hpp"
#include "SyntaxTree.hpp"
#include <stdio.h>


class Parser
{
private:
    SyntaxTree *syntaxTree = nullptr;
    bool error = false;
    unsigned int index = 0;
    Token token;

    SyntaxTree* stmt_sequence (std::vector<Token> Tokens);
    SyntaxTree* statement (std::vector<Token> Tokens);
    SyntaxTree* if_stmt (std::vector<Token> Tokens);
    SyntaxTree* repeat_stmt (std::vector<Token> Tokens);
    SyntaxTree* assign_stmt (std::vector<Token> Tokens);
    SyntaxTree* read_stmt (std::vector<Token> Tokens);
    SyntaxTree* write_stmt (std::vector<Token> Tokens);
    SyntaxTree* exp (std::vector<Token> Tokens);
    SyntaxTree* comparison_op (std::vector<Token> Tokens);
    SyntaxTree* simple_exp(std::vector<Token> Tokens);
    SyntaxTree* addop(std::vector<Token> Tokens);
    SyntaxTree* term(std::vector<Token> Tokens);
    SyntaxTree* mulop(std::vector<Token> Tokens);
    SyntaxTree* factor(std::vector<Token> Tokens);
    void match(QString input, std::vector<Token> Tokens);

public:
    Parser();
    SyntaxTree* program (std::vector<Token> Tokens);
    //Takes a string of TINY-language code and constructs the parse tree in its private member "syntaxTree"
    void parseString(QString code);
    std::set<int> err;
    SyntaxTree *getOutputTree()  ;
    bool getError() const;
};

