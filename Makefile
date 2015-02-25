# a simple makefile for compiling C++ files

# optimization is on
CC= g++-4.7 -std=c++11 -g

test: DBMS.o Parser.o Database.o Table.o Tokenizer.o
	g++ -std=c++11 -g Parser.o DBMS.o Database.o Table.o Tokenizer.o test.cpp -o test
test_debug: Parser.o Database.o Table.o Tokenizer.o
	g++ -std=c++11 -DDEBUG -g DBMS.cpp Parser.o Database.o Table.o Tokenizer.o test.cpp -o test
shell: DBMS.o Parser.o Database.o Table.o Tokenizer.o
	g++ -std=c++11 -g DBMS.o Parser.o Database.o Table.o Tokenizer.o shell.cpp -o shell
shell_debug: Parser.o Database.o Table.o Tokenizer.o
	g++ -std=c++11 -DDEBUG -g DBMS.cpp Parser.o Database.o Table.o Tokenizer.o shell.cpp -o shell
DBMS.o: DBMS.cpp
	g++ -std=c++11 -c DBMS.cpp
Parser.o: Parser/Parser.cpp Parser/Tokenizer.cpp
	g++ -std=c++11 -c Parser/Parser.cpp Parser/Tokenizer.cpp
Tokenizer.o: Parser/Tokenizer.cpp
	g++ -std=c++11 -c Parser/Tokenizer.cpp
Database.o: Engine/Database.cpp
	g++ -std=c++11 -c Engine/Database.cpp
Table.o: Engine/Table.cpp
	g++ -std=c++11 -c Engine/Table.cpp
clean:
	rm *.o test shell