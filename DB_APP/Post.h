#include <string>
#include <iostream>

using namespace std;

class Post{
private:
	//data memebers: private
	string title,author,content,tags,date, comment_on_off;
	string hashcode;
public:
	Post(string title1,string author1,string content1,string tags1, string date1, string hashcode1, string comment_on_off);
	void view();

	//return the command to feed to parser
	string editTitle();	
	string editAuthor();
	string editContent();
	string editTags();

	//member functions to access private members 
	string getTitle(){return title;};
	string getAuthor(){return author;};
	string getContent(){return content;};
	string getTags(){return tags;};
	string getDate(){return date;};
	string getId(){return hashcode;};
	string getcomment_on_off() { return comment_on_off; };

};