#include "Parser.h"
#include <iostream>

using namespace std;

int main(){
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
	cout<<"Parsed Successfully!\n";
	return 0;
}