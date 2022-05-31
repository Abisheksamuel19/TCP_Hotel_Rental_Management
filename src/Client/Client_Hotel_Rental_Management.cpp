#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock.h>
#pragma comment (lib, "ws2_32.lib")
#define PORT 8000

#include"client.h"
#include "login.h"


using namespace std;
void timer(unsigned int mseconds) {
    // Storing start time 
    clock_t startTime = clock();
    // looping till required time is not acheived 
    while (clock() < (startTime + mseconds));
}

void title()
{
    cout << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t**************************************************" << endl;
    cout << "\t\t\t\t*                                                *" << endl;
    cout << "\t\t\t\t*                                                *" << endl;
    cout << "\t\t\t\t*                    WELCOME TO                  *" << endl;
    cout << "\t\t\t\t*           HOTEL RENTAL MANAGEMENT SYSTEM       *" << endl;
    cout << "\t\t\t\t*                                                *" << endl;
    cout << "\t\t\t\t*                                                *" << endl;
    cout << "\t\t\t\t**************************************************" << endl;
   
}

int main()
{
    system("Color B0");
   
    title();
    cout << endl << "\t\t\t\t\tPress any Key to continue!" << endl << endl;
    (void)_getch();
    cout << "\t\t\t\tLoading";
    for (int process = 0; process < 40; process++) {
        timer(50);
        cout << ".";
    }
   
    client cli;
    cli.client1();  

    
   
}
   

