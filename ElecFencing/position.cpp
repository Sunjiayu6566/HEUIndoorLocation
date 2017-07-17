#include "position.h"

Position::Position(QVector<QPoint> v,int n)
{
        m_Polygon.clear();
        m_Polygon.append(v);
        m_count = n;
}

bool Position:: PtInPolygon(QPoint p)

{
        // 交点个数
       int nCross = 0;
       for (int i = 0; i < m_count; i++)
       {
              QPoint p1 = m_Polygon[i];
              QPoint p2 = m_Polygon[(i + 1) % m_count];// 最后一个点与第一个点连线
              if (p1.y()==p2.y())
                      continue;
              if (p.y()<qMin(p1.y(),p2.y()))
                      continue;
              if (p.y()>= qMax(p1.y(),p2.y()))
                     continue;

              // 求交点的x坐标

              double x = (double)(p.y() - p1.y()) * (double)(p2.x() - p1.x()) / (double)(p2.y() - p1.y()) + p1.x();

              // 只统计p1p2与p向右射线的交点
              if (x > p.x())
              {
                     nCross++;
              }
       }
       // 交点为偶数，点在多边形之外
       return (nCross % 2 == 1);
}

Position::~Position(){}
