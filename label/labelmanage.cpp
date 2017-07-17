#include "labelmanage.h"
#include "ui_labelmanage.h"

labelmanage::labelmanage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::labelmanage)
{
    ui->setupUi(this);
}

labelmanage::~labelmanage()
{
    delete ui;
}
