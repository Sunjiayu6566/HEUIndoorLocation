#ifndef USERPATH_H
#define USERPATH_H

#include <QWidget>
#include <QLabel>
#include <QWidget>
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include "basestation/formtitle.h"
#define MARGIN 8

struct userPoint{
    int start;
    int end;
};

class userPath : public QWidget
{
    Q_OBJECT
public:
    explicit userPath(QWidget *parent = 0);
    int countFlag(QPoint p,int row);
    void setCursorType(int flag);
    int countRow(QPoint P);
    ~userPath();
signals:
    void userPointSignal(userPoint&);

public slots:
    void combine();
protected:
    void mousePressEvent(QMouseEvent *eve);
    void mouseReleaseEvent(QMouseEvent *eve);
   // void mouseDoubleClickEvent(QMouseEvent *eve);
    void mouseMoveEvent(QMouseEvent *eve);
private:
    QFormLayout *formlayout;
    QLineEdit *startEdit;
    QLineEdit *endEdit;
    QPushButton *chk_btn;
    QPushButton *can_btn;
    QGridLayout *gridlayout;
    QHBoxLayout *hor_layout;
    QVBoxLayout *mainlayout;
    QWidget *widget_1;
    QWidget *widget_2;
    QScrollArea *scrollArea;
    FormTitle *title;

    bool isLeftPressed;
    int curPos;
    QPoint pLast;

    userPoint m_userPoint;

};

#endif // USERPATH_H
