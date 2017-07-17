#ifndef MOVEITEM_H
#define MOVEITEM_H
#include <QGraphicsItem>
#include <QGraphicsItemAnimation>

class MoveItem : public QGraphicsItem
{
public:
    MoveItem();
    QRectF boundingRect() const;
    void setColor(const QColor &color) { brushColor = color; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QColor brushColor;
};

#endif // MOVEITEM_H
