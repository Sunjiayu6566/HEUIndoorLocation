#include "bqwidget.h"
#include "ui_bqwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QItemSelectionModel>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>



BqWidget::BqWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BqWidget)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);

    QVBoxLayout *ver1=new QVBoxLayout;
    ver1->setAlignment(Qt::AlignCenter);
    ver1->setContentsMargins(10,10,10,10);
    ver1->setSpacing(0);
    setLayout(ver1);

    camera_linkage=new CameraLinkage;
    camera_manage=new CameraManage;

    camera_linkage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    camera_manage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_stackedwidget=new QStackedWidget;
    m_stackedwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_stackedwidget->addWidget(camera_linkage);
    m_stackedwidget->addWidget(camera_manage);

    m_status = 0;
    m_navBtn = new DHPushButton;
    m_navBtn->loadPixmap(":/new/images/right1.png");

    m_naviView = new NaviView(this);
    m_naviView->setVisible(false);
    NavModel* model = new NavModel(this);
    model->ReadDataFromConfig("camera.xml");
    NavDelegate* delegate = new NavDelegate(this);
    m_naviView->setModel(model);
    m_naviView->setItemDelegate(delegate);

    connect(this->m_naviView, SIGNAL(clicked(const QModelIndex &)), model, SLOT(Collapse(const QModelIndex&)));
    connect(this->m_naviView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(switchPage()));
    connect(this->m_navBtn, SIGNAL(clicked()), this, SLOT(setNav()));

    QHBoxLayout *h11= new QHBoxLayout;
    h11->setSpacing(0);
    h11->setContentsMargins(0,0,0,0);

    QHBoxLayout *h12 =new QHBoxLayout;
    h12->setSpacing(0);
    h12->addWidget(m_naviView);
    h12->addWidget(m_navBtn);

    QHBoxLayout *h13 = new QHBoxLayout;
    h13->setSpacing(0);
    h13->addWidget(m_stackedwidget);

    h11->addLayout(h12,1);
    h11->addLayout(h13,5);
    ver1->addLayout(h11);

}

BqWidget::~BqWidget()
{
    delete ui;
}

void BqWidget::switchPage(){
   int n = m_naviView->currentIndex().row();
   m_stackedwidget->setCurrentIndex(n);
}

void BqWidget::setNav(){
    if(m_status==0){
    this->m_naviView->setVisible(true);
    m_naviView->resize(this->width()/6,this->height());
    m_navBtn->loadPixmap(":/new/images/left1.png");
    m_status = 1;
 }
    else{
        m_naviView->setVisible(false);
        m_navBtn->loadPixmap(":/new/images/right1.png");
       // m_navBtn->setFixedSize(30,60);
        m_status = 0;
    }
}







