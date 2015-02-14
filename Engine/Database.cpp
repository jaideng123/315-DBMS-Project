#include "Database.h" 


//Command functions
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

//no need to copy in to a table, just deletes the record
void Database::delete_records(string table_name,vector<int> to_remove){
	
	if(table_exists(table_name)){
		for(int i = 0; i < to_remove.size(); i++){
			if(to_remove[i] < find_table(table_name)->rec_size()){
				find_table(table_name)->remove_record(to_remove[i]);
				for(int j = 0; j < to_remove.size(); j++)
				{
					if(to_remove[j] > to_remove[i])
						to_remove[j]--;
				}
			}
		}
	}
}

//another way to do it: copies data into a table and returns it
// Table Database::delete_records(string table_name, vector<int> to_remove){
	
// 	Table temp("hello");
// 	if(table_exists(table_name)){	

// 		for(int i = 0; i < to_remove.size(); i++){
// 			find_table(table_name)->remove_record(to_remove[i]);
// 		}
// 		for(int i = 0; i < find_table(table_name)->rec_size(); i++){

// 			temp.add_record(find_table(table_name)->get_record(i));
// 		}
// 	}
// 	return temp;
// }


void Database::get_attributes_from_file(ifstream &input,vector<Attribute> &attributes) {
	
	string attribute_line;
	input>>attribute_line;
	stringstream stream(attribute_line);
	string attribute_pair ="";
	//Parse first using ',' delimiter. 
	while(getline ( stream, attribute_pair, ',')) {
		stringstream attribute_string;
		string attribute_name;
		string type;
		getline(attribute_string, attribute_name, '(');
		getline(attribute_string, type);
		Attribute attribute(attribute_name,type);
		attributes.push_back(attribute);
		
	}
}

void Database::get_records_from_file(ifstream &input ,
		vector<Record> &records, int num_attributes) 
	{
	
	string record_line;
	input>>record_line;
	stringstream stream(record_line);
	
	//Parse first using ',' delimiter. 
	while(!stream){
		
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


//Query functions
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
	return NULL;
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
			if(t2.get_attribute(i)==t1.get_attribute(j)
				break;
			if(j == t1.get_attributes().size()-1)
				prod.add_attribute(t2.get_attribute(i))
		}
	}
	prod.set_records(t1.get_records());
	for(int i = 0; i< t2.get_records().size(); i++){
		for(int j = 0; j < t1.get_records().size(); j++){
			if(t2.get_record(i)==t1.get_record(j)
				break;
			if(j == t1.get_record().size()-1)
				prod.add_record(t2.get_record(i))
		}
	}
}


//******************
//private functions*
//******************
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
