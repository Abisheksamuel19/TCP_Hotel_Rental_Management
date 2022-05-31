
#include "signup.h"
#include "login.h"
#include "client.h"


int signup :: signup_guest(int sock)
{
    login log;
    client guest;
    string first_name, last_name, mob_num, mail, city, us_name;
    string passwd;
    //"Sign-UP"
    system("CLS");
    cout << endl << endl;

    cout << setw(60) << "**********************************************" << endl;
    cout << setw(60) << "*             GUEST Sign-Up SCREEN           *" << endl;
    cout << setw(60) << "**********************************************" << endl;
    cout << endl;


    cout << "Enter your First Name          :"; cin >> first_name;
    send(sock, first_name.c_str(), sizeof(first_name), 0);

  
    cout << "Enter your Last Name           :"; cin >> last_name;
    send(sock, last_name.c_str(), sizeof(last_name), 0);

    cout << "Enter your Mobile Number       :"; cin >> mob_num;
    send(sock, mob_num.c_str(), sizeof(mob_num), 0);

    cout << "Enter your Email-Id            :"; cin >> mail;
    send(sock, mail.c_str(), sizeof(mail), 0);

    cout << "Enter your City                :"; cin >> city;
    send(sock, city.c_str(), sizeof(city), 0);


    cout << endl << endl;

    cout << setw(10) << "**********************************************" << endl;
    cout << setw(10) << "*           Guest LOGIN-IN Credentials:      *" << endl;
    cout << setw(10) << "**********************************************" << endl;
    cout << endl;


    cout << "Please Enter your User-Name    :";cin >> us_name;
    send(sock, us_name.c_str(), sizeof(us_name), 0);

    cout << "Please Enter your Password     :";cin >> passwd;
    send(sock, passwd.c_str(), sizeof(passwd), 0);


    

    system("cls");
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t***********************************************" << endl;
    cout << "\t\t\t\t*                                             *" << endl;
    cout << "\t\t\t\t*        You have successfully Signed-Up      *" << endl;
    cout << "\t\t\t\t*       Thank you for Choosing our Hotel!!    *" << endl;
    cout << "\t\t\t\t*                                             *" << endl;
    cout << "\t\t\t\t***********************************************" << endl;

    (void)_getch();
  

    log.login_guest(sock);


}
