#ifndef DROPLABEL_H
#define DROPLABEL_H

#include <QLabel>
#include <QTimer>
class DropLabel : public QLabel
{
Q_OBJECT
public:
    explicit DropLabel(QWidget *parent = 0);
    ~DropLabel();
    void setAnimation(bool open);
    QString filePath() {return filePath_;}
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void paintEvent(QPaintEvent* event);
private:
    bool isAnimation_;
    qreal dashOffset_;
    QTimer timer_;
    QString filePath_;
private Q_SLOTS:
    void onTimeout();
};


#endif // DROPLABEL_H
