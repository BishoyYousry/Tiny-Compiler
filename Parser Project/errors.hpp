#pragma once

#include <QWidget>

namespace Ui {
class Errors;
}

class Errors : public QWidget
{
    Q_OBJECT

public:
    explicit Errors(QWidget *parent = nullptr);
    ~Errors();

private:
    Ui::Errors *ui;
};
