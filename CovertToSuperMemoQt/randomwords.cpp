#include "randomwords.h"
#include "ui_randomwords.h"
#include "collins.h"
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
    onCollinsStarChanged(5);

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
    QList<int> randomList;
    for (int i = 0; i < count; ++i) {
        randomList.append(qrand() % unKnownCollinsList.size());
    }

    QList<CollinsInfo> randomCollinsList;
    int index = 0;
    Q_FOREACH(CollinsInfo info, unKnownCollinsList) {
        if (randomList.contains(index)) {
            randomCollinsList.append(info);
        }
        index++;
    }
    ui->listWidget->clear();

    Q_FOREACH(CollinsInfo info, randomCollinsList) {
       ui->listWidget->addItem(info.word);
    }
    //    do_something_awesome
}

void RandomWords::onCollinsStarChanged(int index)
{
    int star = 5 - index;
    QList<int> unKnownList;
    Q_FOREACH(SuperMemoInfo info, remoteSupermemoInfo_.infoList) {
        if (info.isKnwon == 1) {

        } else {
            unKnownList.append(info.word_id);
        }
    }
    int know = 0;
    QList<CollinsInfo> collinsList = COLLINS->starCollins(star);
    int total = collinsList.size();
    Q_FOREACH(CollinsInfo info, collinsList) {
        if (unKnownList.contains(info.wordID)) {
            know++;
        }
    }
    QString text = QString("%1/%2").arg(know).arg(total);

    ui->label_6->setText(text);
    ui->label_5->setText(QString("%1%").arg(know*100.0/total));
}


