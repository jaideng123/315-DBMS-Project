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
	vector<int> condition(Table t);
	vector<int> comparison(Table t);
	//helper functions
	vector<int> or_indices(vector<int> v1, vector<int> v2);
	vector<int> and_indices(vector<int> v1, vector<int> v2);
	int find_index(vector<Attribute> attrs, string id);
	vector<int> compare(Table t,string id,Token::Token_Type op,Token comp);
	void eat_condition();
	vector<string> grab_list();

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
