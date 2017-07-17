#ifndef BQWIDGET_H
#define BQWIDGET_H

#include <QWidget>
#include "cameralinkage.h"
#include "cameramanage.h"
#include "DaoHang/colordefines.h"
#include "DaoHang/message.h"
#include "DaoHang/navdelegate.h"
#include "DaoHang/naviview.h"
#include "DaoHang/navmodel.h"
#include "DaoHang/dhpushbutton.h"
#include <QStackedWidget>

namespace Ui {
class BqWidget;
}

class BqWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BqWidget(QWidget *parent = 0);
    ~BqWidget();
public slots:
    void switchPage();
    void setNav();

private:
    Ui::BqWidget *ui;

    CameraLinkage *camera_linkage;
    CameraManage *camera_manage;

    QStackedWidget *m_stackedwidget;
    QStandardItemModel *model;
    //QAction *openAct;

    QStackedWidget *stack;
    NaviView * m_naviView;
    DHPushButton * m_navBtn;
    int m_status;
};

#endif // BQWIDGET_H
