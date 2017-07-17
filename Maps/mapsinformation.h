#ifndef MAPSINFORMATION_H
#define MAPSINFORMATION_H

#include <QWidget>

namespace Ui {
class Mapsinformation;
}

class Mapsinformation : public QWidget
{
    Q_OBJECT

public:
    explicit Mapsinformation(QWidget *parent = 0);
    ~Mapsinformation();

private:
    Ui::Mapsinformation *ui;
};

#endif // MAPSINFORMATION_H
