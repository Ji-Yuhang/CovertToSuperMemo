#include "filewords.h"
#include "ui_filewords.h"
#include <QMessageBox>
#include <util.hxx>
#include <QDebug>
#include <QDragEnterEvent>
#include <QUrl>
#include <QPainter>
#include <QDateTime>
#include <QProcess>
#include <QMimeData>


FileWords::FileWords(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileWords),
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

FileWords::~FileWords()
{
    delete ui;
    delete dropLabel_;

}


void FileWords::onPushButtonClicked()
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
    Util::covertToSuperMemoXML(fromFile, toFile_, ui->progressBar,ui->currentWord);
//    Util::covertToSuperMemo(fromFile, toFile_, ui->progressBar,ui->currentWord);

    ui->progressBar->hide();
    ui->currentWord->hide();
    ui->label_2->show();
    ui->pushButton_2->show();
}

void FileWords::onPushButton2Clicked()
{
    QString path = toFile_;
    path.replace("/","\\");
    QProcess::startDetached("explorer /select, "+path);
//    LPCSTR tempPath = " /select,D:\\z1_学习资料\\Qt\\Qt学习之路.pdf";
//    ShellExecuteA(0,"open","explorer.exe",filePath,NULL,true);
}
