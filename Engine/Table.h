#ifndef _table_h_                   // include file only once
#define _table_h_
#include "Record.h"
#include "Attribute.h"
#include <string>
#include <vector>

using namespace std;

class Table{
public:
	Table& operator=(const Table& rhs);
	Table(){}
	//constructors go here!

	string get_name(){return name;}
	void set_name(string new_name){name = new_name;}

	vector<Attribute> get_attributes(){ return attributes;}
	void set_attributes(vector<Attribute> new_attributes){attributes = new_attributes;}
	Attribute get_attribute(int i){return attributes[i];}
	Attribute get_attribute_by_name(string name){}

	vector<Record> get_records(){return records;}
	Record get_record(int i){return records[i];}
	void set_records(vector<Attribute> new_records){}
	void add_record(Record new_record){records.push_back(new_record);}
	void remove_record(int i){}

private:
	string name;
	vector<Attribute> attributes;
	vector<Record> records;


};
Table& Table::operator=(const Table& rhs){
	name = rhs.name;
	attributes.clear();
	for(int i = 0; i<rhs.attributes.size();++i)
		attributes.push_back(rhs.attributes[i]);
	records.clear();
	for(int i = 0; i<rhs.records.size();++i)
		records.push_back(rhs.records[i]);
	return *this;
}
#endif