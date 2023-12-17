#include "parser.hpp"
#include "syntaxTree.hpp"

/* Rule: program → stmt-sequence */
SyntaxTree* Parser::program()
{
    SyntaxTree* programTree = new SyntaxTree();
    programTree = stmt_sequence();
    return programTree;
}

/*
    stmt-sequence → stmt-sequence ; statement | statement
    EBNF: stmt-sequence → statement {; statement}
*/
SyntaxTree* Parser::stmt_sequence()
{
    SyntaxTree* stmtSequenceTree = new SyntaxTree();
    stmtSequenceTree->childs.push_back(statement());
    while( SEMICOLON == tokens[index]->type )
    {
        match(SEMICOLON);
        stmtSequenceTree->childs.push_back(statement());
    }
}




/* Update the index of the token */
void Parser::match(TokenType tokenType)
{
    if(index < tokens.size())
    {
        index++;
    }
}