

#include "search_server.h"
#include"login.h"
#define max 3
string strings[max];

int len(string str)
{
    int length = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        length++;

    }
    return length;
}
void split(string str, char seperator)
{
    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex = 0;
    while (i <= len(str))
    {
        if (str[i] == seperator || i == len(str))
        {
            endIndex = i;
            string subStr = "";
            subStr.append(str, startIndex, endIndex - startIndex);
            strings[currIndex] = subStr;
            currIndex += 1;
            startIndex = endIndex + 1;
        }
        i++;
    }
}
int search_option::search_rooms(int index)
{

    cout << "searchiiiing" << endl  ;

    login log;
    char str[255];

    recv(index, str, sizeof(str), 0);
    char seperator = '-';
    split(str, seperator);

  
    connection C("dbname = hotel_rentel_management_system user = postgres password = qwerty port = 5432");


    std::string sql = "SELECT  room_number,room_type,floor_number,room_rent,occupied_status FROM hotel_rooms_info \
                    WHERE (      ((room_type iLIKE (""'%" + (strings[0]) + "%'"")) or  (floor_number iLIKE (""'%" + (strings[0]) + "%'"")  )) \
                        and ((room_type iLIKE (""'%" + (strings[1]) + "%'"")) or (floor_number iLIKE (""'%" + (strings[1]) + "%'"")  ))  )";

    std::string sql1 = "SELECT count(*)  FROM hotel_rooms_info WHERE(((room_type iLIKE(""'%" + (strings[0]) + "%'"")) or (floor_number iLIKE(""'%" + (strings[0]) + "%'""))) \
                        and ((room_type iLIKE(""'%" + (strings[1]) + "%'"")) or (floor_number iLIKE(""'%" + (strings[1]) + "%'""))))";

    work W(C);
    result R1(W.exec(sql1));
    result::const_iterator  b = R1.begin();
    string count = b[0].as<string>();
    send(index, count.c_str(), 100, NULL);





    result R(W.exec(sql));
    for (result::const_iterator c = R.begin(); c != R.end(); ++c)
    {
       string r_n = c[0].as<string>();
       string r_n1 = c[1].as<string>();
       string  r_n2 = c[2].as<string>();
       string  r_n3 = c[3].as<string>();
       string r_n4 = c[4].as<string>();

        send(index, r_n.c_str(), 100, NULL);send(index, r_n1.c_str(), 100, NULL);

        send(index, r_n2.c_str(), 100, NULL);
        send(index, r_n3.c_str(), 100, NULL);
        send(index, r_n4.c_str(), 100, NULL);
    }
    W.commit();


}