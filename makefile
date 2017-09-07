test:./src/MySQL.cpp ./src/main.cpp
	g++ -g -o test -I./inc -L/usr/lib64/mysql -lmysqlclient -std=c++11 ./src/MySQL.cpp ./src/main.cpp


clean:
	rm -f test
