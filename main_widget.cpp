#include "main_widget.h"
#include "util.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
main_widget::main_widget(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(900, 600);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);

    setWindowIcon(QIcon(":/new/images/account.png"));
    setWindowFlags(Qt::FramelessWindowHint);
    location = this->geometry();

    bool is_read = Util::readInit(QString("./user.ini"), QString("new/skin"), skin_name);
    if(is_read)
    {
        if(skin_name.isEmpty())
        {
            //skin_name = QString(":new/skin/17_big");
            skin_name= QString(":new/skin/bluebackground");
        }
    }
    else
    {
        //skin_name = QString(":new/skin/17_big");
        skin_name= QString(":new/skin/bluebackground");
    }



    title_widget = new  titlewidget();
    content_widget = new contentwidget();
    lomomainwidget= new LoMoMainWidget();
    jzwidget = new JzWidget();
    bqwidget = new BqWidget();
    kqwidget = new KqWidget();
    truebqwidget= new TrueBqWidget();
    mapwidget=new Mapwidget();
    elecwidget =new ElecFenceWidget();
    warningwidget = new warningWidget();
    main_menu = new MainMenu();

    content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lomomainwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    jzwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    kqwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bqwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    truebqwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mapwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    elecwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


  //  character_widget = new CharacterWidget();
  //  about_us_dialog = new AboutUsDialog(this);
  //  setting_dialog = new SettingDialog(this);
  //  skin_widget = new SkinWidget(this);
  //  system_tray = new SystemTray(this);




//    m_status = 0;
//    m_navBtn = new DHPushButton;
//    m_navBtn->loadPixmap(":/new/images/right1.png");

//    m_naviView = new NaviView(this);
//    m_naviView->setVisible(false);
//    NavModel* model = new NavModel(this);
//    model->ReadDataFromConfig("attence.xml");
//    NavDelegate* delegate = new NavDelegate(this);
//    m_naviView->setModel(model);
//    m_naviView->setItemDelegate(delegate);

//    m_stackWidget = new QStackedWidget(this);
//    m_stackWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    QHBoxLayout *h13=new QHBoxLayout();
//    h13->setSpacing(0);
//    h13->setContentsMargins(0,0,0,0);

//    m_stackWidget->addWidget(content_widget);
//    m_stackWidget->addWidget(lomomainwidget);
//    m_stackWidget->addWidget(bqwidget);
//    m_stackWidget->addWidget(jzwidget);
//    m_stackWidget->addWidget(kqwidget);
//    m_stackWidget->addWidget(truebqwidget);
//    m_stackWidget->addWidget(mapwidget);
//    m_stackWidget->addWidget(elecwidget);
  //  m_stackWidget->setLayout(h13);

    lomomainwidget->hide();
    bqwidget->hide();
    jzwidget->hide();
    kqwidget->hide();
    truebqwidget->hide();
    mapwidget->hide();
    elecwidget->hide();

    QHBoxLayout *center_layout =new QHBoxLayout();
    center_layout->setSpacing(0);
//    QHBoxLayout *h11 =new QHBoxLayout();
//    h11->setSpacing(0);
//    h11->addWidget(m_naviView);
//    h11->addWidget(m_navBtn);

    center_layout->addWidget(content_widget);
    center_layout->addWidget(lomomainwidget);
    center_layout->addWidget(jzwidget);
    center_layout->addWidget(kqwidget);
    center_layout->addWidget(bqwidget);
    center_layout->addWidget(truebqwidget);
    center_layout->addWidget(mapwidget);
    center_layout->addWidget(elecwidget);

//    QHBoxLayout *h12 = new QHBoxLayout();
//    h12->setSpacing(0);
//    h12->setContentsMargins(0,10,10,10);
//    h12->addWidget(m_stackWidget);
//    center_layout->addLayout(h11,1);
//    center_layout->addLayout(h12,5);
//    center_layout->addWidget(m_stackWidget,6);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(title_widget);
    main_layout->addLayout(center_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(main_layout);

//    connect(this->m_naviView, SIGNAL(clicked(const QModelIndex &)), model, SLOT(Collapse(const QModelIndex&)));
//    connect(this->m_naviView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(switchPage()));
//    connect(this->m_navBtn, SIGNAL(clicked()), this, SLOT(setNav()));




 // *******************************END 娣诲姞瀵艰埅鏍忕粨鏉�**********************************//

    connect(title_widget, SIGNAL(showMainMenu()), this, SLOT(showMainMenu()));
    connect(title_widget, SIGNAL(showMax()), this, SLOT(showMax()));
    connect(title_widget, SIGNAL(showMin()), this, SLOT(showMinimized()));
    connect(title_widget, SIGNAL(showWarnings()), this, SLOT(showWarnings()));
    connect(title_widget, SIGNAL(closeWidget()), this, SLOT(hide()));
    connect(title_widget, SIGNAL(showDwwidget()), this, SLOT(showDwwidget()));
    connect(title_widget, SIGNAL(showJzwidget()), this, SLOT(showJzwidget()));
    connect(title_widget, SIGNAL(showBqwidget()), this, SLOT(showBqwidget()));
    connect(title_widget, SIGNAL(showKqwidget()), this, SLOT(showKqwidget()));
    connect(title_widget, SIGNAL(showTrueBqwidget()), this, SLOT(showTrueBqwidget()));
    connect(title_widget, SIGNAL(showMapwidget()),this, SLOT(showMapwidget()));
    connect(title_widget, SIGNAL(showElecWidget()),this, SLOT(showElecFenceWidget()));

//        connect(title_widget, SIGNAL(showDwwidget()), this, SLOT(showDwwidget()));
//        connect(title_widget, SIGNAL(showJzwidget()), this, SLOT(showJzwidget()));
//        connect(title_widget, SIGNAL(showBqwidget()), this, SLOT(showBqwidget()));
//        connect(title_widget, SIGNAL(showKqwidget()), this, SLOT(showKqwidget()));
//        connect(title_widget, SIGNAL(showTrueBqwidget()), this, SLOT(showTrueBqwidget()));
//        connect(title_widget, SIGNAL(showMapwidget()),this, SLOT(showMapwidget()));

    connect(main_menu, SIGNAL(showLogs()), this, SLOT(showlogs()));
    connect(main_menu, SIGNAL(showFilterSet()), this, SLOT(showfilterset()));
}

main_widget::~main_widget()
{

}

void main_widget :: showlogs()
{
    Logs *log = new Logs();
    log->show();

}

void main_widget :: showfilterset()
{
    FilterSet *fs = new FilterSet();
    fs->show();

}


//void main_widget::paintEvent(QPaintEvent *)
//{


//    QPainter painter(this);
//    painter.drawPixmap(rect(), QPixmap(skin_name));

//    QPainter painter2(this);
//    painter2.setPen(Qt::gray);
//    static const QPointF points[4] = {QPointF(0, 100), QPointF(0, this->height()-1), QPointF(this->width()-1, this->height()-1), QPointF(this->width()-1, 100)};
//    painter2.drawPolyline(points, 4);
//}


void main_widget::showMax()
{
    static bool is_max=false;
    if(is_max)
    {
        this->setGeometry(location);
    }
    else
    {

        location = this->geometry();
        this->setGeometry(QApplication::desktop()->availableGeometry());
    }
    is_max = !is_max;
}


void main_widget::showMainMenu()
{

    QPoint p = rect().topRight();
    p.setX(p.x() - 150);
    p.setY(p.y() + 22);
    main_menu->exec(this->mapToGlobal(p));
}

void main_widget::iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {

    case QSystemTrayIcon::Trigger:
    {
        showWidget();
        break;
    }

    case QSystemTrayIcon::DoubleClick:
    {
        showWidget();
        break;
    }
    default:
        break;
    }
}

//void main_widget::switchPage(){
//   int n = m_naviView->currentIndex().row();
//   m_stackWidget->setCurrentIndex(n);
//}

//void main_widget::setNav(){
//    if(m_status==0){
//    this->m_naviView->setVisible(true);
//    m_naviView->resize(this->width()/6,this->height());
//    m_navBtn->loadPixmap(":/new/images/left1.png");
//    m_status = 1;
// }
//    else{
//        m_naviView->setVisible(false);
//        m_navBtn->loadPixmap(":/new/images/right1.png");
//       // m_navBtn->setFixedSize(30,60);
//        m_status = 0;
//    }
//}

void main_widget::showWidget()
{
    this->showNormal();
    this->raise();
    this->activateWindow();
    title_widget->turnPage(0);
}



void main_widget::changeSkin(QString skin_name)
{
    Util::writeInit(QString("./user.ini"), QString("/new/skin"), skin_name);
    this->skin_name = skin_name;
    update();
}


void main_widget::showWarnings(){
    warningwidget->show();
}

void main_widget::showDwwidget()
{
    lomomainwidget->show();
    content_widget->hide();
    jzwidget->hide();
    bqwidget->hide();
    kqwidget->hide();
    truebqwidget->hide();
    mapwidget->hide();
    elecwidget->hide();
    //m_stackWidget->setCurrentIndex(1);
}

void main_widget::showJzwidget()
{
    lomomainwidget->hide();
    content_widget->hide();
    jzwidget->show();
    bqwidget->hide();
    kqwidget->hide();
    truebqwidget->hide();
    mapwidget->hide();
    elecwidget->hide();
}

void main_widget::showBqwidget()
{
    lomomainwidget->hide();
    content_widget->hide();
    jzwidget->hide();
    bqwidget->show();
    kqwidget->hide();
    truebqwidget->hide();
    mapwidget->hide();
    elecwidget->hide();
}
void main_widget::showKqwidget()
{
    lomomainwidget->hide();
    content_widget->hide();
    jzwidget->hide();
    bqwidget->hide();
    kqwidget->show();
    truebqwidget->hide();
    mapwidget->hide();
    elecwidget->hide();
}
void main_widget::showTrueBqwidget()
{
    lomomainwidget->hide();
    content_widget->hide();
    jzwidget->hide();
    bqwidget->hide();
    kqwidget->hide();
    truebqwidget->show();
    mapwidget->hide();
    elecwidget->hide();
}
void main_widget:: showMapwidget()
{
    lomomainwidget->hide();
    content_widget->hide();
    jzwidget->hide();
    bqwidget->hide();
    kqwidget->hide();
    truebqwidget->hide();
    mapwidget->show();
    elecwidget->hide();
}

void main_widget:: showElecFenceWidget()
{
    lomomainwidget->hide();
    content_widget->hide();
    jzwidget->hide();
    bqwidget->hide();
    kqwidget->hide();
    truebqwidget->hide();
    mapwidget->hide();
    elecwidget->show();
}




