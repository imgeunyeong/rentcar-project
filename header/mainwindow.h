#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "userinfo.h"
#include "thread.h"
#include "database.h"
#include "chat.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int sock,int i,QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void addcount(QString msg);
    //int i;
    void minus(QString msg);


private:
    Ui::MainWindow *ui;
    Database dbObj;
    int sock;
    Thread * thread;
     int i;

};
#endif // MAINWINDOW_H
