#pragma once


#include<iostream>
#include<stdlib.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock.h>
#pragma comment (lib, "ws2_32.lib")


#include <pqxx/pqxx> 

using namespace std;
using namespace pqxx;


class search_option
{
public:


	char buf[255];
	int search_rooms(int);
};
