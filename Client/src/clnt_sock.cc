/**
 * @file sock.cc
 * @author sbLee (lgh121546@naver.com)
 * @brief Basic sock
 * @version 0.1
 * @date 2021-07-30
 * 
 * @copyright Copyright (c) 2021
 */

#include "clnt_sock.h"

using namespace std;

CSocket::CSocket(){
    m_sock = -1;
}

int CSocket::Open(char *_ip, char *_port){
	struct sigaction act;

	int addr_size, str_len, state;
	pid_t pid;

	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	
	state = sigaction(SIGCHLD, &act, 0);
	if(state != 0)
	{
		puts("sigaction() error");
		exit(1);
	}

	m_sock=socket(PF_INET, SOCK_STREAM, 0);

	memset(&m_serv_addr, 0, sizeof(m_serv_addr));
	m_serv_addr.sin_family=AF_INET;
	m_serv_addr.sin_addr.s_addr= inet_addr(_ip);
	m_serv_addr.sin_port=htons(atoi(_port));
}

// 1개의 클라이언트와만 연결되도록 하기
int CSocket::Connect(){
    if(connect(m_sock, (struct sockaddr*) &m_serv_addr, sizeof(m_serv_addr)) == -1){
        error_handling("connect() error");
    }
}

void CSocket::Write(){
    while(1)
    {
        /* message input, transfer*/
        //fputs("Please input to transfer message (q to quit) : ", stdout);
        sleep(1);
        printf("Please input to transfer message (q to quit) : ");
        // standard output
        fgets(message, BUFSIZE, stdin);     // your input string put in message

        if(!strcmp(message,"q\n"))
        {
            shutdown(m_sock, SHUT_WR);
            close(m_sock);
            exit(0);
        }
        
        write(m_sock, message, strlen(message));
    }
    return;
}

void CSocket::Read(){
    while(1)
    {
        int str_len = read(m_sock, message, BUFSIZE);
        if(str_len == 0) exit(0);
        message[str_len] = 0;
        printf("Message from Server : %s\n", message);
    }
    return;
}

void CSocket::Close(){
    // 연결 종료
    close(m_sock);
    return;
}

void CSocket::error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void CSocket::z_handler(int sig)
{
    pid_t pid;
    int rtn;
    // waitpid func. gets return value of child process. also Concern situation exited several child process while processing repeatibly in while
    while((pid = waitpid(-1, &rtn, WNOHANG)) > 0 ){
        printf("Die Zombie process ID : %d\n", pid); 
        printf("return data : %d \n\n", WEXITSTATUS(rtn));
    }
}

void CSocket::LOG(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
}