#include "../inc/mysqlOpe.h"
#include <iostream>

using namespace std;

int main(int argc,char* argv[])
{
    vector<string> tables;
	vector<string> databases;

	mysqlOpe test("104.224.165.127", "root", ",.klio89", "mydb", 3306);
	test.connectDB();

#if 0
	cout<<"show databases"<<endl;
	test.showDatabases();

	databases = test.getDatabases();
	for (size_t i = 0; i < databases.size(); ++i)
	{
		if (test.changeDB(databases[i]))
		{
			tables.clear();

			tables = test.getTables();
			for (size_t i = 0; i<tables.size(); ++i)
			{
				cout << "show table " << tables[i] << " info..." << endl;
				//test.select(tables[i]);
				string filename = tables[i] + ".txt";
				test.select(tables[i], filename);
				cout << "---------------------" << endl;
			}
		}
	}
	/*//展示表中的信息
	tables = test.getTables();

	//c++ 11
	auto iter = tables.begin();
	while(iter != tables.end())
	{
	cout<<"show table "<<*iter<<" info..."<<endl;
	test.select(*iter);
	++iter;
	}
	*/
#endif	

#if 1
	test.showTable("dept");

#endif
    return 0;
}
