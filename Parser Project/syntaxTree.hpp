#pragma once
#include <string>
#include <vector>
#include <string>

typedef enum{
    NO_EXPRESSION,
    OPERATOR_EXPRESSION,
    CONSTANT_EXPRESSION,
    IDENTIFIER_EXPRESSION,
    ASSIGN_STATEMENT,
    IF_STATEMENT,
    REPEAT_STATEMENT,
    READ_STATEMENT,
    WRITE_STATEMENT
}NodeType;


typedef enum
{
    SEMICOLON,
    IF,
    THEN,
    ELSE,
    END,
    REPEAT,
    UNTIL,
    IDENTIFIER,
    ASSIGN,
    READ,
    WRITE,
    LESSTHAN,
    EQUAL,
    PLUS,
    MINUS,
    MULT,
    DIV,
    OPENBRACKET,
    CLOSEDBRACKET,
    NUMBER,
    EMPTY               /* Just to indicate the end of tokens */
}TokenType;

typedef struct 
{
    NodeType type;
    std::string value;
}NodeData;


typedef struct
{
    TokenType type;
    std::string value;
}Token; 

class SyntaxTree
{
    private:
        std::vector<SyntaxTree*> childs;
        NodeData nodeData;
    public:
        void add_child(SyntaxTree* child);
        void add_node_data(NodeType type, std::string value);
};