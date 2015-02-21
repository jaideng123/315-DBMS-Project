#include "Parser.h"
#include <iostream>

using namespace std;
void select_test(){
	Parser p;
	p.parse("test <- SELECT () (SELECT () (SELECT (age < 5 && (name == \"Eric\" || name != \"Tristan\")) test2));");
	cout<<"Select Parsed Successfully!\n";
}
void rename_test(){
	Parser p;
	p.parse("test <- RENAME (name,age) test2;");
	cout<<"Rename Parsed Successfully!\n";
}

void project_test(){
	Parser p;
	p.parse("test <- PROJECT (name,age) test2;");
	cout<<"Project Parsed Successfully!\n";
}

void union_test(){
	Parser p;
	p.parse("test <- test2 + test3;");
	cout<<"Union Parsed Successfully!\n";
}

void diff_test(){
	Parser p;
	p.parse("test <- test2 - test3;");
	cout<<"Diff Parsed Successfully!\n";
}

void prod_test(){
	Parser p;
	p.parse("test <- test2 * test3;");
	cout<<"Product Parsed Successfully!\n";
}

void exit_test(){
	Parser p;
	p.parse("EXIT;");
	cout<<"Exit Parsed Successfully!\n";
}

void open_test(){
	Parser p;
	p.parse("OPEN testfile;");
	cout<<"Open/Close/Write Parsed Successfully!\n";
}

void show_test(){
	Parser p;
	p.parse("SHOW animals;");
	cout<<"Show Parsed Successfully!\n";
}


void delete_test(){
	Parser p;
	p.parse("DELETE FROM testfile WHERE (sam != 0);");
	cout<<"Delete Test Parsed Successfully!\n";
}


void create_test(){
	Parser p;
	p.parse("CREATE TABLE testfile (name VARCHAR(5), age INTEGER) PRIMARY KEY (name);");
	cout<<"Create Test Parsed Successfully!\n";
}

void update_test(){
	Parser p;
	p.parse("UPDATE test SET name = \"John\" WHERE ( name == 5 );");
	cout<<"Update Test Parsed Successfully!\n";
}

void insert_test(){
	Parser p;
	p.parse("INSERT INTO name VALUES FROM RELATION RENAME (name, age) test2;");
	p.parse("INSERT INTO name VALUES FROM (\"name\", \"age\");");
	//p.test_parse(test2);
	cout<<"Insert Test Parsed Successfully!\n";
}

int main(){
	select_test();
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

	return 0;
}