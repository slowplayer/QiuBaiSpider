#include "widget.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec=QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
    Widget w;
  //  w.setLayout(ui->verticalLayout);
    w.show();

    return a.exec();
}
