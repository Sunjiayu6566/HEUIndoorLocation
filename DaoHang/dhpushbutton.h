#ifndef DHPUSHBUTTON_H
#define DHPUSHBUTTON_H

#include <QPainter>
#include <QPushButton>
#include <QMouseEvent>

/**
* @功能描述   主要设置按钮样式、特效
**/

class DHPushButton : public QPushButton
{
    Q_OBJECT

public:

    /**
    *
    * 功能说明
    *    构造函数
    *
    * 参数说明
    *     QWidget *parent = 0    父窗体
    *
    * 返回值
    *     无
    *
    */
    explicit DHPushButton(QWidget *parent = 0);

    /**
    *
    * 功能说明
    *    析构函数
    *
    * 参数说明
    *     无
    *
    * 返回值
    *     无
    *
    */
    ~DHPushButton();

    /**
    *
    * 功能说明
    *	 加载图标
    *
    * 参数说明
    *     QString pic_name 图标名称
    *
    * 返回值
    *     无
    *
    */
    void loadPixmap(QString pic_name);

protected:

    /**
    *
    * 功能说明
    *    鼠标移进事件
    *
    * 参数说明
    *     QEvent * event    事件
    *
    * 返回值
    *     无
    *
    */
    void enterEvent(QEvent *);

    /**
    *
    * 功能说明
    *     鼠标移出事件
    *
    * 参数说明
    *     QEvent * event    事件
    *
    * 返回值
    *     无
    *
    */
    void leaveEvent(QEvent *);

    /**
    *
    * 功能说明
    *     鼠标按下事件
    *
    * 参数说明
    *     QMouseEvent *event    鼠标事件
    *
    * 返回值
    *     无
    *
    */
    void mousePressEvent(QMouseEvent *event);

    /**
    *
    * 功能说明
    *     鼠标释放事件
    *
    * 参数说明
    *     QMouseEvent *event    鼠标事件
    *
    * 返回值
    *     无
    *
    */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
    *
    * 功能说明
    *     绘图事件
    *
    * 参数说明
    *     QPaintEvent * event    绘图事件
    *
    * 返回值
    *     无
    *
    */
    void paintEvent(QPaintEvent *);

private:

    //枚举按钮的几种状态
    enum ButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS};
    ButtonStatus status;
    QPixmap pixmap;

    int btn_width; //按钮宽度
    int btn_height; //按钮高度
    bool mouse_press; //按钮左键是否按下
};

#endif // DHPUSHBUTTON_H
