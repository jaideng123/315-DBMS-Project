#include "Database.h" 

//******************
//Command functions*
//******************

//Takes a .db file from DB folder and puts it into Main memory
void Database::open(string table_name) {
	ifstream myFile;
	//Warning - Directory Path Hardcoded
	string filename = "Databases/" +table_name+".db"; 
	myFile.open(filename);
	
	if(!myFile) {
		cout<<"Error: unable to open file!\n";
	}
	else {
		//Get first line containing attributes
		vector<Attribute> attributes1;
		vector<Record> records;
		get_attributes_from_file(myFile, attributes1);
		//Get records
		get_records_from_file(myFile,records,attributes1.size());

		Table from_file(table_name,attributes1,records);
		
		this->tables.push_back(from_file);
	}
}

//remove table from memory
void Database::close(string table_name) {
	if(!table_exists(table_name)){
		cout<<"Error Table does not exist";
		return;
	}
	for (int i = 0; i < tables.size(); ++i)
	{
		if(tables[i].get_name() == table_name){
			tables.erase(tables.begin() + i);
			return;
		}
	}

}

void Database::write(string table_name){
	if(!table_exists(table_name)){
		cout<<"Error: Table not found\n";
		return;
	}

	Table table = *find_table(table_name);
	string file_name ="Databases/" + table_name + ".db";
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

void Database::insert(string table_name, Record record){
	if(table_exists(table_name)){
		find_table(table_name)->add_record(record);
	}
}

void Database::show(string table_name){
	if(table_exists(table_name)){
		find_table(table_name)->print();
	}
	else
		cout<<"Error: Table not found!"<<endl;
}


// copies data out of a table then over writes it
void Database::delete_records(string table_name, vector<int> to_remove){
	if(!table_exists(table_name)){	
 		cout<<"Error: Table does not exist\n";
 	}
	vector<Record> rec;
	Table * table = find_table(table_name);
	for(int i = 0; i < table->rec_size(); i++){
		bool found = false;
 		for (int j = 0; j < to_remove.size(); ++j){
 			if (to_remove[j] == i)
 				found = true;
 		}
 		if (!found)
 			rec.push_back(table->get_record(i));
 	}
 	table->set_records(rec);
 }



//****************
//Query functions*
//****************

Table Database::set_union(Table t1, Table t2){
	if(union_compatible(t1, t2))
	{
		Table sunion(t1.get_name());
		//adding attributes
		for (int i = 0; i < t1.get_records().size(); ++i)
		{
			if(record_exists(t2,t1.get_records()[i]))
				sunion.add_record(t1.get_records()[i]);
		}
		return sunion;
	}
	else
		cout<<"Sets are incompatible"<<endl;
	return Table("NULL");
}

//
Table Database::set_difference(Table t1, Table t2){
	if(!union_compatible(t1,t2))
		return Table("NULL");
	Table diff = Table(t1.get_name());
	for (int i = 0; i < t1.get_records().size(); ++i)
	{
		if(!record_exists(t2,t1.get_records()[i]))
			diff.add_record(t1.get_records()[i]);
	}
	return diff;
}

Table Database::set_product(Table t1, Table t2){
	Table prod(t1.get_name());


	prod.set_attributes(t1.get_attributes());

	for(int i = 0; i< t2.get_attributes().size(); i++){
		for(int j = 0; j < t1.get_attributes().size(); j++){
			if(t2.get_attribute(i)==t1.get_attribute(j))
				break;
			if(j == t1.get_attributes().size()-1)
				prod.add_attribute(t2.get_attribute(i));
		}
	}
	prod.set_records(t1.get_records());
	for(int i = 0; i< t2.get_records().size(); i++){
		for(int j = 0; j < t1.get_records().size(); j++){
			if(t2.get_record(i)==t1.get_record(j))
				break;
			if(j == t1.get_records().size()-1)
				prod.add_record(t2.get_record(i));
		}
	}
}

Table Database::set_project(Table t1, vector<string> attrs){
	Table new_table(t1.get_name());
	vector<int> rows;
	vector<Attribute> new_attrs;
	for (int i = 0; i < attrs.size(); ++i){
		for (int j = 0; j < t1.get_attributes().size(); ++j){
			if (t1.get_attributes()[j].get_name() == attrs[i] ){
				new_attrs.push_back(t1.get_attributes()[j]);
				rows.push_back(j);
			}
		}
	}
	vector<Record> new_rec;
	for (int i = 0; i < t1.get_records().size(); ++i){
		Record temp;
		for (int j = 0; j < rows.size(); ++j){
			temp.add_entry(t1.get_record(i).get_entry(rows[j]));
		}
		new_rec.push_back(temp);
	}
	return new_table;

}


//*************************
//private helper functions*
//*************************

void Database::get_attributes_from_file(ifstream &input,vector<Attribute> &attributes){
	
	string attribute_line;
	getline(input, attribute_line);

	stringstream stream(attribute_line);
	string attribute_pair ="";
	//Parse first using ',' delimiter. 
	while(getline ( stream, attribute_pair, ',')) {
		stringstream attribute_string(attribute_pair);
		string attribute_name;
		string type;
		getline(attribute_string, attribute_name, '(');
		getline(attribute_string, type);
		type = type.substr(0,type.size()-1);
		Attribute attribute(attribute_name,type);
		attributes.push_back(attribute);
	}
}

void Database::get_records_from_file(ifstream &input ,
		vector<Record> &records, int num_attributes){
	
	string record_line;
	
	
	
	//Parse first using ',' delimiter. 
	while(getline(input, record_line)){
		stringstream stream(record_line);
		vector<string> tuple_fromFile;
		for(int i = 0; i < num_attributes; i++) {
			string value ="";
			getline ( stream, value, ',');
			tuple_fromFile.push_back(value);
		}
		Record record(tuple_fromFile);
		records.push_back(record);
	 
 	}
	
}

//union compatible = same set of attributes
//used for union and difference
bool Database::union_compatible(Table t1, Table t2){
	vector<Attribute> attr1 = t1.get_attributes();
	vector<Attribute> attr2 = t2.get_attributes();
	if(attr1.size() != attr2.size())
		return false;
	for (int i = 0; i < attr1.size(); ++i)
	{
		if(attr1[i].get_name() != attr2[i].get_name())
			return false;
		if(attr1[i].get_type() != attr2[i].get_type())
			return false;
	}
	return true;
}

bool Database::table_exists(string table_name){
	for (int i = 0; i < tables.size(); ++i)
	{
		if(tables[i].get_name() == table_name)
			return true;
	}
	return false;
}

//checks if a record exists in a table
bool Database::record_exists(Table t1, Record rec){
	vector<Record> records = t1.get_records();
	for (int i = 0; i < records.size(); ++i)
	{
		bool match = true;
		for (int j = 0; j < rec.get_size(); ++j)
		{
			if(rec.get_entry(j) != records[i].get_entry(j))
				match = false;
		}
		if(match == true)
			return true;
	}
	return false;
}

//returns pointer to Table
Table * Database::find_table(string table_name){
	for (int i = 0; i < tables.size(); ++i)
	{
		if(tables[i].get_name() == table_name)
			return &tables[i];
	}
	return NULL;
}
