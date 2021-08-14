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

#include "clnt_sock.h"

int main(){
    pid_t pid;
    CSocket *pSock;

    char _ip[] = "127.0.0.1";
    char _port[] = "8080";

    pSock = new CSocket();
    pSock->Open(_ip, _port);
    pSock->Connect();

    pid = fork();

    if(pid == 0){
        pSock->Write();
    }
    else{
        pSock->Read();
    }

    pSock->Close();
    delete(pSock);

    return 0;
}