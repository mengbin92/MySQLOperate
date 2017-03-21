#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

using namespace std;

class mysqlOpe
{
public:
    mysqlOpe();
    ~mysqlOpe();

    mysqlOpe(string host,string user,string passwd,int port = 3306);
    
    bool connectDB();
private:
    MYSQL *m_con;
    MYSQL_RES *m_res;
    MYSQL_ROW row;
    
    string m_host;
    string m_user;
    string m_passwd;
    string m_db;
    int m_port;
};
