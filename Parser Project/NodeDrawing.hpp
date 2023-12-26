#pragma once

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include "SyntaxTree.hpp"

#define NODE_WIDTH 100
#define NODE_HEIGHT 50

class NodeDrawing : public QGraphicsItem
{
    int x = 0;
    int y = 0;
public:
    NodeDrawing();
    NodeDrawing(SyntaxTree *treeNode, int x, int y);

     //outer bounding for the object
    QRectF boundingRect() const;
    //Important to paint the object
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //value to tell us if object is pressed or not
    bool hovered;
    SyntaxTree *treeNode;
protected:
    void mouseHoverEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

