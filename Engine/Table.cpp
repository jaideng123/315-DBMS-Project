#include "Table.h"
#include <iostream>
#include <vector>

using namespace std;

Table::Table(string table_name, vector<Attribute> attr){
	name = table_name;
	attributes = attr;
}

Table::Table(string table_name, vector<Attribute> attr, vector<Record> rec){
	name = table_name;
	attributes = attr;
	records = rec;
}

Table& Table::operator=(const Table& rhs){
	name = rhs.name;
	attributes = rhs.attributes;
	records = rhs.records;
	return *this;
}

void Table::set_records(vector<Record> new_records){
	records = new_records;
}

Attribute Table::get_attribute_by_name(string name){
	for(int i = 0; i<attributes.size(); ++i){
		if(attributes[i].get_name() == name)
			return attributes[i];
	}
	cout<<"Error: Attribute not found \n";
	return Attribute("NULL","NULL");
}

void Table::add_attribute(Attribute attr){
	attributes.push_back(attr);
	for(int i = 0; i < records.size(); ++i)
		records[i].add_entry("NULL");
}

void Table::remove_attribute(int index){
	attributes.erase(attributes.begin() + index);
	for(int i = 0; i < records.size(); ++i)
		records[i].remove_entry(index);
}

void Table::remove_record(int i){
	records.erase(records.begin() + i);
}

void Table::print(){
	for (int i = 0; i < attributes.size(); ++i){
		cout<<attributes[i].get_name()<<"(";
		cout<<attributes[i].get_type()<<")|";
	}
	cout<<endl;
	for (int i = 0; i < records.size(); ++i){
		for(int j = 0; j < attributes.size(); ++j){
			cout<<records[i].get_entry(j)<<"|";
		}
		cout<<endl;
	}
}