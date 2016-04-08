#include "droplabel.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QUrl>
#include <QPainter>
#include <QDateTime>
#include <QProcess>
#include <QMimeData>
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
    qDebug() << urls;
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
