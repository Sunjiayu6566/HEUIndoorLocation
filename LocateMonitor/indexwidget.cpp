#include "indexwidget.h"
#include "ui_indexwidget.h"

IndexWidget::IndexWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndexWidget)
{
    ui->setupUi(this);

    QHBoxLayout *h1 =new QHBoxLayout();
    h1->setAlignment(Qt::AlignLeft);
    setLayout(h1);

    button1 =new QToolButton();
    button1->setText(QStringLiteral("定位监控"));
    button1->setAutoRaise(true);
    button2 =new QToolButton();
    button2->setText(QStringLiteral("传感器状态"));
    button2->setAutoRaise(true);
    button3 =new QToolButton();
    button3->setText(QStringLiteral("标签状态"));
    button3->setAutoRaise(true);
    button4 =new QToolButton();
    button4->setText(QStringLiteral("过滤器及参数"));
    button4->setAutoRaise(true);
    button5 =new QToolButton();
    button5->setText(QStringLiteral("传感器校准"));
    button5->setAutoRaise(true);
    button6 =new QToolButton();
    button6->setText(QStringLiteral("日志"));
    button6->setAutoRaise(true);

    h1->addWidget(button1);
    h1->addWidget(button2);
    h1->addWidget(button3);
    h1->addWidget(button4);
    h1->addWidget(button5);
    h1->addWidget(button6);

    connect(button1 , SIGNAL(clicked()) , this , SIGNAL(LocateMonitor()));
    connect(button2 , SIGNAL(clicked()) , this , SIGNAL(SensorStatus()));
    connect(button3 , SIGNAL(clicked()) , this , SIGNAL(LabelStatus()));
    connect(button4 , SIGNAL(clicked()) , this , SIGNAL(FilterAndParameter()));
    connect(button5 , SIGNAL(clicked()) , this , SIGNAL(SensorCalibrate()));
    connect(button6 , SIGNAL(clicked()) , this , SIGNAL(Logs()));

}

IndexWidget::~IndexWidget()
{
    delete ui;
}
