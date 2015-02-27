#ifndef _table_h_                   // include file only once
#define _table_h_

#include "Record.h"
#include "Attribute.h"
#include <string>
#include <vector>

using namespace std;

class Table{
public:

	//constructors
	
	Table(string table_name){name = table_name;}
	Table(string table_name, vector<Attribute> attr);
	Table(string table_name, vector<Attribute> attr, vector<Record> rec);

	//name functions
	
	string get_name(){return name;}
	void set_name(string new_name){name = new_name;}

	//attribute functions
	
	vector<Attribute> get_attributes() const { return attributes;}
	void set_attributes(vector<Attribute> new_attributes){attributes = new_attributes;}
	Attribute get_attribute(int i){return attributes[i];}
	Attribute get_attribute_by_name(string name);
	void add_attribute(Attribute attr);
	int att_size(){return attributes.size();}
	void remove_attribute(int index);

	//record functions
	
	vector<Record> get_records() const {return records;}
	Record get_record(int i){return records[i];}
	void set_records(vector<Record> new_records);
	void add_record(Record new_record){records.push_back(new_record);}
	void set_record(int i, Record r) { records[i] = r;}
	int rec_size(){return records.size();}
	void remove_record(int i);

	//prints table to screen
	void print();

	//checks if record is valid
	bool is_valid(Record r);

	//overloading the assignment operator for table class
	Table& operator=(const Table&);


private:
	inline bool is_integer(const std::string & s){
	   	if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
	   		return false ;
		char * p ;
		strtol(s.c_str(), &p, 10) ;
		return (*p == 0) ;
	}
	string name;
	vector<Attribute> attributes;
	vector<Record> records;
};

//overloading equals-equals operator for table class
inline bool operator==(const Table& lhs, const Table& rhs){
	if(lhs.get_records() == rhs.get_records())
		if(lhs.get_attributes() == rhs.get_attributes())
			return true;
	return false;
}
#endif

