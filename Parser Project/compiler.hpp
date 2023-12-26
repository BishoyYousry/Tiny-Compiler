#pragma once

#include <QWidget>
#include <string>
#include "mainwindow.hpp"
extern bool GrammerIsTrue;
namespace Ui {
class Compiler;
}

class Compiler : public QWidget
{
    Q_OBJECT

public:
    explicit Compiler(QWidget *parent = nullptr);
    ~Compiler();

private slots:
    void on_pushButton_2_clicked();

    void on_ReturnToEditBTN_clicked();

    void on_MainMenuBTN_clicked();

    void on_ParseTreeBTN_clicked();

    void on_DisplayErrorsBTN_clicked();

private:
    Ui::Compiler *ui;
};

