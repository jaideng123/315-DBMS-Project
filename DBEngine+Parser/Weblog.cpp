#include "Weblog.h"

void read_string(string &s){

	if(cin.peek() == '\n'){
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	getline(cin, s, '\n');
}

Weblog::Weblog(){

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

//Search functions
void Weblog::searchAuthor(){


}
void Weblog::searchTitle(){

}
void Weblog::searchTags(){

}
void Weblog::searchDate(){

}

//This function should probably write a copy of the app to disk!
void Weblog::exitApp(){

}

void Weblog::send_to_parser(string command){
	p.parse(command);
}


