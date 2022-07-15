#ifndef USERINFO_H
#define USERINFO_H

#include <QDialog>
#include <QMessageBox>
#include "database.h"


namespace Ui {
class userinfo;
}

class userinfo : public QDialog
{
    Q_OBJECT

public:
    explicit userinfo(QWidget *parent = nullptr);
    ~userinfo();

    void showuser();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::userinfo *ui;
    QSqlQuery query; //실행
    QSqlRecord rec; //열번호
    std::string query_string;  //쿼리실행문담기?
};

#endif // USERINFO_H
