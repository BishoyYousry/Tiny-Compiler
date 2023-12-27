#include "parser.hpp"
#include <QString>

extern QString extension;

Parser::Parser()
{
    error=false;
}



/* Rule: program → stmt-sequence */
SyntaxTree* Parser::program (std::vector<Token> Tokens){

    SyntaxTree* programTree = stmt_sequence(Tokens);
    if (index < Tokens.size()-1) {
        std:: cout<<"error"<<std::endl;
        error = true;
        err.insert(index);
    }
    return programTree;
}


/*
    Rule: stmt-sequence → stmt-sequence ; statement | statement
    EBNF: stmt-sequence → statement {; statement}
*/
SyntaxTree* Parser::stmt_sequence (std::vector<Token> Tokens){
    SyntaxTree *stmtSequenceTree = new SyntaxTree();

    stmtSequenceTree = statement(Tokens);

    SyntaxTree *current = new SyntaxTree();

    current = stmtSequenceTree;

    Token x;
    if(index < Tokens.size()){

        x = Tokens[index];
    }

    while (x.Type == "SEMICOLON" && index < Tokens.size()){

        match("SEMICOLON", &Tokens);

        current->setSibling(statement(Tokens));

        current = current->getSibling();

        if(index<Tokens.size()){
            x = Tokens[index];

        }
        else
            break;

    }
    return stmtSequenceTree;
}



/* Rule: statement → if-stmt | repeat-stmt | assign-stmt | read-stmt | write-stmt */
SyntaxTree* Parser::statement (std::vector<Token> Tokens){
    SyntaxTree* statementTree = NULL;
    Token current_token;
    if(index < Tokens.size())
        current_token = Tokens[index];
    if( current_token.Type == "IF" ){
        statementTree = if_stmt(Tokens);
    } else if(current_token.Type == "IDENTIFIER"){
        statementTree = assign_stmt(Tokens);
    } else if (current_token.Type == "READ")
        statementTree = read_stmt(Tokens);
    else if (current_token.Type == "WRITE")
        statementTree = write_stmt(Tokens);
    else if (current_token.Type == "REPEAT")
        statementTree = repeat_stmt(Tokens);
    else{
        error = true;
        err.insert(index);
    }
    return statementTree;
}



/*
    Rule: if-stmt → if exp then stmt-sequence end | if exp then stmt-sequence else stmt-sequence end
    EBNF: if-stmt → if exp then stmt-sequence [else stmt-sequence] end
*/
SyntaxTree* Parser::if_stmt (std::vector<Token> Tokens){
    SyntaxTree *ifStmtTree = new SyntaxTree();
    ifStmtTree->setType(IF_STATEMENT);
    match("IF",&Tokens);
    ifStmtTree->addChild(exp(Tokens));
    match("THEN",&Tokens);
    ifStmtTree->addChild(stmt_sequence(Tokens));
    Token x;
    if(index<Tokens.size()){
        x = Tokens[index];
    }
    if(x.Type == "ELSE"){
        match("ELSE",&Tokens);
        ifStmtTree->addChild(stmt_sequence(Tokens));
    }
    match("END",&Tokens);
    return ifStmtTree;
}


/* Rule: repeat-stmt → repeat stmt-sequence until exp */
SyntaxTree* Parser::repeat_stmt (std::vector<Token> Tokens){
    SyntaxTree* repeatStmtTree = new SyntaxTree();
    match("REPEAT", &Tokens);
    repeatStmtTree->setType(REPEAT_STATEMENT);
    repeatStmtTree->addChild(stmt_sequence(Tokens));
    match("UNTIL", &Tokens);
    repeatStmtTree->addChild(exp(Tokens));
    return repeatStmtTree;
}



/* Rule: assign-stmt → identifier := exp */
SyntaxTree* Parser::assign_stmt (std::vector<Token> Tokens){
    SyntaxTree* assignStmtTree = new SyntaxTree();
    assignStmtTree->setType(ASSIGN_STATEMENT);
    assignStmtTree->setValue(QString::fromStdString(Tokens[index].Value));
    match("IDENTIFIER", &Tokens);
    match("ASSIGN", &Tokens);
    assignStmtTree->addChild(exp(Tokens));
    return assignStmtTree;
}



/* Rule: read-stmt → read identifier */
SyntaxTree* Parser::read_stmt (std::vector<Token> Tokens){
    match("READ", &Tokens);
    SyntaxTree *readStmtTree = new SyntaxTree();
    readStmtTree->setType(READ_STATEMENT);
    readStmtTree->setValue(QString::fromStdString(Tokens[index].Value));
    match("IDENTIFIER", &Tokens);
    return readStmtTree;
}



/* Rule: write-stmt → write exp */
SyntaxTree* Parser::write_stmt (std::vector<Token> Tokens){
    SyntaxTree *writeStmtTree= new SyntaxTree();
    writeStmtTree->setType(WRITE_STATEMENT);
    match("WRITE", &Tokens);
    writeStmtTree->addChild(exp(Tokens));
    return writeStmtTree;
}



/* Rule: exp → simple-exp comparison-op simple-exp | simple-exp
   EBNF: exp → simple-exp [comparison-op simple-exp]
*/
SyntaxTree* Parser::exp (std::vector<Token> Tokens){
    SyntaxTree* cur, *c1 = simple_exp(Tokens), *c2;
    Token x;
    if (index < Tokens.size())
        x = Tokens[index];
    if (x.Type == "LESSTHAN" || x.Type == "EQUAL") {
        cur = comparison_op(Tokens);
        cur->addChild(c1);
        c2 = simple_exp(Tokens);
        cur->addChild(c2);
        c1 = cur;
    }
    return c1;
}




/* Rule: comparison-op → < | = */
SyntaxTree* Parser::comparison_op (std::vector<Token> Tokens){
    Token x;
    if (index < Tokens.size())
        x = Tokens[index];
    SyntaxTree *comparisonOpStmtTree = nullptr;
    if(x.Type == "LESSTHAN"){
        comparisonOpStmtTree = new SyntaxTree();
        comparisonOpStmtTree->setType(OPERATOR_EXPRESSION);
        comparisonOpStmtTree->setValue(QString::fromStdString(Tokens[index].Value));
        match("LESSTHAN", &Tokens);
    }
    else if(x.Type == "EQUAL"){
        comparisonOpStmtTree = new SyntaxTree();
        comparisonOpStmtTree->setType(OPERATOR_EXPRESSION);
        comparisonOpStmtTree->setValue(QString::fromStdString(Tokens[index].Value));
        match("EQUAL", &Tokens);
    }
    else{
        error = true;
        err.insert(index);
    }
    return comparisonOpStmtTree;
}



/* Rule: simple-exp → simple-exp addop term | term
   EBNF: term {addop term}
*/
SyntaxTree* Parser::simple_exp(std::vector<Token> Tokens){
    SyntaxTree *current, *c1 = term(Tokens), *c2;
    Token x;
    if(index<Tokens.size()){
        x=Tokens[index];
    }
    while (x.Type=="PLUS" || x.Type == "MINUS")
    {
        current = addop(Tokens);
        current->addChild(c1);
        c2 = term(Tokens);
        current->addChild(c2);
        c1 = current;
        if(index<Tokens.size()){
            x=Tokens[index];
        }
        else{
            break;
        }
    }
    return c1;
}



/* Rule: addop → + | - */
SyntaxTree* Parser::addop(std::vector<Token> Tokens){
    Token x;
    if(index<Tokens.size()){
        x = Tokens[index];
    }
    SyntaxTree *addOpTree = NULL;
    if(x.Type == "PLUS"){
        addOpTree = new SyntaxTree();
        addOpTree->setType(OPERATOR_EXPRESSION);
        addOpTree->setValue(QString::fromStdString(Tokens[index].Value));
        match("PLUS", &Tokens);
    }
    else if(x.Type == "MINUS"){
        addOpTree = new SyntaxTree();
        addOpTree->setType(OPERATOR_EXPRESSION);
        addOpTree->setValue(QString::fromStdString(Tokens[index].Value));
        match("MINUS", &Tokens);
    }
    else{
        error = true;
        err.insert(index);
    }
    return addOpTree;
}



/* Rule: term → term mulop factor | factor
   EBNF: factor {mulop factor}
*/
SyntaxTree* Parser::term(std::vector<Token> Tokens)
{
    SyntaxTree *current, *c1 = factor(Tokens), *c2;
    Token x;
    if(index<Tokens.size()){
        x=Tokens[index];
    }
    while (x.Type=="MULT" || x.Type == "DIV")
    {
        current = mulop(Tokens);
        current->addChild(c1);
        c2 = factor(Tokens);
        current->addChild(c2);
        c1 = current;
        if(index<Tokens.size()){
            x=Tokens[index];
        }
        else{
            break;
        }
    }
    return c1;
}


/* Rule: mulop → * | / */
SyntaxTree* Parser::mulop(std::vector<Token> Tokens){
    Token x;
    if(index<Tokens.size()){
        x = Tokens[index];
    }
    SyntaxTree *mulOpTree = NULL;
    if(x.Type == "MULT"){
        mulOpTree = new SyntaxTree();
        mulOpTree->setType(OPERATOR_EXPRESSION);
        mulOpTree->setValue(QString::fromStdString(Tokens[index].Value));
        match("MULT", &Tokens);
    }
    else if(x.Type == "DIV"){
        mulOpTree = new SyntaxTree();
        mulOpTree->setType(OPERATOR_EXPRESSION);
        mulOpTree->setValue(QString::fromStdString(Tokens[index].Value));
        match("DIV", &Tokens);
    }
    else{
        error = true;
        err.insert(index);
    }
    return mulOpTree;
}



/* Rule: factor → (exp) | number | identifier */
SyntaxTree* Parser::factor(std::vector<Token> Tokens){
    Token x;
    if(index<Tokens.size()){
        x = Tokens[index];
    }
    SyntaxTree *factorTree = NULL;
    if(x.Type == "OPENBRACKET"){
        match("OPENBRACKET", &Tokens);
        factorTree=exp(Tokens);
        match("CLOSEDBRACKET", &Tokens);
    }
    else if (x.Type == "NUMBER"){
        factorTree = new SyntaxTree();
        factorTree->setType(CONSTANT_EXPRESSION);
        factorTree->setValue(QString::fromStdString(Tokens[index].Value));
        match("NUMBER", &Tokens);
    }
    else if (x.Type == "IDENTIFIER"){
        factorTree = new SyntaxTree();
        factorTree->setType(IDENTIFIER_EXPRESSION);
        factorTree->setValue(QString::fromStdString(Tokens[index].Value));
        match("IDENTIFIER", &Tokens);
    }
    else{
        error = true;
        err.insert(index);
    }
    return factorTree;
}


/* Update the index of the token */
void Parser::match(QString input, std::vector<Token>* Tokens)
{

    if(input.toStdString() == Tokens->at(index).Type)
    {
        if(index < Tokens->size() - 1)
            index++;
        else    /* Semicolon at the end of the code */
            Tokens->at(index).Type = "ERROR";    /* Change the token type to avoid the inf loop in stmt-seq function */
    }
    else{
        error = true;
        err.insert(index);
    }
}


void Parser::parseString(QString code)
{
    index = 0;
    error=false;
    err.clear();
    if(extension == "tiny")
        syntaxTree = Parser::program(getTokenList(code.toStdString()));
    else if(extension == "token")
        syntaxTree = Parser::program(extractTokens(code.toStdString()));
}

SyntaxTree *Parser::getOutputTree()
{
    return syntaxTree;
}



bool Parser::getError() const
{
    std::cout<<error<<std::endl;
    return error;
}
