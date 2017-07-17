#ifndef ROUTE_H
#define ROUTE_H

#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPoint>
#include <QVector>
class Route : public QGraphicsPathItem
{
public:
    Route(QVector<QPoint> v);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //void setPainterPath(QVector<QPoint>v);
private:
  QPainterPath m_path;
};

#endif // ROUTE_H
