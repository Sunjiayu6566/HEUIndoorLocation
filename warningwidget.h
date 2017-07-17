#ifndef WARNINGWIDGET_H
#define WARNINGWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class warningWidget : public QWidget
{
    Q_OBJECT
public:
    explicit warningWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QPushButton *reply;
    QLabel *content;

};

#endif // WARNINGWIDGET_H
