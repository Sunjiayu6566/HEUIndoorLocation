#include "position.h"

Position::Position(QVector<QPoint> v,int n)
{
        m_Polygon.clear();
        m_Polygon.append(v);
        m_count = n;
}

bool Position:: PtInPolygon(QPoint p)

{
        // �������
       int nCross = 0;
       for (int i = 0; i < m_count; i++)
       {
              QPoint p1 = m_Polygon[i];
              QPoint p2 = m_Polygon[(i + 1) % m_count];// ���һ�������һ��������
              if (p1.y()==p2.y())
                      continue;
              if (p.y()<qMin(p1.y(),p2.y()))
                      continue;
              if (p.y()>= qMax(p1.y(),p2.y()))
                     continue;

              // �󽻵��x����

              double x = (double)(p.y() - p1.y()) * (double)(p2.x() - p1.x()) / (double)(p2.y() - p1.y()) + p1.x();

              // ֻͳ��p1p2��p�������ߵĽ���
              if (x > p.x())
              {
                     nCross++;
              }
       }
       // ����Ϊż�������ڶ����֮��
       return (nCross % 2 == 1);
}

Position::~Position(){}
