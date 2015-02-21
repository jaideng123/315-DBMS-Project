#ifndef _tokenizer_h_                   // include file only once
#define _tokenizer_h_

#include "Token.h"
#include <string>
#include <vector>
#include <cctype>
#include <iostream>

class Tokenizer{
public:
	Tokenizer(string line);s
	vector<Token> get_tokens(){
		tokens.clear();
		tokenize_input();
		return tokens;
	}
private:
	void tokenize_input();
	void is_reserve_word();	//Will pushback to vector if true
	void is_symbol();	
	void is_literal();
	void is_identifier();
	void is_number();
	void lookupANDstore(string reserveWord);
	vector<Token> tokens;
	string storedLine;
	string::iterator position;
};

#endif