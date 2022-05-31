#include "signup_server.h"
#include "login.h"

int signup::new_user(int index)
{
    login log;

    connection C("dbname = hotel_rentel_management_system user = postgres password = qwerty port = 5432");


    recv(index, buf, sizeof(buf), 0);
    string first_name = string(buf, 0, sizeof(buf));


    recv(index, buf, sizeof(buf), 0);
    string last_name = string(buf, 0, sizeof(buf));

    recv(index, buf, sizeof(buf), 0);
    string mob_num = string(buf, 0, sizeof(buf));


    recv(index, buf, sizeof(buf), 0);
    string mail = string(buf, 0, sizeof(buf));


    recv(index, buf, sizeof(buf), 0);
    string city = string(buf, 0, sizeof(buf));



    recv(index, buf, sizeof(buf), 0);
    string us_name = string(buf, 0, sizeof(buf));

    recv(index, buf, sizeof(buf), 0);
    string passwd = string(buf, 0, sizeof(buf));

    std::string sql = "insert into guest_info  values(""'" + (first_name)+"'" + "," + "'" + (last_name)+"'" + "," + (mob_num)+"," + "'" + (mail)+"'" + ", " + "'" + (city)+"'" + ")";
    std::string sql1 = "insert into login_credentials values(""'" + (us_name)+"'" + ", " + "'" + (passwd)+"'" + ",'Guest')";
    std::string sql2 = "update guest_info  set guest_user_name = (""'" + (us_name)+"'" + ") where mobile_number = ( " + (mob_num)+")";

    work W(C);
    W.exec(sql);
    W.exec(sql1);
    W.exec(sql2);
    W.commit();

   log.login_guest(index);
}