#include "Post.h"

//constructor
Post::Post(string title1,string author1,string content1,string tags1, string date1, string hashcode1, string comment_on_off1){
	title = title1;
	author = author1;
	content = content1;
	tags = tags1;
	date = date1;
	hashcode = hashcode1;
	comment_on_off = comment_on_off1;

}

//view function to view the post
void Post::view(){
	cout<<"----------------------------------------------------\n"<<title<<'\n'<<"By: "<<
			'\t'<<author<<'\n'<<"Date: "<<date<<'\n'<<'\n'<<content<<'\n'<<'\n'<<"Tags:"<<
			'\t'<<tags<<'\n'<<"----------------------------------------------------\n";
}