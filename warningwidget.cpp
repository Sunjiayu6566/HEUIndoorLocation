#include "warningwidget.h"
#include <QGridLayout>
warningWidget::warningWidget(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(500);
    setFixedHeight(500);
    QGridLayout * grid= new QGridLayout(this);
    QLabel *label = new QLabel();
    label->setText(QStringLiteral("通知："));
    reply = new QPushButton("reply");
    grid->addWidget(label,0,0);
    grid->addWidget(reply,1,1);

}
