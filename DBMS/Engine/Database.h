#ifndef _database_h_                   // include file only once
#define _database_h_

#include "Table.h"
#include "Record.h"
#include "Attribute.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#define FILEPATH "Databases/"

using namespace std;

class Database{
friend class Parser;
public:
	//constructor
	Database(){system("mkdir -p Databases");}

	vector<Table> tables;

	//Command functions

	//bring table into memory from disk
	void open(string table_name);
	//remove table from memory
	void close(string table_name); 
	//write table to disk
	void write(string table_name);
	//create a new table and insert it into tables
	void create(string table_name, vector<Attribute> v);
	//insert a record into a table in tables
	void insert(string table_name, Record record);
	//prints table
	void show(string table_name);
	//swaps out records at the indices in old records for new ones
	void update(string table_name,vector<Record> new_records,vector<int> old_records);
	//delete records based on index
	void delete_records(string table_name,vector<int> to_remove);
	//exit (flush all tables)
	void exit(){tables.clear();}

	//Query functions

	//select based on record ID's(position in table)
	Table set_select(Table t1,vector<int> record_IDs);
	//everything in t1  + everything in t2 not in t1
	Table set_union(Table t1, Table t2);
	//everything in t1 that is not in t2
	Table set_difference(Table t1,Table t2);
	//combine Attributes and Records
	Table set_product(Table t1,Table t2);
	//select only certain attributes
	Table set_project(Table t1, vector<string> attribute_names);
	//rename all attributes
	Table set_rename(Table t1, vector<string> attribute_names);

	Table get_table(string table_name);

private:
	//Helper Functions
	void get_attributes_from_file(ifstream &input,vector<Attribute> &attributes); 
	void get_records_from_file(ifstream &input ,
		vector<Record> &records, int num_attributes);
	
	bool union_compatible(Table t1, Table t2);
	bool table_exists(string table_name);
	bool record_exists(Table t1,Record rec);

	Table * find_table(string table_name);


};
#endif
