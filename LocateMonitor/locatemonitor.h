#ifndef LOCATEMONITOR_H
#define LOCATEMONITOR_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "indexwidget.h"
#include "lomowidget.h"

namespace Ui {
class LocateMonitor;
}

class LocateMonitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit LocateMonitor(QWidget *parent = 0);
    ~LocateMonitor();

private:
    Ui::LocateMonitor *ui;

    IndexWidget *indexwidget;
    LoMoWidget *lomowidget;
};

#endif // LOCATEMONITOR_H
