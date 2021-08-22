/**
 * @file main.cc
 * @author sbLee (lgh121546@naver.com)
 * @brief main Server
 * @version 0.1
 * @date 2021-08-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
// C++ header
#include <iostream>
#include <string>
#include <netdb.h>
#include <map>

// C header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <pthread.h>

using namespace std;

#define BUFSIZE 300

pthread_t g_thread[1024];
int g_clientCount = 0;

struct client {
    int index;
    int id;
    socklen_t len;
    struct sockaddr_in clnt_addr;
};

map<int, struct client> m_clntMap;

void error_handling(char *message);
void LOG(char *message);

void *thread_msg(void * pClient){
    char message[BUFSIZE];

    int str_len;
    while((str_len = read(((struct client *)pClient)->id, message, BUFSIZE)) != 0)
    {
        // client 측에 받은 데이터를 echo 형식으로 보냄
        write(((struct client *)pClient)->id, message, str_len);
        
        // write(1, inet_ntoa(clnt_addr.sin_addr), strlen(inet_ntoa(clnt_addr.sin_addr)) + 1);	
        // write(1, " : ", 4);	
        // write(1, message, str_len);

        printf("%d : %s\n", ((struct client *)pClient)->id, message);
    }

    puts("connect exit\n");
    return NULL;
}

int main(){
    struct sockaddr_in serv_addr;

    int serv_sock;
	int addr_size, str_len, state;
    const char _port[] = "8080";

	pid_t pid;

    // Socket Open
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(_port));

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
	{
		printf("bind() error\n");
	}

	if(listen(serv_sock, 5) == -1)
	{
		printf("listen() error\n");
	}

    while(1){
        struct client Client;

        Client.len = sizeof(Client.clnt_addr);
        
        Client.id = accept(serv_sock, (struct sockaddr*) &Client.clnt_addr, &Client.len);
        if(Client.id == -1)
        {
            printf("[CSocket::Accept] Client.id error occur!");
            return Client.id;
        }

        Client.index = g_clientCount;

        m_clntMap[Client.id] = Client;
        printf("Id : %d번님이 입장하셨습니다.\n", Client.id);

        pthread_create(&g_thread[g_clientCount], NULL, thread_msg, (void *) &Client);

        g_clientCount++;
    }
    
    for(int i = 0 ; i < g_clientCount ; i ++)
		pthread_join(g_thread[i], NULL);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void LOG(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
}