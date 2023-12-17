#pragma once
#include <string>
#include <vector>

typedef enum TokenType
{
    SEMICOLON,
    IF,
    THEN,
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
};

typedef struct Token
{
    std::string data;
    TokenType type;
}; 

class SyntaxTree
{
    public:
        std::vector<SyntaxTree*> childs;
};