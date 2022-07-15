#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QtSql>
#include <QSqlTableModel>

class Database
{
private:
    QSqlDatabase db;
public:
    Database() {
        open_db();  //만들면 생성자에서 알아서 함수실행
    }
    void open_db()
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("127.0.0.1");      // IP 또는 DNS Host name
        db.setDatabaseName("rent"); // DB명
        db.setUserName("root");     // 계정 명
        db.setPassword("root1234");     // 계정 Password
        db.setPort(3306);

        if(!db.open())
        {
            qDebug()<<"connect error";
            exit(1);
        }
    }
    ~Database() {
        db.close();
    }
};

#endif // DATABASE_H
