#include "Weblog.h"

void main_menu();

void read_string(string &s){

	if(cin.peek() == '\n'){
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	getline(cin, s, '\n');
}

Weblog::Weblog(){
	
	if (p.db.isOnDisk("posts")){
		p.parse("OPEN posts;");
		updatePosts();
	}
	else{
		p.parse("CREATE TABLE posts (title VARCHAR(1000) , author VARCHAR(1000) , content VARCHAR(1400) , tags VARCHAR(1000) , date VARCHAR(1400) , id VARCHAR(1000), comment_on_off VARCHAR(1000) ) PRIMARY KEY (id) ;");
		p.parse("WRITE posts;");
	}
}

string Weblog::generateId(){
	
	string date;
	time_t raw = time(0);
	tm * ltm = localtime(&raw);
	string hashcode = "a";
	
	hashcode = hashcode + to_string(ltm->tm_mon);
	hashcode = hashcode + to_string(ltm->tm_mday);
	hashcode = hashcode + to_string(ltm->tm_year);
	hashcode = hashcode + to_string(ltm->tm_hour);
	hashcode = hashcode + to_string(ltm->tm_min);
	hashcode = hashcode + to_string(ltm->tm_sec);

	return hashcode;
}

string Weblog::getDate(){

	time_t t = time(0);   
    struct tm * now = localtime( & t );
    string year = to_string(now->tm_year + 1900);
    string month = to_string(now->tm_mon + 1);
    string day = to_string(now->tm_mday);
	
	return month + "/" + day + "/" + year;
}

void Weblog::makePost(){

	string author;
	string title;
	string date;
	string tags;
	string content;
	string comment_on_off;

	cout << "\nTitle: ";
	read_string(title);
	cout << "\nAuthor: ";
	read_string(author);
	cout << "\nContent: ";
	read_string(content);
	cout << "\nTags: ";
	read_string(tags);
	cout << "\nCommenting(Yes/no)? ";
	read_string(comment_on_off);
	
	//Set time
	date = getDate();
	string id = generateId();

	string input = "INSERT INTO posts VALUES FROM (\"" + title + "\", \"" + author + "\", \"" +
					 content + "\", \"" + tags + "\", \"" + date + "\", \"" + id + "\", \"" +  comment_on_off + "\") ;"; 
	send_to_parser(input);

	string command = "WRITE posts;";	
	send_to_parser(command);

	updatePosts();
}

void Weblog::updatePosts(){
	
	Relation buffer = p.db.getRelation("posts");

	//Must clear vector because update uses pushback
	records.clear();
	vector< vector<Entry> > temp_Records;
	Attribute title,authors, content, tags, date, ids, comment_on_off; 

	if (buffer.getAttribute("title").getNumEntries() > 0){

		title = buffer.getAttribute("title");
		authors = buffer.getAttribute("author");
		content = buffer.getAttribute("content");
		tags = buffer.getAttribute("tags");
		date = buffer.getAttribute("date");
		ids = buffer.getAttribute("id");
		comment_on_off = buffer.getAttribute("comment_on_off");

		for(int i = 0; i < buffer.getAttribute("title").getNumEntries(); i++){
			vector<Entry> temp;
			temp.push_back(title.getEntry(i));
			temp.push_back(authors.getEntry(i));
			temp.push_back(content.getEntry(i));
			temp.push_back(tags.getEntry(i));
			temp.push_back(date.getEntry(i));
			temp.push_back(ids.getEntry(i));
			temp.push_back(comment_on_off.getEntry(i));
			temp_Records.push_back(temp);
		}

		for(int i = 0 ; i < temp_Records.size(); i++) {
			
			string recTitle = temp_Records[i][0].getData();
			string recAuthor = temp_Records[i][1].getData();
			string recContent = temp_Records[i][2].getData();
			string recTags = temp_Records[i][3].getData();
			string recDate = temp_Records[i][4].getData();
			string recId = temp_Records[i][5].getData();
			string reccomment_on_off = temp_Records[i][6].getData();
			records.push_back(Post(recTitle,recAuthor,recContent,recTags,recDate, recId, reccomment_on_off));
		}
	}

}

//*************************************************************************************
//		Menu Interfaces

void Weblog::search_menu(){

	int choice; 
	while(choice != 5)
	{
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

			break;
		}
		else
		{
			cout<<"Invalid Input please choose between 1-5"<<endl;
		}
	}
}

void Weblog::main_menu(){

 	int choice; 
	
	while(choice != 3)
	{
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
			break;
		}
		else
		{
			cout<<"Invalid Input please choose between 1-5"<<endl;
		}
	}
	cout << "Goodbye.\n";
	exit(0);
}

void Weblog::func_menu(Post current){

	int choice; 
	while(choice != 5)
	{
		cout << "1. View\n";
		cout << "2. Edit\n";
		cout << "3. Delete\n";
		cout << "4. Comment\n";
		cout << "5. Return to Previous Menu\n\n";
		cout << "* Enter command: ";

		cin >> choice; 

		if(choice == 1){
			viewPost(current);			 
		}
		else if(choice == 2){
			edit_menu(current);
			
		}
		else if(choice == 3){
			deletePost(current);
			
		}
		else if(choice == 4){

			string data = current.getcomment_on_off();
			transform(data.begin(), data.end(), data.begin(), ::tolower);
			
			if(data == "yes"){
				makeComment(current);
			}
			else{
				cout << "Can't make comment!!!!\n\n";		
			}
		}
		else if(choice == 5){

			break;
		}
		else
		{
			cout<<"Invalid Input please choose between 1-5"<<endl;
		}
	}
}

void Weblog::edit_menu(Post current){

	int choice; 
	bool choose = true;
	while(choose)
	{
		cout << "1. by Author\n";
		cout << "2. by Title\n";
		cout << "3. by Content\n";
		cout << "4. by Tags\n\n";
		cout << "* Enter command: ";

		cin >> choice; 

		if(choice == 1){
			choose = false;
			editAuthor(current);
		}
		else if(choice == 2){
			choose = false;
			editTitle(current);
		}
		else if(choice == 3){
			choose = false;
			editContent(current);
		}
		else if(choice == 4){
			choose = false;
			editTags(current);
		}
	}
}

//**************************************************************************************

Post Weblog::getPost(string id){
	
	for(int i = 0 ; i < records.size(); i++){
		if(records[i].getId() == id){
			return records[i];
		}
	}
	//Error Handling should go here in case nothing is found.
}

void Weblog::viewComment(Post current){
	string id = current.getId();
	if(p.db.isOnDisk(id)){
		if(p.db.relationExists(id)){
			
			cout<<"----------------------------------------------------";
			cout<<"\nComments:\n";
			string command = "SHOW "+id +" ;";
			send_to_parser(command);
			cout<<"----------------------------------------------------\n";
		}
		else{
			cout<<"----------------------------------------------------";
			cout<<"\nComments:\n";
			string command = "OPEN "+id + " ;";
			send_to_parser(command);
			string command2 = "SHOW "+id +" ;";
			send_to_parser(command2);
			cout<<"----------------------------------------------------\n";
		}
	}
}

void Weblog::viewPost(Post current){
	current.view();
	viewComment(current);

}

void Weblog::makeComment(Post current){
	
	if(!(p.db.isOnDisk(current.getId())) ){
		
		string makeCommentTable = "CREATE TABLE "+ current.getId() +
				" (date VARCHAR(1000) , author VARCHAR(1000) , content VARCHAR(1400) , ids VARCHAR(1000) ) PRIMARY KEY (ids) ;";
		send_to_parser(makeCommentTable);
	}
	else{

		string command = "OPEN " + current.getId() + ";";
		send_to_parser(command);
	}
	
	string date = getDate();
	string author, comment, id;
	cout << "Enter your name: ";
	read_string(author);
	cout << "Enter your comment: ";
	read_string(comment);
	id = generateId();

	string insert = "INSERT INTO " + current.getId() + " VALUES FROM (\"" + date + 
					"\", \"" + author + "\", \"" + comment + "\", \"" + id + "\") ;"; 
	send_to_parser(insert);

	//Save Changes
	string write = "WRITE " + current.getId();
	send_to_parser(write);

}

//Edit DB functions
void Weblog::editTitle(Post current){
	
	string input;

	cout << "Enter the new title: ";
	read_string(input);

	
	string command = "UPDATE posts SET title = \"" + input + 
					"\" WHERE title == \"" + current.getTitle() + "\" ;";	
	send_to_parser(command);


	string command1 = "WRITE posts;";
	send_to_parser(command1);
	updatePosts();

	string command2 = "SHOW posts;";
	send_to_parser(command2);

}

void Weblog::editAuthor(Post current){
	
	string input;

	cout << "Enter the new Author: ";
	read_string(input);

	
	string command = "UPDATE posts SET author = \"" + input +
					 "\" WHERE (author == \"" + current.getAuthor() + "\" ) ;";
	send_to_parser(command);


	string command1 = "WRITE posts;";
	send_to_parser(command1);
	updatePosts();

	string command2 = "SHOW posts;";
	send_to_parser(command2);
}

void Weblog::editContent(Post current){
	
	string input;

	cout << "Enter the new Content: ";
	read_string(input);

	
	string command = "UPDATE posts SET content = \"" + input + 
					"\" WHERE id == \"" + current.getId() + "\" ;";
	send_to_parser(command);


	string command1 = "WRITE posts;";
	send_to_parser(command1);
	updatePosts();

	string command2 = "SHOW posts;";
	send_to_parser(command2);
}


void Weblog::editTags(Post current){
	
	string input;

	cout << "Enter the new Tags: ";
	read_string(input);

	
	string command = "UPDATE posts SET tags = \"" + input + 
					 "\" WHERE id == \"" + current.getId() + "\" ;";
	send_to_parser(command);


	string command1 = "WRITE posts;";
	send_to_parser(command1);
	updatePosts();

	string command2 = "SHOW posts;";
	send_to_parser(command2);
}

//This will also delete associated comments
void Weblog::deletePost(Post current){
	
	string deleteCommand = "DELETE FROM posts WHERE id == \"" + current.getId() + "\" ;";
	send_to_parser(deleteCommand);
	send_to_parser("WRITE posts;");
		
	p.db.removeRelationFromDisk(current.getId());
	updatePosts();

}

//****************************************************************
//Search functions
void Weblog::searchAuthor(){
	//Get user input
 
	string user;

	cout << "Enter the author: ";
	read_string(user);

	string command = "temp_author <- select (author == \"" + user + "\") posts;";
	send_to_parser(command);
	
	Relation buffer = p.db.getRelation("temp_author");
	vector< vector<Entry> > Records;

	Attribute title,authors, content, tags, date, ids; 

	if (buffer.getAttribute("author").getNumEntries() > 0){

		title = buffer.getAttribute("title");
		authors = buffer.getAttribute("author");
		content = buffer.getAttribute("content");
		tags = buffer.getAttribute("tags");
		date = buffer.getAttribute("date");
		ids = buffer.getAttribute("id");
		
		for(int i = 0; i < buffer.getAttribute("author").getNumEntries(); i++){
			
			vector<Entry> temp;
			temp.push_back(title.getEntry(i));
			temp.push_back(authors.getEntry(i));
			temp.push_back(content.getEntry(i));
			temp.push_back(tags.getEntry(i));
			temp.push_back(date.getEntry(i));
			temp.push_back(ids.getEntry(i));
			Records.push_back(temp);
		}

		for (int i =0; i < Records.size(); i++){
			
			//Display date and title
			cout << i << ": " << Records[i][0] << Records[i][4];
		}
	}
	
	if(Records.size() > 0){
		
		string choice;
		int index;
		cout<<"Enter the Record number: ";
		read_string(choice);
		index = stoi(choice);
		string desiredID = Records[index][5].getData();
		Post post = getPost(desiredID);
		func_menu(post);
	}
	else
	{
		cout << "No files found.\n";
	}
}

void Weblog::searchTitle(){


	string user;

	cout << "Enter the Title: ";
	read_string(user);

	string command = "temp_title <- select (title == \"" + user + "\") posts;";
	send_to_parser(command);
	
	Relation buffer = p.db.getRelation("temp_title");
	vector< vector<Entry> > Records;

	Attribute title,authors, content, tags, date, ids; 

	if (buffer.getAttribute("author").getNumEntries() > 0){

		title = buffer.getAttribute("title");
		authors = buffer.getAttribute("author");
		content = buffer.getAttribute("content");
		tags = buffer.getAttribute("tags");
		date = buffer.getAttribute("date");
		ids = buffer.getAttribute("id");
		for(int i = 0; i < buffer.getAttribute("author").getNumEntries(); i++){
			vector<Entry> temp;
			temp.push_back(title.getEntry(i));
			temp.push_back(authors.getEntry(i));
			temp.push_back(content.getEntry(i));
			temp.push_back(tags.getEntry(i));
			temp.push_back(date.getEntry(i));
			temp.push_back(ids.getEntry(i));
			Records.push_back(temp);
		}

		for (int i = 0; i < Records.size(); i++){
			
			//Display date and title
			cout << i << ": " << Records[i][0] << Records[i][1];
		}
	}

	if(Records.size() > 0){
		
		string choice;
		int index;
		
		//If multiple records are displayed this allows the user to select which one.
		cout<<"Enter the Record number: ";
		read_string(choice);
		index = stoi(choice);
		
		//The 5 is an unaviodable magic constant that corresponds to the id from parser.
		string desiredID = Records[index][5].getData();
		Post post = getPost(desiredID);
		func_menu(post);
	}
	else
	{
		cout<<"No files found.\n";
	}
}

void Weblog::searchTags(){

	string user;

	cout << "Enter the Tags: ";
	read_string(user);

	string command = "temp_tags <- select (tags == \"" + user + "\") posts;";
	send_to_parser(command);
	
	Relation buffer = p.db.getRelation("temp_tags");
	vector< vector<Entry> > Records;

	Attribute title,authors, content, tags, date, ids; 

	if (buffer.getAttribute("author").getNumEntries() > 0){

		title = buffer.getAttribute("title");
		authors = buffer.getAttribute("author");
		content = buffer.getAttribute("content");
		tags = buffer.getAttribute("tags");
		date = buffer.getAttribute("date");
		ids = buffer.getAttribute("id");
		for(int i = 0; i < buffer.getAttribute("author").getNumEntries(); i++){
			vector<Entry> temp;
			temp.push_back(title.getEntry(i));
			temp.push_back(authors.getEntry(i));
			temp.push_back(content.getEntry(i));
			temp.push_back(tags.getEntry(i));
			temp.push_back(date.getEntry(i));
			temp.push_back(ids.getEntry(i));
			Records.push_back(temp);
		}

		for (int i =0; i < Records.size(); i++){
			
			//Display date and title
			cout << i << ": " << Records[i][0] << Records[i][4];
		}
	}
	if(Records.size() > 0){

		string choice;
		int index;
		cout<<"Enter the Record number: ";
		read_string(choice);
		index = stoi(choice);
		string desiredID = Records[index][5].getData();
		Post post = getPost(desiredID);
		func_menu(post);
	}
	else
	{
		cout<<"No files found.\n";
	}
}

void Weblog::searchDate(){
	
	string user;

	cout << "Enter the Date(mm/dd/yyyy): ";
	read_string(user);

	string command = "temp_date <- select (date == \"" + user + "\") posts;";
	send_to_parser(command);
	
	Relation buffer = p.db.getRelation("temp_date");
	vector< vector<Entry> > Records;

	Attribute title,authors, content, tags, date, ids; 

	if (buffer.getAttribute("author").getNumEntries() > 0){

		title = buffer.getAttribute("title");
		authors = buffer.getAttribute("author");
		content = buffer.getAttribute("content");
		tags = buffer.getAttribute("tags");
		date = buffer.getAttribute("date");
		ids = buffer.getAttribute("id");
		
		for(int i = 0; i < buffer.getAttribute("author").getNumEntries(); i++){
			vector<Entry> temp;
			temp.push_back(title.getEntry(i));
			temp.push_back(authors.getEntry(i));
			temp.push_back(content.getEntry(i));
			temp.push_back(tags.getEntry(i));
			temp.push_back(date.getEntry(i));
			temp.push_back(ids.getEntry(i));
			Records.push_back(temp);
		}

		for (int i =0; i < Records.size(); i++){
			
			//Display date and title
			cout << i << ": " << Records[i][0] << Records[i][4];
		}
	}

	if(Records.size() > 0){
		
		string choice;
		int index;
		
		cout << "Enter the Record number: ";
		read_string(choice);
		
		index = stoi(choice);
		string desiredID = Records[index][5].getData();
		Post post = getPost(desiredID);
		func_menu(post);
	}
	else
	{
		cout<<"No files found.\n";
	}
}

void Weblog::send_to_parser(string command) {
	p.parse(command);
	
}

int main(int argc, char * argv[] ){
	
	Weblog app;

	app.main_menu();

	return 0;
}
