#ifndef FILEWORDS_H
#define FILEWORDS_H

#include <QLabel>
#include <QTimer>
#include <QWidget>

namespace Ui {
class FileWords;
}
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

class FileWords : public QWidget
{
    Q_OBJECT

public:
    explicit FileWords(QWidget *parent = 0);
    ~FileWords();
public Q_SLOTS:
    void onPushButtonClicked();
    void onPushButton2Clicked();

private:
    Ui::FileWords *ui;
    DropLabel* dropLabel_;
    QString toFile_;

};

#endif // FILEWORDS_H
