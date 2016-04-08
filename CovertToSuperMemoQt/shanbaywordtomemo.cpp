#include "shanbaywordtomemo.h"

#include <QFileInfo>
#include <assert.h>
#include "shanbay.hxx"

ShanbayWordToMemo::ShanbayWordToMemo(ShanbayCovertStrategy *detach_strategy) : covertStrategy_(detach_strategy)
{
    assert(covertStrategy_);
}

ShanbayWordToMemo::~ShanbayWordToMemo()
{
    delete covertStrategy_;
}

void ShanbayWordToMemo::addWord(const QString &word)
{
    wordList_.append(word);
}

void ShanbayWordToMemo::addWordList(const QStringList &list)
{
    wordList_.append(list);
}

void ShanbayWordToMemo::setCovertStrategy(ShanbayCovertStrategy *strategy)
{
    covertStrategy_ = strategy;
}

QSharedPointer<MemoCollection> ShanbayWordToMemo::makeCollection()
{
    QSharedPointer<MemoCollection> collection(new MemoCollection);
    Q_FOREACH(const QString& word, wordList_) {
       ShanbayWordInfo info = Shanbay::instance()->getWordInfo(word);
       MemoUnit unit = covertStrategy_->covertToMemoUnit(info);
       collection->addMemoUnit(unit);
    }
    return collection;
}

