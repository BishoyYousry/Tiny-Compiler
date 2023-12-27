#include "mainwindow.hpp"
#include "fileeditor.hpp"
#include "ui_mainwindow.h"
#include "description.hpp"
#include "qfiledialog.h"

QString fileNames;
std::string file;
std::string temp="";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Compiler Project");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_NewFolder_clicked()
{
    fileNames = QFileDialog::getSaveFileName(this, ("Open File"),"C://", ("Token files (*.token);;Tiny files (*.tiny)"));
    file=fileNames.toStdString();
    std::cout<<"mainwindow "<<file<<std::endl;
    FileEditor *F = new FileEditor;
    F->setAttribute(Qt::WA_DeleteOnClose);
    F->fileName=file;
    std::cout<<file<<std::endl;
    F->show();
    this->close();
}


void MainWindow::on_OpenFolder_clicked()
{
    fileNames = QFileDialog::getOpenFileName(this, ("Open File"),"C://", ("Token files (*.token);;Tiny files (*.tiny)"));
    file=fileNames.toStdString();

    std::ifstream MyReadFile(file);
    std::string carrier;

    temp="";
    while (getline (MyReadFile,carrier)) {      
      temp+=carrier+"\n";      
    }
    FileEditor *F = new FileEditor;
    F->setAttribute(Qt::WA_DeleteOnClose);
    F->fileName=file;
    F->code=temp;
    qInfo() << (QString::fromStdString(F->code));
    F->show();
    this->close();
}




void MainWindow::on_AboutBTN_clicked()
{
    AboutPage *A= new AboutPage;
    A->show();
}




