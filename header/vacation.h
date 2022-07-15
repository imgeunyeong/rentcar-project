#ifndef VACATION_H
#define VACATION_H

#include <QDialog>
#include "database.h"

namespace Ui {
class vacation;
}

class vacation : public QDialog
{
    Q_OBJECT

public:
    explicit vacation(QWidget *parent = nullptr);
    ~vacation();
    void showspot();
    void addspot();
    void editspot();


private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_delete_2_clicked();

private:
    Ui::vacation *ui;
    QSqlQuery query;
    QSqlRecord rec;
    std::string query_string;
};

#endif // VACATION_H
