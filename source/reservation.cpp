#include "reservation.h"
#include "ui_reservation.h"

reservation::reservation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reservation)
{
    ui->setupUi(this);
    showreserv();
}

reservation::~reservation()
{
    delete ui;
}

void reservation::showreserv()
{
    ui->tableWidget->clear();
    query.exec("SELECT * FROM reservation");
    rec = query.record();
    int id = rec.indexOf("id");
    int carname = rec.indexOf("carname");     //얘네도 숫잔데...
    int startdate = rec.indexOf("startdate");
    int enddate = rec.indexOf("enddate");
    int rentcost = rec.indexOf("rentcost");
    int reservnum = rec.indexOf("reservnum");
    ui->tableWidget->setRowCount(query.size());
    ui->tableWidget->setColumnCount(rec.count());
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("아이디"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("차 이름"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("랜트일"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("반납일"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("랜트 가격"));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("예약번호"));
    int i=0;
    while(query.next())
    {
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(query.value(id).toString()));
        ui->tableWidget->setItem(i,1, new QTableWidgetItem(query.value(carname).toString()));
        ui->tableWidget->setItem(i,2, new QTableWidgetItem(query.value(startdate).toString()));
        ui->tableWidget->setItem(i,3, new QTableWidgetItem(query.value(enddate).toString()));
        ui->tableWidget->setItem(i,4, new QTableWidgetItem(query.value(rentcost).toString()));
        ui->tableWidget->setItem(i++,5, new QTableWidgetItem(query.value(reservnum).toString()));
    }
 }
