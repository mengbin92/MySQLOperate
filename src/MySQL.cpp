#include "MySQL.h"



MySQL::MySQL(string host, string user, string passwd, string db, unsigned port)
{
	m_host = host;
	m_user = user;
	m_passwd = passwd;
	m_dbname = db;
	m_port = port;

	mysql_init(&connect);
}

bool MySQL::connectDB()
{
	if (!mysql_real_connect(&connect, m_host.c_str(), m_user.c_str(), m_passwd.c_str(), m_dbname.c_str(), m_port, NULL, 0))
	{
		cout << "mysql connect error with " << mysql_errno(&connect) << endl;
		return false;
	}
	return true;
}

bool MySQL::changeDB(string dbname)
{
	cout << "Change DB from " << m_dbname << " to " << dbname << endl;
	m_dbname = dbname;

	sql.clear();
	sql = "use " + dbname + ";";
	ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
	{
		cout << "Change DB Fail:" << mysql_error(&connect) << endl;
		return false;
	}
	else
	{
		cout << "Change DB OK" << endl;
		return true;
	}
}

void MySQL::showDatabases()
{
	sql.clear();
	sql = "show databases;";
	ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
		cout << "mysql query error with " << ret << endl;

	showDetails(connect);

	mysql_free_result(res);
}

void MySQL::showTables()
{
	sql.clear();
	sql = "show tables;";
	ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
		cout << "mysql query error with " << ret << endl;

	showDetails(connect);
}

void MySQL::showTableStructure(string table)
{
	sql.clear();
	sql = "show create table " + table + ";";
	ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
		cout << "mysql query error with " << ret << endl;

	showDetails(connect);
}


MySQL::~MySQL()
{
	
}

bool MySQL::Insert(string table, map<string, string> values)
{
	sql.clear();
	if (values.size() == 0)
	{
		cout << "Input Error!!!" << endl;
		return false;
	}
	else
	{
		sql = "INSERT INTO " + table + "(";
		auto iter = values.begin();
		while (iter != values.end())
		{
			sql += iter->first + ',';
			iter++;
		}
		sql = sql.substr(0, sql.rfind(',')) + ") VALUES(";
		
		iter = values.begin();
		while (iter != values.end())
		{
			sql += string("\"") + iter->second + "\",";
			iter++;
		}
		sql = sql.substr(0, sql.rfind(',')) + ");";
		ret = mysql_query(&connect, sql.c_str());
		if (ret != 0)
		{
			cout << "mysql query error with " << ret << " Reason: " << mysql_error(&connect) << endl;
			return false;
		}
		ret = mysql_query(&connect, "commit");
		return true;
	}
}

bool MySQL::Delete(string table, map<string, string> values)
{
	sql.clear();
	if (values.size() == 0)
	{
		cout << "Input Error!!!" << endl;
		return false;
	}
	else
	{
		sql = "DELETE FROM " + table + " WHERE ";
		auto iter = values.begin();
		while (iter != values.end())
		{
			sql += iter->first + " = " + iter->second + " and ";
			iter++;
		}
		sql = sql.substr(0, sql.rfind("and")) + ";";
		ret = mysql_query(&connect, sql.c_str());
		if (ret != 0)
		{
			cout << "mysql query error with " << ret << " Reason: " << mysql_error(&connect) << endl;
			return false;
		}
		ret = mysql_query(&connect, "commit");
		return true;
	}
}

bool MySQL::Update(string table, map<string, string> values)
{
	sql.clear();
	if (values.size() == 0)
	{
		cout << "Input Error!!!" << endl;
		return false;
	}
	else
	{
		sql = "UPDATE " + table + " SET ";
		auto iter = values.begin();
		while (iter != values.end())
		{
			sql += iter->first + " = \"" + iter->second + "\" and ";
			iter++;
		}
		sql = sql.substr(0, sql.rfind("and")) + ";";
		ret = mysql_query(&connect, sql.c_str());
		if (ret != 0)
		{
			cout << "mysql query error with " << ret << " Reason: " << mysql_error(&connect) << endl;
			return false;
		}
		ret = mysql_query(&connect, "commit");
		return true;
	}
}

bool MySQL::Select(string table, map<string, string> values)
{
	sql.clear();

	if(values.size() == 0)
		sql = "SELECT * FROM " + table + " ;";
	else
	{
		sql = "SELECT * FROM " + table + " where ";
		auto iter = values.begin();
		while (iter != values.end())
		{
			sql += iter->first + " = \"" + iter->second + "\" and ";
			iter++;
		}
		sql = sql.substr(0, sql.rfind("and")) + ";";
	}

	ret = mysql_query(&connect, sql.c_str());
	if (ret != 0)
	{
		cout << "mysql query error with " << ret << " Reason: " << mysql_error(&connect) << endl;
		return false;
	}

	showDetails(connect);

	return true;
}

bool MySQL::Query(string cmd)
{
	size_t pos = cmd.find("select");
	if (pos < 0 || pos > cmd.size())
	{
		sql = cmd;
		ret = mysql_query(&connect, sql.c_str());
		if (ret != 0)
		{
			cout << "mysql query error with " << ret << " Reason: " << mysql_error(&connect) << endl;
			return false;
		}
		return true;
	}
	else
	{
		ret = mysql_query(&connect, sql.c_str());
		if (ret != 0)
		{
			cout << "mysql query error with " << ret << " Reason: " << mysql_error(&connect) << endl;
			return false;
		}
		showDetails(connect);
		return true;
	}
}

void MySQL::showDetails(MYSQL connect)
{
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

string int2string(long num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}
