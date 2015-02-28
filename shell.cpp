#include "DBMS.h"
#include <iostream>

using namespace std;

int main(){
	DBMS db;
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