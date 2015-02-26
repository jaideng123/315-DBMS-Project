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
	string command;
	while(true){
		cout<<">";
		getline(cin,command);
		if (command == "EXIT;")
			break;
		else
			db.execute(command);
		cout<<endl;
	}
	
	
	return 0;
}