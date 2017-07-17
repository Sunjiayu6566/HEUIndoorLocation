#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include "mapsmanage.h"
#include "mapsinformation.h"
#include "DaoHang/colordefines.h"
#include "DaoHang/message.h"
#include "DaoHang/navdelegate.h"
#include "DaoHang/naviview.h"
#include "DaoHang/navmodel.h"
#include "DaoHang/dhpushbutton.h"
#include <QStackedWidget>




namespace Ui {
class Mapwidget;
}

class Mapwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Mapwidget(QWidget *parent = 0);
    ~Mapwidget();
   // void setupModel();

public slots:
    void switchPage();
    void setNav();

private:
    Ui::Mapwidget *ui;

    MapsManage *maps_manage;
    Mapsinformation *maps_infor;

    QStackedWidget *m_stackedwidget;
    QStandardItemModel *model;
    //QAction *openAct;

    QStackedWidget *stack;
    NaviView * m_naviView;
    DHPushButton * m_navBtn;
    int m_status;
};

#endif // MAPWIDGET_H




// //////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////
