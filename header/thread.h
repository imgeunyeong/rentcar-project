#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include <QtDebug>
#include <cstring>

class Thread: public QThread
{
    Q_OBJECT

public:
    Thread(int sock, QObject *parent=0);

private:
    void run();
    int sock;

signals:  //ㅇㅐ가 EMIT 같은건
    void endValue(QString msg);
    void setMsg(QString msg);
};

#endif // THREAD_H
