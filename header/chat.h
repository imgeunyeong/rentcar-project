#ifndef CHAT_H
#define CHAT_H
#include <QDialog>
#include <unistd.h>
#include "database.h"
#include "thread.h"
using namespace std;

namespace Ui {
class chat;
}

class chat : public QDialog
{
    Q_OBJECT

public:
    chat(int sock,Thread *thread, QWidget *parent = nullptr);
    ~chat();

private slots:

    void chatAppend(QString msg);
    //void on_lineEdit_returnPressed();


    //void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void closeEvent(QCloseEvent *event); //x버튼 눌렀을떄 실행되는 함수

private:
    Ui::chat *ui;
    QSqlQuery query;
    QSqlRecord rec;
    string SQL;
    int sock;
    string userId;

};

#endif // CHAT_H
