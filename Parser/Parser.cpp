#include "Parser.h"

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

}

void Parser::command(){

}