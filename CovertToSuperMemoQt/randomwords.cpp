#include "randomwords.h"
#include "ui_randomwords.h"
#include "collins.h"
#include "util.hxx"
#include <QDesktopServices>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QUrl>
RandomWords::RandomWords(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RandomWords)
{
    ui->setupUi(this);
    connect(ui->randomButton, SIGNAL(clicked()), this, SLOT(onRandomButtonClicked()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onCollinsStarChanged(int)));
    remoteSupermemoInfo_.initInfoList();
}

RandomWords::~RandomWords()
{
    delete ui;
}

void RandomWords::initCollinsLabel()
{
    onCollinsStarChanged(0);

}

void RandomWords::onRandomButtonClicked()
{
    int star = 5 - ui->comboBox->currentIndex();
    int count = ui->comboBox_2->currentText().toInt();

    QList<int> unKnownList;
    Q_FOREACH(SuperMemoInfo info, remoteSupermemoInfo_.infoList) {
        if (info.isKnwon == 1) {
        } else {
            unKnownList.append(info.word_id);
        }
    }
    QList<CollinsInfo> collinsList = COLLINS->starCollins(star);
    QList<CollinsInfo> unKnownCollinsList;
    Q_FOREACH(CollinsInfo info, collinsList) {
        if (unKnownList.contains(info.wordID)) {
            unKnownCollinsList.append(info);
        }
    }
//    QList<int> randomList;
//    for (int i = 0; i < count; ++i) {
//        randomList.append(qrand() % unKnownCollinsList.size());
//    }

    QList<CollinsInfo> randomCollinsList;
//    int index = 0;
//    Q_FOREACH(CollinsInfo info, unKnownCollinsList) {
//        if (randomList.contains(index)) {
//            randomCollinsList.append(info);
//        }
//        index++;
//    }
    while (randomCollinsList.size() < count) {
        CollinsInfo info = findRandomWord(unKnownCollinsList);
        QStringList wordList;
        Q_FOREACH(CollinsInfo tempInfo, randomCollinsList) {
            wordList.append(tempInfo.word);
        }
        if (!wordList.contains(info.word))
            randomCollinsList.append(info);
    }

    ui->listWidget->clear();

    randomWordInfoList_.clear();
    Q_FOREACH(CollinsInfo info, randomCollinsList) {
       ui->listWidget->addItem(info.word);
       randomWordInfoList_.append(info);
    }

}

void RandomWords::onCollinsStarChanged(int index)
{
    QTime time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);

    int star = 5 - index;
    QList<int> unKnownList;
    Q_FOREACH(SuperMemoInfo info, remoteSupermemoInfo_.infoList) {
        if (info.isKnwon == 1) {

        } else {
            unKnownList.append(info.word_id);
        }
    }
    int unknow = 0;
    QList<CollinsInfo> collinsList = COLLINS->starCollins(star);
    int total = collinsList.size();
    Q_FOREACH(CollinsInfo info, collinsList) {
        if (unKnownList.contains(info.wordID)) {
            unknow++;
        }
    }
    int know = total - unknow;
    QString text = QString("%1/%2").arg(know).arg(total);

    ui->label_6->setText(text);
    ui->label_5->setText(QString("%1%").arg(know*100.0/total));
}

CollinsInfo RandomWords::findRandomWord(const QList<CollinsInfo> &unKnowWordList)
{
    int index = qrand() % unKnowWordList.size();
    return unKnowWordList.at(index);
}




void RandomWords::on_covertButton_clicked()
{
    QList<CollinsInfo> infoList = randomWordInfoList_;
    QStringList wordList;
    Q_FOREACH(CollinsInfo info, infoList) {
        wordList.append(info.word);
    }
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    ui->progressBar->show();
    ui->label_4->setText("");
    ui->label_4->show();
    ui->openFileDirButton->hide();

    QString date = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    toFile_ = "SuperMemo" + date +".xml";
    bool success = Util::covertToSuperMemoXML(wordList,toFile_,ui->progressBar,ui->label_4);
    if(success) ui->openFileDirButton->show();
    ui->label_4->hide();


}

void RandomWords::on_openFileDirButton_clicked()
{
    QFileInfo fileInfo(toFile_);
    QDir dir = fileInfo.dir();
    QString abPath = dir.absolutePath();
    QUrl url = QUrl::fromLocalFile(abPath);
    QDesktopServices::openUrl(url);

}

void RandomWords::on_setFlagKnowButton_clicked()
{
    QStringList wordList;
    Q_FOREACH(CollinsInfo info, randomWordInfoList_) {
        wordList.append(info.word);
    }
    bool success = remoteSupermemoInfo_.setFlagKnown(wordList);
    if (!success) {
        QMessageBox::warning(0,"set flag to known ERROR","set flag to known ERROR");

    } else {
        QMessageBox::information(0, "SUCCESS","set flag SUCCESS!");
    }

}
