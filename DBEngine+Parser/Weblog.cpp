#include "Weblog.h"

void read_string(string &s){

	if(cin.peek() == '\n'){
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	getline(cin, s, '\n');
}

Weblog::Weblog(){
	p.parse("CREATE TABLE posts(title VARCHAR(30) , author VARCHAR(30) , content VARCHAR(140) , tags VARCHAR(100) , date VARCHAR (14) ) PRIMARY KEY (title , author) ;");
	p.parse("SHOW posts;");
}

//Update DB functions
void Weblog::makePost(){

	string author;
	string title;
	string date;
	string tags;
	string content;

	cout << "\nTitle: ";
	read_string(title);
	cout << "Author: ";
	read_string(author);
	cout << "\nContent: ";
	read_string(content);
	cout << "\nTags: ";
	read_string(tags);
	cout << "\nDate(mm/dd/yyyy): ";
	read_string(date);

	string input = "INSERT INTO posts VALUES FROM (" + title + author + content + tags + date + ");"; 

	send_to_parser(input);

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
