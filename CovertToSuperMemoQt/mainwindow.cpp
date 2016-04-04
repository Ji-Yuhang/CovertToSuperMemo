#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDebug>
#include <QDragEnterEvent>
#include <QMessageBox>
#include <QPainter>
#include <QUrl>
#include "util.hxx"
#include <QProcess>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setFocusPolicy(Qt::NoFocus);
    ui->stackedWidget->insertWidget(0,&fileWords_);
    ui->stackedWidget->insertWidget(1,&randomWords_);
    ui->stackedWidget->insertWidget(2,&shanbayExplain_);

    randomWords_.initCollinsLabel();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "MainWindow dragEnterEvent";
}

void MainWindow::dropEvent(QDropEvent *event)
{
    qDebug() << "MainWindow dropEvent";

}




