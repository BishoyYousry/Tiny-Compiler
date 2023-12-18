#include "parser.hpp"
#include "syntaxTree.hpp"
#include <iostream>

/* Rule: program → stmt-sequence */
SyntaxTree* Parser::program()
{
    SyntaxTree* programTree = new SyntaxTree();
    programTree = stmt_sequence();
    return programTree;
}

/*
    Rule: stmt-sequence → stmt-sequence ; statement | statement
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
    return stmtSequenceTree;
}

/* Rule: statement → if-stmt | repeat-stmt | assign-stmt | read-stmt | write-stmt */
SyntaxTree* Parser::statement()
{
    SyntaxTree* statementTree = new SyntaxTree();
    /* check the possible first tokens of each type of statement rule */
    switch(tokens[index]->type)
    {
        case IF:
            statementTree->childs.push_back(if_stmt());
            break;

        case REPEAT:
            statementTree->childs.push_back(repeat_stmt());
            break;

        case IDENTIFIER:
            statementTree->childs.push_back(assign_stmt());
            break;

        case READ:
            statementTree->childs.push_back(read_stmt());
            break;

        case WRITE:
            statementTree->childs.push_back(write_stmt());
            break;

        default:
            errors.insert(index);
            break;
    }
    return statementTree;
}


/*
    Rule: if-stmt → if exp then stmt-sequence end | if exp then stmt-sequence else stmt-sequence end
    EBNF: if-stmt → if exp then stmt-sequence [else stmt-sequence] end
*/
SyntaxTree* Parser::if_stmt()
{
    SyntaxTree* ifStmtTree = new SyntaxTree();
    match(IF);
    ifStmtTree->childs.push_back(exp());
    match(THEN);
    ifStmtTree->childs.push_back(stmt_sequence());
    if(ELSE == tokens[index]->type)
    {
        match(ELSE);
        ifStmtTree->childs.push_back(stmt_sequence());
        match(END);
    }
    return ifStmtTree;
}

/* Rule: repeat-stmt → repeat stmt-sequence until exp */
SyntaxTree* Parser::repeat_stmt()
{
    SyntaxTree* repeatStmtTree = new SyntaxTree();
    match(REPEAT);
    repeatStmtTree->childs.push_back(stmt_sequence());
    match(UNTIL);
    repeatStmtTree->childs.push_back(exp());
    return repeatStmtTree;
}


/* Rule: assign-stmt → identifier := exp */
SyntaxTree* Parser::exp()
{
    SyntaxTree* expTree = new SyntaxTree();
    match(IDENTIFIER);
    match(ASSIGN);
    expTree->childs.push_back(exp());
    return expTree;
}

/* Rule: read-stmt → read identifier */
SyntaxTree* Parser::read_stmt()
{
    SyntaxTree* readStmtTree = new SyntaxTree();
    match(READ);
    match(IDENTIFIER);
    return readStmtTree;
}



/* Update the index of the token */
void Parser::match(TokenType tokenType)
{
    if(tokenType == tokens[index]->type)
    {
        if(index < tokens.size() - 1)
        {
            index++;
        }
    }
    else
    {
        errors.insert(index);
    }
}