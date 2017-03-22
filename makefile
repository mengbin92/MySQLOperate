test:./src/mysqlOpe.cpp ./src/test.cpp
	g++ -o test -I./inc -L/usr/lib64/mysql -lmysqlclient ./src/mysqlOpe.cpp ./src/test.cpp

clean:
	rm test
