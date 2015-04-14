#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QStringList>
#include "shanbay.hxx"

class Util : public QObject
{
    Q_OBJECT
public:
    explicit Util(QObject *parent = 0);
    ~Util();
    static bool covertToSuperMemo(const QString& fromFile, const QString& toFile);
    static QStringList getSourceWordList(const QString& sourceFile);


signals:

public slots:
};

#endif // UTIL_H
