#include "collins.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNodeList>
#include <QDebug>

Collins* Collins::g_collins_ = 0;
Collins::Collins(QObject *parent) : QObject(parent)
{
    g_collins_ = this;
    zhCollinsdb_ = QSqlDatabase::addDatabase("QSQLITE","zhcollins");
    zhCollinsdb_.setDatabaseName("./collins.db");
    if (!zhCollinsdb_.open()) {
        QMessageBox::warning(0,"cannot find collins.db",QString::fromUtf8("\xE6\x89\xBE\xE4\xB8\x8D\xE5\x88\xB0\xE6\x95\xB0\xE6\x8D\xAE\xE5\xBA\x93\xE6\x96\x87\xE4\xBB\xB6\x20\x63\x6F\x6C\x6C\x69\x6E\x73\x2E\x64\x62"));
    }
    initCollins();
}

void Collins::initCollins()
{
    QSqlQuery query(zhCollinsdb_);
//    QString sql = QString("select * from zhmultiwords where word='%1'").arg(word);
    query.prepare("select * from zhmultiwords ");
//    query.bindValue(":word",word);
    if (query.exec()) {
        qDebug() << "initCollins";
        while (query.next()) {

            CollinsInfo info;
            info.wordID = query.value(0).toInt();
            info.word = query.value(1).toString();
            info.frequency = query.value(2).toInt();
            info.type = query.value(3).toInt();
            info.num = query.value(4).toInt();
            info.st = query.value(5).toString();
            info.cn = query.value(6).toString();
            info.sentences = query.value(7).toString();
            info.grammer = query.value(8).toString();
            info.explain = query.value(9).toString();
            info.usagenote = query.value(10).toString();
            info.exampleXML = query.value(11).toString();
            QDomDocument doc;
            if (doc.setContent(info.exampleXML)) {
                QDomNodeList list = doc.elementsByTagName("pair");
                for (int i = 0; i < list.size(); ++i) {
                    QString entext;
                    QString zhtext;
                    QDomNode one = list.at(i);
                    if (one.isElement()) {
                        QDomElement ele = one.toElement();
                        QDomNodeList enlist = ele.elementsByTagName("en");
                        if (!enlist.isEmpty()) {
                            QDomElement en = enlist.at(0).toElement();
                            entext = en.text();
                        }

                        QDomNodeList znlist = ele.elementsByTagName("zh");
                        if (!znlist.isEmpty()) {
                            QDomElement zh = znlist.at(0).toElement();
                            zhtext = zh.text();
                        }
                        info.example.insert(entext,zhtext);
                    }

                }
            }
//            qDebug() << info.wordID;
            allCollinsInfo_.append(info);
        }
        qDebug() << "init collins finished";


    }else {
        qDebug() << "sql exec ERROR"<< query.lastError().text();
    }
}

QList<CollinsInfo> Collins::zhCollins(QString word)
{
        QList<CollinsInfo> empty;
        QSqlQuery query(zhCollinsdb_);
    //    QString sql = QString("select * from zhmultiwords where word='%1'").arg(word);
        query.prepare("select * from zhmultiwords where word=:word and type=1");
        query.bindValue(":word",word);
        if (query.exec()) {
            while (query.next()) {
                CollinsInfo info;
                info.wordID = query.value(0).toInt();
                info.word = query.value(1).toString();
                info.frequency = query.value(2).toInt();
                info.type = query.value(3).toInt();
                info.num = query.value(4).toInt();
                info.st = query.value(5).toString();
                info.cn = query.value(6).toString();
                info.sentences = query.value(7).toString();
                info.grammer = query.value(8).toString();
                info.explain = query.value(9).toString();
                info.usagenote = query.value(10).toString();
                info.exampleXML = query.value(11).toString();
                QDomDocument doc;
                if (doc.setContent(info.exampleXML)) {
                    QDomNodeList list = doc.elementsByTagName("pair");
                    for (int i = 0; i < list.size(); ++i) {
                        QString entext;
                        QString zhtext;
                        QDomNode one = list.at(i);
                        if (one.isElement()) {
                            QDomElement ele = one.toElement();
                            QDomNodeList enlist = ele.elementsByTagName("en");
                            if (!enlist.isEmpty()) {
                                QDomElement en = enlist.at(0).toElement();
                                entext = en.text();
                            }

                            QDomNodeList znlist = ele.elementsByTagName("zh");
                            if (!znlist.isEmpty()) {
                                QDomElement zh = znlist.at(0).toElement();
                                zhtext = zh.text();
                            }
                            info.example.insert(entext,zhtext);
                        }

                    }
                }
                empty.append(info);



            }

        }else {
            qDebug() << "sql exec ERROR"<< query.lastError().text();
        }
        return empty;
}

QList<CollinsInfo> Collins::allCollins()
{
    return allCollinsInfo_;
}

QList<CollinsInfo> Collins::starCollins(int star)
{
    QList<CollinsInfo> empty;
    Q_FOREACH(CollinsInfo info, allCollinsInfo_) {
        if (info.frequency == star) {
            empty.append(info);
        }
    }
    return empty;
}

