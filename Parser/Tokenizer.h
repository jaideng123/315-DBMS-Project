#ifndef _tokenizer_h_                   // include file only once
#define _tokenizer_h_

//Takes a string, contains a function that returns a vector of tokens
#include "Token.h"
#include <string>
#include <vector>
#include <cctype>

class Tokenizer{
public:
	Tokenizer(string line);
	void tokenizeInput(string line, string::iterator position);
	void isReserveWord(string line, string::iterator &position);	//Will pushback to vector if true
	void isSymbol(string line, string::iterator &position);	
	void isLiteral(string line,string::iterator &position);
	void lookupANDstore(string reserveWord);
private:
	vector<Token> tokens;
};

#endif