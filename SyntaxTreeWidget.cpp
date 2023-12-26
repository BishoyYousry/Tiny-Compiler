#include "SyntaxTreeWidget.hpp"
#include "qgraphicsview.h"
#include "NodeDrawing.hpp"

SyntaxTreeWidget::SyntaxTreeWidget(SyntaxTree *tree, QWidget *parent): QGraphicsView(parent)
{

    scene = new QGraphicsScene(this);

    QPen blackPen (Qt::black);
    blackPen.setWidth(6);

    drawTree(tree);

//    NodeDrawing *node1 = new NodeDrawing(tree, 10, 15);
//    SyntaxTree *tree2 = new SyntaxTree();
//    NodeDrawing *node2 = new NodeDrawing(tree2, 50, 100);
//    QGraphicsLineItem *line = new QGraphicsLineItem(10+50, 15+50, 50+50, 100);
//    scene->addItem(node1);
//    scene->addItem(node2);
//    scene->addItem(line);

    this->setScene(scene);
}

int SyntaxTreeWidget::getTreeWidth(SyntaxTree *tree)
{
    if (tree == nullptr) return 0;
    if (tree->isLeaf() && !tree->hasSibling()) return NODE_WIDTH + NODE_HORIZONTAL_SEPARATION+20;

    int width = 0;
    for (SyntaxTree *child: tree->getChildren())
    {
        width += getTreeWidth(child);
    }
    if (tree->hasSibling()) width += getTreeWidth(tree->getSibling())+20;

    return width;
}

void SyntaxTreeWidget::drawTree(SyntaxTree *tree, int x, int y)
{
    NodeDrawing *node = new NodeDrawing(tree, x, y);
    scene->addItem(node);

    int totalWidth = 0;
    std::vector<int> childrenWidths(tree->getChildren().size());
    for (unsigned long long i = 0; i < tree->getChildren().size(); i++)
    {
        int childWidth = getTreeWidth(tree->getChildren()[i]);
        totalWidth += childWidth;
        childrenWidths[i] = childWidth;
    }
    int currentLeftPos = x - totalWidth/2;

    for (unsigned long long i = 0; i < tree->getChildren().size(); i++)
    {
        int childX = currentLeftPos + childrenWidths[i]/2;
        int childY = y + NODE_VERTICAL_SEPARATION + NODE_HEIGHT;

        QGraphicsLineItem *line = new QGraphicsLineItem(x, y + NODE_HEIGHT/2, childX, childY - NODE_HEIGHT/2);
        scene->addItem(line);

        drawTree(tree->getChildren()[i], childX, childY);

        currentLeftPos += childrenWidths[i];

    }

    if(tree->hasSibling())
    {
        int siblingWidth = 0;
        for (SyntaxTree *child: tree->getSibling()->getChildren())
        {
            siblingWidth += getTreeWidth(child);
        }

        int siblingX = x -30+ totalWidth/2 + siblingWidth/2;
        int siblingY = y;

        QGraphicsLineItem *line = new QGraphicsLineItem(x + NODE_WIDTH/2, y, siblingX - NODE_WIDTH/2, siblingY);
        scene->addItem(line);

        drawTree(tree->getSibling(), siblingX, siblingY);
    }
}



