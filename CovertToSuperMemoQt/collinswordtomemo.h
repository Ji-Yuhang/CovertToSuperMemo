#ifndef COLLINSWORDTOMEMO_H
#define COLLINSWORDTOMEMO_H


#include <QStringList>
#include <QSharedPointer>
#include "memocollection.h"
#include "collins.h"

class CovertStrategy {
public:
    virtual MemoUnit covertToMemoUnit(const CollinsInfo& collinsInfo) = 0;
};

class EnExampleToEnJieshi : public CovertStrategy {
public:

    virtual MemoUnit covertToMemoUnit(const CollinsInfo& collinsInfo);
private:

    QString highlightWord(const QString& sentence, const QString& word/*, Qt::CaseSensitivity cs = Qt::CaseInsensitive*/);
    QString clozeWord(const QString& sentence, const QString& word);
    QString pronToHtml(const QString& pron);
    QString multiSpace(int count);
};

class CollinsWordToMemo {
public:
    CollinsWordToMemo(CovertStrategy* strategy);
    void addWord(const QString& word);
    void addWordList(const QStringList& list);
    void setCovertStrategy(CovertStrategy* strategy);

    QSharedPointer<MemoCollection> makeCollection(); // shared ptr, so you do't need to delete it

private:
    CovertStrategy* covertStrategy_;
    QStringList wordList_;
};
#endif // COLLINSWORDTOMEMO_H
