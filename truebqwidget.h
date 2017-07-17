#ifndef TRUEBQWIDGET_H
#define TRUEBQWIDGET_H

#include <QWidget>

namespace Ui {
class TrueBqWidget;
}

class TrueBqWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrueBqWidget(QWidget *parent = 0);
    ~TrueBqWidget();

private:
    Ui::TrueBqWidget *ui;
};

#endif // TRUEBQWIDGET_H
