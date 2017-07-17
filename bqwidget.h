#ifndef BQWIDGET_H
#define BQWIDGET_H
#include <QPushButton>
#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QFileDialog>

namespace Ui {
class BqWidget;
}

class BqWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BqWidget(QWidget *parent = 0);
    ~BqWidget();
    //void createAction();
    void setupModel();
   // void setupView();
    //void openFile(QString);
//public slots:
//    void slotOpen();


private:
    Ui::BqWidget *ui;
    //以下为lab_1按钮
    QPushButton *xuanze;
    QPushButton *shanchu;
    QPushButton *tianjia;
    QPushButton *firstpage;
    QPushButton *nextpage;
    QPushButton *prepage;
    QPushButton *lastpage;
    //END
    //以下为lab_2按钮
    QPushButton *biaogeshanchu;
    QPushButton *biaogegengxin;
    QPushButton *biaogecharu;


    QPushButton *biaogeFP;
    QPushButton *biaogeNP;
    QPushButton *biaogePP;
    QPushButton *biaogeLP;

    //END


    QStandardItemModel *model;
    //QAction *openAct;
};

#endif // BQWIDGET_H
