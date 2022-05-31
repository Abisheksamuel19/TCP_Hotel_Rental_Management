#pragma once
#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include <string>
#include<stdlib.h>
#include<iomanip>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock.h>


#pragma comment (lib, "ws2_32.lib")
using namespace std;



class reservation
{
public:
    char buf[255];
    char Buffer3[255], Buffer4[255],Buffer[255];
    int reservation_info(int);
    int guest_history(int);
    

};
