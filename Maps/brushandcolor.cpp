#include "brushandcolor.h"

BrushAndColor::BrushAndColor()
{

}

QColor BrushAndColor::get_color()
{
    return color;
}

QColor BrushAndColor::get_brush()
{
    return  brush2;
}

int BrushAndColor::get_width()
{
    return width;
}

void BrushAndColor::set(QColor c1, QColor c2, int w)
{
    color = c1;
    brush2 = c2;
    width = w;
}
