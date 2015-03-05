#include "Weblog.h"

Weblog::Weblog(){
	p.parse("CREATE TABLE posts(title VARCHAR(30) , author VARCHAR(30) , content VARCHAR(140) , tags VARCHAR(100) , date VARCHAR (14) ) PRIMARY KEY (title , author) ;");
	p.parse("SHOW posts;");
}

//Update DB functions
void Weblog::makePost(){

}

void Weblog::makeComment(){

}

//Edit DB functions
void Weblog::editTitle(){
	//interface

	//Get user input

	//create string

	//"UPDATE posts SET title = "userinput" WHERE title==""
}
void Weblog::editAuthor(){

}
void Weblog::editContent(){

}
void Weblog::editTags(){

}

void Weblog::toggleComments(){

}

//This will also delete associated comments
void Weblog::deletePost(){

}



//****************************************************************
//Search functions
void Weblog::searchAuthor(){
	//Get user input
 
	//temporary substitute for string of user input
	string user;

	//
	string command = "temp_author <- select (author == \" " + user + "\" posts";

	send_to_parser(command);
}
void Weblog::searchTitle(){


	string user;

	//
	string command = "temp_title <- select (title == \" " + user + "\" posts";

	send_to_parser(command);
}
void Weblog::searchTags(){

	string user;

	//
	string command = "temp_tags <- select (author == \" " + user + "\" posts";
	send_to_parser(command);
}
void Weblog::searchDate(){
	string user;

	//
	string command = "temp_date <- select (author == \" " + user + "\" posts";
	send_to_parser(command);
}

//This function should probably write a copy of the app to disk!
void Weblog::exitApp(){

}

void Weblog::send_to_parser(string command){
	p.parse(command);
}



int main(){
	Weblog app;
	

	return 0;
}