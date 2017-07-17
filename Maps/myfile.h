#ifndef MYFILE_H
#define MYFILE_H

#include <QString>
#include <QTextStream>
#define max1 100
class MyFile
{
public:
    MyFile();
    void readFile(QString filename);
    void writeFile(QString filename);
    QString* getBuffer();
    int getRow();
private:
QString  m_buffer[max1];
int m_row;
};

#endif // MYFILE_H
