#include "rentcurr.h"
#include "ui_rentcurr.h"
#include <cstring>
#include <unistd.h>
#include <QPixmap>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <sys/types.h>
#include <vector>
using namespace std;

rentcurr::rentcurr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rentcurr)
{
    ui->setupUi(this);
    i=0;
    query_string="SELECT * FROM car";
    query.exec(QString::fromStdString(query_string));
    while(query.next()) //row하나 가져옴 while문으로 끝까지.(전체)
    {
        arr.push_back("Model:  "+query.value(0).toString().toStdString()+"\n"+
                      "Type:  "+query.value(1).toString().toStdString()+"\n"+
                      "Fuel:  "+query.value(2).toString().toStdString()+"\n"+
                      "Cost:  "+query.value(3).toString().toStdString()+"원\n"+ //큐스트링으로 바꿔서 다시 스트링으로 바꿔줌 컬럼4개를 string 형태로 묶어서 하나로 벡터에 저장
                      "Remaining:  "+query.value(4).toString().toStdString()+"대");

    }
     ui->label_2->setText(arr[0].c_str()); //맨 첫번째(0번째)라벨 텍스트 set
}

rentcurr::~rentcurr()
{
    delete ui;
}

void rentcurr::on_pushButton_clicked()
{   if(i<5) ++i;
    string setImg = "/home/iot/다운로드/carpic/car"+to_string(i)+".jpg";  //파일명 숫자 ++해서 다른 이미지 불러오기 //"+to_string(i)+"가 숫자임
    ui->label->setPixmap(QPixmap(setImg.c_str())); //라벨 픽스맵을 경로에 저장된 jpg로 set
    ui->label_2->setText(arr[i].c_str()); //라벨 텍스트 넘기기 ++
}

void rentcurr::on_pushButton_2_clicked()
{
    if(i>0) --i;
       string setImg = "/home/iot/다운로드/carpic/car"+to_string(i)+".jpg";
       ui->label->setPixmap(QPixmap(setImg.c_str()));
       ui->label_2->setText(arr[i].c_str());
}
