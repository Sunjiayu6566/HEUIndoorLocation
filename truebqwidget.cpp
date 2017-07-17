#include "truebqwidget.h"
#include "ui_truebqwidget.h"

TrueBqWidget::TrueBqWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrueBqWidget)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);
}

TrueBqWidget::~TrueBqWidget()
{
    delete ui;
}
