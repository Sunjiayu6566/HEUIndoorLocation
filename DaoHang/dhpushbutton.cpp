#include "dhpushbutton.h"


DHPushButton::DHPushButton(QWidget *parent)
    :QPushButton(parent)
{
    status = NORMAL;
    mouse_press = false;
}

DHPushButton::~DHPushButton()
{

}

void DHPushButton::loadPixmap(QString pic_name)
{
    pixmap.load(pic_name);
    btn_width = pixmap.width();
    btn_height = pixmap.height();
    setFixedSize(btn_width/2, btn_height);
}

void DHPushButton::enterEvent(QEvent *)
{
    status = ENTER;
    update();
}

void DHPushButton::mousePressEvent(QMouseEvent *event)
{
 //若点击鼠标左键
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        status = PRESS;
        update();
    }
}

void DHPushButton::mouseReleaseEvent(QMouseEvent *)
{
    //若点击鼠标左键
    if(mouse_press)
    {
        mouse_press = false;
        status = ENTER;
        update();
        emit clicked();
    }
}

void DHPushButton::leaveEvent(QEvent *)
{
    status = NORMAL;
    update();
}

void DHPushButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), pixmap.copy(btn_width * status, 0, btn_width, btn_height));

}
