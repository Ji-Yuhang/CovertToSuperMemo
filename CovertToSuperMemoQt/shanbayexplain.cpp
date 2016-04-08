#include "shanbayexplain.h"
#include "ui_shanbayexplain.h"
#include <QMessageBox>
#include <QProcess>
#include "collinswordtomemo.h"
#include "util.hxx"
#include <QDateTime>
#include "shanbaywordtomemo.h"
ShanbayExplain::ShanbayExplain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShanbayExplain),
    dropLabel_(new DropLabel)
{
    ui->setupUi(this);

    this->setAcceptDrops(true);
    ui->gridLayout->addWidget(dropLabel_);
    ui->progressBar->hide();
    ui->label_2->hide();
    ui->pushButton_2->hide();
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(onPushButtonClicked()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(onPushButton2Clicked()));

}

ShanbayExplain::~ShanbayExplain()
{
    delete ui;
    delete dropLabel_;
}


void ShanbayExplain::onPushButtonClicked()
{
    QString fromFile = dropLabel_->filePath();
    if (fromFile.isEmpty()) {
        QString emptyFileStr = QString::fromUtf8("\xE7\xA9\xBA\xE6\x96\x87\xE4\xBB\xB6\xEF\xBC\x8C\xE6\x97\xA0\xE6\xB3\x95\xE8\xBD\xAC\xE6\x8D\xA2");
        QMessageBox::warning(0, "Empty File", emptyFileStr);
    }
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    ui->progressBar->show();
    ui->currentWord->setText("");
    ui->currentWord->show();

    QString date = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    toFile_ = "SuperMemo" + date +".xml";

    QStringList wordList = Util::getSourceWordList(fromFile);
    ShanbayWordToMemo collinsToMemo(new EnWordToShanbayCN);
    collinsToMemo.addWordList(wordList);
    QSharedPointer<MemoCollection> collection = collinsToMemo.makeCollection();

    collection->shuffle();
    bool success = collection->toXmlFile(toFile_);
    qDebug() << "ShanbayExplain ShanbayWordToMemo MemoCollection  toXmlFile" << success;

    ui->progressBar->hide();
    ui->currentWord->hide();
    ui->label_2->show();
    ui->pushButton_2->show();
}

void ShanbayExplain::onPushButton2Clicked()
{
    QString path = toFile_;
    path.replace("/","\\");
    QProcess::startDetached("explorer /select, "+path);
//    LPCSTR tempPath = " /select,D:\\z1_学习资料\\Qt\\Qt学习之路.pdf";
//    ShellExecuteA(0,"open","explorer.exe",filePath,NULL,true);
}
