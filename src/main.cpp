#include "MySQL.h"

using namespace std;

int main(int argc, char* argv[])
{
	MySQL sql("104.224.165.127", "root", ",.klio89", "mydb", 3306);
	if(sql.connectDB())
        cout<<"MySQL connect OK"<<endl;
    else
        cout<<"MySQL connect Error"<<endl;
	
    sql.showDatabases();
	

	return 0;
}
