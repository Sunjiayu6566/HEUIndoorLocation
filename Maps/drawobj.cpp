#include "drawobj.h"
#include <QPainter>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QCursor>
#include <QDebug>
#include <QGraphicsEffect>
#include <math.h>

static QPainterPath qt_graphicsItem_shapeFromPath(const QPainterPath &path, const QPen &pen)
{
    // We unfortunately need this hack as QPainterPathStroker will set a width of 1.0
    // if we pass a value of 0.0 to QPainterPathStroker::setWidth()
    const qreal penWidthZero = qreal(0.00000001);

    if (path == QPainterPath() || pen == Qt::NoPen)
        return path;
    QPainterPathStroker ps;
    ps.setCapStyle(pen.capStyle());
    if (pen.widthF() <= 0.0)
        ps.setWidth(penWidthZero);
    else
        ps.setWidth(pen.widthF());
    ps.setJoinStyle(pen.joinStyle());
    ps.setMiterLimit(pen.miterLimit());
    QPainterPath p = ps.createStroke(path);
    p.addPath(path);
    return p;
}


GraphicsItem::GraphicsItem(QGraphicsItem *parent)
    :QAbstractGraphicsShapeItem(parent)
{
//    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
//    effect->setBlurRadius(8);
//    setGraphicsEffect(effect);
}

void GraphicsItem::updateGeometry()
{
    const QRectF &geom = this->boundingRect();

    const int w = SELECTION_HANDLE_SIZE;
    const int h = SELECTION_HANDLE_SIZE;

    const Handles::iterator hend =  m_handles.end();
    for (Handles::iterator it = m_handles.begin(); it != hend; ++it) {
        SizeHandleRect *hndl = *it;;
        switch (hndl->dir()) {
        case SizeHandleRect::LeftTop:
            hndl->move(geom.x() - w / 2, geom.y() - h / 2);
            break;
        case SizeHandleRect::Top:
            hndl->move(geom.x() + geom.width() / 2 - w / 2, geom.y() - h / 2);
            break;
        case SizeHandleRect::RightTop:
            hndl->move(geom.x() + geom.width() - w / 2, geom.y() - h / 2);
            break;
        case SizeHandleRect::Right:
            hndl->move(geom.x() + geom.width() - w / 2, geom.y() + geom.height() / 2 - h / 2);
            break;
        case SizeHandleRect::RightBottom:
            hndl->move(geom.x() + geom.width() - w / 2, geom.y() + geom.height() - h / 2);
            break;
        case SizeHandleRect::Bottom:
            hndl->move(geom.x() + geom.width() / 2 - w / 2, geom.y() + geom.height() - h / 2);
            break;
        case SizeHandleRect::LeftBottom:
            hndl->move(geom.x() - w / 2, geom.y() + geom.height() - h / 2);
            break;
        case SizeHandleRect::Left:
            hndl->move(geom.x() - w / 2, geom.y() + geom.height() / 2 - h / 2);
            break;
        case SizeHandleRect::Center:
            hndl->move(geom.center().x()  - w / 2 , geom.center().y() - h / 2);
            break;
        default:
            break;
        }
    }

}

void GraphicsItem::setState(SelectionHandleState st)
{
    const Handles::iterator hend =  m_handles.end();
    for (Handles::iterator it = m_handles.begin(); it != hend; ++it)
        (*it)->setState(st);
}

SizeHandleRect::Direction GraphicsItem::hitTest(const QPointF &point) const
{
    const Handles::const_iterator hend =  m_handles.end();
    for (Handles::const_iterator it = m_handles.begin(); it != hend; ++it)
    {
        if ((*it)->hitTest(point) ){
            return (*it)->dir();
        }
    }
    return SizeHandleRect::None;
}

Qt::CursorShape GraphicsItem::getCursor(SizeHandleRect::Direction dir)
{
    switch (dir) {
    case SizeHandleRect::Right:
        return Qt::SizeHorCursor;
    case SizeHandleRect::RightTop:
        return Qt::SizeBDiagCursor;
    case SizeHandleRect::RightBottom:
        return Qt::SizeFDiagCursor;
    case SizeHandleRect::LeftBottom:
        return Qt::SizeBDiagCursor;
    case SizeHandleRect::Bottom:
        return Qt::SizeVerCursor;
    case SizeHandleRect::LeftTop:
        return Qt::SizeFDiagCursor;
    case SizeHandleRect::Left:
        return Qt::SizeHorCursor;
    case SizeHandleRect::Top:
        return Qt::SizeVerCursor;
    default:
        break;
    }
    return Qt::ArrowCursor;
}

void GraphicsItem::resizeTo(SizeHandleRect::Direction dir, const QPointF &point)
{

}

void GraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}

QVariant GraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if ( change == QGraphicsItem::ItemSelectedHasChanged ) {
        qDebug()<<" Item Selected : " << value.toString();
        setState(value.toBool() ? SelectionHandleActive : SelectionHandleOff);
    }else if ( change == QGraphicsItem::ItemRotationHasChanged ){
        qDebug()<<"Item Rotation Changed:" << value.toString();
    }else if ( change == QGraphicsItem::ItemTransformOriginPointHasChanged ){
        QPointF newPos=boundingRect().center();

        qDebug()<<"ItemTransformOriginPointHasChanged:" << value.toPointF() << newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}


GraphicsRectItem::GraphicsRectItem(const QRect & rect ,QGraphicsItem *parent)
    :GraphicsItem(parent)
    ,m_width(rect.width())
    ,m_height(rect.height())
{

    // handles
    m_handles.reserve(SizeHandleRect::None);
    for (int i = SizeHandleRect::LeftTop; i <= SizeHandleRect::Left; ++i) {
        SizeHandleRect *shr = new SizeHandleRect(this, static_cast<SizeHandleRect::Direction>(i), this);
        m_handles.push_back(shr);
    }
    updateGeometry();
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->setAcceptHoverEvents(true);
}

QRectF GraphicsRectItem::boundingRect() const
{

    return m_localRect;
}

QPainterPath GraphicsRectItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return qt_graphicsItem_shapeFromPath(path,pen());
}

void GraphicsRectItem::resizeTo(SizeHandleRect::Direction dir, const QPointF &point)
{
    QPointF local = mapFromParent(point);
    QString dirName;

    const QRectF &geom = this->boundingRect();
    QRect delta = this->rect().toRect();
    switch (dir) {
    case SizeHandleRect::Right:
        dirName = "Rigth";
        delta.setRight(local.x());
        break;
    case SizeHandleRect::RightTop:
        dirName = "RightTop";
        delta.setTopRight(local.toPoint());
        break;
    case SizeHandleRect::RightBottom:
        dirName = "RightBottom";
        delta.setBottomRight(local.toPoint());
        break;
    case SizeHandleRect::LeftBottom:
        dirName = "LeftBottom";
        delta.setBottomLeft(local.toPoint());
        break;
    case SizeHandleRect::Bottom:
        dirName = "Bottom";
        delta.setBottom(local.y());
        break;
    case SizeHandleRect::LeftTop:
        dirName = "LeftTop";
        delta.setTopLeft(local.toPoint());
        break;
    case SizeHandleRect::Left:
        dirName = "Left";
        delta.setLeft(local.x());
        break;
    case SizeHandleRect::Top:
        dirName = "Top";
        delta.setTop(local.y());
        break;
   default:
        break;
    }

    m_width = delta.width();
    m_height = delta.height();


    prepareGeometryChange();
    m_localRect = delta;

    updateGeometry();
}

void GraphicsRectItem::changeSize()
{
    QPointF pt1,pt2,delta;
    pt1 = mapToScene(transformOriginPoint());
    pt2 = mapToScene(boundingRect().center());
    delta = pt1 - pt2;

    setTransform(transform().translate(delta.x(),delta.y()));
    setTransformOriginPoint(boundingRect().center());
    setTransform(transform().translate(-delta.x(),-delta.y()));
    moveBy(-delta.x(),-delta.y());

    prepareGeometryChange();

    m_localRect = QRectF(-m_width/2,-m_height/2,m_width,m_height);

    setTransformOriginPoint(boundingRect().center());

    qDebug()<<"changeOrigin: "<< delta << mapFromScene( pos()) << mapFromScene(pt2)<<m_localRect;

    updateGeometry();

}

void GraphicsRectItem::move(const QPointF &point)
{
   moveBy(point.x(),point.y());
}

//void GraphicsRectItem::paint(QPainter *painter)
void GraphicsRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(color,width));
    painter->setBrush(brush2);
    painter->drawRect(rect());

}


GraphicsEllipseItem::GraphicsEllipseItem(const QRect &rect, QGraphicsItem *parent)
    :GraphicsRectItem(rect,parent)
{

}

QPainterPath GraphicsEllipseItem::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return qt_graphicsItem_shapeFromPath(path,pen());
}


//void GraphicsRectItem::paint(QPainter *painter)
void GraphicsEllipseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QRectF rc = rect().normalized();
    painter->setPen(QPen(color,width));
    painter->setBrush(brush2);
    painter->drawEllipse(rc);

}

GraphicsLineItem::GraphicsLineItem(QGraphicsItem *parent)
    :GraphicsRectItem(QRect(0,0,0,0),parent)
{
    // handles
    m_handles.reserve(SizeHandleRect::None);

    Handles::iterator hend =  m_handles.end();
    for (Handles::iterator it = m_handles.begin(); it != hend; ++it)
        delete (*it);
    m_handles.clear();

    SizeHandleRect *shr = new SizeHandleRect(this,SizeHandleRect::LeftTop, this);
    m_handles.push_back(shr);
    shr = new SizeHandleRect(this,SizeHandleRect::RightBottom, this);
    m_handles.push_back(shr);

    updateGeometry();
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->setAcceptHoverEvents(true);
}

QPainterPath GraphicsLineItem::shape() const
{
    QPainterPath path;
    path.moveTo(rect().topLeft());
    path.lineTo(rect().bottomRight());
    return qt_graphicsItem_shapeFromPath(path,pen());
}

void GraphicsLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(color,width));
    painter->setBrush(brush2);

    painter->drawLine(rect().topLeft(),rect().bottomRight());
}

GraphicsItemGroup::GraphicsItemGroup(QGraphicsItemGroup *group, QGraphicsItem *parent)
    :GraphicsRectItem(QRect(0,0,0,0),parent )
    ,m_group(group)
{
    if ( m_group ){
        m_group->setParentItem(this);
        QRectF bound = m_group->boundingRect();

        qDebug()<<" group rect :" << m_group->boundingRect() << " new Rect:" << bound;
        bound.normalized();
        prepareGeometryChange();
        m_width = bound.width();
        m_height = bound.height();

        QPointF pt1,pt2,delta;
        pt1 = mapToScene(pos());
        pt2 = mapToScene(bound.center());
        delta = pt1 - pt2;

        setTransform(transform().translate(delta.x(),delta.y()));
        setTransformOriginPoint(bound.center());
 //       setTransform(transform().translate(-delta.x(),-delta.y()));
        moveBy(-delta.x(),-delta.y());

        m_group->setTransformOriginPoint(bound.center());

        qDebug()<<"pos :" << delta;
        updateGeometry();
    }
}

GraphicsItemGroup::~GraphicsItemGroup()
{

}

QRectF GraphicsItemGroup::boundingRect() const
{

    QRectF bounding = m_group->mapRectToParent(m_group->boundingRect());

    return bounding;
}

QPainterPath GraphicsItemGroup::shape() const
{
    return m_group->shape() ;
}

void GraphicsItemGroup::resizeTo(SizeHandleRect::Direction dir, const QPointF &point)
{
    /*
    QPointF local = mapFromScene(point);
    QString dirName;

    const QRectF &geom = this->boundingRect();
    QRect delta = this->boundingRect().toRect();
    delta.normalized();
    m_width = delta.width();
    m_height = delta.height();

    switch (dir) {
    case SizeHandleRect::Right:
        dirName = "Rigth";
        delta.setRight(local.x());
        break;
    case SizeHandleRect::RightTop:
        dirName = "RightTop";
        delta.setTopRight(local.toPoint());
        break;
    case SizeHandleRect::RightBottom:
        dirName = "RightBottom";
        delta.setBottomRight(local.toPoint());
        break;
    case SizeHandleRect::LeftBottom:
        dirName = "LeftBottom";
        delta.setBottomLeft(local.toPoint());
        break;
    case SizeHandleRect::Bottom:
        dirName = "Bottom";
        delta.setBottom(local.y());
        break;
    case SizeHandleRect::LeftTop:
        dirName = "LeftTop";
        delta.setTopLeft(local.toPoint());
        break;
    case SizeHandleRect::Left:
        dirName = "Left";
        delta.setLeft(local.x());
        break;
    case SizeHandleRect::Top:
        dirName = "Top";
        delta.setTop(local.y());
        break;
   default:
        break;
    }

    prepareGeometryChange();

    delta.normalized();
    qreal fx = delta.width() / m_width;
    qreal fy = delta.height() / m_height;

    m_width = delta.width();
    m_height = delta.height();

    setTransform(transform().scale(fx,fy));

    qDebug()<<"resizeTo :"<<dirName
            <<"move:"<<local
            <<"newSize :"
            <<QSize(m_width,m_height)
            << "scale:" << fx
            << "," << fy;
    updateGeometry();

    */
}

void GraphicsItemGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

#if 0
    QPointF origin = mapFromScene(pos());

    QPointF origin1 = m_group->transformOriginPoint();

    QColor c1 = QColor(Qt::blue);
  //  c1.setAlpha(180);
    painter->setBrush(c1);
    painter->drawEllipse(origin.x() - 3 , origin.y() - 3 ,6,6);


    QColor c2 = QColor(Qt::green);
  //  c2.setAlpha(180);
    painter->setBrush(c2);
    painter->drawEllipse(origin1.x() - 3 , origin1.y() - 3 ,6,6);
#endif

}


GraphicsBezierCurve::GraphicsBezierCurve(QGraphicsItem *parent)
    :GraphicsItem(parent)
{

}

QRectF GraphicsBezierCurve::boundingRect() const
{
    return QRectF(0,0,0,0);
}

QPainterPath GraphicsBezierCurve::shape() const
{
    QPainterPath path ;
    return path;
}

void GraphicsBezierCurve::addPoint(const QPointF &point)
{

}

void GraphicsBezierCurve::resizeTo(SizeHandleRect::Direction dir, const QPointF &point)
{

}

void GraphicsBezierCurve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}


GraphicsBasicItem::GraphicsBasicItem(QGraphicsItem *parent)
    :QGraphicsObject(parent)
{

}

GraphicsBasicItem::GraphicsBasicItem(const QString &name, QGraphicsItem *parent)
    :QGraphicsObject(parent)
{

}

GraphicsBasicItem::~GraphicsBasicItem()
{

}


GridTool::GridTool(const QSize & grid , const QSize & space )
    :QGraphicsItem(NULL)
    ,m_sizeGrid(grid)
    ,m_sizeGridSpace(space)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, false);
}

QRectF GridTool::boundingRect() const
{


    return QRectF(-m_sizeGrid.width()/2,
                  -m_sizeGrid.height()/2,
                  m_sizeGrid.width(),
                  m_sizeGrid.height());
}

QPainterPath GridTool::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void GridTool::paintGrid(QPainter *painter, const QRect &rect)
{
    QColor c(Qt::lightGray);
    painter->setPen(c);
    QLineF linef[rect.width()/m_sizeGridSpace.width()];
    for (int x=rect.left() ;x < rect.right()  ;x+=(int)(m_sizeGridSpace.width()))
    {
          for(int j=0;j<rect.width()/m_sizeGridSpace.width();j++)
          {
              linef[j].setP1(QPointF(x,rect.top()));
              linef[j].setP2(QPointF(x,rect.bottom()));
          }
          painter->drawLines(linef,rect.width()/m_sizeGridSpace.width());
    }
      QLineF linef2[rect.height()/m_sizeGridSpace.height()] ;
      for (int y=rect.top();y<rect.bottom() ;y+=(int)(m_sizeGridSpace.height()))
      {
          for(int i=0;i<rect.height()/m_sizeGridSpace.height();i++)
          {
              linef2[i].setP1(QPointF(rect.left(),y));
              linef2[i].setP2(QPointF(rect.right(),y));
          }
          painter->drawLines(linef2,rect.height()/m_sizeGridSpace.height());
          //painter->drawLines(linef2,rect.height()/m_sizeGridSpace.height());
      }
}

void GridTool::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor c(Qt::darkCyan);
    painter->setPen(c);

    for (int x=boundingRect().left() ;x < boundingRect().right()  ;x+=(int)(m_sizeGridSpace.width())) {
        for (int y=boundingRect().top();y<boundingRect().bottom() ;y+=(int)(m_sizeGridSpace.height()))
        {
            painter->drawPoint(x,y);
        }
    }
}


GraphicsArcItem::GraphicsArcItem(QGraphicsItem *parent)
    :GraphicsLineItem(parent)
{
    // handles
    m_handles.reserve(SizeHandleRect::None);

    Handles::iterator hend =  m_handles.end();
    for (Handles::iterator it = m_handles.begin(); it != hend; ++it)
        delete (*it);
    m_handles.clear();

    SizeHandleRect *shr = new SizeHandleRect(this,SizeHandleRect::LeftTop, this);
    m_handles.push_back(shr);
    shr = new SizeHandleRect(this,SizeHandleRect::RightBottom, this);
    m_handles.push_back(shr);

    updateGeometry();
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->setAcceptHoverEvents(true);
}

QPainterPath GraphicsArcItem::shape() const
{
    qreal startAngle,endAngle;
    QPainterPath path;
   // qreal startAngle,endAngle;
    qreal len_y = m_localRect.bottomLeft().y() - m_localRect.center().y();
    qreal len_x = m_localRect.bottomLeft().x() - m_localRect.center().x();


    endAngle = atan2(len_y,len_x)*180/3.1416;

    if ( endAngle > 360 )
        endAngle -= 360;

    len_y = m_localRect.bottomRight().y() - m_localRect.center().y();
    len_x = m_localRect.bottomRight().x() - m_localRect.center().x();

    startAngle = atan2(len_y,len_x)*180/3.1416;

    if ( startAngle > 360 )
        startAngle -= 360;


    path.arcTo(m_localRect,30 * 16, 120*16);
    return path;
}

void GraphicsArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal startAngle,endAngle;
    qreal len_y = m_localRect.bottomLeft().y() - m_localRect.center().y();
    qreal len_x = m_localRect.bottomLeft().x() - m_localRect.center().x();

    endAngle = atan2(len_y,len_x)*180/3.1416;

    if ( endAngle > 360 )
        endAngle -= 360;

    len_y = m_localRect.bottomRight().y() - m_localRect.center().y();
    len_x = m_localRect.bottomRight().x() - m_localRect.center().x();

    startAngle = atan2(len_y,len_x)*180/3.1416;

    if ( startAngle > 360 )
        startAngle -= 360;

    painter->setPen(QPen(color,width));
    painter->setBrush(brush2);

   //painter->drawArc(m_localRect,30 * 16, 120*16);
    painter->drawChord(m_localRect,30 * 16, 120*16);
}


GraphicsPieItem::GraphicsPieItem(QGraphicsItem *parent)
    :GraphicsLineItem(parent)
{
    // handles
    m_handles.reserve(SizeHandleRect::None);

    Handles::iterator hend =  m_handles.end();
    for (Handles::iterator it = m_handles.begin(); it != hend; ++it)
        delete (*it);
    m_handles.clear();

    SizeHandleRect *shr = new SizeHandleRect(this,SizeHandleRect::LeftTop, this);
    m_handles.push_back(shr);
    shr = new SizeHandleRect(this,SizeHandleRect::RightBottom, this);
    m_handles.push_back(shr);

    updateGeometry();
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->setAcceptHoverEvents(true);
}

QPainterPath GraphicsPieItem::shape() const
{
    qreal startAngle,endAngle;
    QPainterPath path;
   // qreal startAngle,endAngle;
    qreal len_y = m_localRect.bottomLeft().y() - m_localRect.center().y();
    qreal len_x = m_localRect.bottomLeft().x() - m_localRect.center().x();


    endAngle = atan2(len_y,len_x)*180/3.1416;

    if ( endAngle > 360 )
        endAngle -= 360;

    len_y = m_localRect.bottomRight().y() - m_localRect.center().y();
    len_x = m_localRect.bottomRight().x() - m_localRect.center().x();

    startAngle = atan2(len_y,len_x)*180/3.1416;

    if ( startAngle > 360 )
        startAngle -= 360;


    path.arcTo(m_localRect,30 * 16, 120*16);
    return path;
}

void GraphicsPieItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal startAngle,endAngle;
    qreal len_y = m_localRect.bottomLeft().y() - m_localRect.center().y();
    qreal len_x = m_localRect.bottomLeft().x() - m_localRect.center().x();

    endAngle = atan2(len_y,len_x)*180/3.1416;

    if ( endAngle > 360 )
        endAngle -= 360;

    len_y = m_localRect.bottomRight().y() - m_localRect.center().y();
    len_x = m_localRect.bottomRight().x() - m_localRect.center().x();

    startAngle = atan2(len_y,len_x)*180/3.1416;

    if ( startAngle > 360 )
        startAngle -= 360;

    painter->setPen(QPen(color,width));
    painter->setBrush(brush2);

   //painter->drawArc(m_localRect,30 * 16, 120*16);
    painter->drawPie(m_localRect,30 * 16, 120*16);
}


