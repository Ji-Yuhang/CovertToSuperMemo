#include "covertstrategy.h"
#include <QString>
#include <QFileInfo>
#include <QUrl>
//CovertStrategy::CovertStrategy()
//{

//}


QString CovertHelper::highlightWord(const QString &sentence, const QString &word)
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
    //            QString tempSentence = collinsInfo.sentences;
    //            if (tempSentence.contains(word))
    //                tempSentence = tempSentence.replace(word,"<FONT color=#ff0000\"><STRONG>"+word+"</STRONG></FONT>");
    //            if (word.size() > 0) {
    //                QString bigWord = word.at(0).toUpper() + word.mid(1);
    //                if (tempSentence.contains(bigWord))
    //                    tempSentence = tempSentence.replace(bigWord,"<FONT color=#ff0000\"><STRONG>"+bigWord+"</STRONG></FONT>");
    //            }
    return tempSentence;
}

QString CovertHelper::clozeWord(const QString &sentence, const QString &word)
{
    QString tempSentence = sentence;
    QString cloze; // "[____]"
    int size = word.size();
    cloze = "[";
    for (int i = 0; i < size; ++i) {
        cloze += "_";
    }
    cloze += ']';
    // replace word with [___]
    if (tempSentence.contains(word))
        tempSentence = tempSentence.replace(word,"<FONT color=#ff0000\"><STRONG>"+cloze+"</STRONG></FONT>");
    if (size > 0) {
        QString bigWord = word.at(0).toUpper() + word.mid(1);
        if (tempSentence.contains(bigWord))
            tempSentence = tempSentence.replace(bigWord,"<FONT color=#ff0000\"><STRONG>"+cloze+"</STRONG></FONT>");
    }
    return tempSentence;
}

QString CovertHelper::pronToHtml(const QString &pron)
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

QString CovertHelper::multiSpace(int count)
{
    QString space = "&nbsp;";

    if (count < 0) return space;
    QString temp;
    for (int i = 0 ; i < count; ++i) {
        temp += space;
    }
    return temp;
}

QList<MemoUnit> EnExampleToEnJieshi::covertToMemoUnit(const CollinsInfo &collinsInfo)
{

    MemoUnit unit;

    QString br = "<br/>";
    QString word = collinsInfo.word;
    QStringList enzhlist;
    QMap<QString,QString> exampleEnZh = collinsInfo.example; //<en,zh> pair
    for (QMap<QString,QString>::iterator kv = exampleEnZh.begin(); kv != exampleEnZh.end(); ++kv) {
        QString en = kv.key();
        QString zh = kv.value();
        QString enzh = highlightWord(en,word) + multiSpace(10) + zh;
        enzhlist.append(enzh);
    }
    QString example = enzhlist.join(br);
    QStringList enList = exampleEnZh.keys();
    QString exampleEn = enList.join(br);
    QString highlightExampleEn = highlightWord(exampleEn,word);

    QString highlightSentence = clozeWord(collinsInfo.sentences, word);
    QString question = highlightSentence;

    ShanbayWordInfo wordInfo = Shanbay::instance()->getWordInfo(word);

    QString utf16pron = pronToHtml(wordInfo.pron);
    qDebug() << utf16pron;
    QString pron = " [ " +utf16pron + " ] ";

    // TODO: copy mp3 from zip
#if 0
    QFileInfo fileInfo(outFile);
    QString mp3path = fileInfo.baseName()+"_files/Elements";

    Util::downloadFile(wordInfo.audio, mp3path); // down mp3
#endif
//    QTextCodec *gbk = QTextCodec::codecForName("GB18030");
//    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
//    QString g2u = gbk->toUnicode(gbk->fromUnicode(wordInfo.pron));
//    qDebug()<< wordInfo.pron<<"    GBK -> UTF-8     " << g2u<<endl;
//    QString cn = wordInfo.cn;
//    QStringList cnList = cn.split("\n");

    QString answer;

//    QString answer_pron = answer_head +pron+ br;
//    answer.append(answer_pron + "\r\n");
//    foreach (QString onecn, cnList) {
//        QString oneAnswer = answer_head + onecn + br;
//        answer.append(oneAnswer + "\r\n");
//    }
#if 0
    answer = highlightSentence+br       //  If you describe something as immoderate, you disapprove of it because it is too extreme.
            +collinsInfo.cn+br          // 极端的;不合理的
            +collinsInfo.st+br          // ADJ-GRADED	能被表示程度的副词或介词词组修饰的形容词
            +pron+br                    // [immoderate]
            +collinsInfo.grammer+br     // 【搭配模式】：usu ADJ n【语用信息】：disapproval【语域标签】：FORMAL 正式
            +collinsInfo.explain+br     // in BRIT, also use 英国英语亦用 characterise
            +collinsInfo.usagenote;     // Usage Note :In British English, a person's weight is normally measured in stones and pounds.
                                        //A stone is equivalent to 14 pounds, or 6.35 kilograms...
#else

    answer = highlightWord(word,word) + "&nbsp;&nbsp;"
            + pron + multiSpace(80)
            + collinsInfo.cn + br + br
            + example;
#endif
    unit.setQuestion(Question(question));
    unit.setAnswer(Answer(answer));

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
    Sound sound;
    QString audio = wordInfo.audio;
    int audioIndex = audio.lastIndexOf("/");
    audio = audio.mid(audioIndex + 1);
    QString url = "[SecondaryStorage]\\"+ audio;

    sound.setUrl(url);
    sound.setName("");
    sound.setText(pron);
    QUrl sourceUrl = wordInfo.audio;
    QFileInfo fileinfo("./shanbaymp3/" + audio );
    if (fileinfo.exists()) {
        sourceUrl = QUrl::fromLocalFile("./shanbaymp3/" + audio );
    }
    sound.setSource(sourceUrl);
    unit.setSound(sound);
    QList<MemoUnit> list;
    list.append(unit);
    return list;
}

MemoUnit EnWordToShanbayCN::covertToMemoUnit(const ShanbayWordInfo &shanbayInfo)
{
    MemoUnit unit;

    QString br = "<br/>";
    QString word = shanbayInfo.word;
    QString question = word;

    unit.setQuestion(Question(question));

    const ShanbayWordInfo& wordInfo = shanbayInfo;
    QString utf16pron = pronToHtml(wordInfo.pron);
    qDebug() << utf16pron;
    QString pron = " [ " +utf16pron + " ] ";


    QString endef;
    for (QMap<QString, QStringList >::const_iterator i = wordInfo.enMap.begin(); i != wordInfo.enMap.end(); ++i) {
        QStringList list = i.value();
        QString pos = i.key();
        endef = endef
                + pos + multiSpace(4) + br
                + multiSpace(4) + list.join(br+ multiSpace(4)) + br;
    }
    QString answer
            = pron + multiSpace(4)
            + wordInfo.cn + br
            + endef + br;
    unit.setAnswer(Answer(answer));


    // TODO: copy mp3 from zip
#if 0
    QFileInfo fileInfo(outFile);
    QString mp3path = fileInfo.baseName()+"_files/Elements";

    Util::downloadFile(wordInfo.audio, mp3path); // down mp3
#endif
    Sound sound;
    QString audio = wordInfo.audio;
    int audioIndex = audio.lastIndexOf("/");
    audio = audio.mid(audioIndex + 1);
    QString url = "[SecondaryStorage]\\"+ audio;

    sound.setUrl(url);
    sound.setName("");
    sound.setText(pron);
    QUrl sourceUrl = wordInfo.audio;
    QFileInfo fileinfo("./shanbaymp3/" + audio );
    if (fileinfo.exists()) {
        sourceUrl = QUrl::fromLocalFile("./shanbaymp3/" + audio );
    }
    sound.setSource(sourceUrl);
    unit.setSound(sound);

    return unit;
}

QList<MemoUnit> EnExampleToZhExample::covertToMemoUnit(const CollinsInfo &collinsInfo)
{
    QList<MemoUnit> list;


    QString br = "<br/>";
    QString word = collinsInfo.word;
    QStringList enzhlist;
    QMap<QString,QString> exampleEnZh = collinsInfo.example; //<en,zh> pair
    for (QMap<QString,QString>::iterator kv = exampleEnZh.begin(); kv != exampleEnZh.end(); ++kv) {
        QString en = kv.key();
        QString zh = kv.value();
        QString enzh = highlightWord(en,word) + multiSpace(10) + zh;

        QString question = highlightWord(en,word);
        QString answer;
        ShanbayWordInfo wordInfo = Shanbay::instance()->getWordInfo(word);

        QString utf16pron = pronToHtml(wordInfo.pron);
        qDebug() << utf16pron;
        QString pron = " [ " +utf16pron + " ] ";
        answer = zh + br
                + highlightWord(collinsInfo.sentences, word) + br
                + pron + multiSpace(10) + highlightWord(word,word) + multiSpace(10) + collinsInfo.cn + br
                + collinsInfo.st + multiSpace(10) + collinsInfo.grammer + multiSpace(10) + collinsInfo.explain + br
                + collinsInfo.usagenote;

        MemoUnit unit;
        unit.setQuestion(Question(question));
        unit.setAnswer(Answer(answer));
        Sound sound;
        QString audio = wordInfo.audio;
        int audioIndex = audio.lastIndexOf("/");
        audio = audio.mid(audioIndex + 1);
        QString url = "[SecondaryStorage]\\"+ audio;

        sound.setUrl(url);
        sound.setName("");
        sound.setText(pron);
        QUrl sourceUrl = wordInfo.audio;
        QFileInfo fileinfo("./shanbaymp3/" + audio );
        if (fileinfo.exists()) {
            sourceUrl = QUrl::fromLocalFile("./shanbaymp3/" + audio );
        }
        sound.setSource(sourceUrl);
        unit.setSound(sound);
        list.append(unit);
    }
    return list;
}
