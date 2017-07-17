#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include "naviview.h"
#include <QStackedWidget>
#include "dhpushbutton.h"
class centralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit centralWidget(QWidget *parent = 0);

signals:

public slots:
    void switchPage();
    void setNav();
private:
    QStackedWidget *m_stackWidget;
    NaviView * m_naviView;
    DHPushButton * m_navBtn;
    int m_status;
};

#endif // CENTRALWIDGET_H
