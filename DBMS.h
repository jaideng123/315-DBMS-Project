#ifndef _DBMS_h_                   // include file only once
#define _DBMS_h_

#include "Engine/Database.h"
#include "Parser/Parser.h"
#include <string>

class DBMS{
public:
	DBMS(){}
	int execute(string ex);
	Table get_table(string table_name);
private:
	Database db;
};



#endif
