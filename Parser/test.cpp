#include "Parser.h"
#include <iostream>

using namespace std;
void select_test(){
	vector<Token> test;
	//test <- select () (select () (select () test2));
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
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::IDENTIFIER,"test2"));//
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::SEMICOLON,";"));
	Parser p;
	p.test_parse(test);
	cout<<"select Parsed Successfully!\n";
}
void rename_test(){
	vector<Token> test;
	//test <- rename (name,age) test;
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
	cout<<"rename Parsed Successfully!\n";
}

int main(){
	select_test();
	return 0;
}