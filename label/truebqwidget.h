#ifndef TRUEBQWIDGET_H
#define TRUEBQWIDGET_H

#include <QWidget>
#include "labelmanage.h"
#include "labelinformation.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "DaoHang/colordefines.h"
#include "DaoHang/message.h"
#include "DaoHang/navdelegate.h"
#include "DaoHang/naviview.h"
#include "DaoHang/navmodel.h"
#include "DaoHang/dhpushbutton.h"
#include <QStackedWidget>

namespace Ui {
class TrueBqWidget;
}

class TrueBqWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrueBqWidget(QWidget *parent = 0);
    ~TrueBqWidget();

public slots:
    void switchPage();
    void setNav();

private:
    Ui::TrueBqWidget *ui;

    labelmanage *label_mange;
    labelinformation *label_infor;

    QStackedWidget *m_stackedwidget;
    //QAction *openAct;

    QStackedWidget *stack;
    NaviView * m_naviView;
    DHPushButton * m_navBtn;
    int m_status;
};

#endif // TRUEBQWIDGET_H
