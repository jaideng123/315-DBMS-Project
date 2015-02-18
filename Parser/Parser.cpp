#include "Parser.h"
#include <stdexcept>

using namespace std;

void Parser::test_parse(vector<Token> input_tokens){
	tokens = input_tokens;
	current_token = 0;
	if(tokens[current_token].get_type() == Token::IDENTIFIER){
		query();
	}
	else{
		command();
	}

}

void Parser::condition(){
	
}

void Parser::query(){
	if(!is_next(Token::LEFTARROW))
		throw runtime_error("Parsing Error");
	current_token++;
	if(is_next(Token::SELECT))
		select_expr();
	else if(is_next(Token::RENAME))
		rename_expr();
	else if(is_next(Token::PROJECT))
		project_expr();
	else if(is_next(Token::IDENTIFIER))
		atomic_expr();
	else
		throw runtime_error("Parsing Error");
}

void Parser::command(){

}

bool Parser::is_next(Token::Token_Type t){
	if(current_token + 1 >= tokens.size())
		return false;
	if(tokens[current_token+1].get_type() == t)
		return true;
	return false;	
}