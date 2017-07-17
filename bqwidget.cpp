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

   // createAction();
   // createMenu();
    setupModel();
    //setupView();

  //  QSizePolicy ui->verticalLayout
    // main_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setLayout(ui->verticalLayout);


    ui->verticalLayout->setAlignment(Qt::AlignCenter);//布局内控件居中
   // ui->tabWidget->setPalette(QPalette::Window);
    //ui->verticalLayout->setAlignment(Qt::AlignVCenter);
    ui->tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   // ui->tabWidget->setFixedSize(900,600);
    //现在知道的是tabwidget主窗体可以自适应大小，但里面的布局没有变化
    ui->tab->setLayout(ui->verticalLayout_2);
    ui->verticalLayout_2->setAlignment(Qt::AlignCenter);
    ui->widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   // ui->widget->setFixedSize(900,600);
    ui->widget->setLayout(ui->verticalLayout_4);
    ui->verticalLayout_4->setAlignment(Qt::AlignHCenter);
    ui->widget_2->setMaximumSize(1200,650);
    ui->widget_2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  //  ui->verticalLayout_4->addLayout(ui->horizontalLayout_2);
  //  ui->horizontalLayout_2->setAlignment(Qt::AlignHCenter);
   // ui->widget_3->setMaximumSize(950,40);
 //   ui->widget_3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    ui->listView->setBaseSize(300,400);
//    ui->listView->setMaximumSize(400,600);
//    ui->listView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);



    ui->widget_2->setLayout(ui->gridLayout);
    ui->gridLayout->setAlignment(Qt::AlignCenter);

    ui->listView->setMinimumSize(100,300);
    ui->listView->setMaximumSize(200,500);
    ui->listView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    ui->widget_3->setMaximumSize(450,500);
    ui->widget_3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->widget_3->setStyleSheet("background-color: rgb(85, 255, 0);");

    ui->widget_4->setMaximumSize(450,500);
    ui->widget_4->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->widget_4->setStyleSheet("background-color: rgb(85, 255, 0);");


    ui->widget_6->setMaximumSize(1100,40);
    QHBoxLayout *hl1=new QHBoxLayout();
    ui->widget_6->setLayout(hl1);
    xuanze =new QPushButton();
    xuanze->setText(QString::fromLocal8Bit("选择"));
    shanchu=new QPushButton();
    shanchu->setText(QString::fromLocal8Bit("删除"));
   // button_list.at(2)->setText(QString::fromLocal8Bit("摄像头联动"));
    tianjia=new QPushButton();
    tianjia->setText(QString::fromLocal8Bit("添加"));
    hl1->setAlignment(Qt::AlignLeft);
    hl1->addWidget(xuanze);
    hl1->addWidget(shanchu);
    hl1->addWidget(tianjia);
    ui->widget_6->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    ui->gridLayout->addWidget(ui->widget_6,0,0,1,3);
    ui->gridLayout->addWidget(ui->widget_3,1,0,1,1);
    ui->gridLayout->addWidget(ui->listView,1,1,1,1);
    ui->gridLayout->addWidget(ui->widget_4,1,2,1,1);
    ui->gridLayout->addWidget(ui->widget_5,2,0,1,3);


    ui->widget_5->setMaximumSize(1100,40);
    QHBoxLayout *hl2=new QHBoxLayout();
    ui->widget_5->setLayout(hl2);
    firstpage =new QPushButton();
    firstpage->setText(QString::fromLocal8Bit("第一页"));
    nextpage=new QPushButton();
    nextpage->setText(QString::fromLocal8Bit("下一页"));
    prepage=new QPushButton();
    prepage->setText(QString::fromLocal8Bit("前一页"));
    lastpage=new QPushButton();
    lastpage->setText(QString::fromLocal8Bit("最后一页"));
    hl2->setAlignment(Qt::AlignHCenter);
    hl2->addWidget(firstpage);
    hl2->addWidget(nextpage);
    hl2->addWidget(prepage);
    hl2->addWidget(lastpage);
    ui->widget_5->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);



//    ui->tab->setLayout(ui->horizontalLayout_2);//将tab页的布局设定为水平布局2之后widget可以自适应大小
//    ui->horizontalLayout_2->setAlignment(Qt::AlignCenter);
//    ui->horizontalLayout_2->addLayout(ui->horizontalLayout_6);
//    ui->horizontalLayout_6->setAlignment(Qt::AlignHCenter);
//   // ui->verticalLayout_5->addWidget(ui->listView);
//    ui->listView->setMinimumSize(200,400);
//    ui->listView->setMaximumSize(300,600);
//    ui->listView->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

//    ui->widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    ui->widget_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    ui->horizontalLayout_5->setAlignment(Qt::AlignLeft);
//    ui->horizontalLayout_4->setAlignment(Qt::AlignHCenter);

//    ui->horizontalLayout->setAlignment(Qt::AlignHCenter);
//    ui->horizontalLayout_3->setAlignment(Qt::AlignLeft);
//    ui->verticalLayout_3->setAlignment(Qt::AlignHCenter);
//   // ui->tableView->setGeometry(0,0,800,450);
//    //ui->tableView->setFixedSize(800,450);


   // ui->tabWidget->setFixedSize(900,500);
    //setAlignment(ui->verticalLayout,Qt::AlignCenter);

    ui->tab_2->setLayout(ui->verticalLayout_3);
    ui->verticalLayout_3->setAlignment(Qt::AlignCenter);
    ui->widget_7->setMaximumSize(1200,650);
    ui->widget_7->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->widget_7->setLayout(ui->verticalLayout_5);

    ui->widget_8->setMaximumSize(1100,40);
    QHBoxLayout *hl3=new QHBoxLayout();
    ui->widget_8->setLayout(hl3);
    biaogegengxin =new QPushButton();
    biaogegengxin->setText(QString::fromLocal8Bit("更新"));
    biaogecharu=new QPushButton();
    biaogecharu->setText(QString::fromLocal8Bit("插入"));
    biaogeshanchu=new QPushButton();
    biaogeshanchu->setText(QString::fromLocal8Bit("删除"));
    hl3->setAlignment(Qt::AlignLeft);
    hl3->addWidget(biaogegengxin);
    hl3->addWidget(biaogecharu);
    hl3->addWidget(biaogeshanchu);
    ui->widget_8->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);





    ui->tableView->setMaximumSize(1100,500);
    ui->tableView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->tableView->setModel(model);
    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableView->setSelectionModel(selectionModel);
    connect(selectionModel,SIGNAL(selectionChanged(QItemSelection,QItemSelection)),ui->tableView,SLOT(selectionChanged(QItemSelection,QItemSelection)));

    //ui->widget_7->addAction(openAct);
 //   connect(openAct,SIGNAL(triggered()),this,SLOT(slotOpen()));


    ui->widget_9->setMaximumSize(1100,40);
    QHBoxLayout *hl4=new QHBoxLayout();
    ui->widget_9->setLayout(hl4);
    biaogeFP =new QPushButton();
    biaogeFP->setText(QString::fromLocal8Bit("第一页"));
    biaogeNP=new QPushButton();
    biaogeNP->setText(QString::fromLocal8Bit("下一页"));
    biaogePP=new QPushButton();
    biaogePP->setText(QString::fromLocal8Bit("前一页"));
    biaogeLP=new QPushButton();
    biaogeLP->setText(QString::fromLocal8Bit("最后一页"));
    hl4->setAlignment(Qt::AlignHCenter);
    hl4->addWidget(biaogeFP);
    hl4->addWidget(biaogeNP);
    hl4->addWidget(biaogePP);
    hl4->addWidget(biaogeLP);
    ui->widget_9->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->verticalLayout_5->addWidget(ui->widget_8,0);
    ui->verticalLayout_5->addWidget(ui->tableView,1);
    ui->verticalLayout_5->addWidget(ui->widget_9,2);

}

BqWidget::~BqWidget()
{
    delete ui;
}


/***********************************************************************************
 * **********************************************************************************
 *以下为表格控制方法**********************************************************************
 * *******************************************************************************/
//void BqWidget::createAction()
//{
//    openAct = new QAction(tr("打开"),this);

//}

//void BqWidget::createMenu()
//{
//    fileMenu = new QMenu(tr("文件"),this);
//    fileMenu->addAction(openAct);
//    menuBar()->addMenu(fileMenu);
//}


void BqWidget::setupModel()
{
    model = new QStandardItemModel(this);
    model->setColumnCount(8);
   // model->setRowCount(4);
    model->setHeaderData(0,Qt::Horizontal,tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("LOCATION.X"));
    model->setHeaderData(2,Qt::Horizontal,tr("LOCATION.Y"));
    model->setHeaderData(3,Qt::Horizontal,tr("LOCATION.Z"));
    model->setHeaderData(4,Qt::Horizontal,tr("MAC"));
    model->setHeaderData(5,Qt::Horizontal,tr("NUMBER"));
    model->setHeaderData(6,Qt::Horizontal,tr("ANGLE.MIN"));
    model->setHeaderData(7,Qt::Horizontal,tr("ANGLE.MAX"));

    QFile file("test.txt");
    if (file.open(QFile::ReadWrite|QFile::Text))
    {
        QTextStream stream(&file);
        QString line;

        model->removeRows(0,model->rowCount(QModelIndex()),QModelIndex());
        int row = 0;
        do
        {
            line = stream.readLine();
            if (!line.isEmpty())
            {
                model->insertRows(row, 1, QModelIndex());
                QStringList pieces=line.split(",",QString::SkipEmptyParts);
                model->setData(model->index(row, 0, QModelIndex()),pieces.value(0));
                model->setData(model->index(row, 1, QModelIndex()),pieces.value(1));
                model->setData(model->index(row, 2, QModelIndex()),pieces.value(2));
                model->setData(model->index(row, 3, QModelIndex()),pieces.value(3));
                model->setData(model->index(row, 4, QModelIndex()),pieces.value(4));
                model->setData(model->index(row, 5, QModelIndex()),pieces.value(5));
                model->setData(model->index(row, 6, QModelIndex()),pieces.value(6));
                model->setData(model->index(row, 7, QModelIndex()),pieces.value(7));
                row++;
            }
        }while (!line.isEmpty());
        file.close();
    }

}





