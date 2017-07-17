#ifndef CAMERAMANAGE_H
#define CAMERAMANAGE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>


namespace Ui {
class CameraManage;
}

class CameraManage : public QWidget
{
    Q_OBJECT

public:
    explicit CameraManage(QWidget *parent = 0);
    ~CameraManage();
    void setupModel();

private:
    Ui::CameraManage *ui;
    QPushButton *biaogeshanchu;
    QPushButton *biaogegengxin;
    QPushButton *biaogecharu;
    QPushButton *biaogeFP;
    QPushButton *biaogeNP;
    QPushButton *biaogePP;
    QPushButton *biaogeLP;
    QStandardItemModel *model;
};

#endif // CAMERAMANAGE_H
