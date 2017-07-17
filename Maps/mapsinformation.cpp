#include "mapsinformation.h"
#include "ui_mapsinformation.h"

Mapsinformation::Mapsinformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mapsinformation)
{
    ui->setupUi(this);
}

Mapsinformation::~Mapsinformation()
{
    delete ui;
}
