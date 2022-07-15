#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <iostream>
#include "database.h"

#define BUF_SIZE 1024
using namespace std;

void *save_database(void *arg);
void *handle_clnt(void *arg);
void error_handling(const char *msg);
int clnt_cnt = 0;
int sockList[5];
char msg[BUF_SIZE];
Database obj;
char query[1040];

pthread_mutex_t mutx;

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock, str_len;
    //char msg[BUF_SIZE];
    struct sockaddr_in serv_adr, clnt_adr;
    unsigned int clnt_adr_sz;
    pthread_t t_id,t_id2;

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    pthread_mutex_init(&mutx, NULL); //뮤텍스 정의
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    while (1)
    {
        clnt_adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);

        pthread_mutex_lock(&mutx);
        sockList[clnt_cnt++]=clnt_sock;
        pthread_mutex_unlock(&mutx);

        printf("현재 연결된 인원수 : %d\n", clnt_cnt);
        printf("클라이언트 IP : %s\n", inet_ntoa(clnt_adr.sin_addr));
        printf("클라이언트 소켓 : %d번\n\n", clnt_sock);

        pthread_create(&t_id, NULL, handle_clnt, (void *)&clnt_sock); //클라이언트에서 정보를 받는 쓰레드
      //  pthread_create(&t_id2, NULL, save_database, (void *)&clnt_sock); //내가 추가한거
        pthread_detach(t_id);
      //  pthread_detach(t_id2); //추가한거 
    }
    close(serv_sock);

    return 0;
}

void *save_database(void *arg)  //데이터베이스에 채팅 저장하기 
{   
    while(1)
   // {
        sprintf(query,"INSERT INTO chat(chatting) VALUES('%s')",msg);
        if (mysql_query(&obj.conn, query) != 0)
        {
            fprintf(stderr, "Failed to connect to databases: Error: %s\n",mysql_error(&obj.conn));
        }
        //obj.result = mysql_store_result(&obj.conn);
        //obj.row = mysql_fetch_row(obj.result);
   // }
}

void *handle_clnt(void *arg)
{
    int clnt_sock = *((int *)arg);
    int str_len = 0;
    char msg[BUF_SIZE];
    
    /*
    for(int i=0; i<clnt_cnt; i++)
    {
        if(sockList[i]==clnt_sock)//!=
        {
            write(sockList[i], "chatting", sizeof("chatting"));
            sleep(3);
            write(sockList[i], "chatting", sizeof("chatting"));              
        }
    }*/
             
    while(read(clnt_sock, msg, sizeof(msg))>0)
    {   
        if(strcmp(msg,"")!=0)
        {
            sprintf(query,"INSERT INTO chat(chatting) VALUES('%s')",msg);
           // mysql_query(&obj.conn,query);
            if (mysql_query(&obj.conn, query) != 0)
            {
                fprintf(stderr, "Failed to connect to databases: Error: %s\n",mysql_error(&obj.conn));
            }
        }
        if(msg=="end") ////////////////////////////////////////////
        {    for(int i=0; i<clnt_cnt;i++)
            { 
                if(sockList[i]==clnt_sock) //!=
                write(sockList[i],"end",sizeof("end"));

            }        /////////////////////////////////
        }
        cout<<"받은 메세지: "<<msg<<endl;        
        for(int i=0; i<clnt_cnt; i++)
        {
            if(sockList[i]!=clnt_sock)
            {
                write(sockList[i], msg, sizeof(msg));
            }
        }
        memset(msg, 0, sizeof(msg));
    } 
    
    for(int i=0; i < clnt_cnt; i++)
        {
            if(sockList[i] == clnt_sock)
            {	
                //메모리 복사함수. /복사받을 포인터/복사될 포인터/크기. 
                //나간 클라이언트만 빼고 전체가 복사되어야 하니까 numchat-
                memcpy(&sockList[i], &sockList[i+1], sizeof(int) * (clnt_cnt - (i+1)));
                break;
            }
        }
        clnt_cnt--;   
}

void error_handling(const char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}