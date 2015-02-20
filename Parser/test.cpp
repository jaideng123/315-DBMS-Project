#include "Parser.h"
#include <iostream>

using namespace std;
void select_test(){
	vector<Token> test;
	//test <- select () (select () (select (age < 5 && (name == "Eric" || name != "Tristan")) test2));
	/*
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
	test.push_back(Token(Token::AND,"&&"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::IDENTIFIER,"name"));
	test.push_back(Token(Token::EQ,"=="));
	test.push_back(Token(Token::VARCHAR,"Eric"));
	test.push_back(Token(Token::OR,"||"));
	test.push_back(Token(Token::IDENTIFIER,"name"));
	test.push_back(Token(Token::NEQ,"!="));
	test.push_back(Token(Token::VARCHAR,"Tristan"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::IDENTIFIER,"test2"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::SEMICOLON,";"));*/
	Parser p;
	p.parse("test <- select () (select () (select (age < 5 && (name == \"Eric\" || name != \"Tristan\")) test2));");
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

void exit_test(){
	vector<Token> test;
	//ExitXIT;
	test.push_back(Token(Token::EXIT,"EXIT"));
	test.push_back(Token(Token::SEMICOLON,";"));
	Parser p;
	p.test_parse(test);
	cout<<"Exit Parsed Successfully!\n";
}

void open_test(){
	vector<Token> test;
	// OPEN testfile;
	test.push_back(Token(Token::OPEN,"OPEN"));
	test.push_back(Token(Token::IDENTIFIER,"testfile"));
	test.push_back(Token(Token::SEMICOLON,";"));

	Parser p;
	p.test_parse(test);
	cout<<"Open/Close/Write Parsed Successfully!\n";
}

void show_test(){
	vector<Token> test;
	// SHOW animals;
	test.push_back(Token(Token::SHOW,"SHOW"));
	test.push_back(Token(Token::IDENTIFIER,"animals"));
	test.push_back(Token(Token::SEMICOLON,";"));

	Parser p;
	p.test_parse(test);
	cout<<"Show Parsed Successfully!\n";
}


void delete_test(){
	vector<Token> test;
	// DELETE FROM testfile WHERE (sam != 0); 
	test.push_back(Token(Token::DELETE,"DELETE"));
	test.push_back(Token(Token::FROM,"FROM"));
	test.push_back(Token(Token::IDENTIFIER,"testfile"));
	test.push_back(Token(Token::WHERE,"WHERE"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::IDENTIFIER,"sam"));
	test.push_back(Token(Token::NEQ,"!="));
	test.push_back(Token(Token::INTEGER,"0"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::SEMICOLON,";"));

	Parser p;
	p.test_parse(test);
	cout<<"Delete Test Parsed Successfully!\n";
}


void create_test(){
	vector<Token> test;
	// CREATE TABLE testfile (name VARCHAR(5), age INTEGER) PRIMARY KEY (name);
	test.push_back(Token(Token::CREATE,"CREATE"));
	test.push_back(Token(Token::TABLE,"TABLE"));
	test.push_back(Token(Token::IDENTIFIER,"testfile"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::IDENTIFIER,"name"));
	test.push_back(Token(Token::VARCHAR,"VARCHAR"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::INTEGER,"5"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::COMMA,","));
	test.push_back(Token(Token::IDENTIFIER,"age"));
	test.push_back(Token(Token::INTEGER,"INTEGER"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::PRIMARY,"PRIMARY"));
	test.push_back(Token(Token::KEY,"KEY"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::IDENTIFIER,"name"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::SEMICOLON,";"));


	Parser p;
	p.test_parse(test);
	cout<<"Create Test Parsed Successfully!\n";
}

void update_test(){
	vector<Token> test;
	// UPDATE test SET name = john WHERE ( name = 5 );
	test.push_back(Token(Token::UPDATE,"UPDATE"));
	test.push_back(Token(Token::IDENTIFIER,"test"));
	test.push_back(Token(Token::SET,"SET"));
	test.push_back(Token(Token::IDENTIFIER,"name"));
	test.push_back(Token(Token::EQ,"="));
	test.push_back(Token(Token::LITERAL,"john"));
	test.push_back(Token(Token::WHERE,"WHERE"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::IDENTIFIER,"name"));
	test.push_back(Token(Token::EQ,"="));
	test.push_back(Token(Token::INTEGER,"5"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::SEMICOLON,";"));


	Parser p;
	p.test_parse(test);
	cout<<"Update Test Parsed Successfully!\n";
}

void insert_test(){
	vector<Token> test;
	// INSERT INTO name VALUES FROM RELATION rename (name, age) test2;
	test.push_back(Token(Token::INSERT,"INSERT"));
	test.push_back(Token(Token::INTO,"INTO"));
	test.push_back(Token(Token::IDENTIFIER,"name"));
	test.push_back(Token(Token::VALUES,"VALUES"));
	test.push_back(Token(Token::FROM,"FROM"));
	test.push_back(Token(Token::RELATION,"RELATION"));
	test.push_back(Token(Token::RENAME,"rename"));
	test.push_back(Token(Token::LEFTPAREN,"("));
	test.push_back(Token(Token::IDENTIFIER,"name"));
	test.push_back(Token(Token::COMMA,","));
	test.push_back(Token(Token::IDENTIFIER,"age"));
	test.push_back(Token(Token::RIGHTPAREN,")"));
	test.push_back(Token(Token::IDENTIFIER,"test2"));
	test.push_back(Token(Token::SEMICOLON,";"));

	vector<Token> test2;
	// INSERT INTO name VALUES FROM (name, age);
	test2.push_back(Token(Token::INSERT,"INSERT"));
	test2.push_back(Token(Token::INTO,"INTO"));
	test2.push_back(Token(Token::IDENTIFIER,"name"));
	test2.push_back(Token(Token::VALUES,"VALUES"));
	test2.push_back(Token(Token::FROM,"FROM"));
	test2.push_back(Token(Token::LEFTPAREN,"("));
	test2.push_back(Token(Token::LITERAL,"name"));
	test2.push_back(Token(Token::COMMA,","));
	test2.push_back(Token(Token::LITERAL,"age"));
	test2.push_back(Token(Token::RIGHTPAREN,")"));
	test2.push_back(Token(Token::SEMICOLON,";"));

	Parser p;
	p.test_parse(test);
	p.test_parse(test2);
	cout<<"Insert Test Parsed Successfully!\n";
}

int main(){
	// select_test();
	rename_test();
	project_test();
	union_test();
	diff_test();
	prod_test();

	exit_test();
	open_test();
	show_test();
	delete_test();
	create_test();
	update_test();
	insert_test();
	
	Tokenizer test("CLOSE something");
	test.tokenize_input();

	return 0;
}