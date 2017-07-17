#ifndef MAPDRAWING_H
#define MAPDRAWING_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QActionGroup>
#include <QColorDialog>
#include <QMenu>
#include <QSlider>
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QToolBar>
#include <Typeinfo>
#include <QDial>
#include <QLabel>
#include <QTimer>
#include "drawscene.h"
#include "drawtool.h"
#include "drawtool.h"

#include "myfile.h"
#include "dijkstrafindpath.h"
#include "route.h"
#include "moveitem.h"
#include "newroute.h"
#include "userpath.h"
//#include "backgroundstyle.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QMenu;
class QPlainTextEdit;
QT_END_NAMESPACE

class GridTool;
namespace Ui {
class MapDrawing;
}

class MapDrawing : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapDrawing(QWidget *parent = 0);
    ~MapDrawing();
    void wheelEvent(QWheelEvent*event);
    void keyPressEvent(QKeyEvent *);    //键盘事件
    void keyReleaseEvent(QKeyEvent *);  //键盘事件

    void initToolBar();
    void getMapPath(int beginId,int endId);
    void move();

    struct pathData{
        int beginId;
        int endId;
    };

signals:
    void color_change(QColor);          //属性调整信号
    void brush_change(QColor);
    void change_straight(bool);
    void pathdata(pathData& data);

public slots:
    void addShape() ;
    void updateUI();

 //   void openFile(const QString &path = QString()); // 打开文件槽
 //   void setRenderer(QAction *action);              // 设置renderer槽
//    void addbackground();
 //   void deletebackground();


private slots:

    void on_actionBringToFront_triggered();

    void on_actionSendToBack_triggered();

    void on_actionDelete_triggered();

private:
    Ui::MapDrawing *ui;
    //QActions
    QActionGroup *shapeGroup;
    QAction *pie_act;
    QAction *open_act;
    QAction *save_act;
    QAction *select_act;
    QAction *delete_act;
    QAction *line_act;
    QAction *bezier_act;
    QAction *circle_act;
    QAction *rect_act;
    QAction *bringtofont_act;
    QAction *sendtoback_act;
    QAction *rotation_act;
    QAction *brush_act;
    QAction *color_act;
    QAction *back_act;
    // Actions end
    QAction *drawPath_act;

    DrawScene * m_scene;
    QTimer      m_timer;
    QString     path;

    QLabel *widthLabel;     //显示当前线条大小
   // QDial *widthDial;
    QLabel *alphaLabel;     //显示当前透明度
   // QDial *alphaDial;

    QSlider *slider1;
    QSlider *slider2;
   // QString currentPath;

    QAction *m_nativeAction;                    //用于菜单项的动作
    QAction *m_glAction;
    QAction *m_imageAction;
    QAction *m_highQualityAntialiasingAction;
 //   QAction *m_backgroundAction;
 //   QAction *m_outlineAction;

   // MapGraphicsView *view;
    // MainWindow中心的View部件

    QGraphicsView *view;
    QString m_currentPath;                      // open file时的路径

    QVector<QPoint> m_allpoints;
    QVector<QPoint> m_pathpoints;
    DijkstraFindPath *findPath;
    Route * m_route;
    MoveItem *m_moveball;
    pathData m_pathdata;
    newRoute *m_newroute;
    userPath *m_userPath;
private slots:
    void change_widthLabel(int);        ///改变属性的槽
    void change_alphaLabel(int);
    void color_SLOT();
    void brush_SLOT();
    void drawPath(userPoint &data);
    void addWin();


};

#endif // MAPDRAWING_H
