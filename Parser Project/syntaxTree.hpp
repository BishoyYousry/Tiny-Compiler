#pragma once
#include <string>
#include <vector>


typedef enum RuleType
{
    PROGRAM,
    STMT_SEQUENCE,
    STATEMENT,
    IF_STMT,
    REPEAT_STMT,
    ASSIGN_STMT,
    READ_STMT,
    WRITE_STMT,
    EXP,
    SIMPLE_EXP,
    COMPARISON_OP,
    ADDOP,
    TERM,
    MULOP,
    FACTOR,
};


typedef enum TokenType
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