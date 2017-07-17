#include "labelinformation.h"
#include "ui_labelinformation.h"

labelinformation::labelinformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::labelinformation)
{
    ui->setupUi(this);
}

labelinformation::~labelinformation()
{
    delete ui;
}
