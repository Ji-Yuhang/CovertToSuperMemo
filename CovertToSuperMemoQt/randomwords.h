#ifndef RANDOMWORDS_H
#define RANDOMWORDS_H

#include "remotesupermemoinfo.h"

#include <QWidget>
#include "collins.h"
namespace Ui {
class RandomWords;
}

class RandomWords : public QWidget
{
    Q_OBJECT

public:
    explicit RandomWords(QWidget *parent = 0);
    ~RandomWords();
    void initCollinsLabel();
public Q_SLOTS:
    void onRandomButtonClicked();

private slots:
    void onCollinsStarChanged(int);

    void on_covertButton_clicked();

    void on_openFileDirButton_clicked();

    void on_setFlagKnowButton_clicked();

    void onRemoveWord();
private:
    void contextMenuEvent(QContextMenuEvent * event);
private:
    CollinsInfo findRandomWord(const QList<CollinsInfo>& unKnowWordList);
    Ui::RandomWords *ui;
    RemoteSupermemoInfo remoteSupermemoInfo_;
    QList<CollinsInfo> randomWordInfoList_;
    QString toFile_;

};

#endif // RANDOMWORDS_H
