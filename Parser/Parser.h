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
	void expr();
	void atomic_expr();
	void select_expr();
	void rename_expr();
	void project_expr();
	void union_expr();
	void diff_expr();
	void prod_expr();

<<<<<<< HEAD
	void condition();
	
=======
	void condition();
	void comparison();
>>>>>>> 1ec87efb032cf3af4aba9717bff9e4112d7a4eac
	void open_cmd();
	void close_cmd();
	void write_cmd();
	void exit_cmd();
	void show_cmd();
	void create_cmd();
	void update_cmd();
	void insert_cmd();
	void delete_cmd();

};

#endif