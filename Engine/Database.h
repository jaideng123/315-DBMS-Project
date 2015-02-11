#include "Table.h"
#include "Record.h"
#include "Attribute.h"
#include <string>
#include <vector>
using namespace std;

class Database{
public:
	//constructors go here!
	vector<Table> tables;
	//Command functions
	void open(string table_name){}
	void close(string table_name){}
	void write(string table_name){}
	void create(string table_name, vector<Attribute> v;){}
	void insert(string table_name, Record record){}
	void show(string table_name){}
	void update(string table_name,vector<Record> new_records,vector<int> old_records){}
	void delete_records(string table_name,vector<int> old_records){}

	//Query functions
	Table select(Table t1,vector<int> record_IDs ){}
	Table union(Table t1,Table t2){}
	Table difference(Table t1,Table t2){}
	Table product(Table t1,Table t2){}
	Table project(Table t1, vector<string> attribute_names){}
	Table rename(Table t1, vector<string> attribute_names){}

};