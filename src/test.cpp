#include "../inc/mysqlOpe.h"
#include <iostream>

using namespace std;

int main(int argc,char* argv[])
{
    mysqlOpe test("104.224.165.127","root",",.klio89","mydb",3306);
    test.connectDB();
    test.showDatabases();

    return 0;
}
