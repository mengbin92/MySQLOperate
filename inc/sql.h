#pragma once

#include <iomanip>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class ISQL
{
public:
	ISQL(){}
	virtual ~ISQL(){}

public:
	//insert
	virtual bool Insert(string table, map<string, string> values) = 0;

	//delete
	virtual bool Delete(string table, map<string, string> values) = 0;

	//update
	virtual bool Update(string table, map<string, string> values) = 0;

	//select
	virtual bool Select(string table, map<string, string> values) = 0;

	//query
	virtual bool Query(string cmd) = 0;
};