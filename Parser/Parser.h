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
	bool is_next(Token::Token_Type);

	void command();
	void query();
	void select_expr(){}
	void rename_expr(){}
	void project_expr(){}
	void union_expr(){}
	void diff_expr(){}
	void prod_expr(){}
	void atomic_expr(){}

	void condition();

};

#endif