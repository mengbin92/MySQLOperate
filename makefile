test:./src/mysqlOpe.cpp ./src/test.cpp
	g++ -o test -I./inc -L/usr/lib64/mysql -lmysqlclient -std=c++11 ./src/mysqlOpe.cpp ./src/test.cpp

clean:
	rm -f test
