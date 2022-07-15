#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <iostream>
#define BUF_SIZE 100
#define NAME_SIZE 20

void *send_msg(void *arg);
void *recv_msg(void *arg);
void error_handling(char *msg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    pthread_t snd_thread, rcv_thread;
    void *thread_return;
/*
    if (argc != 4)
    {
        printf("Usage: %s <IP> <port> <name>\n", argv[0]);
        exit(1);
    }
*/
  //  sprintf(name, "[%s]", argv[3]);
    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(atoi("9070"));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    pthread_create(&rcv_thread, NULL, recv_msg, (void *)&sock);
    pthread_create(&snd_thread, NULL, send_msg, (void *)&sock);
    pthread_join(rcv_thread, &thread_return);
    pthread_join(snd_thread, &thread_return);
    close(sock);

    return 0;
}

void *send_msg(void *arg)
{
    int sock = *((int *)arg);
    char name_msg[NAME_SIZE + BUF_SIZE];

    while (1)
    {
        fgets(msg, BUF_SIZE, stdin);
        msg[strlen(msg)-1]='\0';
        
        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
        {
            close(sock);
            exit(0);
        }
   
        sprintf(name_msg, "%s %s", name, msg); //name,msg 입력받은걸 한문장으로 엮어서 name_msg에 저장
        write(sock, name_msg, strlen(name_msg));
    }

    return NULL;
}

void *recv_msg(void *arg)
{
    int sock = *((int *)arg);
    char name_msg[NAME_SIZE + BUF_SIZE];
    int str_len;

    while ((str_len = read(sock, name_msg, NAME_SIZE + BUF_SIZE - 1))>0)
    {        
        if (str_len == -1)
            return (void *)-1;
        
        name_msg[str_len+1] = 0;
        //std::cout<<name_msg<<std::endl;
        fputs(name_msg, stdout);
        if(strcmp(name_msg,"")!=0) //받은게 공백 아닐때만 출력
            printf("\n");
        memset(name_msg,0,sizeof(name_msg));
    }

    return NULL;
}

void error_handling(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}