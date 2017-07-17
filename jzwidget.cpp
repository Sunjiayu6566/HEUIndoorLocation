#include "jzwidget.h"
#include "ui_jzwidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDebug>

JzWidget::JzWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JzWidget)
{

    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);
    setupModel();
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QGridLayout *grid = new QGridLayout(this);
    baseTable = new QTableView;
    baseTable->setModel(baseModel);
    baseTable->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:skyblue;"
                                                           "color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");
    baseTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    baseTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    addBase = new QPushButton(QString::fromLocal8Bit("增加"));
    deleteBase = new QPushButton(QString::fromLocal8Bit("删除"));
    freshBase = new QPushButton(QString::fromLocal8Bit("刷新"));
    nextPage = new QPushButton(QString::fromLocal8Bit("下一页"));
    prePage = new QPushButton(QString::fromLocal8Bit("上一页"));
    hLayout1->addWidget(addBase);
    hLayout1->addWidget(deleteBase);
    hLayout1->addWidget(freshBase);
    hLayout1->setSpacing(5);
    hLayout2->addWidget(prePage);
    hLayout2->addWidget(nextPage);
    grid->addLayout(hLayout1,0,0);
    grid->addWidget(baseTable,1,0);
    grid->addLayout(hLayout2,2,1);
    setLayout(grid);

    connect(this->addBase,SIGNAL(clicked()),this,SLOT(addBaseItem()));
    connect(this->deleteBase,SIGNAL(clicked()),this,SLOT(deleteBaseItem()));
    connect(this->freshBase,SIGNAL(clicked()),this,SLOT(freshBaseItem()));

}

JzWidget::~JzWidget()
{
    delete ui;
}


void JzWidget::setupModel(){

    baseModel = new BaseModel(8, 7);
    BaseInfo baseInfo1;
    baseInfo1.SetbaseID("20140611");
    baseInfo1.SetbaseRemark("hehe");
    baseInfo1.SetbaseType("UWB");
    baseInfo1.SetbaseX("11.3");
    baseInfo1.SetbaseY("18.4");
    baseInfo1.SetbaseZ("12.1");
    //加入三条学生信息
    baseModel->AddBaseInfo(baseInfo1);
    BaseInfo baseInfo2;
    baseInfo2.SetbaseID("20140612");
    baseInfo2.SetbaseRemark("heihei");
    baseInfo2.SetbaseType("UWB");
    baseInfo2.SetbaseX("11.3");
    baseInfo2.SetbaseY("18.4");
    baseInfo2.SetbaseZ("12.1");


    baseModel->AddBaseInfo(baseInfo2);

    BaseInfo baseInfo3;
    baseInfo3.SetbaseID("20140613");
    baseInfo3.SetbaseRemark("lala");
    baseInfo3.SetbaseType("UWB");
    baseInfo3.SetbaseX("11.3");
    baseInfo3.SetbaseY("18.4");
    baseInfo3.SetbaseZ("12.1");
    baseModel->AddBaseInfo(baseInfo3);

}



 void JzWidget::addBaseItem(){
     BaseInfo baseInfo;
     baseInfo.SetbaseID("20140614");
     baseInfo.SetbaseRemark("hehe");
     baseInfo.SetbaseType("UWB");
     baseInfo.SetbaseX("11.3");
     baseInfo.SetbaseY("18.4");
     baseInfo.SetbaseZ("12.1");
     baseModel->AddBaseInfo(baseInfo);
     qDebug()<<baseModel->rowCount();


 }
 void JzWidget::deleteBaseItem(){
     int nCount = baseTable->model()->rowCount();//model 里总行数
     QModelIndex index;
     QVariant  ok;
     int j = 0;
     for (int i = 0; i < nCount; ++i)
     {
         //判断是否勾选上
         index= baseTable->model()->index(i-j,0, QModelIndex());
              //i-j 非常重要 因为在下面的代码中会删除行 而造成model里的总行数变小造成相对位置的变化, 0 表示复选框在的列数 根据需要自己改变;
              //通过data函数 取得该 位置的值 通过tobool 判断是否勾选
         ok=baseTable->model()->data(index,Qt::UserRole);

         if (ok.toBool())
         {
             //如果勾选则 删除改行
             baseTable->model()->removeRow(i-j);
             ++j;
         }
 }
}

 void JzWidget::freshBaseItem(){
   baseModel->freshModel();
 }







