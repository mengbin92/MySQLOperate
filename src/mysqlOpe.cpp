#include <iostream>
#include <string>

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

mysqlOpe::mysqlOpe(string host,string user,string passwd,string db,int port)
{
    m_host = host;
    m_user = user;
    m_passwd = passwd;
    m_db = db;
    m_port = port;
    
    m_con = mysql_init(NULL);
    if(NULL == m_con)
    {
        cout<<"mysql init error,errno:"<<mysql_errno(m_con)<<endl;
    }
}

bool mysqlOpe::connectDB()
{
    m_con = mysql_real_connect(m_con,m_host.c_str(),m_user.c_str(),m_passwd.c_str(),m_db.c_str(),m_port,NULL,0);
    if(NULL == m_con)
    {
        cout<<"mysql connect error,errno:"<<mysql_errno(m_con)<<endl;
        return false;
    }
    return true;
}

void mysqlOpe::showTables()
{
    sql.clear();
    sql = "show tables;";
    int ret = mysql_query(m_con,sql.c_str());
    if(!ret)
    {
        m_res = mysql_store_result(m_con);
        if(m_res)
        {
            int numRows = mysql_num_rows(m_res);
            int numFields = mysql_num_fields(m_res);
            cout<<numRows<<"行"<<numFields<<"字段"<<endl;
        }
    }
}
