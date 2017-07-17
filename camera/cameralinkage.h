#ifndef CAMERALINKAGE_H
#define CAMERALINKAGE_H

#include <QWidget>
#include <QPushButton>
#include <QListView>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class CameraLinkage;
}

class CameraLinkage : public QWidget
{
    Q_OBJECT

public:
    explicit CameraLinkage(QWidget *parent = 0);
    ~CameraLinkage();

private:
    Ui::CameraLinkage *ui;
    QPushButton *xuanze;
    QPushButton *shanchu;
    QPushButton *tianjia;
    QPushButton *firstpage;
    QPushButton *nextpage;
    QPushButton *prepage;
    QPushButton *lastpage;
};

#endif // CAMERALINKAGE_H
