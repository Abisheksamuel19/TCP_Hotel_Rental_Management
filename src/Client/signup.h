#pragma once
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<iomanip>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

class signup
{
public:
	char buf[255];
	bool  check = false;
	int test = 0;

	int signup_guest(int);
};
