#include "shanbay.hxx"
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslConfiguration>
#include <assert.h>
#include "json.h"
#include <QDomDocument>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
Shanbay* Shanbay::g_shanbay_ = 0;
Shanbay::Shanbay(QObject *parent) : QObject(parent)
{
    assert(!g_shanbay_);
    g_shanbay_ = this;
    shanbayDB_ = QSqlDatabase::addDatabase("QSQLITE","shanbaydb");
    shanbayDB_.setDatabaseName("./shanbay.db");
    if (!shanbayDB_.open()) {
        QMessageBox::warning(0,"cannot find shanbay.db",QString::fromUtf8("\xE6\x89\xBE\xE4\xB8\x8D\xE5\x88\xB0\xE6\x95\xB0\xE6\x8D\xAE\xE5\xBA\x93\xE6\x96\x87\xE4\xBB\xB6\x20\x63\x6F\x6C\x6C\x69\x6E\x73\x2E\x64\x62"));
    }
}

Shanbay::~Shanbay()
{

}

ShanbayWordInfo Shanbay::getWordInfo(const QString &word)
{
    if (data_.contains(word)) return data_.value(word);
    ShanbayWordInfo localwordInfo;
    if (shanbayDB_.isOpen()) {
        localwordInfo = getWordInfoFromSQLite3(word);
    }
    if (!localwordInfo.word.isEmpty()) return localwordInfo;
    ShanbayWordInfo wordInfo;

    wordInfo.word = word;
    wordInfo.pron = "nit";
    wordInfo.cn;

    QString willWord = word.trimmed();
    if (willWord.contains(" ")) willWord = willWord.replace(" ","%20");

    QString url = QString("https://api.shanbay.com/bdc/search/?word=%1").arg(willWord);
    QNetworkRequest request;
    request.setUrl(QUrl(url));
//    QString tokenStr = QString("Bearer %1").arg(token_);
//    request.setRawHeader("Authorization",tokenStr.toLatin1());
//    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
//    request.setRawHeader("Cache-Control","no-store");
//    request.setRawHeader("Pragma","no-cache");
    QSslConfiguration config;

    config.setPeerVerifyMode(QSslSocket::VerifyNone);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    config.setProtocol(QSsl::TlsV1_0);
#else
    config.setProtocol(QSsl::TlsV1);
#endif

    request.setSslConfiguration(config);

    QNetworkReply* reply = netManager_.get(request);
    QEventLoop loop;
    connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    loop.exec(QEventLoop::ExcludeUserInputEvents);
    QByteArray json = reply->readAll();
    QtJson::JsonObject obj = QtJson::parse(QString::fromUtf8(json)).toMap();
    QtJson::JsonObject data = obj["data"].toMap();
    wordInfo.cn = data["definition"].toString();
    wordInfo.en = data["en_definition"].toString();
    wordInfo.word = data["content"].toString();
    wordInfo.pron = data["pron"].toString();
    qDebug() << wordInfo.pron << wordInfo.pron.toUtf8().toHex();
    wordInfo.audio = data["us_audio"].toString();
    data_[word] = wordInfo;

    return wordInfo;
}

ShanbayWordInfo Shanbay::getWordInfoFromSQLite3(const QString &word)
{
    ShanbayWordInfo info;
    QSqlQuery query(shanbayDB_);
//    QString sql = QString("select * from zhmultiwords where word='%1'").arg(word);
    query.prepare("select json from words where word=:word");
    query.bindValue(":word",word);
    if (query.exec()) {
        while (query.next()) {
            QString json = query.value("json").toString();
            QtJson::JsonObject data = QtJson::parse(json).toMap();
            info.cn = data["definition"].toString();
            info.en = data["en_definition"].toString();
            info.word = data["content"].toString();
            info.pron = data["pron"].toString();
            qDebug() << info.pron << info.pron.toUtf8().toHex();
            info.audio = data["us_audio"].toString();
            data_[word] = info;
        }

    }else {
        qDebug() << "sql exec ERROR"<< query.lastError().text()<<query.lastQuery();
    }
    return info;
}

