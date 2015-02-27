#include "DBMS.h"
#include <iostream>

using namespace std;

 int main(){
	DBMS db;
	db.execute("CREATE TABLE test (id INTEGER,name VARCHAR(20),description VARCHAR(50),user_id INTEGER) PRIMARY KEY (name);");

	for (int i = 0; i < 20; ++i){
		Record r;
		//c++ 11 features
		string pid = to_string(i);
		string uid = to_string(i*20);
		string q = "INSERT INTO test VALUES FROM ("+ pid+",\"Dummy String\",\"Dummy Text\","+uid+");";
		db.execute(q);
	}
	db.execute("SHOW test;");
	db.execute("WRITE test;");
	db.execute("CLOSE test;");
	db.execute("OPEN test;");
	db.execute("SHOW test;");
/* 
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
	
	q = "testing <- SELECT (id == new_id) (test * testing);";
	db.execute(q);
	db.db.show("testing");
	 */
	return 0;
} 