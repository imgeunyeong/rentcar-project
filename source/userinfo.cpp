#include "userinfo.h"
#include "ui_userinfo.h"


userinfo::userinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userinfo)
{
    ui->setupUi(this);
    showuser();

}

userinfo::~userinfo()
{
    delete ui;
}

void userinfo::showuser()
{
    ui->tableWidget->clear();
    query.exec("SELECT * FROM usertable");
    rec = query.record();
    int id = rec.indexOf("id");//db 컬럼명
    int pw = rec.indexOf("pw");
    int grade = rec.indexOf("grade");
    ui->tableWidget->setRowCount(query.size());
    ui->tableWidget->setColumnCount(rec.count());
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("아이디"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("비밀번호"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("유저등급"));
    int i=0;
    while(query.next())
    {
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(query.value(id).toString()));
        ui->tableWidget->setItem(i,1, new QTableWidgetItem(query.value(pw).toString()));
        ui->tableWidget->setItem(i++,2, new QTableWidgetItem(query.value(grade).toString()));
    }
}

void userinfo::on_pushButton_clicked()
{
    ui->tableWidget->clear();
    query_string="SELECT * FROM usertable";
    query.exec(QString::fromStdString(query_string));
    rec=query.record();
    int i=0;
    while(query.next())
    {
        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("아이디"));
        ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("비밀번호"));
        ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("유저등급"));
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(rec.indexOf("id")).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(rec.indexOf("pw")).toString()));
        ui->tableWidget->setItem(i++,2,new QTableWidgetItem(query.value(rec.indexOf("grade")).toString()));
    }
}

void userinfo::on_pushButton_2_clicked()  //수정
{
    QTableWidgetItem *currentText=ui->tableWidget->currentItem();
    std::string line=currentText->text().toStdString();

    int colNum=ui->tableWidget->currentColumn();
    int rowNum=ui->tableWidget->currentRow();

    if(colNum==1)
    {

        qDebug()<<QString::fromStdString(line);
        qDebug()<<QString::fromStdString(ui->tableWidget->item(rowNum, 1)->text().toStdString());

        query_string="UPDATE usertable SET pw='"+line+"' WHERE id='"+ui->tableWidget->item(rowNum, 0)->text().toStdString()+"'";
        //
         qDebug()<<QString::fromStdString(query_string);
        query.exec(QString::fromStdString(query_string));
        QMessageBox::information(nullptr,"Succsefull","비밀번호 변경이 완료되었습니다");
        showuser();

    }
    else
        QMessageBox::information(nullptr,"error","비밀번호 변경만 가능합니다");

}

void userinfo::on_pushButton_3_clicked()//삭제
{
    QTableWidgetItem *currentText=ui->tableWidget->currentItem();
    std::string line=currentText->text().toStdString();

   // int colNum=ui->tableWidget->currentColumn(); //선택한 열정보
    int rowNum=ui->tableWidget->currentRow(); //선택한 행정보

    qDebug()<<QString::fromStdString(line);

    query_string="DELETE FROM usertable WHERE id='"+ui->tableWidget->item(rowNum, 0)->text().toStdString()+"'";

    qDebug()<<QString::fromStdString(query_string);

    query.exec(QString::fromStdString(query_string));
    QMessageBox::information(nullptr,"Succsefull","삭제가 완료되었습니다");
    showuser();

}
