#pragma once
#include<iostream>
#include<stdlib.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

class login
{
public:
	char buf[255];
	char Buffer3[255], RecvBuffer4[255];
	bool check=false;
	int test=0;

	int login_guest(int);
};
