#include "../inc/mysqlOpe.h"
#include <iostream>

using namespace std;

int main(int argc,char* argv[])
{
    vector<string> tables;

    mysqlOpe test("104.224.165.127","root",",.klio89","mydb",3306);
    test.connectDB();
    /*
    cout<<"show databases"<<endl;
    test.showDatabases();

    cout<<"show tables"<<endl;
    test.showTables();

    test.select("emp");
    */

    tables = test.getTables();
    
    for(size_t i = 0;i<tables.size();++i)
    {
        cout<<"show table "<<tables[i]<<" info..."<<endl;
    }

    //c++ 11
    /*
    auto iter = tables.begin();
    while(iter != tables.end())
    {
        cout<<"show table "<<*iter<<" info..."<<endl;
        test.select(*iter);
        ++iter;
    }
    */
    return 0;
}
