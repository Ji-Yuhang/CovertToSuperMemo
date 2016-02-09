#include "memocollection.h"
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <QFileInfo>
#include <QDir>
#include "shanbay.hxx"
#include "util.hxx"
#include <algorithm>
MemoCollection::MemoCollection()
{

}

void MemoCollection::addMemoUnit(const MemoUnit &unit)
{
    data_.append(unit);
}

void MemoCollection::addMemoUnitList(const QList<MemoUnit> &list)
{
    Q_FOREACH( const MemoUnit& unit, list) {
        addMemoUnit(unit);
    }
}

void MemoCollection::shuffle()
{
    std::random_shuffle(data_.begin(), data_.end());
}

bool MemoCollection::toXmlFile(const QString &toFile)
{
    QFile outFile;
    outFile.setFileName(toFile);
    if (!outFile.open(QIODevice::WriteOnly)) {
        qWarning() << "cannot open file -> " + toFile;
        return false;
    }

    QDomDocument document;
    QDomElement root = document.createElement("SuperMemoCollection");
    int count = data_.size() + 1;
    QDomElement eleCount = document.createElement("Count");
    QDomText texCount = document.createTextNode(QString::number(count));
    eleCount.appendChild(texCount);
    root.appendChild(eleCount);
    QDomElement eleA = document.createElement("SuperMemoElement");
    QDomText id = document.createTextNode("1");
    QDomElement idA = document.createElement("ID");
    idA.appendChild(id);
    QDomElement titleA = document.createElement("Title");
    QString todayTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QDomText title = document.createTextNode(todayTime);
    titleA.appendChild(title);
    QDomElement typeA = document.createElement("Type");
    QDomText type = document.createTextNode("Topic");
    typeA.appendChild(type);
    eleA.appendChild(idA);
    eleA.appendChild(titleA);
    eleA.appendChild(typeA);

    int iid = 0;
    Q_FOREACH( const MemoUnit& unit, data_) {
        //    for (int i = 0; i < count - 1; ++i) {
        if (unit.question().toHtmlString().isEmpty()) continue;
        iid = iid + 2;
        QDomElement ele = document.createElement("SuperMemoElement");
        QDomText _id = document.createTextNode(QString::number(iid + 2));
        QDomElement eleID = document.createElement("ID");
        eleID.appendChild(_id);

        QDomElement eleType = document.createElement("Type");
        QDomText _type = document.createTextNode("Item");
        eleType.appendChild(_type);

        QDomElement eleOrd = document.createElement("Ordinal");
        QDomText _ord = document.createTextNode("100");
        eleOrd.appendChild(_ord);

        QDomElement content = document.createElement("Content");
        {
            //            QString pron;
//            ShanbayWordInfo wordInfo = Shanbay::instance()->getWordInfo(word);

//            QString utf16pron = pronToHtml(wordInfo.pron);
//            qDebug() << utf16pron;
//            QString pron = " [ " +utf16pron + " ] ";

//            // TODO: copy mp3 from zip

//            QFileInfo fileInfo(outFile);
//            QString mp3path = fileInfo.baseName()+"_files/Elements";
//            Util::downloadFile(wordInfo.audio, mp3path); // down mp3
//            QString name = wordInfo.word;
//            QString audio = wordInfo.audio;
//            int audioIndex = audio.lastIndexOf("/");
//            audio = audio.mid(audioIndex + 1);
//            QString url = "[SecondaryStorage]\\"+ audio;
//            qDebug() << "mp3name"<<url;
            QDomElement questionEle = document.createElement("Question");
            questionEle.appendChild(document.createTextNode(unit.question().toHtmlString()));
            QDomElement answerEle = document.createElement("Answer");
            answerEle.appendChild(document.createTextNode(unit.answer().toHtmlString()));
            content.appendChild(questionEle);
            content.appendChild(answerEle);

            if (unit.haveSound()) {
                QFileInfo fileInfo(outFile);
                QString mp3path = fileInfo.baseName()+"_files/Elements";
                QUrl sourceUrl = unit.sound().source();
                if (sourceUrl.isLocalFile()) {
                    QDir dir;
                    QString tempPath;
                    QStringList pathList = mp3path.split("/");
                    foreach (QString onePath, pathList) {
                        tempPath += onePath;
                        dir.mkdir(tempPath);
                        tempPath += "/";
                    }

                    dir.mkdir(mp3path);

                    QFileInfo mp3info(sourceUrl.toLocalFile());
                    QString mp3name = mp3info.fileName();
                    QFile::copy(sourceUrl.toLocalFile(), mp3path +"/"+ mp3name );
                } else {

                    Util::downloadFile(sourceUrl.toString(), mp3path); // down mp3
                }

                QDomElement soundEle = document.createElement("Sound");
                QDomElement textEle = document.createElement("Text");
                textEle.appendChild(document.createTextNode(unit.sound().text()));
                QDomElement urlEle = document.createElement("URL");
                urlEle.appendChild(document.createTextNode(unit.sound().url()));
                QDomElement nameEle = document.createElement("Name");
                nameEle.appendChild(document.createTextNode(unit.sound().name()));
                soundEle.appendChild(textEle);
                soundEle.appendChild(urlEle);
                soundEle.appendChild(nameEle);

                content.appendChild(soundEle);
            }

        }
        ele.appendChild(eleID);
        ele.appendChild(eleType);
        ele.appendChild(eleOrd);
        ele.appendChild(content);

        eleA.appendChild(ele);
        //    }
    }
    root.appendChild(eleA);
    document.appendChild(root);
    QTextStream outStream(&outFile);
    outStream.setCodec("UTF-8");
    document.save(outStream,4,QDomNode::EncodingFromTextStream);
    outFile.close();
    return true;

}

QString MemoCollection::pronToHtml(const QString &pron)
{
    const ushort * utf16 = pron.utf16();
    QString utf16pron;
    for (int j = 0; j < pron.size(); ++j){
        ushort ch = *(utf16+j);
        QString temp = "&#";
        temp += QString::number(ch);
        temp += ";";
        utf16pron += temp;
    }
    return utf16pron;
}

