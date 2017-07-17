#include "jzwidget.h"
#include "ui_jzwidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include "basestationform.h"

JzWidget::JzWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JzWidget)
{

    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);
    this->baseStationdao = new BaseStationDao();
    setupModel();
    setLayout(ui->verticalLayout);

    ui->verticalLayout->setContentsMargins(0,0,0,0);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);//布局内控件居中

    QWidget *widget1 =new QWidget();
    QWidget *widget2 =new QWidget();
  //  QWidget *widget3 =new QWidget();


    widget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  //  widget3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_status = 0;
    m_navBtn = new DHPushButton;
    m_navBtn->loadPixmap(":/new/images/right1.png");

    m_naviView = new NaviView(this);
    m_naviView->setVisible(false);
    NavModel* model = new NavModel(this);
    model->ReadDataFromConfig("basestation.xml");
    NavDelegate* delegate = new NavDelegate(this);
    m_naviView->setModel(model);
    m_naviView->setItemDelegate(delegate);


    stack =new QStackedWidget;
    stack->addWidget(widget1);
    stack->addWidget(widget2);
   // stack->addWidget(widget3);
    stack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *ver1=new QVBoxLayout;
    ver1->setAlignment(Qt::AlignCenter);
    ver1->setContentsMargins(10,10,10,10);
    widget1->setLayout(ver1);


    QWidget *widget_2 =new QWidget;
    QHBoxLayout *hl1=new QHBoxLayout();
    widget_2->setLayout(hl1);
    freshBase=new QPushButton();
    freshBase->setText(QStringLiteral("刷新"));
    addBase=new QPushButton();
    addBase->setText(QStringLiteral("添加"));
    deleteBase=new QPushButton();
    deleteBase->setText(QStringLiteral("删除"));
    hl1->setAlignment(Qt::AlignLeft);
    hl1->addWidget(addBase);
    hl1->addWidget(deleteBase);
    hl1->addWidget(freshBase);
    widget_2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    QTableView *tableview1=new QTableView;
    tableview1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    tableview1->setModel(baseModel);
    tableview1->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:skyblue;"
                                                           "color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");
    tableview1->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    tableview1->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableview1->setColumnWidth(0,100);
    tableview1->setColumnWidth(1,100);
    tableview1->setColumnWidth(2,100);
    tableview1->setColumnWidth(3,100);
    tableview1->setColumnWidth(4,100);
    tableview1->setColumnWidth(5,100);
    tableview1->setColumnWidth(6,100);
    tableview1->setColumnWidth(7,100);
    tableview1->setColumnWidth(8,394);
   //  /////////////////////////////
   // ui->widget_3->setMaximumSize(1100,40);
    QWidget *widget_3 =new QWidget;
    QHBoxLayout *hl2=new QHBoxLayout();
    widget_3->setLayout(hl2);
    firstPage =new QPushButton();
    //firstPage->setText(QStringLiteral("第一页"));
    firstPage->setToolTip(QStringLiteral("第一页"));
    firstPage->setObjectName("firstPage");
    nextPage=new QPushButton();
    //nextPage->setText(QStringLiteral("下一页"));
    nextPage->setToolTip(QStringLiteral("下一页"));
    nextPage->setObjectName("nextPage");
    prePage=new QPushButton();
    //prePage->setText(QStringLiteral("上一页"));
    prePage->setToolTip(QStringLiteral("上一页"));
    prePage->setObjectName("prePage");
    lastPage=new QPushButton();
    //lastPage->setText(QStringLiteral("最后一页"));
    lastPage->setToolTip(QStringLiteral("最后一页"));
    lastPage->setObjectName("lastPage");
    hl2->setAlignment(Qt::AlignHCenter);
    hl2->addWidget(firstPage);
    hl2->addWidget(prePage);
    hl2->addWidget(nextPage);
    hl2->addWidget(lastPage);
    widget_3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    connect(this->addBase,SIGNAL(clicked()),this,SLOT(addBaseWin()));
    connect(this->deleteBase,SIGNAL(clicked()),this,SLOT(deleteBaseItem()));
    connect(this->freshBase,SIGNAL(clicked()),this,SLOT(freshBaseItem()));

    connect(this->m_naviView, SIGNAL(clicked(const QModelIndex &)), model, SLOT(Collapse(const QModelIndex&)));
    connect(this->m_naviView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(switchPage()));
    connect(this->m_navBtn, SIGNAL(clicked()), this, SLOT(setNav()));


    ver1->addWidget(widget_2,1);
    ver1->addWidget(tableview1,8);
    ver1->addWidget(widget_3,1);


    QHBoxLayout *h11= new QHBoxLayout;
    h11->setSpacing(0);
    h11->setContentsMargins(0,0,0,0);

    QHBoxLayout *h12 =new QHBoxLayout;
    h12->setSpacing(0);
    h12->addWidget(m_naviView);
    h12->addWidget(m_navBtn);

    QHBoxLayout *h13 = new QHBoxLayout;
    h13->setSpacing(0);
    h13->addWidget(stack);

    h11->addLayout(h12,1);
    h11->addLayout(h13,5);

    ui->verticalLayout->addLayout(h11);

}

JzWidget::~JzWidget()
{
    delete ui;
}

void JzWidget::switchPage(){
   int n = m_naviView->currentIndex().row();
   stack->setCurrentIndex(n);
}

void JzWidget::setNav(){
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


void JzWidget::setupModel(){

    BaseInfo query;
    QVector<BaseInfo> infos =  this->baseStationdao->getPageList(query);
    baseModel = new BaseModel(9, 8);
    baseModel->appendBaseInfos(infos);
}

void JzWidget::addBaseWin(){
    addWin = new BaseStationForm();
    addWin ->show();
    connect(addWin,SIGNAL(newBaseItem(BaseInfo&)),this,SLOT(addBaseItem(BaseInfo&)));
}


void JzWidget::addBaseItem(BaseInfo &info){

    this->baseStationdao->insert(info);
    //baseModel->AddBaseInfo(info);
    freshBaseItem();
}

 void JzWidget::deleteBaseItem(){
     int count = baseModel->rowCount();
     int j = 0;
     for (int i = 0; i < count; ++i)
     {
         if (baseModel->rowCheckStateMap[i]==Qt::Checked)
         {
             BaseInfo info = baseModel->getBaseInfo().at(i-j);
             this->baseStationdao->deleteById(info.GetbaseID().toInt());
             baseModel->removeRow(i-j);
             j++;
         }
     }
     freshBaseItem();
}


 void JzWidget::freshBaseItem(){
     for(int i = 0;i < baseModel->rowCount();i++){
              QModelIndex index = baseModel->index(i,8,QModelIndex());
              baseModel->setData(index,Qt::Unchecked,Qt::CheckStateRole);
     }
     BaseInfo query;
     QVector<BaseInfo> infos =  this->baseStationdao->getPageList(query);
     baseModel->appendBaseInfos(infos);
     baseModel->freshModel();
 }






