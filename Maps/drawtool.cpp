#include "drawtool.h"
#include "drawobj.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QtMath>

#define PI 3.14

QList<DrawTool*> DrawTool::c_tools;
QPointF DrawTool::c_down;
QPointF DrawTool::c_last;
quint32 DrawTool::c_nDownFlags;

DrawShape DrawTool::c_drawShape = selection;

static SelectTool selectTool;
static RectTool   lineTool(line);
static RectTool   rectTool(rectangle);
static RectTool   roundRectTool(roundrect);
static RectTool   ellipseTool(ellipse);
static RectTool   pietool(pie);
static RectTool   arcTool(arc);
static RotationTool rotationTool;

enum SelectMode
{
    none,
    netSelect,
    move,
    size,
    rotate
};

SelectMode selectMode = none;

SizeHandleRect::Direction nDragHandle = SizeHandleRect::None;

static void setCursor(QGraphicsScene * scene , const QCursor & cursor )
{
    QList<QGraphicsView*> views  = scene->views();
    if ( views.count() > 0 ){
        QGraphicsView * view = views.first();
        view->setCursor(cursor);
    }
}

DrawTool::DrawTool(DrawShape shape)
{
    m_drawShape = shape ;
    m_hoverSizer = false;
    c_tools.push_back(this);
}

void DrawTool::mousePressEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    c_down = event->scenePos();
    c_last = event->scenePos();
}

void DrawTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    c_last = event->scenePos();
}

void DrawTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    if (event->scenePos() == c_down)
        c_drawShape = selection;
    setCursor(scene,Qt::ArrowCursor);
}

void DrawTool::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{

}

DrawTool *DrawTool::findTool(DrawShape drawShape)
{
    QList<DrawTool*>::const_iterator iter = c_tools.constBegin();
    for ( ; iter != c_tools.constEnd() ; ++iter ){
        if ((*iter)->m_drawShape == drawShape )
            return (*iter);
    }
    return 0;
}


SelectTool::SelectTool()
    :DrawTool(selection)
{
    m_lastSize.setHeight(0);
    m_lastSize.setWidth(0);
    dashRect = 0;
}

void SelectTool::mousePressEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mousePressEvent(event,scene);

    QPointF itemPoint;

    if (!m_hoverSizer)
      scene->mouseEvent(event);

    selectMode = none;
    QList<QGraphicsItem *> items = scene->selectedItems();
    GraphicsItem *item = 0;

    if ( items.count() == 1 )
        item = qgraphicsitem_cast<GraphicsItem*>(items.first());

    if ( item != 0 ){

        nDragHandle = item->hitTest(event->scenePos());
        if ( nDragHandle !=SizeHandleRect::None)
             selectMode = size;
        else
            selectMode =  move;

        m_lastSize = item->boundingRect().size();
        itemPoint = item->mapFromScene(c_down);

    }


    if( selectMode == none ){
        selectMode = netSelect;
        QList<QGraphicsView*> views  = scene->views();
        if ( views.count() > 0 ){
            QGraphicsView * view = views.first();
            view->setDragMode(QGraphicsView::RubberBandDrag);
        }
    }


    if ( selectMode == move && items.count() == 1 ){

        if (dashRect ){
            scene->removeItem(dashRect);
            delete dashRect;
            dashRect = 0;
        }

        dashRect = new QGraphicsPathItem(item->shape());
        dashRect->setPen(Qt::DashLine);
        dashRect->setPos(item->pos());
        dashRect->setTransformOriginPoint(item->transformOriginPoint());
        dashRect->setTransform(item->transform());
        dashRect->setRotation(item->rotation());
        initialPositions = dashRect->pos();
        scene->addItem(dashRect);
    }
}

void SelectTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{

    DrawTool::mouseMoveEvent(event,scene);
    QList<QGraphicsItem *> items = scene->selectedItems();
    GraphicsItem * item = 0;
    if ( items.count() == 1 ){
        item = qgraphicsitem_cast<GraphicsItem*>(items.first());
        if ( item != 0 ){
            if ( nDragHandle != SizeHandleRect::None && selectMode == size ){
                QSizeF delta(c_last.x() - c_down.x() , c_last.y() - c_down.y());
                item->resizeTo(nDragHandle,c_last);
            }
            else if(nDragHandle == SizeHandleRect::None && selectMode == selection ){
                 SizeHandleRect::Direction handle = item->hitTest(event->scenePos());
                 if ( handle != SizeHandleRect::None){
                     setCursor(scene,item->getCursor(handle));
                     m_hoverSizer = true;
                 }else{
                     setCursor(scene,Qt::ArrowCursor);
                     m_hoverSizer = false;
                 }
             }
        }
    }
    if ( selectMode == move ){
        if ( dashRect ){
            dashRect->setPos(initialPositions + c_last - c_down);
        }
    }
    if ( selectMode != size  && items.count() > 1)
    {
        scene->mouseEvent(event);

    }

}

void SelectTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mouseReleaseEvent(event,scene);

    QList<QGraphicsItem *> items = scene->selectedItems();
    if ( items.count() == 1 ){
        GraphicsItem * item = qgraphicsitem_cast<GraphicsItem*>(items.first());
        if ( item != 0  && selectMode == move && c_last != c_down ){
             item->setPos(initialPositions + c_last - c_down);
             qDebug()<<"move to :" << item->mapFromScene(item->pos());
        }else if ( item !=0 && selectMode == size && c_last != c_down ){
            item->changeSize();
        }
    }

    if (selectMode == netSelect ){
        QList<QGraphicsView*> views  = scene->views();
        if ( views.count() > 0 ){
            QGraphicsView * view = views.first();
            view->setDragMode(QGraphicsView::NoDrag);
        }
    }

    if (dashRect ){
        scene->removeItem(dashRect);
        delete dashRect;
        dashRect = 0;
    }

    selectMode = none;
    nDragHandle = SizeHandleRect::None;
    m_hoverSizer = false;
    scene->mouseEvent(event);

}

RotationTool::RotationTool()
    :DrawTool(rotation)
{
    lastAngle == 0;
    dashRect = 0;
}

void RotationTool::mousePressEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mousePressEvent(event,scene);
    if (!m_hoverSizer)
      scene->mouseEvent(event);

    QList<QGraphicsItem *> items = scene->selectedItems();
    if ( items.count() == 1 ){
        GraphicsItem * item = qgraphicsitem_cast<GraphicsItem*>(items.first());
        if ( item != 0 ){
            nDragHandle = item->hitTest(event->scenePos());
            if ( nDragHandle !=SizeHandleRect::None)
            {
                QPointF origin = item->mapToScene(item->boundingRect().center());

                qreal len_y = c_last.y() - origin.y();
                qreal len_x = c_last.x() - origin.x();

                qreal angle = atan2(len_y,len_x)*180/PI;

                lastAngle = angle;
                selectMode = rotate;

                if (dashRect ){
                    scene->removeItem(dashRect);
                    delete dashRect;
                    dashRect = 0;
                }

                dashRect = new QGraphicsPathItem(item->shape());
                dashRect->setPen(Qt::DashLine);
                dashRect->setPos(item->pos());
                dashRect->setTransformOriginPoint(item->transformOriginPoint());
                dashRect->setTransform(item->transform());
                dashRect->setRotation(item->rotation());
                scene->addItem(dashRect);

                setCursor(scene,QCursor(QPixmap(":/image/rotation.png")));
            }
            else{
                    c_drawShape = selection;
                    selectTool.mousePressEvent(event,scene);
                }
        }
    }
}

void RotationTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mouseMoveEvent(event,scene);

    QList<QGraphicsItem *> items = scene->selectedItems();
    if ( items.count() == 1 ){
        GraphicsItem * item = qgraphicsitem_cast<GraphicsItem*>(items.first());
        if ( item != 0  && nDragHandle !=SizeHandleRect::None && selectMode == rotate ){


             QPointF origin = item->mapToScene(item->boundingRect().center());

             qreal len_y = c_last.y() - origin.y();
             qreal len_x = c_last.x() - origin.x();

             qreal angle = atan2(len_y,len_x)*180/PI;

             angle = item->rotation() + int(angle - lastAngle) ;

             if ( angle > 360 )
                 angle -= 360;

             if ( dashRect ){
                 dashRect->setRotation( angle );
             }

             setCursor(scene,QCursor(QPixmap(":/image/rotation.png")));
        }
        else if ( item )
        {
            SizeHandleRect::Direction handle = item->hitTest(event->scenePos());
            if ( handle != SizeHandleRect::None){
                setCursor(scene,QCursor(QPixmap(":/image/rotation.png")));
                m_hoverSizer = true;
            }else{
                setCursor(scene,Qt::ArrowCursor);
                m_hoverSizer = false;
            }
        }
    }
    scene->mouseEvent(event);
}

void RotationTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mouseReleaseEvent(event,scene);

    QList<QGraphicsItem *> items = scene->selectedItems();
    if ( items.count() == 1 ){
        GraphicsItem * item = qgraphicsitem_cast<GraphicsItem*>(items.first());
        if ( item != 0  && nDragHandle !=SizeHandleRect::None && selectMode == rotate ){

             QPointF origin = item->mapToScene(item->boundingRect().center());

             QPointF delta = c_last - origin ;
             qreal len_y = c_last.y() - origin.y();
             qreal len_x = c_last.x() - origin.x();
             qreal angle = atan2(len_y,len_x)*180/PI;
             angle = item->rotation() + int(angle - lastAngle) ;
             if ( angle > 360 )
                 angle -= 360;
             item->setRotation( angle );
        }
    }

    setCursor(scene,Qt::ArrowCursor);
    selectMode = none;
    nDragHandle = SizeHandleRect::None;
    lastAngle = 0;
    m_hoverSizer = false;
    if (dashRect ){
        scene->removeItem(dashRect);
        delete dashRect;
        dashRect = 0;
    }
    scene->mouseEvent(event);

}

RectTool::RectTool(DrawShape drawShape)
    :DrawTool(drawShape)
{
    item = 0;
}

void RectTool::mousePressEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mousePressEvent(event,scene);

    scene->clearSelection();
    switch ( c_drawShape ){

    case rectangle:
        item = new GraphicsRectItem(QRect(0,0,0,0),NULL);
        //item->setPen(Qt::NoPen);
        item->setPen(QPen(color,width));
       // item->setPen(Qpen(color,width));
        item->setBrush(brush2);
        //qDebug()<<"color:"<<<<endl<<"brush:"<<scene->bc.get_brush()<<endl;
        item->setMyShape(scene->bc.get_color(),scene->bc.get_brush(),scene->bc.get_width());
        break;
    case ellipse:
        item = new GraphicsEllipseItem(QRect(0,0,0,0),NULL);
        //item->setPen(Qt::NoPen);
        item->setPen(QPen(color,width));
        item->setBrush(brush2);
        item->setMyShape(scene->bc.get_color(),scene->bc.get_brush(),scene->bc.get_width());
        break;
    case line:
        item = new GraphicsLineItem(0);
      //  item->setPen(QPen(Qt::black,1));

        item->setPen(QPen(color,width));
        item->setBrush(brush2);
        item->setMyShape(scene->bc.get_color(),scene->bc.get_brush(),scene->bc.get_width());
        break;
    case arc:
        item = new GraphicsArcItem(0);
     //   item->setPen(QPen(Qt::black,1));
        item->setPen(QPen(color,width));
        item->setBrush(brush2);
        item->setMyShape(scene->bc.get_color(),scene->bc.get_brush(),scene->bc.get_width());
        break;
    case pie:
        item = new GraphicsPieItem(0);
     //   item->setPen(QPen(Qt::black,1));
        item->setPen(QPen(color,width));
        item->setBrush(brush2);
        item->setMyShape(scene->bc.get_color(),scene->bc.get_brush(),scene->bc.get_width());
        break;
    }
    if ( item == 0) return;
    item->setPos(event->scenePos());
    scene->addItem(item);
    item->setSelected(true);
    selectMode = size;
    nDragHandle = SizeHandleRect::RightBottom;

    scene->item_container.append(item);

}

void RectTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    setCursor(scene,Qt::CrossCursor);
    selectTool.mouseMoveEvent(event,scene);
}

void RectTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    if ( event->scenePos() == c_down ){

       if ( item != 0){
         item->setSelected(false);
         scene->removeItem(item);
         delete item ;
         item = 0;
       }
       selectTool.mousePressEvent(event,scene);
       qDebug()<<"RectTool removeItem:";
    }
    selectTool.mouseReleaseEvent(event,scene);
   // c_drawShape = selection;
}
