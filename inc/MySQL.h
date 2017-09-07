#pragma once
#include "sql.h"

#include <mysql/mysql.h>
#include <iomanip>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

class MySQL : public ISQL
{
public:
	//初始化
	MySQL(string host, string user, string passwd, string db, unsigned port = 3306);

	//连接数据库
	bool connectDB();
	//修改连接的数据库
	bool changeDB(string dbname);
	//查询用户名下的所有数据库
	void showDatabases();
	//查询数据库中所有数据表
	void showTables();
	//查询数据表结构
	void showTableStructure(string table);

	~MySQL();

public:
	//insert
	virtual bool Insert(string table, map<string, string> values);

	//delete
	virtual bool Delete(string table, map<string, string> values);

	//update
	virtual bool Update(string table, map<string, string> values);

	//select
	virtual bool Select(string table, map<string, string> values);

	//query
	virtual bool Query(string cmd);

private:
	void showDetails(MYSQL connect);

public:
	MYSQL connect;
	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL_FIELD* fields;
	string sql;
	int ret;

private:
	string m_host;
	string m_user;
	string m_passwd;
	string m_dbname;
	int m_port;
};

string int2string(long num);
