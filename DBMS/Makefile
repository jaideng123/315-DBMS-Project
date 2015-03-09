# a simple makefile for compiling C++ files

# optimization is on
CC = g++ -std=c++11 -g

test: DBMS.o Parser.o Database.o Table.o Tokenizer.o
	$(CC) Parser.o DBMS.o Database.o Table.o Tokenizer.o test.cpp -o test
test_debug: Parser.o Database.o Table.o Tokenizer.o
	$(CC) -DDEBUG DBMS.cpp Parser.o Database.o Table.o Tokenizer.o test.cpp -o test
shell: DBMS.o Parser.o Database.o Table.o Tokenizer.o
	$(CC) DBMS.o Parser.o Database.o Table.o Tokenizer.o shell.cpp -o shell
shell_debug: Parser.o Database.o Table.o Tokenizer.o
	$(CC) -DDEBUG DBMS.cpp Parser.o Database.o Table.o Tokenizer.o shell.cpp -o shell
#Merges all into 1 .o file
believe: DBMS.o Parser.o Database.o Table.o Tokenizer.o
	ld -r Parser.o DBMS.o Database.o Table.o Tokenizer.o -o DB.o
DBMS.o: DBMS.cpp
	$(CC) -c DBMS.cpp
Parser.o: Parser/Parser.cpp Parser/Tokenizer.cpp
	$(CC) -c Parser/Parser.cpp Parser/Tokenizer.cpp
Tokenizer.o: Parser/Tokenizer.cpp
	$(CC) -c Parser/Tokenizer.cpp
Database.o: Engine/Database.cpp
	$(CC) -c Engine/Database.cpp
Table.o: Engine/Table.cpp
	$(CC) -c Engine/Table.cpp
clean:
	rm *.o test shell