
#include "search_client.h"
#include"client.h"

void search::search_rooms(int sock)
{
    
    client s;
    char Buffer5[255], Buffer6[255];
    string room_type;
    char buf[255], Buffer7[255];
    system("CLS");
    cout << endl << endl;
    cout << setw(60) << "**********************************************" << endl;
    cout << setw(60) << "*               ROOM SEARCH SCREEN           *" << endl;
    cout << setw(60) << "**********************************************" << endl;
    cout << endl;
   

    //  The Type of Room For Searching 
    cout << "Enter the text for search(Room type and Floor number)    :"; cin >> room_type;
    send(sock, room_type.c_str(), sizeof(room_type), 0);

    recv(sock, buf, sizeof(buf), 0);
    //count                 
    string count = string(buf, 0, sizeof(buf));

    cout << "Room Details according to Room Type and Floor Number:" << endl;
    

    int i = 0,t=1;
    cout << "=====================================================================================================" << endl;
    cout << "|S.No      |  ROOM_NUMBER  |       ROOM_TYPE      |     FLOOR_NUMBER |   ROOM_RENT  |OCCUPIED STATUS|" << endl;
    cout << "=====================================================================================================" << endl;


    while (i < stoi(count))
    {
        i++;
        recv(sock, Buffer3, 100, NULL);
        recv(sock, Buffer4, 100, NULL);
        recv(sock, Buffer5, 100, NULL);
        recv(sock, Buffer6, 100, NULL);
        recv(sock, Buffer7, 100, NULL);


        cout << "|" << t << "\t   |\t" << Buffer3 << "\t   |\t" << setw(10) << Buffer4 << "\t  |\t" << Buffer5 << "\t     |" << " \t" << Buffer6 << "\t    |" << setw(8) << Buffer7 << "\t    |" << endl;
        t++;
    }
    cout << "-----------------------------------------------------------------------------------------------------" << endl;


    s.client1();

}