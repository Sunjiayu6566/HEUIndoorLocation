#include "cameralinkage.h"
#include "ui_cameralinkage.h"

CameraLinkage::CameraLinkage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraLinkage)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);

    QVBoxLayout *ver1=new QVBoxLayout;
    setLayout(ver1);
    ver1->setSpacing(0);
    ver1->setContentsMargins(10,10,10,10);
    ver1->setAlignment(Qt::AlignCenter);

    QWidget *widget1 =new QWidget;
    QHBoxLayout *hl1=new QHBoxLayout();
    hl1->setSpacing(10);
    widget1->setLayout(hl1);
    xuanze =new QPushButton();
    xuanze->setText(QStringLiteral("选择"));
    shanchu=new QPushButton();
    shanchu->setText(QStringLiteral("删除"));
    tianjia=new QPushButton();
    tianjia->setText(QStringLiteral("添加"));
    hl1->setAlignment(Qt::AlignLeft);
    hl1->addWidget(xuanze);
    hl1->addWidget(shanchu);
    hl1->addWidget(tianjia);
    widget1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QWidget *widget3=new QWidget;
    QWidget *widget4 =new QWidget;
    QListView *listview1 =new QListView;


    QWidget *widget2 =new QWidget;
    QHBoxLayout *hl2=new QHBoxLayout();
    hl2->setSpacing(10);
    widget2->setLayout(hl2);

    firstpage =new QPushButton();
    firstpage->setText(QStringLiteral("第一页"));
    nextpage=new QPushButton();
    nextpage->setText(QStringLiteral("下一页"));
    prepage=new QPushButton();
    prepage->setText(QStringLiteral("前一页"));
    lastpage=new QPushButton();
    lastpage->setText(QStringLiteral("最后一页"));
    hl2->setAlignment(Qt::AlignHCenter);
    hl2->addWidget(firstpage);
    hl2->addWidget(nextpage);
    hl2->addWidget(prepage);
    hl2->addWidget(lastpage);
    widget2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QHBoxLayout *h12 = new QHBoxLayout();
    h12->setSpacing(0);
    h12->addWidget(widget3,3);
    h12->addWidget(listview1,1);
    h12->addWidget(widget4,3);

    ver1->addWidget(widget1,1);
    ver1->addLayout(h12,8);
    ver1->addWidget(widget2,1);
}

CameraLinkage::~CameraLinkage()
{
    delete ui;
}
