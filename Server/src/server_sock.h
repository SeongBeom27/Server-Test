/**
 * @file sock.h
 * @author sbLee (lgh121546@naver.com)
 * @brief Basic sock
 * @version 0.1
 * @date 2021-07-30
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

using namespace std;

#define BUFSIZE 300

class CSocket
{
private:
    int m_serv_sock;
	map<int, struct sockaddr_in> m_clntMap;
    string packet;
    char message[BUFSIZE];
	char send_name[BUFSIZE];
public:
    CSocket();
    int Open(char *_port);
    int Accept();
    void Read(int clnt_sock);
    void Close(int clnt_sock);

    void error_handling(char *message);
    void z_handler(int sig);
    void LOG(char *message);
};