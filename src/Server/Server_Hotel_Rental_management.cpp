#include <iostream>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock.h>
#include<thread>
#include "login.h"
#include "signup_S.h"
#include "search_server.h"
#include "reservation_Server.h"


#pragma comment (lib, "ws2_32.lib")
#define PORT 8000

using namespace std;


	int nSocket;
	int nClientSocket[5] = { 0, };
	struct sockaddr_in srv;
	fd_set fr;
	fd_set fw;
	fd_set fe;
	int nMaxFd = 0;


int au_check()
{

	try
	{
		connection C("dbname = hotel_rentel_management_system user = postgres password = qwerty port = 5432");
		if (C.is_open())
		{

			std::string sql = "update hotel_rooms_info as hi set occupied_status = 'No' where Room_number in( select room_alloted_number from guest_info as g where g.check_in_date + g.no_days < current_date )";

			std::string sql1 = "update guest_info as g1 set reservation_status = 'No' where mobile_number in( select mobile_number from guest_info as g where g.check_in_date + g.no_days < current_date  )";

			std::string sql2 = "update guest_info as gi set check_out_date = check_in_date + gi.no_days where mobile_number in (\
                    select mobile_number from guest_info as g where g.check_in_date + g.no_days < current_date )";

			std::string sql3 = "update guest_history as gt set check_out_date = check_in_date + gt.no_of_days where mobile_number in(\
                select mobile_number from guest_info as g where g.check_in_date + g.no_days < current_date )";

			work W(C);
			W.exec(sql);
			W.exec(sql1);
			W.exec(sql2);
			W.exec(sql3);
			W.commit();

		}
		else
		{
			cout << "Can't open database" << endl;

		}

	}
	catch (const std::exception& e) {
		cerr << e.what() << std::endl;
		(void)_getch();
		return 0;
	}

}
void HandleNewConnection()
{
	
	int nNewClient = accept(nSocket, NULL, NULL);

	if (nNewClient < 0)
	{
		cout << endl << "Not able to get a new client socket";
	}
	else
	{
		int nIndex;
		for (nIndex = 0; nIndex < 5; nIndex++)
		{
			if (nClientSocket[nIndex] == 0)
			{
				nClientSocket[nIndex] = nNewClient;
				if (nNewClient > nMaxFd)
				{
					nMaxFd = nNewClient + 1;
				}
				break;
			}
		}

		if (nIndex == 5)
		{
			cout << endl << "Server busy. Cannot accept anymore connections";
		}
	}
}


void HandleDataFromClient()
{
	char buf[255];
	login log;
	for (int nIndex = 0; nIndex < 5; nIndex++)
	{
		if (nClientSocket[nIndex] > 0)
		{

			if (FD_ISSET(nClientSocket[nIndex], &fr))
			{
				
				char sBuff[255];
				ZeroMemory(sBuff, 255);
				int nRet = 1;
				if (nRet < 0)
				{
					
					cout << endl << "Error at client socket";
					closesocket(nClientSocket[nIndex]);
					nClientSocket[nIndex] = 0;
				}
				else
				{
					bool static check = false;


					while (check == false)
					{
						int ret = recv(nClientSocket[nIndex], sBuff, 255, 0);
						if (ret < 0)
						{
							
							cout << endl << "Error at client socket";
							closesocket(nClientSocket[nIndex]);
							nClientSocket[nIndex] = 0;
						}
						check = true;

						string option = string(sBuff, 0, sizeof(sBuff));

						if (option == "1")
						{
							signup guest;
							guest.new_user(nClientSocket[nIndex]);

						}
						else if (option == "2")
						{

							login log;
							log.login_guest(nClientSocket[nIndex]);
						}

					}
			
					search_option rooms;
					reservation guest;
					if (true)
					{
						int ret = recv(nClientSocket[nIndex], buf, 255, NULL);
						if (ret < 0)
						{
							cout << endl << "Error at client socket";
							closesocket(nClientSocket[nIndex]);
							nClientSocket[nIndex] = 0;
						}
						string main_opt = string(buf, 0, sizeof(buf));

						if (main_opt == "1")
						{
							rooms.search_rooms(nClientSocket[nIndex]);

						}
						else if (main_opt == "2")
						{
							guest.reservation_info(nClientSocket[nIndex]);

						}
						else if (main_opt == "3")
						{
							guest.guest_history(nClientSocket[nIndex]);
							closesocket(nClientSocket[nIndex]);
							nClientSocket[nIndex] = 0;
						}
						else if (main_opt == "4")
						{

							closesocket(nClientSocket[nIndex]);
							nClientSocket[nIndex] = 0;
						}
						else

						{
							cout << "Invalid Option \nPlease Try Again.........." << endl;
						}
					}


				}




			}

		}
	}
}




int main()
{
	system("Color f0");

	cout << endl << endl << endl << endl << endl << endl;
	cout << "\t\t\t\t**************************************************" << endl;
	cout << "\t\t\t\t*                                                *" << endl;
	cout << "\t\t\t\t*                                                *" << endl;
	cout << "\t\t\t\t*                    WELCOME TO                  *" << endl;
	cout << "\t\t\t\t*           HOTEL RENTAL MANAGEMENT SYSTEM       *" << endl;
	cout << "\t\t\t\t*                    (SERVER)                    *" << endl;
	cout << "\t\t\t\t*                                                *" << endl;
	cout << "\t\t\t\t**************************************************" << endl;

	au_check();

	int nRet = 0;
	WSADATA wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) < 0)
	{
		cout << endl << "Not able to start the socket environment";
		return (EXIT_FAILURE);
	}

	//Listener socket
	nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (nSocket < 0)
	{
		cout << endl << "The socket cannot be initialized";
		exit(EXIT_FAILURE);
	}

	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	srv.sin_addr.s_addr = INADDR_ANY;
	memset(&srv.sin_zero, 0, 8);

	nRet = ::bind(nSocket, (struct sockaddr*)&srv, sizeof(struct sockaddr));
	if (nRet < 0)
	{
		cout << endl << "The socket cannot be bind";
		exit(EXIT_FAILURE);
	}

	nRet = listen(nSocket, 5);
	if (nRet < 0)
	{
		cout << endl << "The listen failed";
		exit(EXIT_FAILURE);
	}

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;


	//listener socket

	nMaxFd = nSocket + 1;

	while (1)
	{
		
		FD_ZERO(&fr);
		FD_SET(nSocket, &fr);
		for (int nIndex = 0; nIndex < 5; nIndex++)
		{
			if (nClientSocket[nIndex] > 0)
			{
				FD_SET(nClientSocket[nIndex], &fr);
			}
		}

		nRet = select(nMaxFd, &fr, NULL, NULL, &tv);

		if (nRet < 0)
		{
			cout << endl << "select api call failed. Will exit";
			return (EXIT_FAILURE);
		}
	//	else if (nRet == 0)
	//	{
	//		cout << endl << "No client at port waiting for an active connection/new message";
	//	}
		
		else
		{
			if (FD_ISSET(nSocket, &fr))
			{
				
				HandleNewConnection();
			}
			else
			{
				
				HandleDataFromClient();
			}
		}
	}
}



