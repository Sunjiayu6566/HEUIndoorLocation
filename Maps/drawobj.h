#ifndef DRAWOBJ
#define DRAWOBJ

#include <qgraphicsitem.h>
#include <qtcore/qobject.h>
#include <QGraphicsSceneMouseEvent>
#include "brushandcolor.h"
#include "drawtool.h"
#include "sizehandle.h"
#include <QVector>

//class DrawTool;
class GraphicsBasicItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit GraphicsBasicItem(QGraphicsItem * parent);
    explicit GraphicsBasicItem(const QString &name ,QGraphicsItem *parent );
    virtual ~GraphicsBasicItem();
};

class GraphicsItem :public BrushAndColor, public QAbstractGraphicsShapeItem
{
public:
    GraphicsItem(QGraphicsItem * parent );
    enum {Type = UserType+1};
    int  type() const { return Type; }
    SizeHandleRect::Direction  hitTest( const QPointF & point ) const;
    virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
    virtual QPointF origin () const { return QPointF(0,0); }
    virtual Qt::CursorShape getCursor(SizeHandleRect::Direction dir );
    virtual QRectF  rect() const { return m_localRect;}
    virtual void changeSize () {}


    virtual void move( const QPointF & point ){}


     QRectF m_localRect;

    //void

    void setMyShape(QColor pen_color,QColor brush_color,int width)
    {
        this->color = pen_color;
        this->brush2 = brush_color;
        this->width = width;
    }
/*
 * 以下3个方法用于得到图元的颜色，画刷和画笔线粗的数据
 * */
    QColor getitemcolor()
    {
        return this->color;
    }
    QColor getitembrush()
    {
        return this->brush2;
    }
    int getitemwidth()
    {
        return this->width;
    }

    virtual int get_typeid() = 0; //用以返回图元的类型


protected:
    virtual void updateGeometry();
    void setState(SelectionHandleState st);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    typedef QVector<SizeHandleRect*> Handles;
    Handles m_handles;
  //  QRectF m_localRect;
};

class GraphicsRectItem : public GraphicsItem
{
public:
    GraphicsRectItem(const QRect & rect ,QGraphicsItem * parent);
   // setShape(QColor pen_color,QColor brush_color,int width);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
    virtual QRectF  rect() const {  return m_localRect;}
    void changeSize();
    void move( const QPointF & point );

    /* 返回方形的图元类型为1 */
    virtual int get_typeid()
    {
        return 1;
    }

protected:
  //  void paint(QPainter *painter);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    qreal m_width;
    qreal m_height;


//private:
    //DrawTool drawtool;
};

class GraphicsItemGroup : public GraphicsRectItem
{
public:
    GraphicsItemGroup ( QGraphicsItemGroup * group, QGraphicsItem * parent );
    virtual ~GraphicsItemGroup();
    QRectF boundingRect() const;
    QPainterPath shape() const;
    virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
protected:
  //  void paint(QPainter *painter);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QGraphicsItemGroup *m_group;
};

class GraphicsEllipseItem : public GraphicsRectItem
{
public:
    GraphicsEllipseItem(const QRect & rect ,QGraphicsItem * parent);
    QPainterPath shape() const;
protected:
  //  void paint(QPainter *painter);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    /* 返回椭圆的图元类型为2 */
    virtual int  get_typeid() override
    {
        return 2;
    }
};


//class GraphicsPolyItem : public GraphicsRectItem
//{
//public:
//    GraphicsPolyItem(const QRect & rect ,QGraphicsItem * parent);
//    QPainterPath shape() const;
//protected:
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//private:
//    /* 返回椭圆的图元类型为2 */
//    virtual int  get_typeid() override
//    {
//        return 6;
//    }
//};



class GraphicsLineItem : public GraphicsRectItem
{
public:
    GraphicsLineItem(QGraphicsItem * parent );
    QPainterPath shape() const;
protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    /* 返回直线的图元类型为3 */
    virtual int get_typeid() override
    {
        return 3;
    }

};

class GraphicsBezierCurve : public GraphicsItem
{
public:
    GraphicsBezierCurve(QGraphicsItem * parent );
    QRectF boundingRect() const ;
    QPainterPath shape() const;
    void addPoint( const QPointF & point ) ;    
    virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVector<QPointF> m_points;
};

class GraphicsArcItem :public GraphicsLineItem
{
public:
    GraphicsArcItem(QGraphicsItem * parent);
    QPainterPath shape() const;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    //qreal startAngle,endAngle;
    /* 返回曲线的图元类型为4 */
    virtual int get_typeid() override
    {
        return 4;
    }
};

class GraphicsPieItem :public GraphicsLineItem
{
public:
    GraphicsPieItem(QGraphicsItem * parent);
    QPainterPath shape() const;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    //qreal startAngle,endAngle;
    /* 返回曲线的图元类型为4 */
    virtual int get_typeid() override
    {
        return 5;
    }
};


//class GraphicsPixmapItem : public QGraphicsItem
//{


//};

class GridTool : public QGraphicsItem
{
public:
    GridTool(const QSize &grid = QSize(3200,2400) , const QSize & space = QSize(40,40) );
    QRectF boundingRect() const ;
    QPainterPath shape() const;
    void paintGrid(QPainter *painter,const QRect & rect );
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QSize m_sizeGrid;
    QSize m_sizeGridSpace;
};

#endif // DRAWOBJ
