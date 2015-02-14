#include "Database.h"
#include <string>

using namespace std;

int main(){
	
	Database db;
	vector<Attribute> attr;
	
	attr.push_back(Attribute("ID","integer"));
	attr.push_back(Attribute("Name","string"));
	attr.push_back(Attribute("Description","text"));
	attr.push_back(Attribute("User ID","integer"));
	
	Table test("Test Table",attr);
	
	for (int i = 0; i < 20; ++i)
	{
		Record r;
		
		//c++ 11 features
		string pid = to_string(i);
		string uid = to_string(i*20);
		
		r.add_entry(pid);
		r.add_entry("Dummy String");
		r.add_entry("Dummy Text");
		r.add_entry(uid);
		
		test.add_record(r);
	}
		
	Record r2;
	string pid = to_string(7);
	string uid = to_string(13);

	r2.add_entry(pid);
	r2.add_entry("Nabir");
	r2.add_entry("Dinani");
	r2.add_entry(uid);

	db.tables.push_back(test); 
	db.insert(test.get_name(), r2);
	test.add_record(r2);
	vector<int> temp;

	temp.push_back(15);
	temp.push_back(7);
	temp.push_back(19);

	db.delete_records(test.get_name(), temp);
	

	// db.create("Test Table 2", attr);
	// db.insert("Test Table 2", r2);
	// Test commands involving disk
	db.show("Test Table");
	db.write("Test Table");
	db.close("Test Table");
	db.open("Test Table");
	db.show("Test Table");
	//db.write("Test Table 2");

	return 0;
}
