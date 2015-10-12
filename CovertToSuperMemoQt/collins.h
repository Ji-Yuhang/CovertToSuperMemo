#ifndef COLLINS_H
#define COLLINS_H

#include <QMap>
#include <QObject>
#include <QSqlDatabase>

struct CollinsInfo
{
    int wordID;
    QString word;
    int frequency;
    int type;
    int num;
    QString st;
    QString cn;
    QString sentences;
    QString grammer;
    QString explain;
    QString usagenote;
    QString exampleXML;
    QMap<QString,QString> example;
};

class Collins : public QObject
{
    Q_OBJECT
public:
    explicit Collins(QObject *parent = 0);
    void initCollins();
    QList<CollinsInfo> zhCollins(QString word);
    QList<CollinsInfo> allCollins();
    QList<CollinsInfo> starCollins(int star);

    static Collins* instance(){return g_collins_;}

signals:

public slots:
private:
    QSqlDatabase zhCollinsdb_;
    static Collins* g_collins_;
    QList<CollinsInfo> allCollinsInfo_;
};
#define COLLINS Collins::instance()
#endif // COLLINS_H
