#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

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

	mysqlOpe(string host, string user, string passwd, string db, unsigned port = 3306);
 
    //连接数据库
	bool connectDB();
	//修改连接的数据库
    bool changeDB(string dbname);
    //查看数据库
	void showDatabases();
    //查看数据库中的表
	void showTables();
    //查看表结构
	void showTable(string table);
    //查询数据表中的数据
	void select(string table);
	void select(string table, string filename);

    //执行sql操作
    bool querySQL(string sqlCMD);

    //获取数据库
	vector<string> getDatabases();
    //获取表
	vector<string> getTables();

public:
	MYSQL connect;
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
