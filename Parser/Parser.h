#ifndef _parser_h_                   // include file only once
#define _parser_h_

#include "Tokenizer.h"
#include <vector>

class Parser{
public:
	Parser(){}

	void parse(string input){}//use test_parse till tokenizer is done
	void test_parse(vector<Token> tokens);

private:
	vector<Token> tokens;
	int current_token;

	void command();
	void query();
	void condition();

};

#endif