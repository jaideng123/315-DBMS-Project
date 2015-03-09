#include "Database.h" 

//******************
//Command functions*
//******************

//Takes a .db file from DB folder and puts it into Main memory
void Database::open(string table_name) {
	ifstream myFile;
	string filename = FILEPATH +table_name+".db"; 
	myFile.open(filename);
	
	if(!myFile) {
		throw runtime_error("Error: unable to open file!\n");
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
		throw runtime_error("Error Table does not exist");
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

//write table to disk
void Database::write(string table_name){
	if(!table_exists(table_name)){
		throw runtime_error("Error: Table not found\n");
		return;
	}

	Table table = *find_table(table_name);
	string file_name = FILEPATH + table_name + ".db";
	ofstream my_file;
  	my_file.open(file_name.c_str());
	if(!my_file) {
		throw runtime_error("Error: unable to open file!\n");
	}

  	//write attributes
  	vector<Attribute> attr = table.get_attributes();
  	for (int i = 0; i < attr.size(); ++i){
  		my_file<<attr[i].get_name()<<"("<<attr[i].get_type()<<")";
  		if(i != attr.size()-1)
  			my_file<<",";
  	}
  	my_file<<endl;

  	//write records
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

//create a new table and insert it into tables
void Database::create(string table_name, vector<Attribute> v){
	if(!table_exists(table_name))
		tables.push_back(Table(table_name, v));
	else
		throw runtime_error("Error: Table already exists in database\n");
}

//insert a record into a table in tables
void Database::insert(string table_name, Record record){
	if(table_exists(table_name)){
		Table* t = find_table(table_name);
		if(t->is_valid(record))
			t->add_record(record);
		else
			throw runtime_error("Record is not compatible with table");
	}
	else
		throw runtime_error("Error: Table not found\n");
}

//prints table
void Database::show(string table_name){
	if(table_exists(table_name)){
		find_table(table_name)->print();
	}
	else
		throw runtime_error("Error: Table not found\n");
}


// copies records out of a table then over writes it
void Database::delete_records(string table_name, vector<int> to_remove){
	if(!table_exists(table_name)){	
 		throw runtime_error("Error: Table not found\n");
 		return;
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

 void Database::update(string table_name,vector<Record> new_records,vector<int> old_records){

	if(table_exists(table_name)){

		for(int i = 0; i < new_records.size(); i++){
			find_table(table_name)->set_record(old_records[i], new_records[i]);
		}
	}
	else
		throw runtime_error("Error: Table not found\n");

}

//****************
//Query functions*
//****************

Table Database::set_select(Table t1,vector<int> record_IDs){
	Table selection (t1.get_name(),t1.get_attributes());
	for(int i =0; i< record_IDs.size(); i++){
		Record buffer = t1.get_record(record_IDs[i]);
		
		selection.add_record(buffer);
	}
	
	return selection;
}


//everything in t1  + everything in t2 not in t1
Table Database::set_union(Table t1, Table t2){
	if(union_compatible(t1, t2))
	{
		Table sunion(t1.get_name());
		//adding records
		sunion.set_records(t1.get_records());
		for (int i = 0; i < t2.get_records().size(); ++i)
		{
			if(!record_exists(t1,t2.get_records()[i]))
				sunion.add_record(t2.get_records()[i]);
		}
		//adding attributes
		sunion.set_attributes(t1.get_attributes());
		return sunion;
	}
	else
		throw runtime_error("Error: Sets are incompatible\n");
	return Table("NULL");
}

//everything in t1 that is not in t2
Table Database::set_difference(Table t1, Table t2){
	if(!union_compatible(t1,t2)){
		throw runtime_error("Error: Sets are incompatible\n");
		return Table("NULL");
	}
	Table diff = Table(t1.get_name());
	for (int i = 0; i < t1.get_records().size(); ++i)
	{
		if(!record_exists(t2,t1.get_records()[i]))
			diff.add_record(t1.get_records()[i]);
	}
	diff.set_attributes(t1.get_attributes());
	return diff;
}

//combine Attributes and Records
Table Database::set_product(Table t1, Table t2){
	Table prod(t1.get_name());
	
	vector<Attribute> attributes;
	for(int i = 0; i< t1.get_attributes().size(); i++){
		Attribute attr(t1.get_attribute(i).get_name(),t1.get_attribute(i).get_type());
		prod.add_attribute(attr);
	}
	for(int i = 0; i< t2.get_attributes().size(); i++){
		Attribute attr(t2.get_attribute(i).get_name(),t2.get_attribute(i).get_type());
		prod.add_attribute(attr);
	}
	
	for(int i = 0; i< t1.get_records().size(); i++){
		for(int j = 0; j < t2.get_records().size(); j++){
			vector<string> values_1 = t1.get_record(j).get_values();
			vector<string> values_2 = t2.get_record(i).get_values();
			for(int i=0; i<values_2.size(); i++)
			{
				values_1.push_back(values_2[i]);
			}
			Record new_rec(values_1);
			prod.add_record(new_rec);
		}
	}
	return prod;
}

//select only certain attributes
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
	new_table.set_attributes(new_attrs);
	new_table.set_records(new_rec);
	return new_table;

}

//rename all attributes
Table Database::set_rename(Table t1, vector<string> attribute_names){
	Table new_table = t1;
	vector<Attribute> new_attrs;
	vector<Attribute> old_attrs = t1.get_attributes();

	for (int i = 0; i < old_attrs.size(); ++i){
		new_attrs.push_back(Attribute(attribute_names[i],old_attrs[i].get_type()));
	}

	new_table.set_attributes(new_attrs);
	return new_table;
}

Table Database::get_table(string table_name){
	if(table_exists(table_name)){
		return	*find_table(table_name);
	}
	else{
		cout<<"Error: Table not found: "+table_name+"\n";
		return Table("NULL");
	}
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
