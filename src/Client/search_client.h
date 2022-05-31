#pragma once
#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include <string>
#include<stdlib.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

class search
{
public:
	char Buffer3[255], Buffer4[255];
	void search_rooms(int);
};