#ifndef RESERVATION_H
#define RESERVATION_H

#include <QDialog>
#include "database.h"

namespace Ui {
class reservation;
}

class reservation : public QDialog
{
    Q_OBJECT

public:
    explicit reservation(QWidget *parent = nullptr);
    ~reservation();
    void showreserv();

private:
    Ui::reservation *ui;
    QSqlQuery query; //실행
    QSqlRecord rec; //열번호
    std::string query_string;  //쿼리실행문담기?

};

#endif // RESERVATION_H
