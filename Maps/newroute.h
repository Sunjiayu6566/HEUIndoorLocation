#ifndef NEWROUTE_H
#define NEWROUTE_H


#include<QGraphicsItem>
#include<QString>
#include <QPoint>
#include <QDebug>
enum Direction{m_up,m_down,m_left,m_right};
class newRoute:public QGraphicsItem
{
public:
    newRoute(QVector<QPoint> p);
    Direction calTheDir(QPoint p1,QPoint p2);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QVector<QPoint> m_pathPoints;
};

#endif // NEWROUTE_H
