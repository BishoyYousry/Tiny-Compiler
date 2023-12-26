#include "SyntaxTree.hpp"

SyntaxTree::SyntaxTree()
{

}

const std::vector<SyntaxTree *> &SyntaxTree::getChildren() const
{
    return children;
}

void SyntaxTree::addChild(SyntaxTree *child)
{
    children.push_back(child);
}

bool SyntaxTree::isLeaf()
{
    return children.empty();
}

SyntaxTree *SyntaxTree::getSibling() const
{
    return sibling;
}

void SyntaxTree::setSibling(SyntaxTree *newSibling)
{
    sibling = newSibling;
}

bool SyntaxTree::hasSibling()
{
    return (sibling != nullptr);
}

NodeType SyntaxTree::getType() const
{
    return type;
}

void SyntaxTree::setType(NodeType newType)
{
    type = newType;
}

const QString &SyntaxTree::getValue() const
{
    return value;
}

void SyntaxTree::setValue(const QString &newValue)
{
    value = newValue;
}

SyntaxTree::~SyntaxTree()
{
    for (SyntaxTree *child: children)
    {
        delete child;
        child = nullptr;
    }
    delete sibling;
}
