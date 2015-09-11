#include "randomwords.h"
#include "ui_randomwords.h"

RandomWords::RandomWords(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RandomWords)
{
    ui->setupUi(this);
}

RandomWords::~RandomWords()
{
    delete ui;
}
