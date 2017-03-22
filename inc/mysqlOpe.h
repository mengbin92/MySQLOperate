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

    mysqlOpe(string host,string user,string passwd,string db,unsigned port = 3306);
    
    bool connectDB();
    void showDatabases();
    void showTables();

public:
    MYSQL* connect;
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD* fields;
    string sql;
    int ret;
    
    string m_host;
    string m_user;
    string m_passwd;
    string m_dbname;
    int m_port;

};
