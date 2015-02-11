#ifndef _database_h_                   // include file only once
#define _database_h_
#include "Table.h"
#include "Record.h"
#include "Attribute.h"
#include <string>
#include <vector>
using namespace std;

class Database{
public:
	Database(){}
	//constructors go here!
	vector<Table> tables;
	//Command functions
	void open(string table_name){}
	void close(string table_name){}
	void write(string table_name){}
	void create(string table_name, vector<Attribute> v){}
	void insert(string table_name, Record record){}
	void show(string table_name){}
	void update(string table_name,vector<Record> new_records,vector<int> old_records){}
	void delete_records(string table_name,vector<int> old_records){}

	//Query functions
	Table set_select(Table t1,vector<int> record_IDs){}
	Table set_union(Table tab1, Table tab2){}
	Table set_difference(Table t1,Table t2){}
	Table set_product(Table t1,Table t2){}
	Table set_project(Table t1, vector<string> attribute_names){}
	Table set_rename(Table t1, vector<string> attribute_names){}

};
#endif