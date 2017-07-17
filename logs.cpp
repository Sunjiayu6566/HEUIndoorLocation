#include "logs.h"
#include "ui_logs.h"

Logs::Logs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Logs)
{
    ui->setupUi(this);
    QWidget *widget = new QWidget();
    setCentralWidget(widget);
    QVBoxLayout *v1 =new QVBoxLayout();
    widget->setLayout(v1);

    v1->setAlignment(Qt::AlignLeft);
    v1->setContentsMargins(10,0,10,10);
    QVBoxLayout *v2 =new QVBoxLayout();
    v2->setAlignment(Qt::AlignLeft);
    v2->setSpacing(0);

    productname =new QLabel();
    productname->setText(QStringLiteral("产品名称：室内定位系统"));
    productname->setStyleSheet("font-size: 13px;");

    version =new QLabel();
    version->setText(QStringLiteral(" 版本号：v1.0.01"));
    version->setStyleSheet("font-size: 13px;");

    heu=new QLabel();
    heu->setText(QStringLiteral("哈尔滨工程大学网络技术与信息安全实验室"));
    heu->setStyleSheet("font-size: 13px;");

    v2->addWidget(productname);
    v2->addWidget(version);
    v2->addWidget(heu);

    QHBoxLayout *h1 = new QHBoxLayout();
    h1->setContentsMargins(0,0,0,0);
    table1 =new QTableView();
    table1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy :: Expanding);
    h1->addWidget(table1);

    v1->addLayout(v2,1);
    v1->addLayout(h1,8);



}

Logs::~Logs()
{
    delete ui;
}
