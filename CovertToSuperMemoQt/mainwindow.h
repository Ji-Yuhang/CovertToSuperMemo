#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include "filewords.h"
#include "randomwords.h"
#include "shanbayexplain.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);


private:
    Ui::MainWindow *ui;
    FileWords fileWords_;
    RandomWords randomWords_;
    ShanbayExplain shanbayExplain_;
};

#endif // MAINWINDOW_H
