#include "DBMS.h"

int DBMS::execute(string ex){
	//try{
		Parser p(&db);
		p.parse(ex);
		return 0;
	//}
	//catch(...){
	//	cout<<"Parsing error"<<endl;
	//	return 1;
	//}
}

Table DBMS::get_table(string table_name){
	return db.get_table(table_name);
}