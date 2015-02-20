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

//i will call this when i need it, it will start pointing
//to the token after the left parentheses and should end
//pointing at the right parentheses
//***edit 2/18/2015: instead of pointing after leftparen, 
//***it points before leftparen when we get to condition()
//***edit 2/19/2015: fixed! now points correctly
void Parser::condition(){
	if(!is_next(Token::LEFTPAREN))
		throw runtime_error("Parsing Error");
	current_token++;
	int paren_count = 1;
	while(paren_count > 0){
		if(is_next(Token::RIGHTPAREN)){
			paren_count--;
		}
		else if(is_next(Token::LEFTPAREN)){
			paren_count++;
			current_token++;
		}
		else if(is_next(Token::IDENTIFIER)){
			comparison();
		}
		else
			throw runtime_error("Parsing Error");
	}
	current_token++;
}

void Parser::comparison(){
	//operand 1
	current_token++;
	//symbol
	if(is_next(Token::EQ))
		current_token++;
	else if(is_next(Token::LT))
		current_token++;
	else if(is_next(Token::LEQ))
		current_token++;
	else if(is_next(Token::GT))
		current_token++;
	else if(is_next(Token::GEQ))
		current_token++;
	else if(is_next(Token::NEQ))
		current_token++;
	else if(is_next(Token::LT))
		current_token++;
	else
		throw runtime_error("Parsing Error");
	//operand 2
	if(is_next(Token::NUMBER) || is_next(Token::INTEGER))
		current_token++;
	else if(is_next(Token::VARCHAR) &&(
				tokens[current_token].get_type() == Token::EQ ||
				tokens[current_token].get_type() == Token::NEQ))
		current_token++;
	else
		throw runtime_error("Parsing Error");
	//check for conjunction
	if(is_next(Token::AND))
		current_token++;
	else if(is_next(Token::OR))
		current_token++;
	
	
}

//parse query
void Parser::query(){

	if(!is_next(Token::LEFTARROW))
		throw runtime_error("Parsing Error");
	current_token++;
	expr();
	if(!is_next(Token::SEMICOLON))
		throw runtime_error("Parsing Error");
}

//determine type of expression
void Parser::expr(){
	if(is_next(Token::SELECT))
		select_expr();
		
	else if(is_next(Token::RENAME))
		rename_expr();
		
	else if(is_next(Token::PROJECT))
		project_expr();
		
	else if(is_next(Token::IDENTIFIER)){
		current_token++;
		if(is_next(Token::UNION))
			union_expr();
		else if(is_next(Token::DIFF))
			diff_expr();
		else if(is_next(Token::PRODUCT))
			prod_expr();
		else if(is_next(Token::SEMICOLON))
			return;
		else
			throw runtime_error("Parsing Error");
	}
	
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
	}
	
	else
		throw runtime_error("Parsing Error");
}

//for nested instructions
//takes atomic expression without ()
void Parser::atomic_expr(){
	if(is_next(Token::IDENTIFIER))
		current_token++;
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
	}
	else{
		expr();
	}
}

//for select expressions
void Parser::select_expr(){
	//select
	current_token++;
	//(condition)
	condition();
	//expr
	if(is_next(Token::IDENTIFIER))
		current_token++;
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		current_token++;
	}
	else
		throw runtime_error("Parsing Error");
	return;
}

//for rename expressions
void Parser::rename_expr(){
	//rename
	current_token++;
	//(attr_list)
	if(!is_next(Token::LEFTPAREN))
		throw runtime_error("Parsing Error");
	current_token++;
	while(!is_next(Token::RIGHTPAREN)){
		if(!is_next(Token::IDENTIFIER))
			throw runtime_error("Parsing Error");
		current_token++;
		if(!is_next(Token::COMMA))
			break;
		current_token++;
	}
	if(!is_next(Token::RIGHTPAREN))
		throw runtime_error("Parsing Error");
	current_token++;
	//expr
	if(is_next(Token::IDENTIFIER))
		current_token++;
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		current_token++;
	}
	else
		throw runtime_error("Parsing Error");
	return;
}

//for project expressions
void Parser::project_expr(){
	//project
	current_token++;
	//(attr_list)
	if(!is_next(Token::LEFTPAREN))
		throw runtime_error("Parsing Error");
	current_token++;
	while(!is_next(Token::RIGHTPAREN)){
		if(!is_next(Token::IDENTIFIER))
			throw runtime_error("Parsing Error");
		current_token++;
		if(!is_next(Token::COMMA))
			break;
		current_token++;
	}
	if(!is_next(Token::RIGHTPAREN))
		throw runtime_error("Parsing Error");
	current_token++;
	//expr
	if(is_next(Token::IDENTIFIER))
		current_token++;
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		current_token++;
	}
	else
		throw runtime_error("Parsing Error");
	return;
}

//for union expressions
void Parser::union_expr(){
	//identifier is current token here
	//+ 
	current_token++;
	//expr
	if(is_next(Token::IDENTIFIER))
		current_token++;
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		current_token++;
	}
	else
		throw runtime_error("Parsing Error");
	return;
}

//for difference expressions
void Parser::diff_expr(){
	//identifier is current token here
	//- 
	current_token++;
	//expr
	if(is_next(Token::IDENTIFIER))
		current_token++;
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		current_token++;
	}
	else
		throw runtime_error("Parsing Error");
	return;
}

//for product expressions
void Parser::prod_expr(){
	//identifier is current token here
	//- 
	current_token++;
	//expr
	if(is_next(Token::IDENTIFIER))
		current_token++;
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		current_token++;
	}
	else
		throw runtime_error("Parsing Error");
	return;
}
//HOLEE
//not done
void Parser::command(){

	if(is_next(Token::OPEN)){
		open_cmd();
	}
	else if(is_next(Token::CLOSE)){
		close_cmd();
	}
	else if(is_next(Token::WRITE)){
		write_cmd();
	}
	else if(is_next(Token::EXIT)){
		exit_cmd();
	}
	else if(is_next(Token::SHOW)){
		show_cmd();
	}
	else if(is_next(Token::CREATE)){
		create_cmd();
	}
	else if(is_next(Token::UPDATE)){
		update_cmd();
	}
	else if(is_next(Token::INSERT)){
		insert_cmd();
	}
	else if(is_next(Token::DELETE)){
		delete_cmd();
	}
	if(!is_next(Token::SEMICOLON))
		throw runtime_error("Parsing Error");
}

void Parser::open_cmd(){
	current_token++;
	if(is_next(Token::IDENTIFIER))
		current_token++;
	else
		throw runtime_error("Parsing Error");
}

void Parser::close_cmd(){
	current_token++;
	if(is_next(Token::IDENTIFIER))
		current_token++;
	else
		throw runtime_error("Parsing Error");
}

void Parser::write_cmd(){
	current_token++;
	if(is_next(Token::IDENTIFIER))
		current_token++;
	else
		throw runtime_error("Parsing Error");
}

void Parser::exit_cmd(){
	current_token++;
	if(is_next(Token::SEMICOLON))
		return;
	throw runtime_error("Parsing Error");
}

void Parser::show_cmd(){
	current_token++;
	if(is_next(Token::IDENTIFIER)){
		current_token++;
		if(is_next(Token::UNION))
			union_expr();
		else if(is_next(Token::DIFF))
			diff_expr();
		else if(is_next(Token::PRODUCT))
			prod_expr();
		else if(is_next(Token::SEMICOLON))
			return;
	}
	if(is_next(Token::SELECT))
		select_expr();
	else if(is_next(Token::RENAME))
		rename_expr();
	else if(is_next(Token::PROJECT))
		project_expr();
	return;
}

void Parser::create_cmd(){
	current_token++;

	if(!is_next(Token::TABLE))
		throw runtime_error("Parsing Error");
	current_token++;

	if(!is_next(Token::IDENTIFIER))
		throw runtime_error("Parsing Error");
	current_token++;
	//------------------------------(
	if(!is_next(Token::LEFTPAREN))
		throw runtime_error("Parsing Error");
	current_token++;
	while(!is_next(Token::RIGHTPAREN)){
		if(!is_next(Token::IDENTIFIER))
			throw runtime_error("Parsing Error");
		current_token++;

		if(is_next(Token::VARCHAR)){
			current_token++;
			if(!is_next(Token::LEFTPAREN))
				throw runtime_error("Parsing Error");
			current_token++;
			if(!is_next(Token::INTEGER))
				throw runtime_error("Parsing Error");
			current_token++;
			if(!is_next(Token::RIGHTPAREN))
				throw runtime_error("Parsing Error");
			current_token++;
		}
		else if(is_next(Token::INTEGER)){
			current_token++;
		}
		else
			throw runtime_error("Parsing Error");

		if(!is_next(Token::COMMA))
			break;
		current_token++;
	}
	current_token++;
	//-------------------------------)
	if(!is_next(Token::PRIMARY))
		throw runtime_error("Parsing Error");
	current_token++;
	if(!is_next(Token::KEY))
		throw runtime_error("Parsing Error");
	current_token++;
	//------------------------------(
	if(!is_next(Token::LEFTPAREN))
		throw runtime_error("Parsing Error");
	current_token++;
	while(!is_next(Token::RIGHTPAREN)){
		if(!is_next(Token::IDENTIFIER))
			throw runtime_error("Parsing Error");
		current_token++;
		if(!is_next(Token::COMMA))
			break;
		current_token++;
	}
	//-------------------------------)	
	current_token++;
}

void Parser::update_cmd(){
	current_token++;
	if(!is_next(Token::IDENTIFIER))
		throw runtime_error("Parsing Error");
	current_token++;
	if(!is_next(Token::SET))
		throw runtime_error("Parsing Error");
	current_token++;

	//---------------------------------------------need to do list of literals here too

	if(is_next(Token::WHERE)){
		current_token++;
		condition();
	}
	else
		throw runtime_error("Parsing Error");
	
	

}

void Parser::insert_cmd(){
	current_token++;
	if(!is_next(Token::INTO))
		throw runtime_error("Parsing Error");
	current_token++;
	if(!is_next(Token::IDENTIFIER))
		throw runtime_error("Parsing Error");
	current_token++;
	if(!is_next(Token::VALUES))
		throw runtime_error("Parsing Error");
	current_token++;
	if(!is_next(Token::FROM))
		throw runtime_error("Parsing Error");
	current_token++;
	if(is_next(Token::RELATION)){
		current_token++;
		expr();
	}//---------------------------------------DO AN ELSE HERE FOR LIST OF LITERALS ()
}

void Parser::delete_cmd(){
	current_token++;
	if(!is_next(Token::FROM))
		throw runtime_error("Parsing Error");
	current_token++;
	if(!is_next(Token::IDENTIFIER))
		throw runtime_error("Parsing Error");
	current_token++;
	if(is_next(Token::WHERE)){
		current_token++;
		condition();
	}
	else
		throw runtime_error("Parsing Error");
	

}
//determine what the next token will be
//will not go out of range
bool Parser::is_next(Token::Token_Type t){
	if(current_token + 1 >= tokens.size())
		return false;
	if(tokens[current_token+1].get_type() == t)
		return true;
	return false;	
}