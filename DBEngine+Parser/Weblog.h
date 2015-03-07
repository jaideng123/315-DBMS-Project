#ifndef WEBLOG_H
#define WEBLOG_H

//#include "Headers.h"
#include "Parser.h"

// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <iostream>



class Weblog{
public:
	Weblog(); 	//init - // Make post "CREATE TABLE posts () PRIMARY KEY ();"
	
	//Update DB functions
	void makePost();
	void makeComment();

	void send_to_parser(string command);
	void view();
	string getOutput(string command);

	//Edit DB functions
	void editTitle();			//
	void editAuthor();
	void editContent();
	void editTags();

	void toggleComments();

	//This will also delete associated comments
	void deletePost();

	//Search functions
	void searchAuthor();
	void searchTitle();
	void searchTags();
	void searchDate();

	//Helper Functions
	void setViewBuffer();

	void main_menu();
	void search_menu();
	void func_menu();

 	//This function should probably write a copy of the app to disk!
	void exitApp();

	bool isOnDisk(string rName, vector<string> relationsOnDisk);
	vector<string> getAllFilesInFolder(string fileName);

private:
	Parser p;
	vector <vector<string> > viewBuffer;

	//Menu Functions
	//void main_menu();
	//void post_menu();
	//void search_menu();


};

#endif /* WEBLOG_H */
