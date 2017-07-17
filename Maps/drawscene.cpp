#include "drawscene.h"
//#include<QGraphicsSceneMouseEvent>
//#include<QGraphicsRectItem>
//#include <QDebug>
DrawScene::DrawScene(QWidget *parent)
    :QGraphicsScene(parent)
{
    currentBrush = Qt::transparent;
    currentColor = Qt::black;
    currentWidth = 1;
}

void DrawScene::drawGridBackground(int width)
{


    QPolygonF myPolygon1;
    myPolygon1 << QPointF(0,width/2) << QPointF(width,width/2);
    QPolygonF myPolygon2;
    myPolygon2 << QPointF(width/2,0) << QPointF(width/2,width);
    QPixmap pixmap(width, width);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPen pen(Qt::lightGray,1);
/*
    QVector<qreal> dashes;//line style--虚线
    qreal space = 2;
    dashes << 2 << space << 2 <<space;
*/
  //  pen.setDashPattern(Qt::PenStyle(Qt::SolidLine));
    pen.setWidth(1);

    painter.setPen(pen);
    painter.translate(0, 0);
    painter.drawPolyline(myPolygon1);
    painter.drawPolyline(myPolygon2);
    this->setBackgroundBrush(pixmap);
}
void DrawScene::mouseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch( mouseEvent->type() ){
    case QEvent::GraphicsSceneMousePress:
        QGraphicsScene::mousePressEvent(mouseEvent);
        break;
    case QEvent::GraphicsSceneMouseMove:
        QGraphicsScene::mouseMoveEvent(mouseEvent);
        break;
    case QEvent::GraphicsSceneMouseRelease:
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
        break;
    }
}


void DrawScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    BrushAndColor *shape=new BrushAndColor();
    DrawTool * tool = DrawTool::findTool( DrawTool::c_drawShape );
    shape->set(currentColor, currentBrush, currentWidth);
    this->bc = *shape;
    if ( tool )
        tool->mousePressEvent(mouseEvent,this);

}

void DrawScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    BrushAndColor *shape=new BrushAndColor();
    DrawTool * tool = DrawTool::findTool( DrawTool::c_drawShape );
     // qDebug()<<"color:"<<currentColor<<endl<<"brush:"<<currentBrush<<endl;
    shape->set(currentColor, currentBrush, currentWidth);
    this->bc = *shape;
    if ( tool )
        tool->mouseMoveEvent(mouseEvent,this);
   ;
}

void DrawScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    DrawTool * tool = DrawTool::findTool( DrawTool::c_drawShape );
    if ( tool )
        tool->mouseReleaseEvent(mouseEvent,this);
}


void DrawScene :: set_brush(QColor c)
{
    int tmp;
    int a;
    //currentBrush.getRgb(&tmp, &tmp, &tmp, &a);
    qDebug()<<"set_brush:"<<c<<endl;
    currentBrush = c;

   // currentBrush.setAlpha(a);
}

void DrawScene::set_color(QColor c)
{
    currentColor = c;
}

void DrawScene::set_width(int w)
{
    currentWidth = w;
}

void DrawScene::set_alpha(int a)
{
    currentBrush.setAlpha((100 - a) * 255 / 100);
}

void DrawScene::set_straight(bool c)
{
    is_straight = c;
}

void DrawScene :: save_file()
{

    if (currentPath.isEmpty())
    {
        QString s = QFileDialog::getSaveFileName(0, "Select A File", "/", "Txt File(*.txt)");
        currentPath = s;
    }
    else
    {
        QMessageBox::information(0, tr("Information"), tr("Save Successful!"));
    }
    int r1, r2, g1, g2, b1, b2, a1, a2;
    qDebug()<<"ad"<<endl;
    QFile file(currentPath);
    if (file.open(QFile::WriteOnly))
    {
        QTextStream cout(&file);
        foreach( GraphicsItem* item, item_container)
        {
           // 65536是UserType的第一个数

           if(item->type()>65536)
            {
                qDebug()<<"zheshige    "<<item->type()<<"   "<<item->x()<<item->y();
                if(item->get_typeid()==1)
                {
                qDebug()<<"jiaodu    "<<item->rotation();
                cout<< item->get_typeid()<<"  ";             //保存图元的种类
                cout<<item_container.indexOf(item)<<"  ";
                cout<<item->x()<<"  "<<item->y()<<"  "
                 <<item->rect().width()<<"  "<<item->rect().height()<<"  "
                 <<item->rotation()<<"  ";
                //保存图元的位置信息
                item->getitemcolor().getRgb(&r1,&g1,&b1,&a1);
                item->getitembrush().getRgb(&r2,&g2,&b2,&a2);

                cout <<r1<<" "<<g1<<" "<<b1<<" "<<a1<<" "
                     <<r2<<" "<<g2<<" "<<b2<<" "<<a2<<" "
                     << item->getitemwidth() <<"\r\n"<< endl;    //保存图元的画笔颜色，画刷颜色，画笔线宽
                }

                else if(item->get_typeid()==2)
                {
                    cout<< item->get_typeid()<<"  ";             //保存图元的种类
                     cout<<item_container.indexOf(item)<<"  ";
                    cout<<item->x()<<"  "<<item->y()<<"  "
                       <<item->rect().width()<<"  "<<item->rect().height()<<"  "
                      <<item->rotation()<<"  ";
                    //保存图元的位置信息
                    item->getitemcolor().getRgb(&r1,&g1,&b1,&a1);
                    item->getitembrush().getRgb(&r2,&g2,&b2,&a2);

                    cout <<r1<<" "<<g1<<" "<<b1<<" "<<a1<<" "
                         <<r2<<" "<<g2<<" "<<b2<<" "<<a2<<" "
                         << item->getitemwidth() <<"\r\n"<< endl;    //保存图元的画笔颜色，画刷颜色，画笔线宽

                }
                else if(item->get_typeid()==3)
                {
                    cout<< item->get_typeid()<<"  ";             //保存图元的种类
                     cout<<item_container.indexOf(item)<<"  ";
                    cout<<item->x()<<"  "<<item->y()<<"  "
                     <<item->rect().width()<<"  "<<item->rect().height()<<"  "
                     <<item->rotation()<<"  ";
                    //保存图元的位置信息
                    item->getitemcolor().getRgb(&r1,&g1,&b1,&a1);
                    item->getitembrush().getRgb(&r2,&g2,&b2,&a2);

                    cout <<r1<<" "<<g1<<" "<<b1<<" "<<a1<<" "
                         <<r2<<" "<<g2<<" "<<b2<<" "<<a2<<" "
                         << item->getitemwidth() <<"\r\n"<< endl;    //保存图元的画笔颜色，画刷颜色，画笔线宽
                }
                else if(item->get_typeid()==4)
                {
                    cout<< item->get_typeid()<<"  ";             //保存图元的种类
                     cout<<item_container.indexOf(item)<<"  ";
                    cout<<item->x()<<"  "<<item->y()<<"  "
                       <<item->rect().width()<<"  "<<item->rect().height()<<"  "
                      <<item->rotation()<<"  ";
                    //保存图元的位置信息
                    item->getitemcolor().getRgb(&r1,&g1,&b1,&a1);
                    item->getitembrush().getRgb(&r2,&g2,&b2,&a2);

                    cout <<r1<<" "<<g1<<" "<<b1<<" "<<a1<<" "
                         <<r2<<" "<<g2<<" "<<b2<<" "<<a2<<" "
                         << item->getitemwidth() <<"\r\n"<< endl;    //保存图元的画笔颜色，画刷颜色，画笔线宽
                }
                else if(item->get_typeid()==5)
                {
                    cout<< item->get_typeid()<<"  ";             //保存图元的种类
                     cout<<item_container.indexOf(item)<<"  ";
                    cout<<item->x()<<"  "<<item->y()<<"  "
                       <<item->rect().width()<<"  "<<item->rect().height()<<"  "
                      <<item->rotation()<<"  ";
                    //保存图元的位置信息
                    item->getitemcolor().getRgb(&r1,&g1,&b1,&a1);
                    item->getitembrush().getRgb(&r2,&g2,&b2,&a2);

                    cout <<r1<<" "<<g1<<" "<<b1<<" "<<a1<<" "
                         <<r2<<" "<<g2<<" "<<b2<<" "<<a2<<" "
                         << item->getitemwidth() <<"\r\n"<< endl;    //保存图元的画笔颜色，画刷颜色，画笔线宽
                }
            }
        }
    }
    file.close();
}

void DrawScene :: open_file()
{
    QString s = QFileDialog::getOpenFileName(0, "Select A File", "/", "Txt File(*.txt)");
    if (s.isEmpty())
    {
        QMessageBox::information(0, tr("INformation"), tr("Open failed!"));
        return;
    }
    int st = 0;
    int id;
    float x1,y1,a,b,angle;
    int r1, r2, g1, g2, a1, a2, b1, b2;
    int width;
    currentPath = s;
    QFile file(currentPath);
    if (file.open(QFile::ReadOnly))
    {
        QTextStream cin(&file);
        while(!cin.atEnd())
        {
          //  st = 0;       //st用以保存图元的类型
            cin >>st>>id;
            GraphicsItem *item;
            if (st == 0)
                break;
            if (st == 3)   //如果是线的话
            {
                //float x2,y2;
               // cin>>x1>>y1>>x2>>y2>>a>>b>>r1>>g1>>b1>>a1>>r2>>g2>>b2>>a2>>width;
                cin>>x1>>y1>>a>>b>>angle>>r1>>g1>>b1>>a1>>r2>>g2>>b2>>a2>>width;
                qDebug()<<"WHY"<<x1<<" "<<y1<<"  "<<a<<"  "<<b;
                item = new GraphicsLineItem(0);
                item->setX(x1);
                item->setY(y1);
                item->setPen(QPen(QColor(r1, g1, b1, a1),width));
                item->setBrush( QColor(r2, g2, b2, a2));
                item->setMyShape(QColor(r1, g1, b1, a1), QColor(r2, g2, b2, a2), width);
                item->resizeTo(SizeHandleRect::LeftTop,QPointF(x1-a/2,y1-b/2));
                item->resizeTo( SizeHandleRect::RightBottom,QPointF(x1+a/2,y1+b/2));
                item->setRotation(angle);
                this->addItem(item);
                item_container.append(item);
                item_container.at(id);
                continue;
            }
            else
                cin>>x1>>y1>>a>>b>>angle>>r1>>g1>>b1>>a1>>r2>>g2>>b2>>a2>>width;

            switch(st)
            {
            case 1:
                qDebug()<<"GraphicsRectItem"<<x1<<" "<<y1<<"  "<<a<<"  "<<b;
                item=new GraphicsRectItem(QRect(0,0,0,0),NULL);
                break;
            case 2:
                qDebug()<<"GraphicsEllipseItem"<<x1<<" "<<y1<<"  "<<a<<"  "<<b;
                item =new GraphicsEllipseItem(QRect(0,0,0,0),NULL);
//                item->setX(x1);
//                item->setY(y1);
//                rect.setWidth(a);
//                rect.setHeight(b);
//                item->rect()=rect;
                break;
            case 4:
                qDebug()<<"GraphicsArcItem"<<x1<<" "<<y1<<"  "<<a<<"  "<<b;
                item= new GraphicsArcItem(0);
                break;
            case 5:
                item=new GraphicsPieItem(0);
                break;
            }
            item->setX(x1);
            item->setY(y1);
            item->setPen(QPen(QColor(r1, g1, b1, a1),width));
            item->setBrush( QColor(r2, g2, b2, a2));
            item->setMyShape(QColor(r1, g1, b1, a1), QColor(r2, g2, b2, a2), width);
            item->resizeTo(SizeHandleRect::LeftTop,QPointF(x1-a/2,y1-b/2));
            item->resizeTo( SizeHandleRect::RightBottom,QPointF(x1+a/2,y1+b/2));
            item->setRotation(angle);
            this->addItem(item);
            item_container.append(item);
            item_container.at(id);
        }
    }
    file.close();
}




