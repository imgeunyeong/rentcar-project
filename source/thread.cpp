#include "thread.h"
#include <unistd.h>
#include <QMessageBox>

Thread::Thread(int sock, QObject *parent) :
    QThread(parent)
{
    this->sock=sock;
}

void Thread::run()
{
    while(1)
    {
        char msg[1024];
        read(sock, msg, sizeof(msg));
        //if(read(sock, msg, sizeof(msg))>0)
        //     emit setMsg(QString(msg)); //메세지올때마다 발생하ㅡㄴ 시그널

        if(std::string(msg)=="end")
            emit endValue(QString(msg)); //메세지 큐스트링으로 바꿔서 신호발생시키기
        else
             emit setMsg(QString(msg));



    }
}
