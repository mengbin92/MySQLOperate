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

	mysql_init(&connect);

}

bool mysqlOpe::connectDB()
{
	if (!mysql_real_connect(&connect, m_host.c_str(), m_user.c_str(), m_passwd.c_str(), m_dbname.c_str(), m_port, NULL, 0))
	{
		cout << "mysql connect error with " << mysql_errno(&connect) << endl;
		return false;

	}
	return true;

}

bool mysqlOpe::changeDB(string dbname)
{
	cout<<"Change DB from "<<m_dbname<<" to "<<dbname<<endl;
	m_dbname = dbname;

	sql.clear();
	sql = "use " + dbname + ";";
	ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
	{
		cout << "Change DB Fail:" << mysql_error(&connect)<<endl;
		return false;
	}
	else
	{
		cout << "Change DB OK" << endl;
		return true;
	}
}

void mysqlOpe::showDatabases()
{
	sql.clear();
	sql = "show databases;";
	ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
		cout << "mysql query error with " << ret << endl;

	//获取列数
	int col = mysql_field_count(&connect);

	//获取结果集
	res = mysql_store_result(&connect);
	if (res == NULL)
	{
		cout << "mysql store result error with " << mysql_error(&connect) << endl;
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
		{
			if (row[i] == NULL)
				cout << "NULL | ";
			else
				cout << row[i] << " | ";
		}
		cout << endl;
	}

	mysql_free_result(res);
}

void mysqlOpe::showTables()
{
	sql.clear();
	sql = "show tables;";
	ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
		cout << "mysql query error with " << ret << endl;

	//获取列数
	int col = mysql_field_count(&connect);

	//获取结果集
	res = mysql_store_result(&connect);
	if (res == NULL)
	{
		cout << "mysql store result error with " << mysql_error(&connect) << endl;
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
		{
			if (row[i] == NULL)
				cout << "NULL | ";
			else
				cout << row[i] << " | ";
		}
		cout << endl;
	}

}

void mysqlOpe::showTable(string table)
{
	sql.clear();
	sql = "show create table " + table + ";";
	ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
		cout << "mysql query error with " << ret << endl;

	//获取列数
	int col = mysql_field_count(&connect);

	//获取结果集
	res = mysql_store_result(&connect);
	if (res == NULL)
	{
		cout << "mysql store result error with " << mysql_error(&connect) << endl;
		exit(-1);
	}

	//打印表头
	fields = mysql_fetch_fields(res);
	for (int i = 0; i < col; ++i)
		cout << setw(10) << fields[i].name << " | ";
	cout << endl;

	//输出检索结果
	while ((row = mysql_fetch_row(res)))
	{
		for (int i = 0; i < col; ++i)
		{
			if (row[i] == NULL)
				cout << setw(10) << "NULL | ";
			else
				cout << setw(10) << row[i] << " | ";
		}
		cout << endl;
	}
}

void mysqlOpe::select(string table)
{
	sql.clear();
	sql = "select * from " + table + ";";
	ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
		cout << "mysql query error with " << ret << endl;

	//获取列数
	int col = mysql_field_count(&connect);

	//获取结果集
	res = mysql_store_result(&connect);
	if (res == NULL)
	{
		cout << "mysql store result error with " << mysql_error(&connect) << endl;
		exit(-1);
	}

	//打印表头
	fields = mysql_fetch_fields(res);
	for (int i = 0; i < col; ++i)
		cout << setw(10) << fields[i].name << " | ";
	cout << endl;

	//输出检索结果
	while ((row = mysql_fetch_row(res)))
	{
		for (int i = 0; i < col; ++i)
		{
			if (row[i] == NULL)
				cout << setw(10) << "NULL | ";
			else
				cout << setw(10) << row[i] << " | ";
		}
		cout << endl;
	}
}

void mysqlOpe::select(string table, string filename)
{
	ofstream outPut(filename.c_str());

	sql.clear();
	sql = "select * from " + table + ";";
	ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
	{
		cout << "Select Tables "<< table <<" error with " << ret << endl;
		cout << "Reason: " << mysql_error(&connect);
		return;
	}

	//获取列数
	int col = mysql_field_count(&connect);

	//获取结果集
	res = mysql_store_result(&connect);
	if (res == NULL)
	{
		cout << "mysql store result error with " << mysql_error(&connect) << endl;
		exit(-1);
	}

	//打印表头
	fields = mysql_fetch_fields(res);
	for (int i = 0; i < col; ++i)
		outPut << setw(10) << fields[i].name << " | ";
	outPut << endl;

	//输出检索结果
	while ((row = mysql_fetch_row(res)))
	{
		for (int i = 0; i < col; ++i)
		{
			if (row[i] == NULL)
				outPut << setw(10) << "NULL | ";
			else
				outPut << setw(10) << row[i] << " | ";
		}
		outPut << endl;
	}
	outPut.close();
}

bool mysqlOpe::querySQL(string sqlCMD)
{
    sql.clear();
    sql = sqlCMD;
    
    ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
		{
			cout << "mysql query error with " << ret << endl;
			cout <<"Reason: "<<mysql_error(&connect) <<endl;
			return false;
		}

	//获取列数
	int col = mysql_field_count(&connect);

	//获取结果集
	res = mysql_store_result(&connect);
	if (res == NULL)
	{
		cout << "mysql store result error with " << mysql_error(&connect) << endl;
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
		{
			if (row[i] == NULL)
				cout << "NULL | ";
			else
				cout << row[i] << " | ";
		}
		cout << endl;
	}
	return true;
}

vector<string> mysqlOpe::getDatabases()
{
	vector<string> dataVector;

	sql.clear();
	sql = "show databases;";
	ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
		cout << "Show Databases error with " << ret << endl;

	//获取列数
	int col = mysql_field_count(&connect);

	//获取结果集
	res = mysql_store_result(&connect);
	if (res == NULL)
	{
		cout << "mysql store result error with " << mysql_error(&connect) << endl;
		exit(-1);
	}

	//输出检索结果
	while ((row = mysql_fetch_row(res)))
	{
		for (int i = 0; i < col; ++i)
		{
			if (row[i] == NULL)
				dataVector.push_back("NULL");
			else
				dataVector.push_back(row[i]);
		}
	}
	return dataVector;
}

vector<string> mysqlOpe::getTables()
{
	vector<string> tableVector;

	sql.clear();
	sql = "show tables;";
	ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
		cout << "Show Tables error with " << ret << endl;

	//获取列数
	int col = mysql_field_count(&connect);

	//获取结果集
	res = mysql_store_result(&connect);
	if (res == NULL)
	{
		cout << "mysql store result error with " << mysql_error(&connect) << endl;
		exit(-1);
	}

	//输出检索结果
	while ((row = mysql_fetch_row(res)))
	{
		for (int i = 0; i < col; ++i)
		{
			if (row[i] == NULL)
				tableVector.push_back("NULL");
			else
				tableVector.push_back(row[i]);
		}
	}
	return tableVector;
}

mysqlOpe::~mysqlOpe()
{
	if (res != NULL)
	{
		mysql_free_result(res);
	}
}
