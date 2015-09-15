#ifndef RANDOMWORDS_H
#define RANDOMWORDS_H

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
public Q_SLOTS:
    void onRandomButtonClicked();

private:
    Ui::RandomWords *ui;
};

#endif // RANDOMWORDS_H
