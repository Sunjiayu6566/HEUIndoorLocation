#include "lomowidget.h"
#include <QIcon>
#include <QPixmap>
#include <QGraphicsScene>
#include <QPointF>
#include "ui_lomowidget.h"

LoMoWidget::LoMoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoMoWidget)
{
    ui->setupUi(this);
    setSizePolicy(QSizePolicy::Expanding , QSizePolicy :: Expanding);
    /*
     *
     * 定位监控的工具栏布局
     *
     */
    //this->setMinimumSize(900,450);
    QVBoxLayout *v1= new QVBoxLayout();
    setLayout(v1);
    v1->setSpacing(0);
    v1->setContentsMargins(1,0,1,10);
    v1->setAlignment(Qt::AlignHCenter);

   // QHBoxLayout *h1 =new QHBoxLayout();
  //  v1->addLayout(h1);
  //  h1->setAlignment(Qt::AlignLeft);



//    h1->addWidget(locatelabel);
//    h1->addWidget(Xlabel);
//    h1->addWidget(Ylabel);

    QHBoxLayout *h2 =new QHBoxLayout();
    h2->setContentsMargins(0,10,10,10);//left , top , right , bottom
    v1->addLayout(h2);
    QVBoxLayout *v2 =new QVBoxLayout();
    v2->setSpacing(10);
    v2->setContentsMargins(10,0,20,0);
    h2->addLayout(v2,1);

    v2->setAlignment( Qt::AlignLeft);

    tablelabel =new QLabel();
    tablelabel->setText(QStringLiteral("参考点设置"));
    tablelabel->setStyleSheet("font-size: 13px;");
    table1 = new QTableView();
    //table1->setFixedSize(300,250);
    tabwidget = new QTabWidget();
    //tabwidget->setFixedSize(300,250);
/*
 *
 *tabwidget第一页的布局
 *
 */
    QWidget *tab1 =new QWidget();
    tabwidget->addTab(tab1,QStringLiteral("过滤设置"));
    QVBoxLayout *tab1_v1 =new QVBoxLayout();
    tab1->setLayout(tab1_v1);
    tab1_v1->setSpacing(0);
    tab1_v1->setContentsMargins(10,0,10,0);
    QGridLayout *tab1_g1 =new QGridLayout();
    tab1_g1->setAlignment(Qt::AlignLeft);
    radio1 = new QRadioButton();
    radio1->setText(QStringLiteral("无场景"));
    radio2 = new QRadioButton();
    radio2->setText(QStringLiteral("场景1"));
    radio3 = new QRadioButton();
    radio3->setText(QStringLiteral("场景2"));
    radio4 = new QRadioButton();
    radio4->setText(QStringLiteral("场景3"));

    tab1_g1->addWidget(radio1,0,0,1,1);
    tab1_g1->addWidget(radio2,0,1,1,1);
    tab1_g1->addWidget(radio3,1,0,1,1);
    tab1_g1->addWidget(radio4,1,1,1,1);

    tab1_v1->addLayout(tab1_g1);

    QHBoxLayout *tab1_h1 = new QHBoxLayout();
    tab1_h1->setAlignment(Qt::AlignLeft);

    supersets = new QCheckBox();
    supersets->setText(QStringLiteral("高级设置"));
    supersets->setCheckable(true);
    supersets->setChecked(false);
    connect(supersets,SIGNAL(clicked()),this,SLOT(supersetvisble()));
    //connect(supersets,SIGNAL());

    tab1_h1->addWidget(supersets);
    tab1_v1->addLayout(tab1_h1);

    QGridLayout *tab1_g2 = new QGridLayout();
    tab1_g2->setAlignment(Qt::AlignLeft);
    filterbeginnum = new QLabel();
    filterbeginnum->setVisible(false);
    filterbeginnum->setText(QStringLiteral("过滤器初始数："));
    filterbeginnum->setStyleSheet("font-size: 13px;");
    filternum = new QLineEdit();
    filternum->setFixedSize(50,20);
    filternum->setVisible(false);
    pointfrequency = new QLabel();
    pointfrequency->setVisible(false);
    pointfrequency->setText(QStringLiteral("切点频率（500~8000）："));
    pointfrequency->setStyleSheet("font-size: 13px;");
    pointFre = new QLineEdit();
    pointFre->setFixedSize(50,20);
    pointFre->setVisible(false);
    tab1_g2->addWidget(filterbeginnum,0,0,1,1);
    tab1_g2->addWidget(filternum,0,1,1,1);
    tab1_g2->addWidget(pointfrequency,1,0,1,1);
    tab1_g2->addWidget(pointFre,1,1,1,1);

    tab1_v1->addLayout(tab1_g2);


//--------------tabwidget の tab1设置结束   TAB1_END-----------------------------
    /*
     *
     *tabwidget's tab2 set
     *
     */
    QWidget *tab2 = new QWidget();
    tabwidget->addTab(tab2,QStringLiteral("数据保存"));

    QGridLayout *tab2_g1 = new QGridLayout();
    tab2->setLayout(tab2_g1);

    tab2_g1->setSpacing(20);
    tab2_g1->setContentsMargins(10,0,10,0);
    tab2_g1->setAlignment(Qt::AlignHCenter);

    savebegin = new QToolButton();
    savebegin->setText(QStringLiteral("开始保存"));
    saveend = new QToolButton();
    saveend->setText(QStringLiteral("保存结束"));
    openfileindex = new QToolButton();
    openfileindex->setText(QStringLiteral("打开文件所在目录"));

    tab2_g1->addWidget(savebegin,0,0,1,1);
    tab2_g1->addWidget(saveend,0,1,1,1);
    tab2_g1->addWidget(openfileindex,1,0,1,2);


//--------------tabwidget の tab2设置结束   TAB2_END-----------------------------
    /*
     *
     *tabwidget's tab3 set
     *
     */
    QWidget *tab3 = new QWidget();
    tabwidget->addTab(tab3,QStringLiteral("数据回放"));

    QVBoxLayout *tab3_v1 =new QVBoxLayout();
    tab3_v1->setSpacing(0);
    tab3_v1->setContentsMargins(10,10,10,0);
    tab3_v1->setAlignment(Qt::AlignLeft);
    tab3->setLayout(tab3_v1);

    QHBoxLayout *tab3_h1 =new QHBoxLayout();
    tab3_h1->setSpacing(5);
    tab3_h1->setAlignment(Qt::AlignLeft);
    scan= new QToolButton();
    scan->setText(QStringLiteral("浏览"));
    scanedit=new QLineEdit();
    scanedit->setFixedSize(150,20);
    tab3_h1->addWidget(scan);
    tab3_h1->addWidget(scanedit);

    tab3_v1->addLayout(tab3_h1);

    playerback=new QLabel();
    playerback->setText(QStringLiteral("回放控制"));
    playerback->setStyleSheet("font-size: 13px;");
    hslider = new QSlider(Qt::Horizontal);

    QHBoxLayout *tab3_h2 = new QHBoxLayout();
    tab3_h2->setSpacing(5);
    tab3_h2->setAlignment(Qt::AlignLeft);
    playbegin =new QToolButton();
    playbegin->setIcon(QIcon(":/new/images/playerbegin1.png"));
    playend = new QToolButton();
    playend->setIcon(QIcon(":/new/images/playerstop1.png"));
    roundplay = new QCheckBox();
    roundplay->setText(QStringLiteral("循环"));
    null= new QLabel();
    null->setText(QStringLiteral("无"));
    null->setStyleSheet("font-size: 13px;");
    tab3_h2->addWidget(playbegin);
    tab3_h2->addWidget(playend);
    tab3_h2->addWidget(roundplay);
    tab3_h2->addWidget(null);

    tab3_v1->addWidget(playerback);
    tab3_v1->addWidget(hslider);
    tab3_v1->addLayout(tab3_h2);



//--------------tabwidget の tab3设置结束   TAB3_END-----------------------------

    pushbutton1 = new QPushButton();
    pushbutton1->setText(QStringLiteral("加载配置"));
   // pushbutton1->setStyleSheet("font-size: 13px;");


    v2->addWidget(tablelabel,1,Qt::AlignHCenter);
    v2->addWidget(table1,8,Qt::AlignLeft);
    v2->addWidget(tabwidget,5);
    v2->addWidget(pushbutton1,1,Qt::AlignHCenter);

    scene1 = new DrawScene();
    view =new LoMoView();

    view->setScene(scene1);
    scene1->drawGridBackground(50);
    scene1->setSceneRect(-view->rect().width()/2,-view->rect().height()/2,view->rect().width(),view->rect().height());
    h2->addWidget(view,5);
    view->show();
    view->setSizePolicy(QSizePolicy::Expanding , QSizePolicy :: Expanding);

    QVBoxLayout *vn =new QVBoxLayout();
    vn->setAlignment(Qt::AlignLeft);
    vn->setSpacing(20);
    vn->setContentsMargins(10,20,10,20);

    toolbutton1=new QToolButton();
    toolbutton2=new QToolButton();
    toolbutton3=new QToolButton();
    toolbutton4=new QToolButton();

    toolbutton1->setText(QStringLiteral("启动定位"));
    toolbutton1->setAutoRaise(true);
    toolbutton1->setStyleSheet("width:90px;");
    toolbutton2->setText(QStringLiteral("停止定位"));
    toolbutton2->setAutoRaise(true);
    toolbutton2->setStyleSheet("width:90px;");
    toolbutton3->setText(QStringLiteral("定位接口配置"));
    toolbutton3->setAutoRaise(true);
    toolbutton3->setStyleSheet("width:90px;");
    toolbutton4->setText(QStringLiteral("数据转发配置"));
    toolbutton4->setAutoRaise(true);
    toolbutton4->setStyleSheet("width:90px;");





//    h1->addWidget(toolbutton1);
//    h1->addWidget(toolbutton2);
//    h1->addWidget(toolbutton3);
//    h1->addWidget(toolbutton4);

    locatelabel = new QLabel();
    Xlabel = new QLabel();
    Ylabel = new QLabel();

    locatelabel->setText(QStringLiteral("鼠标位置："));
    locatelabel->setStyleSheet("font-size: 13px;");
    Xlabel->setText(QStringLiteral("X坐标"));
    Xlabel->setStyleSheet("font-size: 13px;");
    Ylabel->setText(QStringLiteral("Y坐标"));
    Ylabel->setStyleSheet("font-size: 13px;");

  //  connect(view,SIGNAL(clicked()),this,SLOT(supersetvisble()));
    connect(view , SIGNAL(xlabel(double)) , this, SLOT(setxlabelvalue(double)));
    connect(view , SIGNAL(ylabel(double)) , this, SLOT(setylabelvalue(double)));



    bilichi1 =new QLabel();
    bilichi1->setText(QStringLiteral("比例尺:"));
    bilichi1->setStyleSheet("font-size: 13px;");

    QVBoxLayout *hnn1= new QVBoxLayout();
    hnn1->setSpacing(5);
    hnn1->setAlignment(Qt::AlignLeft);
    blilixiangsu = new QLabel();
    blilixiangsu->setPixmap(QPixmap(":/new/images/50pxbilichi.png"));
    bilivalue = new QLabel();
    bilivalue->setText(QStringLiteral("50Px=5米"));
    bilivalue->setStyleSheet("font-size: 13px;");
    hnn1->addWidget(blilixiangsu);
    hnn1->addWidget(bilivalue);
    connect(view , SIGNAL(bilichi(double)) , this, SLOT(setbililabelvalue(double)));


    QHBoxLayout *hn2 = new QHBoxLayout();
    hn2->setAlignment(Qt::AlignLeft);
    hn2->setAlignment(Qt::AlignTop);
    hn2->setContentsMargins(0,0,0,0);
    hn2->setSpacing(10);

    hn2->addWidget(Xlabel);
    hn2->addWidget(Ylabel);
    QVBoxLayout *vn2 =new QVBoxLayout();
    vn2->setAlignment(Qt::AlignLeft);
    vn2->setAlignment(Qt::AlignTop);
    vn2->setSpacing(20);
    vn2->setContentsMargins(7,0,0,0);
    vn2->addWidget(locatelabel);
    vn2->addLayout(hn2);
    vn2->addWidget(bilichi1);
    vn2->addLayout(hnn1);

    vn->addWidget(toolbutton1);
    vn->addWidget(toolbutton2);
    vn->addWidget(toolbutton3);
    vn->addWidget(toolbutton4);
    vn->addLayout(vn2);
    h2->addLayout(vn,1);

}

LoMoWidget::~LoMoWidget()
{
    delete ui;
}

void LoMoWidget::supersetvisble()
{
    if (supersets->checkState()==Qt::Checked)
    {
        filterbeginnum->setVisible(true);
        filternum->setVisible(true);
        pointfrequency->setVisible(true);
        pointFre->setVisible(true);
    }
    if (supersets->checkState()==Qt::Unchecked)
    {

        filterbeginnum->setVisible(false);
        filternum->setVisible(false);
        pointfrequency->setVisible(false);
        pointFre->setVisible(false);
    }
}

void LoMoWidget :: setxlabelvalue(double x)
{
    Xlabel->setText(QString::number(x));
}
void LoMoWidget :: setylabelvalue(double y)
{
    Ylabel->setText(QString::number(y));
}
void LoMoWidget :: setbililabelvalue(double bili)
{
    bilivalue->setText(QStringLiteral("50px=")+QString::number(bili)+QStringLiteral("米"));
}


