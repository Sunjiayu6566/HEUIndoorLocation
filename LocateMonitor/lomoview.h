#ifndef LOMOVIEW_H
#define LOMOVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>

class LoMoView : public QGraphicsView
{
    Q_OBJECT
public:
    LoMoView();

    void wheelEvent(QWheelEvent*event);
    QPointF mapToMap(QPointF p);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    xlabel(double);
    ylabel(double);
    mapxlabel(double);
    mapylabel(double);
    bilichi(double);

};

#endif // LOMOVIEW_H
