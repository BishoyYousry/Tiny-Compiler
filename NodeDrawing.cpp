#include "NodeDrawing.hpp"

NodeDrawing::NodeDrawing()
{
    hovered = false;
}
//outer most edge of our shape
NodeDrawing::NodeDrawing(SyntaxTree * treeNode, int x, int y)
{
    hovered = false;
    this->treeNode = treeNode;
    this->x = x - NODE_WIDTH/2;
    this->y = y - NODE_HEIGHT/2;
}

QRectF NodeDrawing::boundingRect() const
{
    return QRectF(x, y, NODE_WIDTH, NODE_HEIGHT);
}

void NodeDrawing::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QRectF rec = boundingRect();
    QBrush brush (Qt::white);
/*
    if(hovered)
    {
        brush.setColor(Qt::red);
    }
    else
    {
        brush.setColor(Qt::white);
    }
    */

    painter -> fillRect(rec,brush);
    painter -> setFont(QFont("Arial",12,-1,true));
    QString type="";
    /*
     * typedef enum{
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
     */
    switch(treeNode->getType())
    {
    case IF_STATEMENT:
        type="if";
        break;
    case READ_STATEMENT:
        type="read";
        break;
    case WRITE_STATEMENT:
        type="write";
        break;
    case ASSIGN_STATEMENT:
        type="assign";
        break;
    case OPERATOR_EXPRESSION:
        type="op";
        break;
    case CONSTANT_EXPRESSION:
        type="const";
        break;
    case IDENTIFIER_EXPRESSION:
        type="id";
        break;
    case REPEAT_STATEMENT:
        type="repeat";
        break;

    }

    painter -> drawText(x + 30, y + 25,type);
    if(!(treeNode->getValue().isEmpty()))
        painter -> drawText(x + 35, y + 40,"("+treeNode->getValue()+")");

    if(treeNode->getType() >= ASSIGN_STATEMENT)
    {
        painter -> drawRect(rec);
    }
    else if(treeNode->getType() <= IDENTIFIER_EXPRESSION)
    {
         painter->drawEllipse(rec);
    }
}

void NodeDrawing::mouseHoverEvent(QGraphicsSceneMouseEvent *event)
{
    hovered = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void NodeDrawing::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    hovered = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
