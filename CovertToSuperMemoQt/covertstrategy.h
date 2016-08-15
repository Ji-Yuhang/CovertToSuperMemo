#ifndef COVERTSTRATEGY_H
#define COVERTSTRATEGY_H
#include "memounit.h"
#include "collins.h"
#include "shanbay.hxx"
class CovertHelper {
protected:
    QString highlightWord(const QString& sentence, const QString& word/*, Qt::CaseSensitivity cs = Qt::CaseInsensitive*/);
    QString clozeWord(const QString& sentence, const QString& word);
    QString pronToHtml(const QString& pron);
    QString multiSpace(int count);
};

class CovertStrategy : public CovertHelper{
};
class CollinsCovertStrategy : public CovertStrategy{
public:
    virtual QList<MemoUnit> covertToMemoUnit(const CollinsInfo& collinsInfo) = 0;
};
class ShanbayCovertStrategy : public CovertStrategy {
public:
    virtual MemoUnit covertToMemoUnit(const ShanbayWordInfo& shanbayInfo) = 0;
};
class EnWordToShanbayCN : public ShanbayCovertStrategy {
public:
    virtual MemoUnit covertToMemoUnit(const ShanbayWordInfo& shanbayInfo);
};

class EnExampleToEnJieshi : public CollinsCovertStrategy {
public:

    virtual QList<MemoUnit> covertToMemoUnit(const CollinsInfo& collinsInfo);
};

class EnExampleToZhExample : public CollinsCovertStrategy {
public:

    virtual QList<MemoUnit> covertToMemoUnit(const CollinsInfo& collinsInfo);
};

#endif // COVERTSTRATEGY_H
