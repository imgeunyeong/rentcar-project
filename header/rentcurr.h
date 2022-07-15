#ifndef RENTCURR_H
#define RENTCURR_H

#include <QDialog>
#include <vector>
#include "database.h"
using namespace std;

namespace Ui {
class rentcurr;
}

class rentcurr : public QDialog
{
    Q_OBJECT

public:
    explicit rentcurr(QWidget *parent = nullptr);
    ~rentcurr();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::rentcurr *ui;
    int i;
    vector <string>arr;
    QSqlQuery query; //실행
    QSqlRecord rec; //열번호
    std::string query_string;
};

#endif // RENTCURR_H
