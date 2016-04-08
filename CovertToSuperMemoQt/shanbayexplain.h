#ifndef SHANBAYEXPLAIN_H
#define SHANBAYEXPLAIN_H

#include <QWidget>
#include "droplabel.h"
namespace Ui {
class ShanbayExplain;
}

class ShanbayExplain : public QWidget
{
    Q_OBJECT

public:
    explicit ShanbayExplain(QWidget *parent = 0);
    ~ShanbayExplain();
public Q_SLOTS:
    void onPushButtonClicked();
    void onPushButton2Clicked();

private:
    Ui::ShanbayExplain *ui;
    DropLabel* dropLabel_;
    QString toFile_;

};

#endif // SHANBAYEXPLAIN_H
