#ifndef FORMTITLE_H
#define FORMTITLE_H

#include <QWidget>
#include <QLabel>
#include <QStyle>
#include <QStyleOption>
#include "push_button.h"
#include "tool_button.h"

class QLabel;

class FormTitle : public QWidget
{
    Q_OBJECT
public:
    explicit FormTitle(QWidget* parent,QString str);
    ~FormTitle();

signals:
    void showMin();
    void closeWidget();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    QPoint press_point;
    bool is_move;

    PushButton *min_button;
    PushButton *close_button;
    QLabel *version_title;
};

#endif // FORMTITLE_H
