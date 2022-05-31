
#include "login.h"




int login::login_guest(int index)
{

    char buf[255];
    string get_password;
            opt2:
                try
                {
                   connection C("dbname = hotel_rentel_management_system user = postgres password = qwerty port = 5432");

                    int bytesReceived = recv(index, buf, 255, NULL);
                    string user_name = string(buf, 0, bytesReceived);


                   recv(index, buf, 255, NULL);
                   string pwd = string(buf, 0, 255);

 
                         std::string sql = "select Password from login_credentials where User_name = (""'" + (user_name)+"'" + ")";
                               work W(C);

                                  result R(W.exec(sql));
                                  for (result::const_iterator c = R.begin(); c != R.end(); ++c) {

                                    get_password = c[0].as<string>();
                                  }
                               send(index, get_password.c_str(), 255, 0);


                               W.commit();

                   if (get_password == pwd)

                               {
                       std::string sql = "select first_name from guest_info where guest_user_name = (""'" + (user_name)+"'" + ")";
                       work W(C);
                       result R(W.exec(sql));
                       result::const_iterator  c = R.begin();

                       string name = c[0].as<string>();
                       send(index, name.c_str(), 255, 0);

                       std::string sql1 = "select first_name,Last_name,mobile_number,email_id,city from guest_info where guest_user_name = (""'" + (user_name)+"'" + ")";
                  

                       result R1(W.exec(sql1));
                       for (result::const_iterator b = R1.begin(); b != R1.end(); ++b) {


                           string r_n = b[0].as<string>();
                           string r_n1 = b[1].as<string>();
                           string  r_n2 = b[2].as<string>();
                           string  r_n3 = b[3].as<string>();
                           string r_n4 = b[4].as<string>();

                           send(index, r_n.c_str(), 100, NULL);send(index, r_n1.c_str(), 100, NULL);

                           send(index, r_n2.c_str(), 100, NULL);
                           send(index, r_n3.c_str(), 100, NULL);
                           send(index, r_n4.c_str(), 100, NULL);
                       
                       
                       }
                               }
                               else
                               {
                                   test++;

                                   if (test == 3) { 
                                       return 1;
                                   }
                                   goto opt2;

                               }
                                                       
                }
                catch (const std::exception& e) {
                    cerr << e.what() << std::endl;
                }           

}