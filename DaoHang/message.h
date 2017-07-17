#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>
#include <QLineEdit>
class Message : public QWidget
{
    Q_OBJECT
public:
    explicit Message(QWidget *parent = 0);

signals:

public slots:
private:
    QLineEdit * m_line;
};

#endif // MESSAGE_H
