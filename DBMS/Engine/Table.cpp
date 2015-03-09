#include "Table.h"
#include <iostream>
#include <vector>

using namespace std;

//constructors

Table::Table(string table_name, vector<Attribute> attr){
	name = table_name;
	attributes = attr;
}

Table::Table(string table_name, vector<Attribute> attr, vector<Record> rec){
	name = table_name;
	attributes = attr;
	records = rec;
}

//attribute functions

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

//record functions

void Table::set_records(vector<Record> new_records){
	records = new_records;
}

void Table::remove_record(int i){
	records.erase(records.begin() + i);
}

//prints table to screen
void Table::print(){
	cout<<name<<endl;
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
bool Table::is_valid(Record r){
	if(r.get_size() != attributes.size())
		return false;
	for (int i = 0; i < attributes.size(); ++i){
		if(attributes[i].get_type() == "INTEGER"){
			if (!is_integer(r.get_entry(i)))
				return false;
		}
		else if(attributes[i].get_type().substr(0,7) == "VARCHAR"){
			if (r.get_entry(i).size() > attributes[i].get_size())
				return false;
		}
		else if(!(attributes[i].get_type() == "STRING")){
			return false;
		}
	}
	return true;
}

//overloading the assignment operator for the table class
Table& Table::operator=(const Table& rhs){
	name = rhs.name;
	attributes = rhs.attributes;
	records = rhs.records;
	return *this;
}
