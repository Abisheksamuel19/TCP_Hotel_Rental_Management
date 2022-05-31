#include "reservation_guest.h"


int reservation::reservation_info(int sock)
{
reserve:
    string mob_num, room_all;
    system("CLS");
    cout << setw(60) << "**********************************************" << endl;
    cout << setw(60) << "*              RESERVATION OF ROOM           *" << endl;
    cout << setw(60) << "**********************************************" << endl;
    cout << endl;

    cout << "Enter Your Mobile Number       :"; cin >> mob_num;
    send(sock, mob_num.c_str(), sizeof(mob_num), 0);
    cout << "Enter the Room Number for accommodation    :"; cin >> room_all;
    send(sock, room_all.c_str(), sizeof(room_all), 0);


    recv(sock, buf, sizeof(buf), 0);
    string ocp = string(buf, 0, sizeof(buf));

    if (ocp == "Yes")
    {
        cout << "The Room has been already Reserved" << endl;
        cout << "Please Try again... " << endl;
        goto reserve;
    }
    else
    {
        int x = 2;
        string check_in, stay, person;
        cout << "Enter the Check-IN Date  [yyyy-mm-dd]      :";cin >> check_in;
        send(sock, check_in.c_str(), sizeof(check_in), 0);

        cout << "Enter How many days of Stay                :";cin >> stay;
        send(sock, stay.c_str(), sizeof(stay), 0);

    reserve_again:
        cout << "Enter Number of Person for accomodation    :";cin >> person;
        send(sock, person.c_str(), sizeof(person), 0);

        //capacity
        recv(sock, buf, sizeof(buf), 0);
        string cap = string(buf, 0, sizeof(buf));


        if (stoi(person) > stoi(cap))
        {
            cout << "\n Number of Person Exceeds Maximum capacity of Room number..\n" << endl;

            cout << "...Please Try Again...\n\n" << endl;

            goto reserve_again;
        }
        else
        {
            string first_name, last_name, mob_num, mail, city, us_name;
            if (stoi(person) > 1)
            {
                while (x <= stoi(person))
                {
                    //other Guest Details

                    cout << "\n\t ->> Please Enter the Other Guest Details <<--\n\n";
                    cout << "Guest No." << x << endl;
                    cout << "\tEnter your First Name          :"; cin >> first_name;
                    send(sock, first_name.c_str(), sizeof(first_name), 0);
                    cout << "\tEnter your Last Name           :"; cin >> last_name;
                    send(sock, last_name.c_str(), sizeof(last_name), 0);

                    cout << "\tEnter your Mobile Number       :"; cin >> mob_num;
                    send(sock, mob_num.c_str(), sizeof(mob_num), 0);

                    cout << "\tEnter your Email-Id            :"; cin >> mail;
                    send(sock, mail.c_str(), sizeof(mail), 0);

                    cout << "\tEnter your City                :"; cin >> city;
                    send(sock, city.c_str(), sizeof(city), 0);

                    cout << endl << endl;
                    cout << "\t >> Please Enter your User-Name for Loging-in   :";cin >> us_name;
                    send(sock, us_name.c_str(), sizeof(us_name), 0);
                    x++;

                }

            }

            //Rooms Reserved Sucessfull
            cout << "\n\n Room Reserved Sucessfull" << endl;

            (void)_getch();


        }
    }
    return 1;

}

int reservation::guest_history(int sock)
{
    string mob_num;
    char Buffer5[255], Buffer6[255];
    char Buffer1[255], Buffer2[255];
    char Buffer7[255], Buffer8[255], Buffer9[255];
    system("CLS");
    cout << setw(60) << "**********************************************" << endl;
    cout << setw(60) << "*                  Guest HISTORY             *" << endl;
    cout << setw(60) << "**********************************************" << endl;
    cout << endl << endl;


    cout << "Enter Your Mobile Number To Search Your History :";
    cin >> mob_num;
    send(sock, mob_num.c_str(), sizeof(mob_num), 0);


    recv(sock, buf, sizeof(buf), 0);
    string count1 = string(buf, 0, sizeof(buf));

  
    cout << endl << endl;


    cout << "==============================================================================================================================================================================================================" << endl;
    cout << "|S.No      |  ROOM_NUMBER  |      ROOM_TYPE       |   FLOOR_NUMBER   |    NAME     |    MOBILE_NUMBER     |          CITY          | Check_IN Date |   Check_OUT Date    | No.Of Days Stayed |   ROOM_RENT   |" << endl;
    cout << "==============================================================================================================================================================================================================" << endl;

  
    //Guest history 
    int i = 0,t=1;

    while (i < stoi(count1))
    {
        i++;
        ZeroMemory(Buffer, sizeof(Buffer));
        recv(sock, Buffer, 100, NULL);
        ZeroMemory(Buffer1, sizeof(Buffer1));
        recv(sock, Buffer1, 100, NULL);
        ZeroMemory(Buffer2, sizeof(Buffer2));
        recv(sock, Buffer2, 100, NULL);
        ZeroMemory(Buffer3, sizeof(Buffer3));
        recv(sock, Buffer3, 100, NULL);
        ZeroMemory(Buffer4, sizeof(Buffer4));
        recv(sock, Buffer4, 100, NULL);
        recv(sock, Buffer5, 100, NULL);
        recv(sock, Buffer6, 100, NULL);
        recv(sock, Buffer7, 100, NULL);
        recv(sock, Buffer8, 100, NULL);
        recv(sock, Buffer9, 100, NULL);

        cout << "|" << t << "\t   |\t" << Buffer << "\t   |\t" << setw(8) << Buffer1 << "\t  |\t" << Buffer2 << "\t     |" << " \t" << Buffer3 << "\t   |\t" << Buffer4 << "\t  |\t" << setw(8) << Buffer5 << "\t   |   \t" << Buffer6 << " | \t" << Buffer7 << "\t | " << setw(5) << Buffer8 << "\t     |" << Buffer9 << "\t     |" << endl;
        t++;

    }

   
   cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

   
   (void)_getch();
    system("CLS");
    return 1;


}