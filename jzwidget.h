#ifndef JZWIDGET_H
#define JZWIDGET_H

#include <QWidget>
#include <QPushButton>
#include"basemodel.h"
#include<QTableView>

namespace Ui {
class JzWidget;
}

class JzWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JzWidget(QWidget *parent = 0);
    ~JzWidget();
    void setupModel();
private:
    Ui::JzWidget *ui;
public slots:
    void deleteBaseItem();
    void addBaseItem();
    void freshBaseItem();
private:
    QPushButton *addBase;
    QPushButton *deleteBase;
    QPushButton *freshBase;
    BaseModel   *baseModel;
    QTableView  *baseTable;
    QPushButton *nextPage;
    QPushButton *prePage;

};

#endif // JZWIDGET_H
