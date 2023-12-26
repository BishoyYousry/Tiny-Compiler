#include "description.hpp"
#include "ui_description.h"

AboutPage::AboutPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutPage)
{
    ui->setupUi(this);
    this->setWindowTitle("Description");
}

AboutPage::~AboutPage()
{
    delete ui;
}
