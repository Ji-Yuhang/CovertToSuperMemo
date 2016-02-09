#ifndef MEMOCOLLECTION_H
#define MEMOCOLLECTION_H
#include <QList>

#include "memounit.h"

class MemoCollection
{
public:
    MemoCollection();

    void addMemoUnit(const MemoUnit& unit);
    void addMemoUnitList(const QList<MemoUnit>& list);

    void shuffle();
    bool toXmlFile(const QString& toFile);
    QString pronToHtml(const QString &pron);


private:
    QList<MemoUnit> data_;
};

#endif // MEMOCOLLECTION_H
