#include "../inc/mysqlOpe.h"

#include <string>

using namespace std;


mysqlOpe::mysqlOpe()
{

}

mysqlOpe::mysqlOpe(string host, string user, string passwd, string dbname, unsigned port)
{
    m_host = host;
    m_user = user;
    m_passwd = passwd;
    m_dbname = dbname;
    m_port = port;

    connect = mysql_init(connect);
    if (NULL == connect)
    {
        cout << "mysql init error with " << mysql_errno(connect) << endl;

    }

}

bool mysqlOpe::connectDB()
{
    connect = mysql_real_connect(connect, m_host.c_str(), m_user.c_str(), m_passwd.c_str(), m_dbname.c_str(), m_port, NULL, 0);
    if (NULL == connect)
    {
        cout << "mysql connect error with " << mysql_errno(connect) << endl;
        return false;

    }
    return true;

}

void mysqlOpe::showDatabases()
{
    sql.clear();
    sql = "show databases;";
    ret = mysql_query(connect, sql.c_str());
    if (ret != 0)
        cout << "mysql query error with " << ret << endl;

    //获取列数
    int col = mysql_field_count(connect);

    //获取结果集
    res = mysql_store_result(connect);
    if (res == NULL)
    {
        cout << "mysql store result error with " << mysql_error(connect) << endl;
        exit(-1);
    }

    //打印表头
    fields = mysql_fetch_fields(res);
    for (int i = 0; i < col; ++i)
        cout << fields[i].name << " | ";
    cout << endl;

    //输出检索结果
    while ((row = mysql_fetch_row(res)))
    {
        for (int i = 0; i < col; ++i)
            cout << row[i] << " | ";
        cout << endl;
    }

    mysql_free_result(res);
}

void mysqlOpe::showTables()
{
} 


mysqlOpe::~mysqlOpe()
{
    /*
    if (connect != NULL)
    {
        mysql_close(connect);
    }
    if (res != NULL)
    {
        mysql_free_result(res);
    }
    */
}
