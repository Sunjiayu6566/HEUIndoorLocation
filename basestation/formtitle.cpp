#include "formtitle.h"
#include <QHBoxLayout>
#include <QSignalMapper>
#include "tool_button.h"

FormTitle::FormTitle(QWidget *parent,QString str)
    : QWidget(parent)
{
    this->setFixedHeight(45);
    version_title = new QLabel();
    version_title->setStyleSheet("color:white;");

    min_button=new PushButton();
    close_button=new PushButton();

    min_button->loadPixmap(":/new/images/min_button.png");
    close_button->loadPixmap(":/new/images/close_button.png");

    connect(min_button,SIGNAL(clicked()),this,SIGNAL(showMin()));
    connect(close_button,SIGNAL(clicked()),this,SIGNAL(closeWidget()));

    QHBoxLayout *title_layout=new QHBoxLayout();
    title_layout->addWidget(version_title,0,Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(min_button,0,Qt::AlignTop);
    title_layout->addWidget(close_button,0,Qt::AlignTop);

    title_layout->setSpacing(0);
    title_layout->setContentsMargins(0,0,0,0);
    version_title->setContentsMargins(2, 3, 0, 0);
    version_title->setText(str);

    setLayout(title_layout);
    setFixedHeight(20);
    is_move=false;

    min_button->setToolTip(QString::fromLocal8Bit("最小化"));
    close_button->setToolTip(QString::fromLocal8Bit("关闭"));
    setStyleSheet("background:#87ceff;");

}

FormTitle::~FormTitle()
{}

void FormTitle::mousePressEvent(QMouseEvent *e)
{
    press_point=e->pos();
    is_move=true;
}

void FormTitle::mouseMoveEvent(QMouseEvent *e)
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


void FormTitle::mouseReleaseEvent(QMouseEvent *)
{

    if(is_move)
    {
        is_move=false;
    }
}

void FormTitle::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

