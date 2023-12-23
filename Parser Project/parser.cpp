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
    while(index < tokens.size() && SEMICOLON == tokens[index]->type)
    {
        match(SEMICOLON);
        stmtSequenceTree = statement();
    }
    return stmtSequenceTree;
}

/* Rule: statement → if-stmt | repeat-stmt | assign-stmt | read-stmt | write-stmt */
SyntaxTree* Parser::statement()
{
    SyntaxTree* statementTree = nullptr;
    /* check the possible first tokens of each type of statement rule */
    
    switch (tokens[index]->type)
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
    repeatStmtTree->add_node_data(REPEAT_STATEMENT, "REPEAT");
    match(REPEAT);
    repeatStmtTree->add_child(stmt_sequence());     /* Body child */
    match(UNTIL);
    repeatStmtTree->add_child(exp());               /* Test child */
    return repeatStmtTree;
}


/* Rule: assign-stmt → identifier := exp */
SyntaxTree* Parser::assign_stmt()
{
    SyntaxTree* assignStmtTree = new SyntaxTree();
    assignStmtTree->add_node_data(ASSIGN_STATEMENT, tokens[index]->value);
    match(IDENTIFIER);
    match(ASSIGN);
    assignStmtTree->add_child(exp());              /* Exp child */
    return assignStmtTree;
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

/* Rule: write-stmt → write exp */
SyntaxTree* Parser::write_stmt()
{
    SyntaxTree* writeStmtTree = new SyntaxTree();
    match(WRITE);
    writeStmtTree->add_node_data(WRITE_STATEMENT, "WRITE");
    writeStmtTree->add_child(exp());
    return writeStmtTree;
}

/* Rule: exp → simple-exp comparison-op simple-exp | simple-exp
   EBNF: exp → simple-exp [comparison-op simple-exp]
*/
SyntaxTree* Parser::exp()
{
    SyntaxTree* expStmtTree = simple_exp();
    if (LESSTHAN == tokens[index]->type || EQUAL == tokens[index]->type)
    {
        SyntaxTree* comparisonOpStmtTree = comparison_op();
        comparisonOpStmtTree->add_child(expStmtTree);
        comparisonOpStmtTree->add_child(simple_exp());
        expStmtTree = comparisonOpStmtTree;
    }
    return expStmtTree;
}

/* Rule: comparison-op → < | = */
SyntaxTree* Parser::comparison_op()
{
    SyntaxTree* comparisonOpStmtTree = new SyntaxTree();
    if (LESSTHAN == tokens[index]->type)
    {
        match(LESSTHAN);
        comparisonOpStmtTree->add_node_data(OPERATOR_EXPRESSION, "<");
    }
    else if (EQUAL == tokens[index]->type)
    {
        match(EQUAL);
        comparisonOpStmtTree->add_node_data(OPERATOR_EXPRESSION, "=");
    }
    else
    {
        errors.insert(index);
    }
    return comparisonOpStmtTree;
}

/* Rule: simple-exp → simple-exp addop term | term
   EBNF: term {addop term}
*/
SyntaxTree* Parser::simple_exp()
{
    SyntaxTree* simpleExpTree = term();
    while (PLUS == tokens[index]->type || MINUS == tokens[index]->type)
    {
        SyntaxTree* addOpTree =  addop();
        addOpTree->add_child(simpleExpTree);
        addOpTree->add_child(term());
        simpleExpTree = addOpTree;
    }
    return simpleExpTree;
}

/* Rule: addop → + | - */
SyntaxTree* Parser::addop()
{
    SyntaxTree* addOpTree = new SyntaxTree();
    if (PLUS == tokens[index]->type)
    {
        match(PLUS);
        addOpTree->add_node_data(OPERATOR_EXPRESSION, "+");
    }
    else if (MINUS == tokens[index]->type)
    {
        match(MINUS);
        addOpTree->add_node_data(OPERATOR_EXPRESSION, "-");
    }
    else
    {
        errors.insert(index);
    }
    return addOpTree;
}

/* Rule: term → term mulop factor | factor
   EBNF: factor {mulop factor}
*/
SyntaxTree* Parser::term()
{
    SyntaxTree* termTree = factor();
    while (MULT == tokens[index]->type || DIV == tokens[index]->type)
    {
        SyntaxTree* mulOpTree = mulop();
        mulOpTree->add_child(termTree);
        mulOpTree->add_child(factor());
        termTree = mulOpTree;
    }
    return termTree;
}

/* Rule: mulop → * | / */
SyntaxTree* Parser::mulop()
{
    SyntaxTree* mulOpTree = new SyntaxTree();
    if (MULT == tokens[index]->type)
    {
        match(MULT);
        mulOpTree->add_node_data(OPERATOR_EXPRESSION, "*");
    }
    else if (DIV == tokens[index]->type)
    {
        match(DIV);
        mulOpTree->add_node_data(OPERATOR_EXPRESSION, "/");
    }
    else
    {
        errors.insert(index);
    }
    return mulOpTree;
}

/* Rule: factor → (exp) | number | identifier */
SyntaxTree* Parser::factor()
{
    SyntaxTree* factorTree = nullptr;
    if (OPENBRACKET == tokens[index]->type)
    {
        match(OPENBRACKET);
        factorTree = exp();
        match(CLOSEDBRACKET);
    }
    else if (NUMBER == tokens[index]->type)
    {
        match(NUMBER);
        factorTree = new SyntaxTree();
        factorTree->add_node_data(CONSTANT_EXPRESSION, tokens[index]->value);
    }
    else if (IDENTIFIER == tokens[index]->type)
    {
        match(IDENTIFIER);
        factorTree = new SyntaxTree();
        factorTree->add_node_data(IDENTIFIER_EXPRESSION, tokens[index]->value);
    }
    else
    {
        errors.insert(index);
    }
    return factorTree;
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
        else
        {
            tokens[index]->type = EMPTY;
        }
    }
    else
    {
        errors.insert(index);
    }
}