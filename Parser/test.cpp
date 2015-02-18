#include "Parser.h"

using namespace std;

int main(){
	vector<Token> test;
	test.push_back(Token(Token::IDENTIFIER,"test"));
	test.push_back(Token(Token::LEFTARROW,"<-"));
	test.push_back(Token(Token::IDENTIFIER,"test2"));
	test.push_back(Token(Token::SEMICOLON,";"));
	Parser p;
	p.test_parse(test);
	return 0;
}