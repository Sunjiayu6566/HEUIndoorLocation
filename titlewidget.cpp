#include "titlewidget.h"
#include "ui_titlewidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QSignalMapper>
#include "tool_button.h"

//titlewidget::titlewidget(QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::titlewidget)
//{
//    ui->setupUi(this);
//}

//titlewidget::~titlewidget()
//{
//    delete ui;
//}

titlewidget::titlewidget(QWidget *parent)
    : QWidget(parent)
{
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QColor(14,110,255)));
    setPalette(palette);
    setAutoFillBackground(true);
    version_title = new QLabel();
   // skin_button = new PushButton();
    main_menu_button = new PushButton();
    min_button = new PushButton();
    max_button = new PushButton();
    close_button = new PushButton();
    warning_button = new PushButton();

    version_title->setStyleSheet("color:white;");

    //设置图片
    //skin_button->loadPixmap(":/new/images/skin_button.png");

    main_menu_button->loadPixmap(":/new/images/main_menu.png");
    warning_button->loadPixmap(":/new/images/baojing1.png");
    min_button->loadPixmap(":/new/images/min_button.png");
    max_button->loadPixmap(":/new/images/max_button.png");
    close_button->loadPixmap(":/new/images/close_button.png");

    /*

    QIcon warn_icon(":/new/images/email.png");
    warning_button->setIcon(warn_icon);
    warning_button->setFixedSize(25, 25);
    warning_button->setIconSize(QSize(15, 15));
    warning_button->setStyleSheet("background:transparent;");
*/
  //  connect(skin_button, SIGNAL(clicked()), this, SIGNAL(showSkin()));
    connect(main_menu_button, SIGNAL(clicked()), this, SIGNAL(showMainMenu()));
    connect(min_button, SIGNAL(clicked()), this, SIGNAL(showMin()));
    connect(max_button, SIGNAL(clicked()), this, SIGNAL(showMax()));
    connect(close_button, SIGNAL(clicked()), this, SIGNAL(closeWidget()));
    connect(warning_button, SIGNAL(clicked()), this, SIGNAL(showWarnings()));


    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(version_title,0,Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(warning_button, 0, Qt::AlignTop);
   // title_layout->addWidget(skin_button, 0, Qt::AlignTop);
    title_layout->addWidget(main_menu_button, 0, Qt::AlignTop);
    title_layout->addWidget(min_button, 0, Qt::AlignTop);
    title_layout->addWidget(max_button, 0, Qt::AlignTop);
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    title_layout->setSpacing(0);
    title_layout->setContentsMargins(0, 0, 10, 0);
    version_title->setContentsMargins(15, 0, 0, 0);
    //skin_button->setContentsMargins(0, 0, 10, 0);

    QStringList string_list;
    string_list<<":/new/images/locate.png"<<":/new/images/jizhan.png"<<":/new/images/camera.png"<<":/new/images/biaoqian.png"<<":/new/images/kaoqin.png"
              <<":/new/images/maps.png"<<":/new/images/person.png"<<":/new/images/way.png"<<":/new/images/gard.png"
           /*  <<":/new/images/xunluo.png"*/;

    QHBoxLayout *button_layout = new QHBoxLayout();

    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for(int i=0; i<string_list.size(); i++)
    {
        ToolButton *tool_button = new ToolButton(string_list.at(i));
        button_list.append(tool_button);
        connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(tool_button, QString::number(i, 10));

        button_layout->addWidget(tool_button, 0, Qt::AlignBottom);
    }
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(turnPage(QString)));

//    QLabel *logo_label = new QLabel();
//   // QPixmap pixmap(":/new/images/account.png");
//    logo_label->setPixmap(pixmap);
//    logo_label->setFixedSize(pixmap.size());
//    logo_label->setCursor(Qt::PointingHandCursor);

    button_layout->addStretch();
  //  button_layout->addWidget(logo_label);
    button_layout->setSpacing(8);
    button_layout->setContentsMargins(15, 0, 0, 0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(title_layout);
    main_layout->addLayout(button_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    //this->translateLanguage();

    setLayout(main_layout);
    setFixedHeight(100);
    is_move = false;


//void titlewidget::translateLanguage()
//{
    version_title->setText(tr("HEUIndoorLocation"));
    version_title->setStyleSheet("color:lightgreen");
    //skin_button->setToolTip(tr("change skin"));
    main_menu_button->setToolTip(tr("main menu"));
    min_button->setToolTip(tr("minimize"));
    max_button->setToolTip(tr("maximize"));
    warning_button->setToolTip(tr("warning"));
    close_button->setToolTip(tr("close"));

    button_list.at(0)->setText(QStringLiteral("定位监控"));
    button_list.at(1)->setText(QStringLiteral("基站管理"));
    button_list.at(2)->setText(QStringLiteral("摄像头联动"));
    button_list.at(3)->setText(QStringLiteral("标签管理"));
    button_list.at(4)->setText(QStringLiteral("考勤管理"));
    button_list.at(5)->setText(QStringLiteral("地图管理"));
    button_list.at(6)->setText(QStringLiteral("人员管理"));
    button_list.at(7)->setText(QStringLiteral("路径管理"));
    button_list.at(8)->setText(QStringLiteral("电子围栏"));
  //  button_list.at(9)->setText(QStringLiteral("巡逻管理"));

   connect( button_list.at(0), SIGNAL(clicked()), this, SIGNAL(showDwwidget()));
   connect( button_list.at(1), SIGNAL(clicked()), this, SIGNAL(showJzwidget()));
   connect( button_list.at(2), SIGNAL(clicked()), this, SIGNAL(showBqwidget()));
   connect( button_list.at(3), SIGNAL(clicked()), this, SIGNAL(showTrueBqwidget()));
   connect( button_list.at(4), SIGNAL(clicked()), this, SIGNAL(showKqwidget()));
   connect( button_list.at(5), SIGNAL(clicked()), this, SIGNAL(showMapwidget()));
   connect( button_list.at(8), SIGNAL(clicked()), this, SIGNAL(showElecWidget()));
//}
}

void titlewidget::mousePressEvent(QMouseEvent *e)
{
    press_point = e->pos();
    is_move = true;
}

void titlewidget::mouseMoveEvent(QMouseEvent *e)
{
    if((e->buttons() == Qt::LeftButton) && is_move)
    {
        static QWidget* parent_widget = this->parentWidget();
        QPoint parent_point = parent_widget->pos();
        parent_point.setX(parent_point.x() + e->x() - press_point.x());
        parent_point.setY(parent_point.y() + e->y() - press_point.y());
        parent_widget->move(parent_point);
    }
}

void titlewidget::mouseReleaseEvent(QMouseEvent *)
{
    if(is_move)
    {
        is_move = false;
    }
}

void titlewidget::mouseDoubleClickEvent(QMouseEvent *)
{
    emit showMax();
}

void titlewidget::turnPage(QString current_page)
{
    bool ok;
    int current_index = current_page.toInt(&ok, 10);

    for(int i=0; i<button_list.count(); i++)
    {
        ToolButton *tool_button = button_list.at(i);
        if(current_index == i)
        {
            tool_button->setMousePress(true);
        }
        else
        {
            tool_button->setMousePress(false);
        }
    }
}
