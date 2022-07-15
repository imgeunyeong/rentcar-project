#include "chat.h"
#include "ui_chat.h"

chat::chat(int sock,Thread *thread, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    this->sock=sock;
    connect(thread, SIGNAL(setMsg(QString)), this, SLOT(chatAppend(QString)));
////////////
    query.exec("SELECT chatting FROM chat");
    rec = query.record();
    int chatting = rec.indexOf("chatting");
    while(query.next())
    {
        ui->textBrowser->append((query.value(chatting).toString()));
    }

}

chat::~chat()
{
    delete ui;
}


void chat::chatAppend(QString msg)
{

    ui->textBrowser->append(msg);
}

void chat::on_pushButton_2_clicked() //보내기버튼
{
    string chatMsg="[Server] "+ui->lineEdit->text().toStdString();
    ui->textBrowser->append(QString::fromStdString(chatMsg));
    write(sock, chatMsg.c_str(), chatMsg.length());
    ui->lineEdit->clear();
}

void chat::closeEvent(QCloseEvent *event) //x버튼
{
    string chatMsg="end";
    write(sock, chatMsg.c_str(), chatMsg.length());
    this->close();
}

