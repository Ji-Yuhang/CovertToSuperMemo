#include "shanbay.hxx"
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslConfiguration>
#include <assert.h>
#include "json.h"
Shanbay* Shanbay::g_shanbay_ = 0;
Shanbay::Shanbay(QObject *parent) : QObject(parent)
{
    assert(!g_shanbay_);
    g_shanbay_ = this;

}

Shanbay::~Shanbay()
{

}

ShanbayWordInfo Shanbay::getWordInfo(const QString &word)
{
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

    return wordInfo;
}

