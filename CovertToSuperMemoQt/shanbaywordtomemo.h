#ifndef SHANBAYWORDTOMEMO_H
#define SHANBAYWORDTOMEMO_H
#include <QStringList>
#include <QSharedPointer>
#include "memocollection.h"
#include "covertstrategy.h"
class ShanbayWordToMemo
{
public:
    ShanbayWordToMemo(ShanbayCovertStrategy* detach_strategy);
    ~ShanbayWordToMemo();
    void addWord(const QString& word);
    void addWordList(const QStringList& list);
    void setCovertStrategy(ShanbayCovertStrategy* strategy);

    QSharedPointer<MemoCollection> makeCollection(); // shared ptr, so you do't need to delete it

private:
    ShanbayCovertStrategy* covertStrategy_;
    QStringList wordList_;
};

#endif // SHANBAYWORDTOMEMO_H
