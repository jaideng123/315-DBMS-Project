#include "Post.h"


Post::Post(string title1,string author1,string content1,string tags1, string date1, string hashcode1){
	title = title1;
	author = author1;
	content = content1;
	tags = tags1;
	date = date1;
	hashcode = hashcode1;
}

void Post::view(){
	cout<<title<<'\n'<<date<<'\t'<<author<<'\n'<<content<<'\n'<<tags<<'\n';
}