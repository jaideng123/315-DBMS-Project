#ifndef WEBLOG_H
#define WEBLOG_H

//#include "Headers.h"
#include "Parser.h"
//#include "Database.h"


class Weblog{
public:
	Weblog(); 	//init - // Make post "CREATE TABLE posts () PRIMARY KEY ();"
	
	//Update DB functions
	void makePost();
	void makeComment();

	void send_to_parser(string command);

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

 	//This function should probably write a copy of the app to disk!
	void exitApp();

private:
	Parser p;

	//Menu Functions
	//void main_menu();
	//void post_menu();
	//void search_menu();

private: 
	Parser p;


};

#endif /* WEBLOG_H */
