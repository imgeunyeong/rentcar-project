#include "addvacation.h"
#include "ui_addvacation.h"
#include <QMessageBox>

addvacation::addvacation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addvacation)
{
    ui->setupUi(this);
}

addvacation::~addvacation()
{
    delete ui;
}

void addvacation::on_pushButton_clicked()
{
        std::string name=ui->lineEdit->text().toStdString();
        std::string addr=ui->lineEdit_2->text().toStdString();

        query_string="INSERT INTO vacation(course,addr) VALUES('"+name+"','"+addr+"')";
        query.exec(QString::fromStdString(query_string)); //쿼리문 실행

        QMessageBox::information(nullptr,"Succsefull","추가되었습니다");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        this->close();

}
