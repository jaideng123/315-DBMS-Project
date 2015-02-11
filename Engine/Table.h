#include "Record.h"
#include "Attribute.h"
#include <string>
#include <vector>

using namespace std;

class Table{
public:
	//constructors go here!

	string get_name(){return name;}
	void set_name(strin new_name){name = new_name;}

	vector<Attribute> get_attributes(){ return attributes;}
	void set_attributes(vector<Attribute> new_attributes){attributes = new_attributes;}
	Attribute get_attribute(int i){return attributes[i];}
	Attribute get_attribute_by_name(string name){}

	vector<Record> get_records(){return records;}
	Record get_record(int i){return records[i];}
	void set_records(vector<Attribute> new_records){records = new_records;}
	void add_record(Record new_record){records.push_back(new_record);}
	void remove_record(int i){}

private:
	string name;
	vector<Attribute> attributes;
	vector<Record> records;


};