#include "elecfencewidget.h"
#include "ui_elecfencewidget.h"
#include <QPointF>
#include <QPolygonF>
#include <QDebug>

ElecFenceWidget::ElecFenceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElecFenceWidget)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);

    QVBoxLayout *v1 =new QVBoxLayout();
    setLayout(v1);
    v1->setAlignment(Qt::AlignLeft);
    v1->setContentsMargins(10,10,10,10);
    v1->setSpacing(0);

    QHBoxLayout *h1 =new QHBoxLayout();
    h1->setAlignment(Qt::AlignLeft);
    h1->setSpacing(10);
    h1->setContentsMargins(0,0,0,10);

    jiazaiditu=new QToolButton();
    jiazaiditu->setText(QStringLiteral("加载地图"));
    connect(jiazaiditu,SIGNAL(clicked()) , this, SLOT(jiazai()));
    location =new QToolButton();
    location->setText(QStringLiteral("开始定位"));
    endlocation =new QToolButton();
    endlocation->setText(QStringLiteral("终止定位"));

    h1->addWidget(jiazaiditu);
    h1->addWidget(location);
    h1->addWidget(endlocation);

    QHBoxLayout *h2=new QHBoxLayout();
    h2->setSpacing(10);
    view1 =new LoMoView();
    scene1=new DrawScene();
    view1->setScene(scene1);
    scene1->drawGridBackground(50);
    scene1->setSceneRect(-view1->rect().width()/2,-view1->rect().height()/2,view1->rect().width(),view1->rect().height());
    view1->show();
    view1->setSizePolicy(QSizePolicy::Expanding , QSizePolicy :: Expanding);


    h2->addWidget(view1 ,6);

    QVBoxLayout *v2=new QVBoxLayout();
    v2->setAlignment(Qt::AlignTop);
    v2->setSpacing(20);


    QVBoxLayout *vn1=new QVBoxLayout();
    vn1->setAlignment(Qt::AlignLeft);
    vn1->setSpacing(10);
    scenelocate =new QLabel();
    scenelocate->setText(QStringLiteral("场景坐标"));
    QHBoxLayout *hn3=new QHBoxLayout();
    hn3->setSpacing(10);
    sceneX =new QLabel();
    sceneX->setText(QStringLiteral("场景X坐标"));
    sceneY =new QLabel();
    sceneY->setText(QStringLiteral("场景Y坐标"));
    connect(view1 , SIGNAL(xlabel(double)) , this, SLOT(setscenexlabelvalue(double)));
    connect(view1 , SIGNAL(ylabel(double)) , this, SLOT(setsceneylabelvalue(double)));

    hn3->addWidget(sceneX);
    hn3->addWidget(sceneY);
    vn1->addWidget(scenelocate);
    vn1->addLayout(hn3);

    QVBoxLayout *vn2=new QVBoxLayout();
    vn2->setAlignment(Qt::AlignLeft);
    vn2->setSpacing(10);
    Maplocate =new QLabel();
    Maplocate->setText(QStringLiteral("地图坐标"));
    QHBoxLayout *hn4=new QHBoxLayout();
    hn4->setSpacing(10);
    MapX =new QLabel();
    MapX->setText(QStringLiteral("地图X坐标"));
    MapY =new QLabel();
    MapY->setText(QStringLiteral("地图Y坐标"));
    connect(view1 , SIGNAL(mapxlabel(double)) , this, SLOT(setmapxlabelvalue(double)));
    connect(view1 , SIGNAL(mapylabel(double)) , this, SLOT(setmapylabelvalue(double)));
    hn4->addWidget(MapX);
    hn4->addWidget(MapY);
    vn2->addWidget(Maplocate);
    vn2->addLayout(hn4);

    QVBoxLayout *vn5= new QVBoxLayout();
    vn5->setAlignment(Qt::AlignLeft);
    vn5->setSpacing(10);
    bilichi1=new QLabel();
    bilichi1->setText(QStringLiteral("比例尺"));
    bilichiValue = new QLabel();
    bilichiValue->setText(QStringLiteral("1格=5米"));
    connect(view1 , SIGNAL(bilichi(double)) , this, SLOT(setbililabelvalue(double)));
    vn5->addWidget(bilichi1);
    vn5->addWidget(bilichiValue);

    QHBoxLayout *hn1= new QHBoxLayout();
    hn1->setSpacing(10);
    xianshiweilan=new QLabel();
    xianshiweilan->setText(QStringLiteral("显示围栏"));
    setfence = new QComboBox();
    connect(setfence, SIGNAL(currentIndexChanged(int)),this,SLOT(addfence(int)));
    //connect(setfence,SIGNAL())

    hn1->addWidget(xianshiweilan);
    hn1->addWidget(setfence);

    QHBoxLayout *hn2=new QHBoxLayout();
    hn2->setSpacing(10);
    yincangweilan=new QLabel();
    yincangweilan->setText(QStringLiteral("隐藏围栏"));
    removefence = new QComboBox();
    connect(removefence, SIGNAL(currentIndexChanged(int)),this,SLOT(deletefence(int)));
    hn2->addWidget(yincangweilan);
    hn2->addWidget(removefence);

    jiazaiwenjian = new QToolButton();
    jiazaiwenjian->setText(QStringLiteral("加载围栏文件"));

    connect(jiazaiwenjian , SIGNAL (clicked()), this, SLOT(ReadFile()));

    v2->addLayout(vn1);
    v2->addLayout(vn2);
    v2->addLayout(vn5);
    v2->addWidget(jiazaiwenjian);
    v2->addLayout(hn1);
    v2->addLayout(hn2);
    h2->addLayout(v2,1);
    v1->addLayout(h1,1);
    v1->addLayout(h2,10);
}

ElecFenceWidget::~ElecFenceWidget()
{
    delete ui;
}

void ElecFenceWidget::jiazai()
{
    if(!scene1->item_container.isEmpty())
    {
        scene1->clear();
    }
    scene1->open_file();
}


void ElecFenceWidget :: setscenexlabelvalue(double x)
{
    sceneX->setText(QString::number(x));
}
void ElecFenceWidget :: setsceneylabelvalue(double y)
{
    sceneY->setText(QString::number(y));
}
void ElecFenceWidget :: setmapxlabelvalue(double x)
{
    MapX->setText(QString::number(x));
}
void ElecFenceWidget :: setmapylabelvalue(double y)
{
    MapY->setText(QString::number(y));
}
void ElecFenceWidget :: setbililabelvalue(double bili)
{
    bilichiValue->setText(QStringLiteral("1格=")+QString::number(bili)+QStringLiteral("米"));
}


void ElecFenceWidget:: ReadFile()
{
    QString s = QFileDialog::getOpenFileName(0, "Select A File", "/", "Txt File(*.txt)");
    if (s.isEmpty())
    {
        QMessageBox::information(0, tr("INformation"), tr("Open failed!"));
        return;
    }
    currentPath = s;
    QFile file(currentPath);
    if (file.open(QFile::ReadOnly))
    {
        QTextStream cin(&file);
        int rowcount;
        cin>>rowcount;

        while(!cin.atEnd())
        {
         int id;
         cin>>id;
         int n;
         cin>>n;
         double array[n];

         //for (int i=0;i<)

    //     QVector<QPointF> pp;

         for(int i=0;i<n;i+=2)
         {
             cin>>array[i]>>array[i+1];
//             QPointF p;
//             p.setX(array[i]);
//             p.setY(array[i+1]);
//            // i+=2;
//             pp.append(p);
         }


         for(int i=0;i<n;++i)
         {
         qDebug()<<" Item Selected : " <<array[i];
         }

         int r1,g1,b1;
         cin>>r1>>g1>>b1;
         int alpha;
         cin>>alpha;

         qDebug()<<" Item Selected : " <<r1<<"  "<<g1<<"  "<<b1<<"  "<<alpha;
         QGraphicsPolygonItem *poly=new QGraphicsPolygonItem();
         QPolygonF polygon;
         for(int i=0;i<n;i+=2)
         {
             polygon<<(QPointF (array[i],array[i+1]));
            // polygon<<pp.at(i);
         }
         poly->setPolygon(polygon);
         poly->setBrush(QColor(r1,g1,b1,alpha));
         poly->setZValue(alpha);
         poly_vector.append(poly);

        // poly_vector.at(i);
      //   removefence->addItem((QString("Fence") + QString::number(i)));
        // return poly;
        // scene1->poly_container.append(poly);
        // scene1->poly_container.at(i);
        // i++;

         //poly->paint();
        }
        for(int i=1;i<=rowcount;i++)
        {
            //ComboboxItem * item = new ComboboxItem(this);
            setfence->addItem((QString("Fence") + QString::number(i)));
        }
        for(int i=1;i<=rowcount;i++)
        {
            //ComboboxItem * item = new ComboboxItem(this);
            removefence->addItem((QString("Fence") + QString::number(i)));
        }
    }

    file.close();
}

void ElecFenceWidget ::addfence(int i)
{
    scene1->addItem(poly_vector.at(i));
    scene1->poly_container.append(poly_vector.at(i));
  // scene1->poly_container.at(i)->show();

  // scene1->poly_container.at(i);
  //  removefence->addItem((QString("Fence") + QString::number(i)));
   // removefence->setCurrentIndex(i);
}

void ElecFenceWidget::deletefence(int i)
{
    scene1->poly_container.removeAt(i);
    scene1->removeItem(poly_vector.at(i));
    //removefence->removeItem(i);
}




