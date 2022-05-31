
#include"client.h"
#include "login.h"
#include "signup.h"
#include "search_client.h"
#include "reservation_guest.h"


void delay(unsigned int mseconds) {
    // Storing start time 
    clock_t startTime = clock();
    // looping till required time is not acheived 
    while (clock() < (startTime + mseconds));
}

void client::client1()
{

    login log;
    signup new_user;
    WSAStartup(MAKEWORD(2, 2), &w);

    int nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    string main_opt;
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");
    srv.sin_port = htons(PORT);
    memset(&(srv.sin_zero), 0, 8);
    int connResult = connect(nSocket, (struct sockaddr*)&srv, sizeof(srv));

    if (connResult == SOCKET_ERROR) {
        cout << "\n\n\t\t\t\t     Error: can't connect to server.\n\n" << endl;
        closesocket(nSocket);
        WSACleanup();
        return;
    }
    int i = 1;


        string option;
        Sleep(1000);
        static bool check = false;
        while (check==false)
        {
            cout << endl << endl << endl << endl << endl << endl;
            cout << "\t\t\t\t***************************************************" << endl;
            cout << "\t\t\t\t*                                                 *" << endl;
            cout << "\t\t\t\t*         1. Sign-Up for a New User               *" << endl;
            cout << "\t\t\t\t*         2. Guest Login                          *" << endl;
            cout << "\t\t\t\t*                                                 *" << endl;
            cout << "\t\t\t\t***************************************************" << endl;
            cout << "\t\t\t\tPlease enter your choose: "; cin >> option;

            i++;
               send(nSocket, option.c_str(), 255, 0);
                
                if (option == "1")
                {

                 //   thread cd(new_user.signup_guest(nSocket));
                     new_user.signup_guest(nSocket);
                  //  cd.join();
                }
                else if (option == "2")
                {
                    log.login_guest(nSocket);
                }
                else
                {
                    cout << "Invalid Option";
                }
                check = true;

        }
        while (1)
        {
            reservation guest;

            string option1;
            cout << endl << endl << endl;
            cout << "\t\t\t\t***************************************************" << endl;
            cout << "\t\t\t\t*                                                 *" << endl;
            cout << "\t\t\t\t*         1. Search Rooms in Hotel                *" << endl;
            cout << "\t\t\t\t*         2. Reserve Rooms                        *" << endl;
            cout << "\t\t\t\t*         3. My History                           *" << endl;
            cout << "\t\t\t\t*         4. Sign-out                             *" << endl;
            cout << "\t\t\t\t*                                                 *" << endl;
            cout << "\t\t\t\t***************************************************" << endl;
            cout << "\t\t\t\tPlease enter your choose: "; cin >> option1;
            cin.ignore();

            send(nSocket, option1.c_str(), 255, 0);
   
             if (option1 == "1")
            {
                search room;
                room.search_rooms(nSocket);
            }
            else if (option1 == "2")
            {
               guest.reservation_info(nSocket);
         
            }
            else if (option1 == "3")
            {
               
                guest.guest_history(nSocket);
            }
            else if (option1 == "4")
             {

                 system("cls");
                 cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                 cout << "\t\t\t\t\t\t Signing-Out..";
                 for (int process = 0; process < 36; process++) {
                     delay(50);
                     cout << ".";
                 }
                 system("cls");
                 cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                 cout << "\t\t\t\t\t\t*********************************************" << endl;
                 cout << "\t\t\t\t\t\t*                                           *" << endl;
                 cout << "\t\t\t\t\t\t*        You have exited the system!        *" << endl;
                 cout << "\t\t\t\t\t\t*                 Thank You!                *" << endl;
                 cout << "\t\t\t\t\t\t*        For Using Choosing Our Hotel!      *" << endl;
                 cout << "\t\t\t\t\t\t*                                           *" << endl;
                 cout << "\t\t\t\t\t\t*********************************************" << endl;
                 cout << endl << endl << endl;
                 exit(0);
              
             }
            else
            {
                cout << "Invalid option" << endl;;
            }

    
 
        }


    }

