#ifndef DRAWSCENE
#define DRAWSCENE

#include <QGraphicsScene>
#include <QWidget>
#include <QBrush>
#include <QPen>
#include <Qpainter>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QDebug>

#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

#include <QMenu>
#include <QPointF>
#include <QGraphicsLineItem>
#include <QFont>
#include <QGraphicsTextItem>
#include <QColor>

#include <QPaintEvent>
#include <QGraphicsPolygonItem>
#include "brushandcolor.h"
#include "drawtool.h"
#include "drawobj.h"
//QT_BEGIN_NAMESPACE
//class QGraphicsSceneMoveEvent;
//class QMenu;
//class QPointF;
//class QGraphicsLineItem;
//class QFont;
//class QGraphicsTextItem;
//class QColor;
//class QObject;
//QT_END_NAMESPACE

class GridTool;
class GraphicsItem;
class DrawScene : public QGraphicsScene
{
        Q_OBJECT
public:
    DrawScene(QWidget *parent = 0);
    BrushAndColor bc;
    QList<GraphicsItem* > item_container;
    QList<QGraphicsPolygonItem* > poly_container;
public:
    void mouseEvent(QGraphicsSceneMouseEvent *mouseEvent );
    void drawGridBackground(int width = 50);

public slots:
    void set_color(QColor);
    void set_brush(QColor);
    void set_width(int);
    void set_alpha(int);
    //void removebackground();
    //void drawBackground(QPainter * painter, const QRectF & rect);
    //void Background();
    //void OpenFile(const QString &path);
   // bool setflag();
    void save_file();
    void open_file();


     void set_straight(bool);

protected:



    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    //void drawBackground(QPainter * painter, const QRectF & rect) Q_DECL_OVERRIDE;


private:
   // DrawScene *drawscene;
    QColor currentColor;
    QColor currentBrush;
    int currentWidth;

    QString currentPath;
    //BrushAndColor *shape;
    GridTool *m_grid;

    bool is_straight;
    bool flag;

  //  QString currentPath;

};

#endif // DRAWSCENE
