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
        WordInfo wordInfo = Shanbay::instance()->getWordInfo(word);

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

