#include "syntaxTree.hpp"
#include <vector>

void SyntaxTree::add_child(SyntaxTree* child)
{
    childs.push_back(child);
}

void SyntaxTree::add_node_data(NodeType type, std::string value)
{
    nodeData.type = type;
    nodeData.value = value;
}