#ifndef _tokenizer_h_                   // include file only once
#define _tokenizer_h_

//Takes a string, contains a function that returns a vector of tokens
#include "Token.h"
#include <string>
#include <vector>
#include <cctype>
#include <iostream>

class Tokenizer{
public:
	Tokenizer(string line);

	void tokenize_input();
	void isReserveWord();	//Will pushback to vector if true
	void isSymbol();	
	void isLiteral();
	void isIdentifier();
	void isNumber();
	void lookupANDstore(string reserveWord);
	vector<Token> tokens;
private:
	string storedLine;
	string::iterator position;
};

#endif