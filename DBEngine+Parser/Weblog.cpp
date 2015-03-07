#include "Weblog.h"

void main_menu();

void read_string(string &s){

	if(cin.peek() == '\n'){
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	getline(cin, s, '\n');
}

Weblog::Weblog(){
	// vector <string> relations = getAllFilesInFolder("Relations.db");
	// if (!this->isOnDisk("posts", relations)){
	// 	cout<<"I am here";
	// 	p.parse("CREATE TABLE posts (title VARCHAR(30) , author VARCHAR(30) , content VARCHAR(140) , tags VARCHAR(100) , date VARCHAR (14) ) PRIMARY KEY (title , author) ;");
	// 	p.parse("WRITE posts;");
	// }
	p.parse("OPEN posts;");
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
	cout << "\nAuthor: ";
	read_string(author);
	cout << "\nContent: ";
	read_string(content);
	cout << "\nTags: ";
	read_string(tags);
	cout << "\nDate(mm/dd/yyyy): ";
	read_string(date);

	string input = "INSERT INTO posts VALUES FROM (\"" + title + "\", \"" + author + "\", \"" + content + "\", \"" + tags + "\", \"" + date + "\");"; 
	send_to_parser(input);

	string command = "WRITE posts;";
	send_to_parser(command);

	string command1 = "SHOW posts;";
	send_to_parser(command1);
}

void Weblog::search_menu(){

	int choice; 

	cout << "\n[Search Menu]\n\n";
	cout << "Search by:\n";
	cout << "1. Author\n";
	cout << "2. Title\n";
	cout << "3. Tag(s)\n";
	cout << "4. Date\n"; 
	cout << "5. Return to Main Menu\n\n";
	cout << "* Enter command: ";
	
	cin >> choice;

	if(choice == 1){

		searchAuthor();
	}
	else if(choice == 2){

		searchTitle();
	}
	else if(choice == 3){

		searchTags();
	}
	else if(choice == 4){

		searchDate();
	}
	else if(choice == 5){

		main_menu();
	}
}

void Weblog::main_menu(){

 	int choice; 
	
	cout << "[Main Menu]\n\n";
	cout << "1. Make a new post\n";
	cout << "2. Search a post\n";
	cout << "3. Exit\n\n";
	cout << "* Enter command: ";

	cin >> choice; 

	if(choice == 1){
		makePost();
	}
	else if(choice == 2){
		search_menu();
	}
	else if(choice == 3){
		cout << "Goodbye.\n";
		exit(0);
	}
}

void Weblog::func_menu(){

	int choice; 

	cout << "1. View";
	cout << "2. Edit";
	cout << "3. Delete";
	cout << "4. Comment";
	cout << "5. Return to Main Menu";

	cin >> choice; 

	if(choice == 1){

		 
	}
	else if(choice == 2){

		
	}
	else if(choice == 3){

		
	}
	else if(choice == 4){

		int comm_choice;

		cout << "1. Comment on post";
		cout << "2. Comment on comment";
		cin >> comm_choice;

		if(choice == 1){

		}
		else if(choice == 2){

		}
		
	}
	else if(choice == 5){

		main_menu();
	}
}


void Weblog::view(){

	// string command = "SHOW posts";
	// send_to_parser(command);
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

	cout << "Enter the author: ";
	read_string(user);
	//
	string command = "temp_author <- select (author == \"" + user + "\") posts;";
	//cout <<command;
	send_to_parser(command);
	Relation buffer = p.db.getRelation("temp_author");
	vector< <vector<Entry>> records;
	
	//vector<Entry> v = ;

}
void Weblog::searchTitle(){


	string user;
	cout << "Enter the title: ";
	read_string(user);
	//
	string command = "temp_title <- select (title == \"" + user + "\") posts;";

	send_to_parser(command);
}
void Weblog::searchTags(){

	string user;
	cout << "Enter the tags: ";
	read_string(user);
	//
	string command = "temp_tags <- select (author == \"" + user + "\") posts;";
	send_to_parser(command);
}
void Weblog::searchDate(){
	
	string user;
	cout << "Enter the date: ";
	read_string(user);
	//
	string command = "temp_date <- select (author == \"" + user + "\") posts;";
	send_to_parser(command);
}

//This function should probably write a copy of the app to disk!
// void Weblog::exitApp(){

// 	string command = "WRITE posts";
// 	send_to_parser(command);
// }

void Weblog::send_to_parser(string command) {
	p.parse(command);
	
}

string Weblog::getOutput(string command){
	//int child = fork();
	//if(child)
}

vector<string> Weblog::getAllFilesInFolder(string fileName){
	//returns all the names of the files of relations on the disk
	vector<string> files;
	string relationName;
	ifstream relationFile(fileName);
	if (relationFile.is_open()){
		while (getline(relationFile, relationName)){
			files.push_back(relationName);
		}
		relationFile.close();
	}
	else{
		//cout << "Error in getAllFilesInFolder() :: \"Relations.db\" is not in the current folder." << endl;
		//cout << "You may Create relations but there are no relations to read." << endl;
	}

	return files;
}

bool Weblog::isOnDisk(string rName, vector<string> relationsOnDisk){
	//Checks if the relation is already on the disk
	//returns true if it is already on disk false otherwise
	for (int i = 0; i < relationsOnDisk.size(); ++i){
		if (relationsOnDisk[i] == rName){
			return true;
		}
	}
	return false;
}

void Weblog::setViewBuffer(){
	//string buffer = 
}


int main(int argc, char * argv[] ){
	Weblog app;

	app.main_menu();

	//app.makePost();
	//app.exitApp();
	//app.view();
	

	return 0;
}
