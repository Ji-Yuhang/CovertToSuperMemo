#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
namespace Ui {
class MainWindow;
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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    DropLabel* dropLabel_;
    QString toFile_;
};

#endif // MAINWINDOW_H
