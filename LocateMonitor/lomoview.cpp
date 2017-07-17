#include "lomoview.h"
qreal bilis=5;
LoMoView::LoMoView()
{


}

void LoMoView::wheelEvent(QWheelEvent *event)
{
    setMouseTracking(true);
    qreal sc;
    if(event->delta()>0) //鼠标滚轮向外
    {
        int numSteps = event->delta()/15/8;
        sc = pow(1.01,numSteps);
        this->scale(sc,sc);
        bilis*=sc;
        emit bilichi(bilis);
    }
    if(event->delta()<0)  //鼠标滚轮向内
    {
        int numSteps = event->delta()/15/8;
        sc= pow(1/1.01, - numSteps);
        this ->scale(sc,sc);
        bilis*=sc;
        emit bilichi(bilis);
    }

}
QPointF LoMoView ::mapToMap(QPointF p)
{
    QPointF zuobiao;
    qreal w= sceneRect().width();
    qreal h=sceneRect().height();

    qreal xzuobiao=p.x()+w;
    qreal yzuobiao=p.y()+h;

    zuobiao.setX(xzuobiao);
    zuobiao.setY(yzuobiao);
    return zuobiao;

}

void LoMoView :: mouseMoveEvent(QMouseEvent *event)
{
    this->setMouseTracking(true);
    QPoint viewPoint = event->pos();
    QPointF scenePoint = this->mapToScene(viewPoint);
    QPointF MapPoint = mapToMap(scenePoint);
    emit xlabel(scenePoint.x());
    emit ylabel(scenePoint.y());
    emit mapxlabel(MapPoint.x());
    emit mapylabel(MapPoint.y());


}

