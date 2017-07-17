#include "myfile.h"
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
MyFile::MyFile()
{
m_row = 0;
}


void MyFile::readFile(QString fileName){
     QFile file(fileName);
     if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
        //QMessageBox::warning(this,"Warning","can't open",QMessageBox::Yes);
        qDebug() << "open failed";
     }
     QTextStream in(&file);//读取一行//如果读取多行
     while (!in.atEnd()) {
        m_buffer[m_row++] = in.readLine();
   }
}
void MyFile::writeFile(QString fileName){

     QString str="CSDN";
     QFile file(fileName);
     if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
     {
         qDebug() << "open failed";
        //QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);

     }

      QTextStream in(&file);
      in<<str<<"\n";//如果写多行，同上循环即可
      file.close();

}


 QString* MyFile::getBuffer(){
     return m_buffer;
 }

 int MyFile::getRow(){
     return m_row;
 }



