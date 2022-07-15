#include "/usr/include/mysql/mysql.h"
#include <iostream>
#include <cstring>

class Database
{   

public:
    MYSQL *connection = NULL, conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    Database()
    {
        mysql_init(&conn);
        mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "utf8");
        connection = mysql_real_connect(&conn, "localhost", "root", "root1234", "rent", 3306, NULL, 0);
        if(connection==NULL)
        {
            fprintf(stderr, "Failed to connect to databases: Error: %s\n",
            mysql_error(&conn));
            return;
        }
       
        else
        {
            puts("Database connect!");
        }
    }
};