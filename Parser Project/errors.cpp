#include "errors.hpp"
#include "ui_errors.h"
#include "fileeditor.hpp"
#include "scanner.hpp"
Errors::Errors(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Errors)
{

    ui->setupUi(this);
    std::string errorsStr;
    if(P->err.empty())
    {
     errorsStr="No errors";
     std:: cout<<"No errors";
    }
    else
    {
     errorsStr="";

    for(int looper=0;looper<(P->err).size();looper++)
    {
        std::cout<<std::to_string(*next(P->err.begin(),looper));
         errorsStr+="Type:  "+Tokens[(*next(P->err.begin(),looper))].Type+"    Value:  "+Tokens[(*next(P->err.begin(),looper))].Value+"    index:  "+std::to_string((*next(P->err.begin(),looper)))+"\n";

    }
    }
    ui->ErrorsTXT->setText(QString::fromStdString(errorsStr));
}

Errors::~Errors()
{
    delete ui;
}
