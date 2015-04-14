#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDebug>
#include <QDragEnterEvent>
#include <QMessageBox>
#include <QPainter>
#include <QUrl>
#include "util.hxx"
#include <QProcess>

DropLabel::DropLabel(QWidget *parent)
    :QLabel(parent)
    ,isAnimation_(false)
    ,dashOffset_(0.0)
{
    this->setAcceptDrops(true);
    QString text = QString::fromUtf8("\xE6\x8A\x8A\xE6\x96\x87\xE4\xBB\xB6\xE6\x8B\x96\xE5\x88\xB0\xE8\xBF\x99\xE9\x87\x8C\xE6\x9D\xA5");
    this->setText(text);
    this->setAlignment(Qt::AlignCenter);

    connect(&timer_, SIGNAL(timeout()), this, SLOT(onTimeout()));
    isAnimation_ = true;
    timer_.start(100);
    this->setWordWrap(true);

}

DropLabel::~DropLabel()
{

}

void DropLabel::setAnimation(bool open)
{
    isAnimation_ = open;
}

void DropLabel::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "DropLabel dragEnterEvent";
    this->update();

    if (event->mimeData()->hasFormat("text/uri-list")) {
            event->acceptProposedAction();
    }
}

void DropLabel::dropEvent(QDropEvent *event)
{
    qDebug() << "DropLabel dropEvent";
    isAnimation_ = false;
    timer_.stop();
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) return;
    QString path = urls.first().toLocalFile();
    qDebug() << " event->mimeData()->text() " << path;
    setText(path);
    filePath_ = path;
    event->accept();
    this->update();
}

void DropLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    if (!isAnimation_) return;

    QPainter p(this);
    QPen pen;
    pen.setStyle((Qt::DashLine));
    pen.setWidth(2);
    pen.setColor(Qt::red);
    pen.setDashOffset(dashOffset_);
    p.setPen(pen);
    p.drawRect(2,2,this->width() - 4, this->height() - 4);
}

void DropLabel::onTimeout()
{
    dashOffset_ += 0.5;
    this->update();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dropLabel_(new DropLabel)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    ui->gridLayout->addWidget(dropLabel_);
    ui->progressBar->hide();
    ui->label_2->hide();
    ui->pushButton_2->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dropLabel_;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "MainWindow dragEnterEvent";
}

void MainWindow::dropEvent(QDropEvent *event)
{
    qDebug() << "MainWindow dropEvent";

}




void MainWindow::on_pushButton_clicked()
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
    toFile_ = "SuperMemo" + date +".txt";
    Util::covertToSuperMemo(fromFile, toFile_, ui->progressBar,ui->currentWord);
    ui->progressBar->hide();
    ui->currentWord->hide();
    ui->label_2->show();
    ui->pushButton_2->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString path = toFile_;
    path.replace("/","\\");
    QProcess::startDetached("explorer /select, "+path);
//    LPCSTR tempPath = " /select,D:\\z1_学习资料\\Qt\\Qt学习之路.pdf";
//    ShellExecuteA(0,"open","explorer.exe",filePath,NULL,true);
}
