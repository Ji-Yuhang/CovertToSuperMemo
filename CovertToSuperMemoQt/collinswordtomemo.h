#ifndef COLLINSWORDTOMEMO_H
#define COLLINSWORDTOMEMO_H


#include <QStringList>
#include <QSharedPointer>
#include "memocollection.h"
#include "collins.h"
#include "covertstrategy.h"

class CollinsWordToMemo {
public:
    CollinsWordToMemo(CollinsCovertStrategy* detach_strategy);
    ~CollinsWordToMemo();
    void addWord(const QString& word);
    void addWordList(const QStringList& list);
    void setCovertStrategy(CollinsCovertStrategy* strategy);

    QSharedPointer<MemoCollection> makeCollection(); // shared ptr, so you do't need to delete it

private:
    CollinsCovertStrategy* covertStrategy_;
    QStringList wordList_;
};
#endif // COLLINSWORDTOMEMO_H
