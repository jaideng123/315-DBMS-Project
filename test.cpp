#include "DBMS.h"
#include <iostream>

using namespace std;

 int main(){
	DBMS db;
	vector<Attribute> attr;

 	attr.push_back(Attribute("id","INTEGER"));
	attr.push_back(Attribute("name","VARCHAR(20)"));
	attr.push_back(Attribute("description","STRING"));
	attr.push_back(Attribute("user_id","INTEGER"));

	Table test("test",attr);

	for (int i = 0; i < 20; ++i){
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
	db.db.tables.push_back(test);

	string q = "testing <- SELECT (id < 5 && (name == \"Eric\" || name != \"Tristan\")) test;";
	db.execute(q);
	db.db.show("testing");
	
	q = "testing <- test - testing;";
	db.execute(q);
	db.db.show("testing");
	
	q = "testing <- test + testing;";
	db.execute(q);
	db.db.show("testing");
	
	q = "testing <- RENAME (new_id,new_name,new_descr,new_user_id) testing;";
	db.execute(q);
	db.db.show("testing");
	
	q = "testing <- PROJECT (new_id,new_name) testing;";
	db.execute(q);
	db.db.show("testing");
	
	q = "testing <- test * testing;";
	db.execute(q);
	db.db.show("testing");
	
	
	return 0;
} 