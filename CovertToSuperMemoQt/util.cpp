#include "util.hxx"
#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <QTextStream>
Util::Util(QObject *parent) : QObject(parent)
{

}

Util::~Util()
{

}

bool Util::covertToSuperMemo(const QString &fromFile, const QString &toFile)
{
    QFile outFile;
    outFile.setFileName(toFile);
    if (!outFile.open(QIODevice::WriteOnly)) {
        qWarning() << "cannot open file -> " + toFile;
        return false;
    }
    QTextStream outStream(&outFile);

    QStringList wordList = getSourceWordList(fromFile);
    int index = 0;
    foreach (QString word, wordList) {
        index++;
        qDebug() <<index<< ": get word -> " << word;
        WordInfo wordInfo = Shanbay::instance()->getWordInfo(word);
        /*
         * write word info with Q&A format which supermemo can import
         *
         *
         *
         */
        QString pron = "[ " +wordInfo.pron + " ]";

        QString question_head = "Q:";
        QString answer_head = "A:";
        QString br = "<br/>";

        QString question = question_head + wordInfo.word;
        outStream << question <<endl;

        QString answer_pron = answer_head + pron + br;
        QString answer_cn = answer_head + wordInfo.cn + br;
        outStream << answer_pron << endl;
        outStream << answer_cn << endl;
        outStream << endl;


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

