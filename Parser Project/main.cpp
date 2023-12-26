#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/Resources/Resources/logos/compiler.png"));
    MainWindow w;
    qInfo() << "C++ Style Info Message";
    w.show();
    return a.exec();
}
