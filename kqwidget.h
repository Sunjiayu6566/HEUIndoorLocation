#ifndef KQWIDGET_H
#define KQWIDGET_H

#include <QWidget>

namespace Ui {
class KqWidget;
}

class KqWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KqWidget(QWidget *parent = 0);
    ~KqWidget();

private:
    Ui::KqWidget *ui;
};

#endif // KQWIDGET_H
