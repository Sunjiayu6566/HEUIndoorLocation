#include "newRoute.h"
#include "newRoute.h"
#include <QPixmap>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QDebug>
#include <QRectF>
newRoute::newRoute(QVector<QPoint> v)
{
 m_pathPoints.clear();
 m_pathPoints.append(v);
}

void newRoute::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
   QPixmap pleft,pright,pup,pdown,padd;
   pright.load(":/new/images/allright.jpg");
   pleft.load(":/new/images/allleft.jpg");
   pup.load(":/new/images/allup.jpg");
   pdown.load(":/new/images/alldown.jpg");
   padd.load(":/new/images/puregreen.jpg");
   for(int i = 1;i < m_pathPoints.size();i++){
       QPoint start = m_pathPoints[i-1];
       QPoint end = m_pathPoints[i];
       Direction dir = calTheDir(start,end);
       int n,distance;
       int m_x,m_y;
       int m;
       switch (dir) {
       case m_right:
          distance = end.x()-start.x();
          n = distance/10;
          m = distance%10;
          for(int j = 0;j < n;j++){
             m_x = start.x()+10*j;
             m_y = start.y()-5;
             QRect rec(m_x,m_y,10,10);
             painter->drawPixmap(rec,pright);
          }
          if(m!=0)
           {
              QRect recAdd(m_x+10,m_y,m,10);
              painter->drawPixmap(recAdd,padd);
            }
           break;

        case m_left:
           distance = start.x()-end.x();
           n = distance/10;
           m = distance%10;
           for(int j = 0;j < n;j++){
               m_x = (start.x()-10)-10*j;
               m_y = start.y()-5;
              QRect rec(m_x,m_y,10,10);
              painter->drawPixmap(rec,pleft);
           }

       if(m!=0)
       {
           QRect recAdd(m_x-m,m_y,m,10);
           painter->drawPixmap(recAdd,padd);
       }
           break;


        case m_up:
           distance = start.y()-end.y();
           n = distance/10;
           m = distance%10;
           for(int j = 0;j < n;j++){
               m_x = start.x()-5;
               m_y = start.y()-10-10*j;
              QRect rec(m_x,m_y,10,10);
              painter->drawPixmap(rec,pup);
           }

       if(m!=0)
       {
           QRect recAdd(m_x,m_y-10,10,m);
           painter->drawPixmap(recAdd,padd);
       }
           break;

        case m_down:
           distance = end.y()-start.y();
           n = distance/10;
           m = distance%10;
           for(int j = 0;j < n;j++){
               m_x = start.x()-5;
               m_y = start.y() + 10*j;
              QRect rec(m_x,m_y,10,10);
              painter->drawPixmap(rec,pdown);
           }
       if(m!=0)
       {
           QRect recAdd(m_x,m_y+10,10,m);
           painter->drawPixmap(recAdd,padd);
       }
            break;

       default:
           break;
       }
   }
}


 QRectF newRoute::boundingRect() const{

     qreal adjust = 0.5;
     return QRectF(-10 - adjust, -10 - adjust,
                   10 + adjust, 10 + adjust);
 }


 Direction newRoute::calTheDir(QPoint p1,QPoint p2){

     if((p1.y()==p2.y())&&(p2.x()>p1.x()))
         return m_right;
     if((p1.y()==p2.y())&&(p2.x()<p1.x()))
         return m_left;
     if((p1.x()==p2.x())&&(p1.y()>p2.y()))
        return m_up;
     if((p1.x()==p2.x())&&(p1.y()<p2.y()))
        return m_down;
 }

