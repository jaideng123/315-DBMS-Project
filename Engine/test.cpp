#include "Database.h"
#include <string>

using namespace std;

int main(){
	Database db();
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
	test.print();

	return 0;
}