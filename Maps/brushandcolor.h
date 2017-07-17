#ifndef BRUSHANDCOLOR_H
#define BRUSHANDCOLOR_H


#include <QPoint>
#include <QPainter>
#include <QColor>

class BrushAndColor
{
public:
    BrushAndColor();
   // void set_start(QPoint p);
   // void set_end(QPoint p);
   // void set_pos(QPoint, QPoint, bool);
    void set(QColor, QColor, int);
    void setPColor(QColor p){
        this->color = p;
    }
    void setPBrush(QColor p)
    {
        this->brush2 = p;
    }
    void setPWidth(int i)
    {
        this->width = i;
    }
   // virtual void paint (QPainter& painter) = 0;
    QColor get_color();
    QColor get_brush();
    int get_width();
protected:
    QColor color;
    QColor brush2;
    int width;
};

#endif // BRUSHANDCOLOR_H
