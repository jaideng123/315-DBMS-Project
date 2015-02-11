#include "Table.h"

using namespace std;

Table::Table(string table_name, vector<Attribute> a){

}
Table::Table(string table_name, vector<Attribute> attr, vector<Record> rec){

}
Table& Table::operator=(const Table& rhs){
	name = rhs.name;
	attributes = rhs.attributes;
	records = rhs.records;
	return *this;
}