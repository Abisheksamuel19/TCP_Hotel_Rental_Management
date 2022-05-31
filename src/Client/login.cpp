


#include "login.h"
#include "client.h"


int login::login_guest(int sock)
{
    system("CLS");
    int test = 0;
    client guest;

opt2:
    cout << endl<<endl;

    cout << "\t\t\t\t   ********************************************" << endl;
    cout << "\t\t\t\t   *             GUEST SIGN-IN SCREEN         *" << endl;
    cout << "\t\t\t\t   ********************************************" << endl;


    string user_name, pwd;


    cout << "\t\t\t\t     Username: "; cin >> user_name;
    cout << "\t\t\t\t     Password: "; cin >> pwd;

    send(sock, user_name.c_str(), 255, 0);
    send(sock, pwd.c_str(), 255, 0);


//pwd verification:

    recv(sock, buf, 255, 0);
    string passwd = string(buf, 0, 255);

    if (passwd == pwd)
    {
        char RecvBuffer5[255], RecvBuffer6[255];
        char  RecvBuffer7[255];
        string mob_num, room_all;
        //login sucessfull 

        cout << endl << endl << endl;
        cout << "\t\t\t\t   Login successfully!...." << endl;
        cout << "\t\t\t\t   Press any key to continue!";
        (void)_getch();
        system("cls");
        recv(sock, buf, 255, 0);
        string name = string(buf, 0, 255);

        cout << endl << endl;
        cout << setw(10) << "  ***************************" << endl;
        cout << setw(10) << "       Welcome " <<name << "!!" << endl;
        cout << setw(10) << "  ***************************" << endl;
        cout << endl;
        cout << "  Guest Details :" << endl << endl;
       
            recv(sock, Buffer3, 100, NULL);
            recv(sock, RecvBuffer4, 100, NULL);
            recv(sock, RecvBuffer5, 100, NULL);
            recv(sock, RecvBuffer6, 100, NULL);
            recv(sock, RecvBuffer7, 100, NULL);
            cout << "\t          " << Buffer3 << "." << RecvBuffer4 << "\t " << setw(10) << RecvBuffer5 << endl;
            cout << "\t          " << RecvBuffer7 << "\t " << RecvBuffer6 << endl << endl;



        check = true;
    }
    else
    {

        test++;
        system("cls");

        cout << "\n\n\t\t\t\t You have entered the wrong username or password\n" << endl;
        cout << "\t\t\t\t Please Try Again....\n" << endl;
        (void)_getch();
        system("cls");

        if (test == 3)
        {
            cout << "You have entered the wrong username or password 3 times and you are not allowed to login to the system!\n" << endl;
            exit(0);
        }
        goto opt2;
    }


   
}