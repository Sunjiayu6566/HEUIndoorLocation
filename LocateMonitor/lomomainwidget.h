#ifndef LOMOMAINWIDGET_H
#define LOMOMAINWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "indexwidget.h"
#include "lomowidget.h"

namespace Ui {
class LoMoMainWidget;
}

class LoMoMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoMoMainWidget(QWidget *parent = 0);
    ~LoMoMainWidget();

private:
    Ui::LoMoMainWidget *ui;
    IndexWidget *indexwidget;
    LoMoWidget *lomowidget;
};

#endif // LOMOMAINWIDGET_H
