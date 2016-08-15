#include "collinswordtomemo.h"
#include <QFileInfo>
#include <assert.h>
#include "shanbay.hxx"

CollinsWordToMemo::CollinsWordToMemo(CollinsCovertStrategy *detach_strategy) : covertStrategy_(detach_strategy)
{
    assert(covertStrategy_);
}

CollinsWordToMemo::~CollinsWordToMemo()
{
    delete covertStrategy_;
}

void CollinsWordToMemo::addWord(const QString &word)
{
    wordList_.append(word);
}

void CollinsWordToMemo::addWordList(const QStringList &list)
{
    wordList_.append(list);
}

void CollinsWordToMemo::setCovertStrategy(CollinsCovertStrategy *strategy)
{
    covertStrategy_ = strategy;
}

QSharedPointer<MemoCollection> CollinsWordToMemo::makeCollection()
{
    QSharedPointer<MemoCollection> collection(new MemoCollection);
    Q_FOREACH(const QString& word, wordList_) {
        QList<CollinsInfo> infoList = COLLINS->zhCollins(word);
        Q_FOREACH(const CollinsInfo& info, infoList) {
            QList<MemoUnit> units = covertStrategy_->covertToMemoUnit(info);
            collection->addMemoUnitList(units);
        }
    }
    return collection;
}

