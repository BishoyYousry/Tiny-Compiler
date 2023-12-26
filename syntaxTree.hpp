#pragma once

#include <vector>
#include <QString>

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

class SyntaxTree
{
    std::vector<SyntaxTree *> children;
    SyntaxTree *sibling = nullptr;
    NodeType type = NO_EXPRESSION;
    QString value = "";
public:
    SyntaxTree();

    const std::vector<SyntaxTree *> &getChildren() const;

    void addChild(SyntaxTree *child);

    bool isLeaf();

    SyntaxTree *getSibling() const;

    void setSibling(SyntaxTree *newSibling);

    bool hasSibling();

    NodeType getType() const;

    void setType(NodeType newType);

    const QString &getValue() const;

    void setValue(const QString &newValue);

    ~SyntaxTree();
};

