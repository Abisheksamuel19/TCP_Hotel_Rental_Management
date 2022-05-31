
#include"reservation_Server.h"

int reservation::reservation_info(int index)
{
    cout << "reservation;" << endl;

    string mob_num;
reserve:

    int bytesReceived = recv(index, buf1, sizeof(buf1), 0);
    string mob_num1 = string(buf1, 0, bytesReceived);


    recv(index, buf1, sizeof(buf1), 0);
    string room_all = string(buf1, 0, sizeof(buf1));

    connection C("dbname = hotel_rentel_management_system user = postgres password = qwerty port = 5432");

    std::string sql = "select occupied_status from hotel_rooms_info  where room_number = (" + (room_all)+")";

    work W(C);
    result R(W.exec(sql));
    result::const_iterator  c = R.begin();
    string ocp = c[0].as<string>();

    send(index, ocp.c_str(), sizeof(ocp), 0);

    if (c[0].as<string>() == "Yes")
    {
        goto reserve;

    }
    else
    {
        int x = 2;

        recv(index, buf1, sizeof(buf1), 0);
        string check_in = string(buf1, 0, sizeof(buf1));


        recv(index, buf1, sizeof(buf1), 0);
        string stay = string(buf1, 0, sizeof(buf1));

    reserve_again:

        recv(index, buf1, sizeof(buf1), 0);
        string person = string(buf1, 0, sizeof(buf1));

        std::string sql1 = "select capacity from hotel_rooms_info where  room_number = (" + (room_all)+")";
        result R1(W.exec(sql1));
        result::const_iterator  b = R1.begin();

        string cap = to_string(b[0].as<int>());
        send(index, cap.c_str(), sizeof(cap), 0);

        if (stoi(person) > b[0].as<int>())
        {
            goto reserve_again;
        }
        else
        {
            if (stoi(person) > 1)
            {
                while (x <= stoi(person))
                {
                    recv(index, buf1, sizeof(buf1), 0);
                    string first_name = string(buf1, 0, sizeof(buf1));

                    recv(index, buf1, sizeof(buf1), 0);
                    string last_name = string(buf1, 0, sizeof(buf1));

                    recv(index, buf1, sizeof(buf1), 0);
                    string mob_num = string(buf1, 0, sizeof(buf1));

                    recv(index, buf1, sizeof(buf1), 0);
                    string mail = string(buf1, 0, sizeof(buf1));

                    recv(index, buf1, sizeof(buf1), 0);
                    string city = string(buf1, 0, sizeof(buf1));

                    recv(index, buf1, sizeof(buf1), 0);
                    string user_name = string(buf1, 0, sizeof(buf1));



                    std::string sql = "insert into guest_info  values(""'" + (first_name)+"'" + "," + "'" + (last_name)+"'" + ", \
                            " + (mob_num)+"," + "'" + (mail)+"'" + ", " + "'" + (city)+"'" + ")";

                    std::string sql1 = "insert into login_credentials values(""'" + (user_name)+"'" + ",12345,'Guest')";

                    std::string sql2 = "update guest_info  set guest_user_name = (""'" + (user_name)+"'" + ") where mobile_number = ( " + (mob_num)+")";


                    std::string sql3 = "update guest_info set check_in_date =(" "'" + (check_in)+"'" + ") where mobile_number =(" + (mob_num)+")";
                    std::string sql4 = "update guest_info set no_days =(" + (stay)+") where mobile_number =(" + (mob_num)+")";

                    std::string sql5 = "update guest_info set room_alloted_number =(" + (room_all)+") where mobile_number =(" + (mob_num)+")";

                    std::string sql6 = "update guest_info set reservation_status ='Reserved' where mobile_number =(" + (mob_num)+")";

                    std::string sql7 = "update hotel_rooms_info set occupied_status = 'Yes' where room_number = (" + (room_all)+")";

                    std::string sql8 = "insert into guest_history values(" + (mob_num)+"," + (room_all)+", \
                    " + "'" + (check_in)+"'" + ",NULL," + (stay)+" )";

                    W.exec(sql);
                    W.exec(sql1);W.exec(sql2);
                    W.exec(sql3);W.exec(sql4);
                    W.exec(sql5);W.exec(sql6);
                    W.exec(sql7);W.exec(sql8);

                    x++;

                }
                goto res;
            }
            else
            {
            res:


                std::string sql0 = "update guest_info set check_in_date =(" "'" + (check_in)+"'" + ") where mobile_number =(" + (mob_num1)+")";
                std::string sql2 = "update guest_info set no_days =(" + (stay)+") where mobile_number =(" + (mob_num1)+")";

                std::string sql3 = "update guest_info set room_alloted_number =(" + (room_all)+") where mobile_number =(" + (mob_num1)+")";

                std::string sql4 = "update guest_info set reservation_status ='Reserved' where mobile_number =(" + (mob_num1)+")";
                std::string sql5 = "update hotel_rooms_info set occupied_status = 'Yes' where room_number = (" + (room_all)+")";

                std::string sql6 = "insert into guest_history values(" + (mob_num1)+"," + (room_all)+"," + "'" + (check_in)+"'" + ", NULL, " + (stay)+" )";

                W.exec(sql0);  W.exec(sql2);
              
                W.exec(sql3);  W.exec(sql4);
      
                W.exec(sql5);  W.exec(sql6);
          
                cout << endl;

                W.commit();



            }
        }
    }


}


int reservation::guest_history(int sock)
{
    string r_n4, r_n5, r_n6, r_n7, r_n8, r_n9;

    recv(sock, buf1, sizeof(buf1), 0);
    string mob_num = string(buf1, 0, sizeof(buf1));
    connection C("dbname = hotel_rentel_management_system user = postgres password = qwerty port = 5432");

    std::string sql = "select a.room_number, a.room_type, a.floor_number, b.first_name, b.mobile_number, b.city, c.check_in_date, c.check_out_date, c.no_of_days, a.room_rent\
      from hotel_rooms_info as a, guest_info as b, guest_history as c where b.mobile_number = (" + (mob_num)+") and c.mobile_number = (" + (mob_num)+") and c.room_no_stayed = a.room_number ";

    std::string sql1 = "SELECT count(*)  from hotel_rooms_info as a, guest_info as b, guest_history as c \
                where b.mobile_number = (" + (mob_num)+") and c.mobile_number = (" + (mob_num)+") and c.room_no_stayed = a.room_number ";

    work W(C);
    result R1(W.exec(sql1));
    result::const_iterator  b = R1.begin();

    string count = b[0].as<string>();
    send(sock, count.c_str(), 100, NULL);



    result R(W.exec(sql));
    for (result::const_iterator c = R.begin(); c != R.end(); ++c)
    {
       string r_n = to_string(c[0].as<int>());
       string  r_n1 = c[1].as<string>();
       string r_n2 = c[2].as<string>();
       string r_n3 = c[3].as<string>();


        r_n4 = to_string(c[4].as<long long int>());
        r_n5 = c[5].as<string>();

        r_n6 = c[6].as<string>();

        r_n7 = c[7].as<string>();
        r_n8 = to_string(c[8].as<int>());
        r_n9 = to_string(c[9].as<int>());

        send(sock, r_n.c_str(), 100, NULL);send(sock, r_n1.c_str(), 100, NULL);

        send(sock, r_n2.c_str(), 100, NULL); send(sock, r_n3.c_str(), 100, NULL);
        send(sock, r_n4.c_str(), 100, NULL);
        send(sock, r_n5.c_str(), 100, NULL);
        send(sock, r_n6.c_str(), 100, NULL);


        send(sock, r_n7.c_str(), 100, NULL);
        send(sock ,r_n8.c_str(), 100, NULL);

        send(sock, r_n9.c_str(), 100, NULL);

    }


    W.commit();
}
