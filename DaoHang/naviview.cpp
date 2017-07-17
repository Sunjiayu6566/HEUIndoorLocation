#include "naviview.h"
#include "colordefines.h"
#include <QMouseEvent>
#include <QRect>
#include <QPoint>
#include <QApplication>
#include <QDesktopWidget>
NaviView::NaviView(QWidget *parent)
    : QListView(parent)
{
    //this->resize(parent->height(),parent->width()/4);
    setStyleSheet(
        QString(
        "QListView{background-color:%1;"
        "border:0px solid %2;"
        "border-right-width:1px;}")
        .arg(ColorToString(color_child_normal))
        .arg(ColorToString(color_line)));
    this->setVisible(true);
}

NaviView::~NaviView()
{

}




