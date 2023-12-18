#include "parser.hpp"
#include "syntaxTree.hpp"
#include <iostream>

/* Rule: program → stmt-sequence */
SyntaxTree* Parser::program()
{
    SyntaxTree* programTree = stmt_sequence();
    return programTree;
}

/*
    Rule: stmt-sequence → stmt-sequence ; statement | statement
    EBNF: stmt-sequence → statement {; statement}
*/
SyntaxTree* Parser::stmt_sequence()
{
    SyntaxTree* stmtSequenceTree = statement();
    while( SEMICOLON == tokens[index]->type )
    {
        match(SEMICOLON);
        stmtSequenceTree = statement();
    }
    return stmtSequenceTree;
}

/* Rule: statement → if-stmt | repeat-stmt | assign-stmt | read-stmt | write-stmt */
SyntaxTree* Parser::statement()
{
    SyntaxTree* statementTree;
    /* check the possible first tokens of each type of statement rule */
    switch(tokens[index]->type)
    {
        case IF:
            statementTree = if_stmt();
            break;

        case REPEAT:
            statementTree = repeat_stmt();
            break;

        case IDENTIFIER:
            statementTree = assign_stmt();
            break;

        case READ:
            statementTree = read_stmt();
            break;

        case WRITE:
            statementTree = write_stmt();
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
    ifStmtTree->add_node_data(IF_STATEMENT, "if");
    match(IF);
    ifStmtTree->add_child(exp());                   /* Test child */
    match(THEN);
    ifStmtTree->add_child(stmt_sequence());         /* Then child */
    if(ELSE == tokens[index]->type)
    {
        match(ELSE);
        ifStmtTree->add_child(stmt_sequence());     /* Else child if exists */
    }
    match(END);
    return ifStmtTree;
}

/* Rule: repeat-stmt → repeat stmt-sequence until exp */
SyntaxTree* Parser::repeat_stmt()
{
    SyntaxTree* repeatStmtTree = new SyntaxTree();
    repeatStmtTree->add_node_data(READ_STATEMENT, "REPEAT");
    match(REPEAT);
    repeatStmtTree->add_child(stmt_sequence());     /* Body child */
    match(UNTIL);
    repeatStmtTree->add_child(exp());               /* Test child */
    return repeatStmtTree;
}


/* Rule: assign-stmt → identifier := exp */
SyntaxTree* Parser::assign_stmt()
{
    SyntaxTree* expTree = new SyntaxTree();
    expTree->add_node_data(ASSIGN_STATEMENT, ":=");
    match(IDENTIFIER);
    match(ASSIGN);
    expTree->add_child(exp());              /* Exp child */
    return expTree;
}

/* Rule: read-stmt → read identifier */
SyntaxTree* Parser::read_stmt()
{
    SyntaxTree* readStmtTree = new SyntaxTree();
    match(READ);
    readStmtTree->add_node_data(READ_STATEMENT, tokens[index]->value);
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