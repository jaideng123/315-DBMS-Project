#ifndef _tokenizer_h_                   // include file only once
#define _tokenizer_h_

#include "Token.h"
#include <string>
#include <vector>
#include <cctype>
#include <iostream>

class Tokenizer{
public:
	Tokenizer(string line);

	vector<Token> get_tokens(){
		position = storedLine.begin();
		tokens.clear();
		tokenize_input();
		return tokens;
	}
	
private:
	void tokenize_input();
	void is_reserve_word();
	void is_symbol();	
	void is_literal();
	void is_identifier();
	void is_number();
	void lookup(string reserveWord);
	vector<Token> tokens;
	string storedLine;
	string::iterator position;
};

#endif