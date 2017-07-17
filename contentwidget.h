#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>

namespace Ui {
class contentwidget;
}

class contentwidget : public QWidget
{
    Q_OBJECT

public:
    explicit contentwidget(QWidget *parent = 0);
    ~contentwidget();

private:
    Ui::contentwidget *ui;
};

#endif // CONTENTWIDGET_H
