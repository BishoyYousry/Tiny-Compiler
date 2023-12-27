#include "SyntaxTreeWidget.hpp"
#include "qgraphicsview.h"
#include "NodeDrawing.hpp"

// Constructor for the SyntaxTreeWidget class
SyntaxTreeWidget::SyntaxTreeWidget(SyntaxTree *tree, QWidget *parent) : QGraphicsView(parent) {

    // Create a new graphics scene to hold the tree visualization
    scene = new QGraphicsScene(this);

    // Set up a black pen with a width of 6 for drawing lines
    QPen blackPen(Qt::black);
    blackPen.setWidth(6);

    // Call the drawTree function to create the visual representation of the tree
    drawTree(tree);

    // Set the scene to be displayed in the QGraphicsView
    this->setScene(scene);
}

// Function to calculate the total width of the tree
int SyntaxTreeWidget::getTreeWidth(SyntaxTree *tree) {
    // If the tree is empty, return 0
    if (tree == nullptr) return 0;

    // If the tree is a leaf node and doesn't have a sibling, return its basic width
    if (tree->isLeaf() && !tree->hasSibling()) return NODE_WIDTH + NODE_HORIZONTAL_SEPARATION + 20;

    // Recursively calculate the widths of all subtrees
    int width = 0;
    for (SyntaxTree *child : tree->getChildren()) {
        width += getTreeWidth(child);
    }

    // If the tree has a sibling, add its width as well
    if (tree->hasSibling()) width += getTreeWidth(tree->getSibling()) + 20;

    return width;
}

// Function to recursively draw the tree
void SyntaxTreeWidget::drawTree(SyntaxTree *tree, int x, int y) {
    // Create a NodeDrawing object to represent the current node
    NodeDrawing *node = new NodeDrawing(tree, x, y);
    scene->addItem(node);

    // Calculate the total width of all children
    int totalWidth = 0;
    std::vector<int> childrenWidths(tree->getChildren().size());
    for (unsigned long long i = 0; i < tree->getChildren().size(); i++) {
        int childWidth = getTreeWidth(tree->getChildren()[i]);
        totalWidth += childWidth;
        childrenWidths[i] = childWidth;
    }

    // Calculate the starting position for the children
    int currentLeftPos = x - totalWidth / 2;

    // Draw each child node and connecting lines
    for (unsigned long long i = 0; i < tree->getChildren().size(); i++) {
        int childX = currentLeftPos + childrenWidths[i] / 2;
        int childY = y + NODE_VERTICAL_SEPARATION + NODE_HEIGHT;

        // Draw a line connecting the parent and child nodes
        QGraphicsLineItem *line = new QGraphicsLineItem(x, y + NODE_HEIGHT / 2, childX, childY - NODE_HEIGHT / 2);
        scene->addItem(line);

        // Recursively draw the child tree
        drawTree(tree->getChildren()[i], childX, childY);

        // Update the position for the next child
        currentLeftPos += childrenWidths[i];
    }

    // If the tree has a sibling, draw it as well
    if (tree->hasSibling()) {
        // Calculate the width of the sibling tree
        int siblingWidth = 0;
        for (SyntaxTree *child : tree->getSibling()->getChildren()) {
            siblingWidth += getTreeWidth(child);
        }

        int siblingX;
        if(tree->getType() != READ_STATEMENT)
        {
            // Calculate the position of the sibling node
            siblingX = x - 30 + totalWidth / 2 + siblingWidth / 2;
        }
        else
        {
            // Calculate the position of the sibling node
            siblingX = 150 + x + totalWidth / 2 + siblingWidth / 2;
        }
        int siblingY = y;

        // Draw a line connecting the sibling nodes
        QGraphicsLineItem *line = new QGraphicsLineItem(x + NODE_WIDTH / 2, y, siblingX - NODE_WIDTH / 2, siblingY);
        scene->addItem(line);

        // Recursively draw the sibling tree
        drawTree(tree->getSibling(), siblingX, siblingY);
    }
}
