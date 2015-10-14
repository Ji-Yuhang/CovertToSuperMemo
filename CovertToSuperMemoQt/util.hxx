#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QStringList>
#include <QProgressBar>
#include <QLabel>
#include "shanbay.hxx"

class Util : public QObject
{
    Q_OBJECT
public:
    explicit Util(QObject *parent = 0);
    ~Util();
    static bool covertToSuperMemo(const QString& fromFile, const QString& toFile,QProgressBar* bar = 0, QLabel* label = 0);
    static bool covertToSuperMemoXML(const QString& fromFile, const QString& toFile,QProgressBar* bar = 0, QLabel* label = 0);
    static bool covertToSuperMemoXML(const QStringList& wordList, const QString& toFile,QProgressBar* bar = 0, QLabel* label = 0);

    static QStringList getSourceWordList(const QString& sourceFile);
    static void downloadFile(const QString& uri, const QString& path);


signals:

public slots:
};

#endif // UTIL_H
