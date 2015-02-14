#include "Database.h"
#include <string>

using namespace std;

int test2(){
	Database db;
	string dbFilename = "Test Table";
	db.open(dbFilename);

	db.show("Test Table");
}