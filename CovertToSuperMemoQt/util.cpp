#include "util.hxx"
#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <QTextStream>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <QDateTime>
#include <QTextCodec>
#include <QFileInfo>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDir>
#include <QTimer>
#include "collins.h"
#include <QDebug>
#include "collinswordtomemo.h"
Util::Util(QObject *parent) : QObject(parent)
{

}

Util::~Util()
{

}

bool Util::covertToSuperMemo(const QString &fromFile, const QString &toFile, QProgressBar *bar, QLabel* label)
{
    QFile outFile;
    outFile.setFileName(toFile);
    if (!outFile.open(QIODevice::WriteOnly)) {
        qWarning() << "cannot open file -> " + toFile;
        return false;
    }
    QTextStream outStream(&outFile);
    outStream.setCodec("UTF-8");

    QStringList wordList = getSourceWordList(fromFile);
    if (bar) bar->setRange(0, wordList.size());

    int index = 0;
    foreach (QString word, wordList) {
        index++;
        qDebug() <<index<< ": get word -> " << word;
        ShanbayWordInfo wordInfo = Shanbay::instance()->getWordInfo(word);

        if (bar) bar->setValue(index);
        if (label) label->setText(word);

        /*
         * write word info with Q&A format which supermemo can import
         *
         *
         *
         */

        QString question_head = "Q: ";
        QString answer_head = "A: ";
        QString br = "<br/>";


        QTextCodec *gbk = QTextCodec::codecForName("GB18030");
        QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

        QString g2u = gbk->toUnicode(gbk->fromUnicode(wordInfo.pron));
        qDebug()<< wordInfo.pron<<"    GBK -> UTF-8     " << g2u<<endl;

        QString pron = " [ " +wordInfo.pron + " ] ";
        QString cn = wordInfo.cn;
        QStringList cnList = cn.split("\n");

        QString question = question_head + wordInfo.word;
        outStream << question +"\r"<<endl;

        QString answer_pron = answer_head + pron + br;
        outStream << answer_pron <<"\r"<< endl;

        foreach (QString onecn, cnList) {
            QString oneAnswer = answer_head + onecn + br;
            outStream << oneAnswer <<"\r"<< endl;
        }

        outStream << "\r"<<endl;


        /*
         * end
         *
         *
         *
         */

    }
    outStream.flush();
    outFile.close();

    return false;
}

bool Util::covertToSuperMemoXML(const QString &fromFile, const QString &toFile, QProgressBar *bar, QLabel *label)
{

    QStringList wordList = getSourceWordList(fromFile);
    return covertToSuperMemoXML(wordList,toFile,bar,label);

}

QString highlightWord(const QString& sentence, const QString& word/*, Qt::CaseSensitivity cs = Qt::CaseInsensitive*/)
{
//    if (cs == Qt::CaseInsensitive) {
//    }
    QString tempSentence = sentence;
    if (tempSentence.contains(word))
        tempSentence = tempSentence.replace(word,"<FONT color=#ff0000\"><STRONG>"+word+"</STRONG></FONT>");
    if (word.size() > 0) {
        QString bigWord = word.at(0).toUpper() + word.mid(1);
        if (tempSentence.contains(bigWord))
            tempSentence = tempSentence.replace(bigWord,"<FONT color=#ff0000\"><STRONG>"+bigWord+"</STRONG></FONT>");
    }
    return tempSentence;
}

bool Util::covertToSuperMemoXML(const QStringList &wordList, const QString &toFile, QProgressBar *bar, QLabel *label)
{
    CollinsWordToMemo collinsToMemo(new EnExampleToZhExample);//EnExampleToEnJieshi
    collinsToMemo.addWordList(wordList);
    QSharedPointer<MemoCollection> collection = collinsToMemo.makeCollection();

    collection->shuffle();
    return collection->toXmlFile(toFile);

    QFile outFile;
    outFile.setFileName(toFile);
    if (!outFile.open(QIODevice::WriteOnly)) {
        qWarning() << "cannot open file -> " + toFile;
        return false;
    }

    if (bar) bar->setRange(0, wordList.size());

    QDomDocument document;
    QDomElement root = document.createElement("SuperMemoCollection");
    int count = wordList.size() + 1;
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
    for (int i = 0; i < count - 1; ++i) {
        QString word = wordList[i];
        qDebug() <<i<< ": get word -> " << word;
        ShanbayWordInfo wordInfo = Shanbay::instance()->getWordInfo(word);
        if (wordInfo.word.isEmpty()) continue;

        if (bar) bar->setValue(i);
        if (label) label->setText(word);

        /*
         * write word info with Q&A format which supermemo can import
         *
         *
         *
         */
        QList<CollinsInfo> collinsInfoList = COLLINS->zhCollins(word);
        Q_FOREACH(CollinsInfo collinsInfo, collinsInfoList) {
            QMap<QString,QString> tempExample = collinsInfo.example; //<en,zh> pair
            QStringList tempEnList = tempExample.keys();
            QString tempEn = tempEnList.join("<br/>");
            QString highlightEn = highlightWord(tempEn, word);
//            QString tempSentence = collinsInfo.sentences;
//            if (tempSentence.contains(word))
//                tempSentence = tempSentence.replace(word,"<FONT color=#ff0000\"><STRONG>"+word+"</STRONG></FONT>");
//            if (word.size() > 0) {
//                QString bigWord = word.at(0).toUpper() + word.mid(1);
//                if (tempSentence.contains(bigWord))
//                    tempSentence = tempSentence.replace(bigWord,"<FONT color=#ff0000\"><STRONG>"+bigWord+"</STRONG></FONT>");
//            }
            QString tempSentence = highlightWord(collinsInfo.sentences, word);

//            QString question = collinsInfo.sentences.replace(word,"<FONT color=#ff0000\"><STRONG>"+word+"</STRONG></FONT>");
#if 0
            QString question = tempSentence;
#else
            QString question = highlightEn;
#endif
            QString answer;

            QString question_head = "Q: ";
            QString answer_head = "";
            QString br = "<br/>";

            //        QString pron = " [ " +wordInfo.pron + " ] ";
            const ushort * utf16 = wordInfo.pron.utf16();
            QString utf16pron;
            for (int j = 0; j < wordInfo.pron.size(); ++j){
                ushort ch = *(utf16+j);
                QString temp = "&#";
                temp += QString::number(ch);
                temp += ";";
                utf16pron += temp;
//                qDebug()<<temp;
            }

            qDebug() << utf16pron;

            QFileInfo fileInfo(outFile);
            QString mp3path = fileInfo.baseName()+"_files/Elements";
            Util::downloadFile(wordInfo.audio, mp3path);

            QString pron = " [ " +utf16pron + " ] ";
            QTextCodec *gbk = QTextCodec::codecForName("GB18030");
            QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

            QString g2u = gbk->toUnicode(gbk->fromUnicode(wordInfo.pron));
            qDebug()<< wordInfo.pron<<"    GBK -> UTF-8     " << g2u<<endl;

            QString cn = wordInfo.cn;
            QStringList cnList = cn.split("\n");

            //        QString question = question_head + wordInfo.word;
            //        outStream << question +"\r"<<endl;

            QString answer_pron = answer_head +pron+ br;
            answer.append(answer_pron + "\r\n");
            //        outStream << answer_pron <<"\r"<< endl;

            foreach (QString onecn, cnList) {
                QString oneAnswer = answer_head + onecn + br;
                answer.append(oneAnswer + "\r\n");
                //            outStream << oneAnswer <<"\r"<< endl;
            }
            answer = tempSentence+br+collinsInfo.cn+br+collinsInfo.st+br+pron+br+collinsInfo.grammer+br+collinsInfo.explain+br+collinsInfo.usagenote;

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
                QString name = wordInfo.word;
                QString audio = wordInfo.audio;
                int audioIndex = audio.lastIndexOf("/");
                audio = audio.mid(audioIndex + 1);
                QString url = "[SecondaryStorage]\\"+ audio;
                qDebug() << "mp3name"<<url;
                QDomElement questionEle = document.createElement("Question");
                questionEle.appendChild(document.createTextNode(question));
                QDomElement answerEle = document.createElement("Answer");
                answerEle.appendChild(document.createTextNode(answer));

                QDomElement soundEle = document.createElement("Sound");
                QDomElement textEle = document.createElement("Text");
                textEle.appendChild(document.createTextNode(pron));
                QDomElement urlEle = document.createElement("URL");
                urlEle.appendChild(document.createTextNode(url));
                QDomElement nameEle = document.createElement("Name");
                nameEle.appendChild(document.createTextNode(name));
                soundEle.appendChild(textEle);
                soundEle.appendChild(urlEle);
                soundEle.appendChild(nameEle);

                content.appendChild(questionEle);
                content.appendChild(answerEle);
                content.appendChild(soundEle);
            }
            ele.appendChild(eleID);
            ele.appendChild(eleType);
            ele.appendChild(eleOrd);
            ele.appendChild(content);

            eleA.appendChild(ele);
        }
        root.appendChild(eleA);
        document.appendChild(root);
    }




    QTextStream outStream(&outFile);
    outStream.setCodec("UTF-8");
    document.save(outStream,4,QDomNode::EncodingFromTextStream);
    outFile.close();
    return true;
}

QStringList Util::getSourceWordList(const QString &sourceFile)
{
    QStringList wordList;
    QFile file;
    file.setFileName(sourceFile);
    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << "cannot open file -> " + sourceFile;
    }
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        line = line.trimmed();
        qDebug() <<"word: "<< line << "   length: "<< line.length();
        if (!line.isEmpty())
            wordList.append(line);
    }
    return wordList;
}

void Util::downloadFile(const QString &uri, const QString &path)
{
    QUrl _url(uri);
#if (QT_VERSION > QT_VERSION_CHECK(5, 0, 0))
    QString fileName = _url.fileName();
#else
    int index = uri.lastIndexOf("/");
    QString fileName = uri.mid(index + 1);
#endif
    QFileInfo info;
    info.setFile(path+"/"+fileName);
    if (info.exists() && info.size() != 0) {
        return;
    }

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(_url));
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    QTimer::singleShot(3000, &loop, SLOT(quit()));

    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), &loop, SLOT(quit()));
    loop.exec();
    if (reply->error() != QNetworkReply::NoError) {
        return;
    }
    QDir dir;

    QString tempPath;
    //.mid(0,path.lastIndexOf("/"));
    QString remainPath;
    QStringList pathList = path.split("/");
    foreach (QString onePath, pathList) {
        tempPath += onePath;
        dir.mkdir(tempPath);
        tempPath += "/";
    }

    dir.mkdir(path);
    QFile file;
    file.setFileName(path+"/"+fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    QByteArray all = reply->readAll();
    file.write(all);
    file.close();
    if (all.isEmpty()) {
        file.remove();
    }
}

