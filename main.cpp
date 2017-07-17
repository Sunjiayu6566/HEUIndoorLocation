#include "main_widget.h"
#include <QApplication>
#include "style.h"
//#include<QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Style::setStyle(":/new/style.qss");

    main_widget main;
    main.show();
   // QTextCodec *codec = QTextCodec::codecForName("GB2312");
  //  QTextCodec::setCodecForLocale(codec);
   // QTextCodec::setCodecForCStrings(codec);
   // QTextCodec::setCodecForTr(codec);
    return a.exec();
}

