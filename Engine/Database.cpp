#include "Database.h" 
#include <iostream>
#include <fstream>


void Database::write(string table_name){
	if(!table_exists(table_name)){
		cout<<"Error: Table not found\n";
		return;
	}

	Table table = find_table(table_name);
	string file_name = table_name + ".db";
	ofstream my_file;
  	my_file.open(file_name.c_str());
  	//print attributes
  	vector<Attribute> attr = table.get_attributes();
  	for (int i = 0; i < attr.size(); ++i)
  	{
  		my_file<<attr[i].get_name()<<"("<<attr[i].get_type()<<")";
  		if(i != attr.size()-1)
  			my_file<<",";
  	}
  	my_file<<endl;
  	//print actual records
	vector<Record> rec = table.get_records();
	for (int i = 0; i < rec.size(); ++i){
  		for (int j = 0; j < rec[i].get_size(); ++j){
	  		my_file<<rec[i].get_entry(j);
	  		if(j != rec[i].get_size()-1)
	  			my_file<<",";
  		}
  		if(i != rec.size()-1)
  			my_file<<endl;
  	}
  	my_file.close();
  	return;

}

void Database::create(string table_name, vector<Attribute> v){
	tables.push_back(Table(table_name, v));
}

void Database::show(string table_name){
	if(table_exists(table_name)){
		find_table(table_name).print();
	}
}

bool Database::table_exists(string table_name){
	for (int i = 0; i < tables.size(); ++i)
	{
		if(tables[i].get_name() == table_name)
			return true;
	}
	return false;
}

Table Database::find_table(string table_name){
	for (int i = 0; i < tables.size(); ++i)
	{
		if(tables[i].get_name() == table_name)
			return tables[i];
	}
	return Table("NULL");
}
