#ifndef FILTERSET_H
#define FILTERSET_H

#include <QMainWindow>
#include <QListView>
#include <QTableView>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QLabel>

namespace Ui {
class FilterSet;
}

class FilterSet : public QMainWindow
{
    Q_OBJECT

public:
    explicit FilterSet(QWidget *parent = 0);
    ~FilterSet();

private:
    Ui::FilterSet *ui;

    QLabel *systemset;
    QToolButton *reset;
    QToolButton *fresh;

    QListView *list1;
    QTableView *table1;
    QWidget *widget1;


};

#endif // FILTERSET_H
