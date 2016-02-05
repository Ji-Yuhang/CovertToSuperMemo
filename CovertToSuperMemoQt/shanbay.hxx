#ifndef SHANBAY_H
#define SHANBAY_H

#include <QObject>
#include <QNetworkAccessManager>
struct ShanbayWordInfo {
    QString word;
    QString pron;
    QString audio;
    QString cn;
    QString en;
    QString sentence;
};

class Shanbay : public QObject
{
    Q_OBJECT
public:
    explicit Shanbay(QObject *parent = 0);
    ~Shanbay();
    ShanbayWordInfo getWordInfo(const QString& word);
    static Shanbay* instance() {return g_shanbay_;}
private:
    static Shanbay* g_shanbay_;
    QNetworkAccessManager netManager_;

signals:

public slots:
};

#endif // SHANBAY_H
