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
	Table query();
	Table expr();
	Table atomic_expr();
	Table select_expr();
	Table rename_expr();
	Table project_expr();
	Table union_expr(Table t1);
	Table diff_expr(Table t1);
	Table prod_expr(Table t1);

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
