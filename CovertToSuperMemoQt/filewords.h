#ifndef FILEWORDS_H
#define FILEWORDS_H

#include <QLabel>
#include <QTimer>
#include <QWidget>
#include "droplabel.h"
namespace Ui {
class FileWords;
}

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
