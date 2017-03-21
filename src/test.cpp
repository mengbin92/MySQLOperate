#include "../inc/mysqlOpe.h"
#include <iostream>

using namespace std;

int main(int argc,char* argv[])
{
    mysqlOpe test("104.224.165.127","root",",.klio89","mysql",3306);
    test.connectDB();
    test.showTables();

    return 0;
}
