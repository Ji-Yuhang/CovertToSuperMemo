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

bool RemoteSupermemoInfo::setFlagKnown(const QStringList list)
{
    if (!aliyun_.open()) {
        QMessageBox::warning(0,"cannot open aliyun Mysql",QString::fromUtf8("\xE6\x89\xBE\xE4\xB8\x8D\xE5\x88\xB0\xE6\x95\xB0\xE6\x8D\xAE\xE5\xBA\x93\xE6\x96\x87\xE4\xBB\xB6\x20\x63\x6F\x6C\x6C\x69\x6E\x73\x2E\x64\x62"));
        return false;
    }
    QList<int> supermemoIDList;
    QSqlQuery query(aliyun_);
    Q_FOREACH(QString collinInfo, list) {
        QList<SuperMemoInfo> superMemoInfo = findSuperMemoInfoList(collinInfo);
        Q_FOREACH(SuperMemoInfo sinfo,superMemoInfo)
        if (sinfo.id != 0) {
            supermemoIDList.append(sinfo.id);
        }
//infoList
    }
    errorSupermemoIDlist.clear();
    QDateTime now = QDateTime::currentDateTime();
    QString nowStr = now.toString("yyyy-MM-dd hh:mm:ss");
    aliyun_.transaction();
    Q_FOREACH(int supermemoID, supermemoIDList) {
        query.prepare("update supermemo set flag = 1,is_known = 1,add_time=:add_time where supermemo_id=:id;");
        query.bindValue(":add_time",nowStr);
        query.bindValue(":id",supermemoID);
        if (query.exec()) {

        }else {
            errorSupermemoIDlist.append(supermemoID);
            qDebug() << "sql exec ERROR"<< query.lastError().text();
        }
    }
    aliyun_.commit();
    return errorSupermemoIDlist.isEmpty();


}

QList<SuperMemoInfo> RemoteSupermemoInfo::findSuperMemoInfoList(const QString &word)
{
    QList<SuperMemoInfo> empty;

    Q_FOREACH(SuperMemoInfo info, infoList) {
        if (info.word == word) {
            empty.append(info);
//            return info;
        }

    }
    return empty;
}

//SuperMemoInfo RemoteSupermemoInfo::findSuperMemoInfo(int collinsWordID)
//{
//    SuperMemoInfo empty;
//    empty.id = 0;
//    empty.word_id = 0;
//    Q_FOREACH(SuperMemoInfo info, infoList) {
//        if (info.word_id == collinsWordID) {
//            return info;
//        }

//    }
//    return empty;
//}

