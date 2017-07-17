#ifndef NAVIVIEW_H
#define NAVIVIEW_H
#include<QListView>
class NaviView : public QListView
{
    Q_OBJECT
public:
    NaviView(QWidget *parent);
    ~NaviView();
    //void enterEvent(QEvent *event);
    // void leaveEvent(QEvent *event);
    //void mouseReleaseEvent(QMouseEvent*event);
   // void mouseMoveEvent(QMouseEvent*event);
   //void mousePressEvent(QMouseEvent*event);
private:
    QPoint  m_dragPos;
};

#endif // NAVIVIEW_H
