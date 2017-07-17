#include "mapsmanage.h"
#include "ui_mapsmanage.h"

MapsManage::MapsManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapsManage)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);

    setupModel();

    QVBoxLayout *ver1=new QVBoxLayout;
    setLayout(ver1);
    ver1->setContentsMargins(10,10,10,10);
    ver1->setSpacing(10);
    ver1->setAlignment(Qt::AlignLeft);

    QWidget *widget1=new QWidget;

    QHBoxLayout *hl3=new QHBoxLayout();
    widget1->setLayout(hl3);



    checkmap=new QPushButton();
    checkmap->setText(QStringLiteral("查看地图"));
    createmap=new QPushButton();
    createmap->setText(QStringLiteral("创建地图"));
    deletemap=new QPushButton();
    deletemap->setText(QStringLiteral("删除地图"));
    connect(createmap,SIGNAL(clicked()),this,SLOT(drawmap_show()));


    hl3->setAlignment(Qt::AlignLeft);
    hl3->addWidget(createmap);
    hl3->addWidget(checkmap);
    hl3->addWidget(deletemap);
    widget1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QTableView *tableview1=new QTableView;
    tableview1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    tableview1->setModel(model);
    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    tableview1->setSelectionModel(selectionModel);
    connect(selectionModel,SIGNAL(selectionChanged(QItemSelection,QItemSelection)),tableview1,SLOT(selectionChanged(QItemSelection,QItemSelection)));

    QWidget *widget2=new QWidget;
    QHBoxLayout *hl4=new QHBoxLayout();
    widget2->setLayout(hl4);
    biaogeFP =new QPushButton();
    biaogeFP->setText(QStringLiteral("第一页"));
    biaogeNP=new QPushButton();
    biaogeNP->setText(QStringLiteral("下一页"));
    biaogePP=new QPushButton();
    biaogePP->setText(QStringLiteral("前一页"));
    biaogeLP=new QPushButton();
    biaogeLP->setText(QStringLiteral("最后一页"));

    hl4->setAlignment(Qt::AlignHCenter);
    hl4->addWidget(biaogeFP);
    hl4->addWidget(biaogeNP);
    hl4->addWidget(biaogePP);
    hl4->addWidget(biaogeLP);

    widget2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    ver1->addWidget(widget1,1);
    ver1->addWidget(tableview1,8);
    ver1->addWidget(widget2,1);

}

MapsManage::~MapsManage()
{
    delete ui;  
}
void MapsManage :: drawmap_show()
{
    MapDrawing *mapdrawing = new MapDrawing ;
    mapdrawing->show();

}

void MapsManage::setupModel()
{
    model = new QStandardItemModel(this);
    model->setColumnCount(8);
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

