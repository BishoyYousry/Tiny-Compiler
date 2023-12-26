#pragma once

#include <QWidget>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "parser.hpp"
#include "scanner.hpp"

extern std::vector<Token> Tokens;
extern std::string ScannerOutput;
extern Parser *P;
namespace Ui {
class FileEditor;
}

class FileEditor : public QWidget
{
    Q_OBJECT


public:
    explicit FileEditor(QWidget *parent = nullptr);
    ~FileEditor();
    std::string fileName;
    std::string code;

private slots:
    void on_Save_clicked();

    void on_OpenFile_clicked();

    void on_OpenFile_2_clicked();

    void on_OpenFile_3_clicked();

    void on_NewFile_clicked();

    void on_Compile_clicked();



private:
    Ui::FileEditor *ui;

    void SaveProcedure();
};

