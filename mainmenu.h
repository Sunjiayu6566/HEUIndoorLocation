#ifndef MAINMENU_H
#define MAINMENU_H


#include <QMenu>

class MainMenu : public QMenu
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);

    void translateActions();

signals:
    void showLocationInterface();
    void showDataTrans();
    void showFilterSet();
    void showLogs();
    void showAboutUs();

private:
    void createActions();

private:

    QAction *action_location;  //定位接口
    QAction *action_data;      //数据转发
    QAction *action_filter;    //过滤器参数及设置
    QAction *action_logs;      //日志
    QAction *action_aboutus;   //关于我们

};

#endif // MAINMENU_H
