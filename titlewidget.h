#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>

#include "push_button.h"
#include "tool_button.h"

class QLabel;
class titlewidget : public QWidget
{
    Q_OBJECT
public:
    explicit titlewidget(QWidget *parent = 0);
   // void translateLanguage();

signals:
    void showMin();
    void showMax();
    void showMainMenu();
    void closeWidget();
    void showWarnings();

    void showDwwidget();
    void showBqwidget();
    void showJzwidget();
    void showKqwidget();
    void showTrueBqwidget();
    void showMapwidget();
    void showElecWidget();

public slots:
    void turnPage(QString current_page);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

private:
    QPoint press_point;//鼠标按下去的点
    bool is_move;

    QLabel *version_title; //标题
    PushButton *warning_button; //警告通知
   // PushButton *skin_button; //换肤
    PushButton *main_menu_button; //主菜单
    PushButton *min_button;//minwindow
    PushButton *max_button; //最大化
    PushButton *close_button; //关闭

    QList<ToolButton *> button_list;
};

#endif // TITLEWIDGET_H
