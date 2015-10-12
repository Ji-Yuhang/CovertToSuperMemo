#ifndef RANDOMWORDS_H
#define RANDOMWORDS_H

#include "remotesupermemoinfo.h"

#include <QWidget>

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

private:
    Ui::RandomWords *ui;
    RemoteSupermemoInfo remoteSupermemoInfo_;

};

#endif // RANDOMWORDS_H
