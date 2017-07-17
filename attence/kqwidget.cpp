#include "kqwidget.h"
#include "ui_kqwidget.h"

KqWidget::KqWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KqWidget)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);
}

KqWidget::~KqWidget()
{
    delete ui;
}
