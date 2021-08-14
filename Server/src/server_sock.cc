/**
 * @file sock.cc
 * @author sbLee (lgh121546@naver.com)
 * @brief Basic sock
 * @version 0.1
 * @date 2021-07-30
 * 
 * @copyright Copyright (c) 2021
 */

#include "server_sock.h"

using namespace std;

CSocket::CSocket(){
    m_serv_sock = -1;
}

int CSocket::Open(char *_port){
	struct sigaction act;
    struct sockaddr_in serv_addr;

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

	m_serv_sock=socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(_port));

	if(bind(m_serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
	{
		error_handling("bind() error\n");
	}

	if(listen(m_serv_sock, 5) == -1)
	{
		error_handling("listen() error\n");
	}
}

// 1개의 클라이언트와만 연결되도록 하기
int CSocket::Accept(){
    int clnt_sock;
    struct sockaddr_in clnt_addr;

    socklen_t addr_size = sizeof(clnt_addr);
    
    LOG("[CSocket::Accept] Server Accpet Start");
    clnt_sock = accept(m_serv_sock, (struct sockaddr*) &clnt_addr, &addr_size);

    if(clnt_sock == -1)
    {
        error_handling("[CSocket::Accept] clnt_sock error occur!");
        return clnt_sock;
    }

    m_clntMap[clnt_sock] = clnt_addr;

    return clnt_sock;
}

void CSocket::Read(int clnt_sock){
    int str_len;
    sockaddr_in clnt_addr = m_clntMap[clnt_sock];
    while((str_len = read(clnt_sock, message, BUFSIZE)) != 0)
    {
        write(clnt_sock, message, str_len);
        
        write(1, inet_ntoa(clnt_addr.sin_addr), strlen(inet_ntoa(clnt_addr.sin_addr)) + 1);	
        write(1, " : ", 4);	
        write(1, message, str_len);
    }

    puts("connect exit\n");
    close(clnt_sock);
    return;
}

void CSocket::Close(int clnt_sock){
    // 클라이언트 소켓 디스크립터 맵 종료
    memset(&m_clntMap[clnt_sock], 0, sizeof(m_clntMap[clnt_sock]));
    
    // 연결 종료
    close(clnt_sock);
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