#include "mainwindow.h"
#include <QApplication>
#include <QPicture>
#include <QPixmap>
#include <QTextCodec>
#include "util.hxx"
#include "shanbay.hxx"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
//    QPixmap pic;
//    pic.load("./sang.png");
//    a.setWindowIcon(QIcon(pic));

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
