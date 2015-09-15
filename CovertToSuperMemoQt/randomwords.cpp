#include "randomwords.h"
#include "ui_randomwords.h"

RandomWords::RandomWords(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RandomWords)
{
    ui->setupUi(this);
    connect(ui->randomButton, SIGNAL(clicked()), this, SLOT(onRandomButtonClicked()));
}

RandomWords::~RandomWords()
{
    delete ui;
}

void RandomWords::onRandomButtonClicked()
{
//    do_something_awesome
}
