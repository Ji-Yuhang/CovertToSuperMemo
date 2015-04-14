#include "mainwindow.h"
#include <QApplication>
#include "util.hxx"
#include "shanbay.hxx"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Shanbay shanbay;    // singleton
    MainWindow w;
    w.show();

    QString fromFile;// = "/home/jiyuhang/myjianguoyun/nce/one.txt";
    QString toFile = "out.txt";
    QStringList argus = QApplication::arguments();
    if (argus.size() >= 2) {
        fromFile = argus[1];
    }
    if (argus.size() >= 3) {
        toFile = argus[2];

    }
//    if (!fromFile.isEmpty()) Util::covertToSuperMemo(fromFile, toFile);

    return a.exec();
}
