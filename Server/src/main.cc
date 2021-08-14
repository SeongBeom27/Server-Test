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

#include "server_sock.h"

int main(){
    CSocket *pSock;

    pSock = new CSocket();
    pSock->Open("8080");
    int c_sock = pSock->Accept();
    pSock->Read(c_sock);

    delete(pSock);

    return 0;
}