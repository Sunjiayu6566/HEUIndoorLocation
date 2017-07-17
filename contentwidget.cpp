#include "contentwidget.h"
#include "ui_contentwidget.h"

contentwidget::contentwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::contentwidget)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);
}

contentwidget::~contentwidget()
{
    delete ui;
}
