#ifndef LABELINFORMATION_H
#define LABELINFORMATION_H

#include <QWidget>

namespace Ui {
class labelinformation;
}

class labelinformation : public QWidget
{
    Q_OBJECT

public:
    explicit labelinformation(QWidget *parent = 0);
    ~labelinformation();

private:
    Ui::labelinformation *ui;
};

#endif // LABELINFORMATION_H
