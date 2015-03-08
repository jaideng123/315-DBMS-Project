#ifndef WEBLOG_H
#define WEBLOG_H

//#include "Headers.h"
#include "Parser.h"
#include "Post.h"
#include <ctime>
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
	void makeComment(Post current);

	Post getPost(string id);
	void updatePosts();
	//NOTE - DOES NOT RETURN THE ID MAKES NEW ONE!!!!!!!!!
	string generateId();	//generates an ID number
	
	string getDate();
	void send_to_parser(string command);
		
	//Edit DB functions
	void editTitle(Post current);			//
	void editAuthor(Post current);
	void editContent(Post current);
	void editTags(Post current);

	void toggleComments();

	//This will also delete associated comments
	void deletePost(Post current);

	//Search functions
	void searchAuthor();
	void searchTitle();
	void searchTags();
	void searchDate();


	//Menu Functions
	void main_menu();
	void search_menu();
	void func_menu(Post current);
	void edit_menu(Post current);


	
private:
	Parser p;

	vector< Post > records;
	

};

#endif /* WEBLOG_H */
