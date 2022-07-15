#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vacation.h"
#include "reservation.h"
#include <QTableWidgetItem>
#include "rentcurr.h"
#include "chat.h"
#include "QDebug"

MainWindow::MainWindow(int sock,int i,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<QString::number(i);
    if(i==0)
        ui->label_9->hide();
    this->sock=sock;
    thread = new Thread(sock, this);
    connect(thread, SIGNAL(setMsg(QString)), this, SLOT(addcount(QString)));
    connect(thread, SIGNAL(endValue(QString)), this, SLOT(minus(QString)));
    thread->start(); //실행
    this->i=i;//받아온 i로 멤버 i를 초기화
}

void MainWindow::minus(QString msg)
{
    ui->label_9->hide();
    i=0;
    qDebug()<<QString::number(i);
}

void MainWindow::addcount(QString msg)
{
    ui->label_9->show();
    ui->label_9->setText("  "+QString::number(++i));//인티저를 큐스트링으로 바꿔서 라벨에 넣기
    qDebug()<<QString::number(i);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    userinfo obj;
    obj.setModal(true);
    obj.exec();
    this->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->hide();
    vacation obj;
    obj.setModal(true);
    obj.exec();
    this->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    this ->hide();
    reservation obj;
    obj.exec();
    this->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    this ->hide();
    rentcurr obj;
    obj.setModal(true);
    obj.exec();
    this->show();
}

void MainWindow::on_pushButton_clicked()
{   i=0;
    ui->label_9->hide();
    this ->hide();
    chat obj(sock,thread);
    obj.setModal(true);
    obj.exec();
    this->show();

}
