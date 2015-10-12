#ifndef REMOTESUPERMEMOINFO_H
#define REMOTESUPERMEMOINFO_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QSqlDatabase>
#include <QDateTime>

enum SuperMemoFlag {
    NEW_INFO = 0,
    SET_KNOWN
};

struct SuperMemoInfo {
    int id;
    int word_id;
    QString word;
    QDateTime addTime;
    int isKnwon;
    SuperMemoFlag flag;
};

class RemoteSupermemoInfo : public QObject
{
    Q_OBJECT
public:
    explicit RemoteSupermemoInfo(QObject *parent = 0);
    ~RemoteSupermemoInfo();
    void initInfoList();

    QList<SuperMemoInfo> infoList;
    QSqlDatabase aliyun_;
signals:

public slots:
};

#endif // REMOTESUPERMEMOINFO_H
