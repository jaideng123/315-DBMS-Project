#include "Parser.h"
#include <iostream>

using namespace std;
void select_test(){
	vector<Token> test;
	//test <- select () (select () (select (age < 5) test2));
	test.push_back(Token(Token::IDENTIFIER,"test"));
	test.push_back(Token(Token::LEFTARROW,"<-"));
	test.push_back(Token(Token::SELECT,"select"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::SELECT,"select"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::SELECT,"select"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::IDENTIFIER,"age"));
	test.push_back(Token(Token::LT,"<"));
	test.push_back(Token(Token::INTEGER,"5"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::IDENTIFIER,"test2"));//
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::SEMICOLON,";"));
	Parser p;
	p.test_parse(test);
	cout<<"Select Parsed Successfully!\n";
}
void rename_test(){
	vector<Token> test;
	//test <- rename (name,age) test2;
	test.push_back(Token(Token::IDENTIFIER,"test"));
	test.push_back(Token(Token::LEFTARROW,"<-"));
	test.push_back(Token(Token::RENAME,"rename"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::IDENTIFIER,"name"));
	test.push_back(Token(Token::COMMA,","));
	test.push_back(Token(Token::IDENTIFIER,"age"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::IDENTIFIER,"test2"));
	test.push_back(Token(Token::SEMICOLON,";"));
	Parser p;
	p.test_parse(test);
	cout<<"Rename Parsed Successfully!\n";
}

void project_test(){
	vector<Token> test;
	//test <- project (name,age) test2;
	test.push_back(Token(Token::IDENTIFIER,"test"));
	test.push_back(Token(Token::LEFTARROW,"<-"));
	test.push_back(Token(Token::PROJECT,"project"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::IDENTIFIER,"name"));
	test.push_back(Token(Token::COMMA,","));
	test.push_back(Token(Token::IDENTIFIER,"age"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::IDENTIFIER,"test2"));
	test.push_back(Token(Token::SEMICOLON,";"));
	Parser p;
	p.test_parse(test);
	cout<<"Project Parsed Successfully!\n";
}

void union_test(){
	vector<Token> test;
	//test <- test2 + test3;
	test.push_back(Token(Token::IDENTIFIER,"test"));
	test.push_back(Token(Token::LEFTARROW,"<-"));
	test.push_back(Token(Token::IDENTIFIER,"test2"));
	test.push_back(Token(Token::UNION,"+"));
	test.push_back(Token(Token::IDENTIFIER,"test3"));
	test.push_back(Token(Token::SEMICOLON,";"));
	Parser p;
	p.test_parse(test);
	cout<<"Union Parsed Successfully!\n";
}

void diff_test(){
	vector<Token> test;
	//test <- test2 - test3;
	test.push_back(Token(Token::IDENTIFIER,"test"));
	test.push_back(Token(Token::LEFTARROW,"<-"));
	test.push_back(Token(Token::IDENTIFIER,"test2"));
	test.push_back(Token(Token::DIFF,"-"));
	test.push_back(Token(Token::IDENTIFIER,"test3"));
	test.push_back(Token(Token::SEMICOLON,";"));
	Parser p;
	p.test_parse(test);
	cout<<"Diff Parsed Successfully!\n";
}

void prod_test(){
	vector<Token> test;
	//test <- test2 * test3;
	test.push_back(Token(Token::IDENTIFIER,"test"));
	test.push_back(Token(Token::LEFTARROW,"<-"));
	test.push_back(Token(Token::IDENTIFIER,"test2"));
	test.push_back(Token(Token::PRODUCT,"*"));
	test.push_back(Token(Token::IDENTIFIER,"test3"));
	test.push_back(Token(Token::SEMICOLON,";"));
	Parser p;
	p.test_parse(test);
	cout<<"Product Parsed Successfully!\n";
}


int main(){
	select_test();
	rename_test();
	project_test();
	union_test();
	diff_test();
	prod_test();
	return 0;
}