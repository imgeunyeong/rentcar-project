#include "vacation.h"
#include "ui_vacation.h"
#include "addvacation.h"
#include <QMessageBox>
#include <qdebug.h>


vacation::vacation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vacation)
{
    ui->setupUi(this);
    showspot();
}

vacation::~vacation()
{
    delete ui;
}

void vacation::showspot()
{
    ui->tableWidget->clear();
    query.exec("SELECT * FROM vacation");
    rec = query.record();
    int number = rec.indexOf("course");
    int name = rec.indexOf("addr");
    ui->tableWidget->setRowCount(query.size());
    ui->tableWidget->setColumnCount(rec.count());
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("코스번호"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("관광지명"));
    int i=0;
    while(query.next())
    {
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(query.value(number).toString()));
        ui->tableWidget->setItem(i++,1, new QTableWidgetItem(query.value(name).toString()));
    }
 }


void vacation::on_pushButton_2_clicked()
{
    this->hide();
    addvacation obj2;
    obj2.setModal(true);
    obj2.exec();
    this->show();
}

void vacation::on_pushButton_3_clicked() //수정
{
    QTableWidgetItem *currentText=ui->tableWidget->currentItem(); //선택한 row 값 가져와서
    std::string line=currentText->text().toStdString();

    int colNum=ui->tableWidget->currentColumn(); //선택한 열정보
    int rowNum=ui->tableWidget->currentRow(); //선택한 행정보

    if(colNum==0) //0번째 열을 선택했을때 관광지 이름
    {
        //string updateName=ui->lineEdit->text().toStdString(); //라인에디터에 쓴 정보 가져와서
        qDebug()<<QString::fromStdString(line);
        qDebug()<<QString::fromStdString(ui->tableWidget->item(rowNum, 1)->text().toStdString());

        query_string="UPDATE vacation SET course='"+line+"' WHERE addr='"+ui->tableWidget->item(rowNum, 1)->text().toStdString()+"'";
        //1번째 열에 있는 아이디를 기준으로 이름을 업데이트
         qDebug()<<QString::fromStdString(query_string);

        query.exec(QString::fromStdString(query_string));//쿼리문 실행
        QMessageBox::information(nullptr,"Succsefull","이름 변경이 완료되었습니다");
      //  ui->lineEdit->clear(); //라인에디터 비우기
        showspot();

    }
   if(colNum==1) //나머지 행을 선택했을때
    {
        qDebug()<<QString::fromStdString(line);
        qDebug()<<QString::fromStdString(ui->tableWidget->item(rowNum, 0)->text().toStdString());

        query_string="UPDATE vacation SET addr='"+line+"' WHERE course='"+ui->tableWidget->item(rowNum, 0)->text().toStdString()+"'";
        qDebug()<<QString::fromStdString(query_string);
        query.exec(QString::fromStdString(query_string));//쿼리문 실행
        QMessageBox::information(nullptr,"Succsefull","주소 변경이 완료되었습니다");
        showspot();
     }


}

void vacation::on_delete_2_clicked() //삭제
{
    QTableWidgetItem *currentText=ui->tableWidget->currentItem();
    std::string line=currentText->text().toStdString();

    int colNum=ui->tableWidget->currentColumn(); //선택한 열정보
   // int rowNum=ui->tableWidget->currentRow(); //선택한 행정보

    if(colNum==0) //관광지 이름
    {

        qDebug()<<QString::fromStdString(line);

        query_string="DELETE FROM vacation WHERE course='"+line+"'";

        qDebug()<<QString::fromStdString(query_string);

        query.exec(QString::fromStdString(query_string));
        QMessageBox::information(nullptr,"Succsefull","삭제가 완료되었습니다");
        showspot();
     }

     if(colNum==1)
     {
        qDebug()<<QString::fromStdString(line);

        query_string="DELETE FROM vacation WHERE addr='"+line+"'";

        qDebug()<<QString::fromStdString(query_string);

        query.exec(QString::fromStdString(query_string));
        QMessageBox::information(nullptr,"Succsefull","삭제가 완료되었습니다");
        showspot();
     }

}
