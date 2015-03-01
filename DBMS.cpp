#include "DBMS.h"

int DBMS::execute(string ex){
	#if DEBUG
		Parser p(&db);
		p.parse(ex);
		return 0;
	#else
	try{
		Parser p(&db);
		p.parse(ex);
		return 0;
	}
	catch(exception& e){
		cout<<e.what()<<endl;
		return 1;
	}
	#endif
}

Table DBMS::get_table(string table_name){
	return db.get_table(table_name);
}