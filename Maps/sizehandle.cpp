#include "sizehandle.h"
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>
#include <qdebug.h>
#include <QtWidgets>

SizeHandleRect::SizeHandleRect(QGraphicsItem* parent , Direction d, QGraphicsItem *resizable)
    :QGraphicsRectItem(0,0,SELECTION_HANDLE_SIZE,SELECTION_HANDLE_SIZE,parent)
    ,m_dir(d)
    ,m_resizable(resizable)
    ,m_state(SelectionHandleOff)
    ,borderColor("limegreen")
{
    setParentItem(parent);
    hide();
}

void SizeHandleRect::updateCursor()
{
    switch (m_dir) {
    case Right:
        setCursor(Qt::SizeHorCursor);
        return;
    case RightTop:
        setCursor(Qt::SizeBDiagCursor);
        return;
    case RightBottom:
        setCursor(Qt::SizeFDiagCursor);
        return;
    case LeftBottom:
        setCursor(Qt::SizeBDiagCursor);
        return;
    case Bottom:
        setCursor(Qt::SizeVerCursor);
        return;
    case LeftTop:
        setCursor(Qt::SizeFDiagCursor);
        return;
    case Left:
        setCursor(Qt::SizeHorCursor);
        return;
    case Top:
        setCursor(Qt::SizeVerCursor);
        return;
    default:
        break;
    }
    setCursor(Qt::ArrowCursor);
}


void SizeHandleRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(borderColor));

    if ( m_dir == Center )
    {
        painter->setBrush(QBrush(Qt::blue));
        painter->drawEllipse(rect());
    }else
      painter->drawRect(rect());

}


void SizeHandleRect::setState(SelectionHandleState st)
{
    if (st == m_state)
        return;
    switch (st) {
    case SelectionHandleOff:
        hide();
        break;
    case SelectionHandleInactive:
    case SelectionHandleActive:
        show();
        break;
    }
    m_state = st;
}

bool SizeHandleRect::hitTest(const QPointF &point)
{
    QPointF pt = mapFromScene(point);
    bool result = rect().contains(pt);
    return result;
}

void SizeHandleRect::move(qreal x, qreal y)
{
    setPos(x,y);
}





