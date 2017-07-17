#include "centralwidget.h"
#include "navmodel.h"
#include "navdelegate.h"
#include "naviview.h"
#include "message.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include "push_button.h"
#include <QPalette>
centralWidget::centralWidget(QWidget *parent) : QWidget(parent)
{

    this->resize(900,600);

    m_status = 0;
    //指向右边的按钮
    m_navBtn = new DHPushButton;
    m_navBtn->loadPixmap(":/images/right1.png");
    //m_navBtn->setFlat(true);
    //m_navBtn->setAutoFillBackground(true);
    //QPalette palette = m_navBtn->palette();
    //palette.setColor(QPalette::Button,Qt::red);
    //m_navBtn->setPalette(palette);


    m_naviView = new NaviView(this);
    m_naviView->setVisible(false);
    NavModel* model = new NavModel(this);
    model->ReadDataFromConfig("config.xml");
    NavDelegate* delegate = new NavDelegate(this);
    m_naviView->setModel(model);
    m_naviView->setItemDelegate(delegate);

    m_stackWidget = new QStackedWidget(this);
    QPushButton *btn1 = new QPushButton(QString::fromLocal8Bit("点我"));
    QPushButton *btn2 = new QPushButton(QString::fromLocal8Bit("点我啊"));
    m_stackWidget->addWidget(btn1);
    m_stackWidget->addWidget(btn2);
    QHBoxLayout *Hlayout = new QHBoxLayout(this);
    Hlayout->setSpacing(0);
    QHBoxLayout *h11 =new QHBoxLayout();
    h11->setSpacing(1);
    h11->addWidget(m_naviView);
    h11->addWidget(m_navBtn);
//    Hlayout->addWidget(m_naviView);
//    Hlayout->addWidget(m_right);
    Hlayout->addLayout(h11,1);
    Hlayout->addWidget(m_stackWidget,5);
    //Hlayout->addWidget(m_stackWidget);
  //  Hlayout->setStretchFactor(m_naviView,1);
   // Hlayout->setStretchFactor(m_stackWidget,3);
    this->setLayout(Hlayout);

    connect(this->m_naviView, SIGNAL(clicked(const QModelIndex &)), model, SLOT(Collapse(const QModelIndex&)));
    connect(this->m_naviView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(switchPage()));
    connect(this->m_navBtn, SIGNAL(clicked()), this, SLOT(setNav()));
}
void centralWidget::switchPage(){
   int n = m_naviView->currentIndex().row();
   m_stackWidget->setCurrentIndex(n);
}

void centralWidget::setNav(){
    if(m_status==0){
    this->m_naviView->setVisible(true);
    m_naviView->resize(this->width()/6,this->height());
    m_navBtn->loadPixmap(":/images/left1.png");
    m_status = 1;
 }
    else{
        m_naviView->setVisible(false);
        m_navBtn->loadPixmap(":/images/right1.png");
       // m_navBtn->setFlat(true);
        //m_navBtn->setAutoFillBackground(true);
       // QPalette palette = m_navBtn->palette();
        //palette.setColor(QPalette::Button,Qt::red);
        //m_navBtn->setPalette(palette);
        m_status = 0;
    }
}


