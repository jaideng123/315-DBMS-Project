#ifndef _parser_h_                   // include file only once
#define _parser_h_

#include "Tokenizer.h"
#include <vector>

class Parser{
public:
	Parser(){}

	void parse(string input);

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

	void condition();
	void comparison();

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
