#include "moveitem.h"
#include <QPainter>
#include <QPen>
MoveItem::MoveItem()
{
    //setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(0, 160, 230));
    painter->setPen(pen);
    painter->setBrush(QColor(247, 160, 57));
    painter->drawEllipse(0,0,10,10);
}


QRectF MoveItem::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10 - adjust, -10 - adjust,
                  20 + adjust, 20 + adjust);
}
