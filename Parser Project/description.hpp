#pragma once

#include <QWidget>

namespace Ui {
class AboutPage;
}

class AboutPage : public QWidget
{
    Q_OBJECT

public:
    explicit AboutPage(QWidget *parent = nullptr);
    ~AboutPage();

private:
    Ui::AboutPage *ui;
};

