#include <iostream>

#include "../inc/mysqlOpe.h"

using namespace std;

mysqlOpe::mysqlOpe()
{
}

mysqlOpe::~mysqlOpe()
{
    if(m_con != NULL)
        mysql_close(m_con);
}

mysqlOpe::mysqlOpe(string host,string user,string passwd,int port)
{
    m_host = host;
    m_user = user;
    m_passwd = passwd;
    m_port = port;
}

bool mysqlOpe::connectDB()
{
}
