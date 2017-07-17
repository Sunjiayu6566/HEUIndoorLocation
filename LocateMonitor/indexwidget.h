#ifndef INDEXWIDGET_H
#define INDEXWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QHBoxLayout>


namespace Ui {
class IndexWidget;
}

class IndexWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IndexWidget(QWidget *parent = 0);
    ~IndexWidget();

signals:

    void LocateMonitor();     //定位监控
    void SensorStatus();      //传感器状态
    void LabelStatus();       //标签状态
    void FilterAndParameter();//过滤器及参数
    void SensorCalibrate();   //传感器校准
    void Logs();              //日志

private:
    Ui::IndexWidget *ui;
    QToolButton *button1;
    QToolButton *button2;
    QToolButton *button3;
    QToolButton *button4;
    QToolButton *button5;
    QToolButton *button6;


};

#endif // INDEXWIDGET_H
