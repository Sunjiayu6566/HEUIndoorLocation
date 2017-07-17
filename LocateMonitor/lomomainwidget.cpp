#include "lomomainwidget.h"
#include "ui_lomomainwidget.h"

LoMoMainWidget::LoMoMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoMoMainWidget)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);
 //   QWidget *widget = new QWidget(this);

    QVBoxLayout *ver_1 =new QVBoxLayout();

    //QWidget *widget = new QWidget(this);

    setLayout(ver_1);
    //setLayout(ver_1);
   // setCentralWidget(widget);
    //this->setLayout(ver_1);   //ui->verticalLayout是窗口的主布局
  //  QHBoxLayout *her_0 =new QHBoxLayout();
  //  ver_1->addLayout(her_0);//用于放置indexwidget
    ver_1->setSpacing(0);
    ver_1->setContentsMargins(0,0,0,0);
  //  indexwidget=new IndexWidget();
   // her_0->addWidget(indexwidget);
  //  indexwidget->setFixedHeight(60);
   // indexwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *ver_2= new QVBoxLayout();

    ver_1->addLayout(ver_2);//ui->verticalLayout_2作为窗口变换的布局

    lomowidget =new LoMoWidget();
    //lomowidget->setFixedSize(900,400);
    ver_2->addWidget(lomowidget);
    ver_2->setAlignment(Qt::AlignCenter);
    lomowidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}

LoMoMainWidget::~LoMoMainWidget()
{
    delete ui;
}
