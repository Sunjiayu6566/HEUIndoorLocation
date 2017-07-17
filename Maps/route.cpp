#include "route.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QPainterPath>
Route::Route(QVector<QPoint> v)
{ 
  //QPen pen;
  //pen.setWidth (4);
  //pen.setColor (Qt::red);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(10);
    pen.setBrush(Qt::green);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    this->setPen(pen);
    this->setFlag (QGraphicsItem::ItemIsPanel);

    m_path.moveTo(v[0].x(),v[0].y());
    for(int i = 1;i < v.size();i++){
        m_path.lineTo(v[i].x(),v[i].y());
    }
    this->setPath(m_path);

}

/*
void Route::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    //painter->setPen(QPen(Qt::green,4,Qt::SolidLine));
    //painter->drawArc(20,20,210,160,500,1000);
    //painter->setBrush(Qt::FDiagPattern);
    //painter->setRenderHint(QPainter::Antialiasing);

}
*/


/*
void  Route::setPainterPath(QVector<QPoint> v){
    m_path.moveTo(0,0);
    for(int i = 0;i < v.size();i++){
        m_path.lineTo(v[i].x(),v[i].y());
    }
}
*/
