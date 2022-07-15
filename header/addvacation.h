#ifndef ADDVACATION_H
#define ADDVACATION_H

#include <QDialog>
#include "database.h"

namespace Ui {
class addvacation;
}

class addvacation : public QDialog
{
    Q_OBJECT

public:
    explicit addvacation(QWidget *parent = nullptr);
    ~addvacation();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addvacation *ui;
    QSqlQuery query;
    QSqlRecord rec;
    std::string query_string;
};

#endif // ADDVACATION_H
