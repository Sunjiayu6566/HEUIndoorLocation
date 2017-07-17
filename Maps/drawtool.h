#ifndef DRAWTOOL
#define DRAWTOOL

#include <QGraphicsScene>
#include <QList>
#include <QPainter>
#include <Qpen>
#include <QCursor>
#include "drawscene.h"
#include "brushandcolor.h"
//#include <QGraphicsSceneMouseEvent>
//#include <QMenu>
//#include <QPointF>
//#include <QFont>
//#include <QColor>
//#include <QAbstractGraphicsShapeItem>
//#include <QGraphicsItem>
QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
class QAbstractGraphicsShapeItem;
QT_END_NAMESPACE

class DrawScene;
class GraphicsItem;

enum DrawShape
{
    selection ,
    rotation  ,
    line ,
    rectangle ,
    roundrect ,
    ellipse ,
    pie,
    bezier,
    poly,
    arc,
};

class DrawTool : public BrushAndColor
{
public:
    DrawTool( DrawShape shape );
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene );
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event ,DrawScene *scene );
    DrawShape m_drawShape;
    bool m_hoverSizer;

    static DrawTool * findTool( DrawShape drawShape );
    static QList<DrawTool*> c_tools;
    static QPointF c_down;
    static quint32 c_nDownFlags;
    static QPointF c_last;
    static DrawShape c_drawShape;


//    void set(QColor, QColor, int);
//    QColor get_color();
//    QColor get_brush();
//    int get_width();
//protected:
//    QColor color;
//    QColor brush2;
//    int width;
};

class SelectTool : public DrawTool
{
public:
    SelectTool();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene );
    QSizeF  m_lastSize;
    QPointF initialPositions;
    QGraphicsPathItem * dashRect;
};

class  RotationTool : public DrawTool
{
public:
    RotationTool();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene );
    qreal lastAngle;
    QGraphicsPathItem * dashRect;
};

class RectTool : public DrawTool
{
public:
    RectTool(DrawShape drawShape);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene ) ;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event , DrawScene * scene );
    //QAbstractGraphicsShapeItem * item;
    GraphicsItem *item;
};

#endif // DRAWTOOL

