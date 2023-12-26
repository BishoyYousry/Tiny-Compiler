#pragma once

#include <QDialog>
#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGui>
#include "SyntaxTree.hpp"

#define NODE_VERTICAL_SEPARATION 50
#define NODE_HORIZONTAL_SEPARATION 10

class SyntaxTreeWidget : public QGraphicsView
{
    Q_OBJECT

public:
    SyntaxTreeWidget(SyntaxTree *tree, QWidget *parent = nullptr);

private:
    QGraphicsScene *scene;

    int getTreeWidth(SyntaxTree *tree);

    void drawTree(SyntaxTree *tree, int x = 0, int y = 0);
};

