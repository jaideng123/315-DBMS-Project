#include <string>
#include <iostream>

using namespace std;

class Post{
private:
	string title,author,content,tags,date;
	string hashcode;
public:
	Post(string title1,string author1,string content1,string tags1, string date1, string hashcode1);
	void view();
	string editTitle();	//return the command to feed to parser
	string editAuthor();
	string editContent();
	string editTags();

	string getTitle(){return title;};
	string getAuthor(){return author;};
	string getContent(){return content;};
	string getTags(){return tags;};
	string getDate(){return date;};
	string getId(){return hashcode;};
};