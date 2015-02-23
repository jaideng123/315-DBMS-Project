#ifndef _parser_h_                   // include file only once
#define _parser_h_

#include "Tokenizer.h"
#include "../Engine/Database.h"
#include <vector>

class Parser{
public:
	Parser(Database* database){db = database;}

	void parse(string input);

private:
	Database* db;
	vector<Token> tokens;
	int current_token;
	bool is_next(Token::Token_Type);

	void command();
	//these will return tables
	void query();
	void expr();
	void atomic_expr();
	void select_expr();
	void rename_expr();
	void project_expr();
	void union_expr();
	void diff_expr();
	void prod_expr();

	//these will return vector<int>
	void condition();
	void comparison();

	//these will stay void
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
