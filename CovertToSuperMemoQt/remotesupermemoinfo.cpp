#include "remotesupermemoinfo.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QVariant>
#include <QSqlRecord>
#include <QDebug>
RemoteSupermemoInfo::RemoteSupermemoInfo(QObject *parent) : QObject(parent)
{

}

RemoteSupermemoInfo::~RemoteSupermemoInfo()
{

}

void RemoteSupermemoInfo::initInfoList()
{
    aliyun_ = QSqlDatabase::addDatabase("QMYSQL","mysql");;
    aliyun_.setDatabaseName("english");
    aliyun_.setHostName("rds1m2iqskhitpx6nmx7u.mysql.rds.aliyuncs.com");
    aliyun_.setUserName("jiyuhang");
    aliyun_.setPassword("jiyuhang8757871");
    if (!aliyun_.open()) {
        QMessageBox::warning(0,"cannot open aliyun Mysql",QString::fromUtf8("\xE6\x89\xBE\xE4\xB8\x8D\xE5\x88\xB0\xE6\x95\xB0\xE6\x8D\xAE\xE5\xBA\x93\xE6\x96\x87\xE4\xBB\xB6\x20\x63\x6F\x6C\x6C\x69\x6E\x73\x2E\x64\x62"));
        return;
    }
    QSqlQuery query(aliyun_);

    if (query.exec("select * from supermemo")) {

        while (query.next()) {

            SuperMemoInfo info;
            info.id = query.value(0).toInt();
            info.word_id = query.value(1).toInt();
            info.word = query.value(2).toString();
            info.addTime = query.value(3).toDateTime();
            info.isKnwon = query.value(4).toInt();
            info.flag = SuperMemoFlag(query.value(5).toInt());
            infoList.append(info);
        }

    }else {
        qDebug() << "sql exec ERROR"<< query.lastError().text();
    }
}

