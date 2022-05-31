#pragma once
#include<iostream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<thread>
#include<stdlib.h>
#include <string>
#include<stdlib.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock.h>
#pragma comment (lib, "ws2_32.lib")
#define PORT 8000


class client
{
public:
    WSADATA w;
    int nRet = 0;
    sockaddr_in srv;

    char buf[255];
    int test = 0;
  
    bool check = false;

    void client1();
   
};
