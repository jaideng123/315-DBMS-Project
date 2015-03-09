#ifndef WEBLOG_H
#define WEBLOG_H

#include "Parser.h"
#include "Post.h"
#include <ctime>
#include <ctype.h>
#include <string>
#include <algorithm>

class Weblog{
public:
	Weblog(); 	
	
	//Update DB functions
	void makePost();
	void makeComment(Post current);
	Post getPost(string id);
	void updatePosts();
	
	//Helper Functions
	string generateId();	//generates an ID number
	string getDate(); 		//Uses system time
	void send_to_parser(string command);	
	void viewPost(Post current);
	void viewComment(Post current);
	
	//Edit DB functions
	void editTitle(Post current);			
	void editAuthor(Post current);
	void editContent(Post current);
	void editTags(Post current);

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
