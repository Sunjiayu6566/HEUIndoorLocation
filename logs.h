#ifndef LOGS_H
#define LOGS_H

#include <QMainWindow>
#include <QLabel>
#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class Logs;
}

class Logs : public QMainWindow
{
    Q_OBJECT

public:
    explicit Logs(QWidget *parent = 0);
    ~Logs();

private:
    Ui::Logs *ui;

    QLabel *productname;
    QLabel *version;
    QLabel *heu;

    QTableView *table1;
};

#endif // LOGS_H
