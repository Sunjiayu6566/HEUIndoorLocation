#ifndef LABELMANAGE_H
#define LABELMANAGE_H

#include <QWidget>

namespace Ui {
class labelmanage;
}

class labelmanage : public QWidget
{
    Q_OBJECT

public:
    explicit labelmanage(QWidget *parent = 0);
    ~labelmanage();

private:
    Ui::labelmanage *ui;
};

#endif // LABELMANAGE_H
