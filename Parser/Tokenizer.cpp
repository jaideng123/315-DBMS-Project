#include "Tokenizer.h"
#include <stdexcept>

Tokenizer::Tokenizer(string line){
	storedLine = line;
	position = storedLine.begin();
}

//process string into tokens
void Tokenizer::tokenize_input(){
	while(position != storedLine.end()){
		
		//skip whitespace - handles single space, tab, new line
		if((*position == ' ') || (*position == '\n') || (*position == '\t')){
			++position;
		}
		//check if alpaha
		else if(isalpha(*position)) {
			//Check if reserve word
			if(isupper(*(position)) && isupper(*(position+1))) {
				is_reserve_word();
			}
			else{
				is_identifier();
			}
		}
		//Look for literals
		else if(*position == '\"') {
			is_literal();
		}
		//look for symbols
		else if(ispunct(*position)) {
			is_symbol();
		}
		//look for digits
		else if(isdigit(*position)) {
			is_number();
		}
		else
			throw runtime_error("Tokenizing error:Symbol not recognized");
		
	}
}

void Tokenizer::is_number(){
	string::iterator current = position;
	string numbers;
	while ((current != storedLine.end()) && isdigit(*current)){
		numbers += *current;
		++current;
	}
	position += numbers.size();

	tokens.push_back(Token(Token::NUMBER, numbers));
}

//Will push_back to vector if true
void Tokenizer::is_reserve_word(){
	string::iterator current = position;
	string word;
	//Get complete word - Checks for whitespace and parentheses
	while ( (current != storedLine.end()) && (!(isspace(*current))) && 
			(*current != '(') && (*current != ')') && (*current != ';')&&
			(*current != ',')) {
		word += *current;
		++current;
	}
	
	//Update position to end of word
	position += word.size();

	lookup(word);
}	

void Tokenizer::is_symbol(){
	string::iterator current = position;
	string symbol;
	while ((current != storedLine.end()) && ispunct(*current)){
		symbol += *current;
		if(symbol == ")" || symbol == "(" || symbol == ";" || 
			symbol == "," || symbol == "\"")
			break;
		++current;
	}
	position += symbol.size();
	lookup(symbol);
}

//create and store literals
void Tokenizer::is_literal(){
	string::iterator current = position;
	string lit;
	if(*current == '\"'){
		++current;
		while ( (current != storedLine.end()) && *current != '\"'){
			lit += *current;
			++current;
		}
		position += lit.size()+2;

		tokens.push_back(Token(Token::LITERAL, lit));
	}
}

//create and store identifier
void Tokenizer::is_identifier(){
	string::iterator current = position;
	string ident;
	while ( (current != storedLine.end()) && ( ( isalpha(*current)) || 
		(*current == '_') || isdigit(*current) )  ){
		ident += *current;
		++current;
	}
	position += ident.size();

	tokens.push_back(Token(Token::IDENTIFIER, ident));
}

//lookup word and store int tokens vector
void Tokenizer::lookup(string reserveWord){
	if( reserveWord == "OPEN"){
		tokens.push_back(Token(Token::OPEN,""));
		return;
	}
	else if( reserveWord == "CLOSE"){
		tokens.push_back(Token(Token::CLOSE,""));
		return;
	}
	else if( reserveWord == "WRITE"){
		tokens.push_back(Token(Token::WRITE,""));
		return;
	}
	else if( reserveWord == "EXIT"){
		tokens.push_back(Token(Token::EXIT,""));
		return;
	}
	else if( reserveWord == "SHOW"){
		tokens.push_back(Token(Token::SHOW,""));
		return;
	}
	else if( reserveWord == "CREATE"){
		tokens.push_back(Token(Token::CREATE,""));
		return;
	}
	else if( reserveWord == "TABLE"){
		tokens.push_back(Token(Token::TABLE,""));
		return;
	}
	else if( reserveWord == "PRIMARY"){
		tokens.push_back(Token(Token::PRIMARY,""));
		return;
	}
	else if( reserveWord == "KEY"){
		tokens.push_back(Token(Token::KEY,""));
		return;
	}
	else if( reserveWord == "UPDATE"){
		tokens.push_back(Token(Token::UPDATE,""));
		return;
	}
	else if( reserveWord == "SET"){
		tokens.push_back(Token(Token::SET,""));
		return;
	}
	else if( reserveWord == "WHERE"){
		tokens.push_back(Token(Token::WHERE,""));
		return;
	}
	else if( reserveWord == "INSERT"){
		tokens.push_back(Token(Token::INSERT,""));
		return;
	}
	else if( reserveWord == "INTO"){
		tokens.push_back(Token(Token::INTO,""));
		return;
	}
	else if( reserveWord == "DELETE"){
		tokens.push_back(Token(Token::DELETE,""));
		return;
	}
	else if( reserveWord == "FROM"){
		tokens.push_back(Token(Token::FROM,""));
		return;
	}
	else if( reserveWord == "RELATION"){
		tokens.push_back(Token(Token::RELATION,""));
		return;
	}
	else if( reserveWord == "VARCHAR"){
		tokens.push_back(Token(Token::VARCHAR,""));
		return;
	}
	else if( reserveWord == "VALUES"){
		tokens.push_back(Token(Token::VALUES,""));
		return;
	}
	else if( reserveWord == "SELECT"){
		tokens.push_back(Token(Token::SELECT,""));
		return;
	}
	else if( reserveWord == "RENAME"){
		tokens.push_back(Token(Token::RENAME,""));
		return;
	}
	else if( reserveWord == "PROJECT"){
		tokens.push_back(Token(Token::PROJECT,""));
		return;
	}
	else if( reserveWord == "INTEGER"){
		tokens.push_back(Token(Token::INTEGER,""));
		return;
	}
	//*************************************
	//Symbol Section
	//*************************************
	else if( reserveWord == "+"){
		tokens.push_back(Token(Token::UNION,""));
		return;
	}
	else if( reserveWord == "-"){
		tokens.push_back(Token(Token::DIFF,""));
		return;
	}
	else if( reserveWord == "*"){
		tokens.push_back(Token(Token::PRODUCT,""));
		return;
	}
	else if( reserveWord == "("){
		tokens.push_back(Token(Token::LEFTPAREN,""));
		return;
	}
	else if( reserveWord == ")"){
		tokens.push_back(Token(Token::RIGHTPAREN,""));
		return;
	}
	else if( reserveWord == "<-"){
		tokens.push_back(Token(Token::LEFTARROW,""));
		return;
	}
	else if( reserveWord == "="){
		tokens.push_back(Token(Token::EQUALSIGN,""));
		return;
	}
	else if( reserveWord == "=="){
		tokens.push_back(Token(Token::EQ,""));
		return;
	}
	else if( reserveWord == "<"){
		tokens.push_back(Token(Token::LT,""));
		return;
	}
	else if( reserveWord == "<="){
		tokens.push_back(Token(Token::LEQ,""));
		return;
	}
	else if( reserveWord == ">"){
		tokens.push_back(Token(Token::GT,""));
		return;
	}
	else if( reserveWord == ">="){
		tokens.push_back(Token(Token::GEQ,""));
		return;
	}
	else if( reserveWord == "!="){
		tokens.push_back(Token(Token::NEQ,""));
		return;
	}
	else if( reserveWord == "&&"){
		tokens.push_back(Token(Token::AND,""));
		return;
	}
	else if( reserveWord == "||"){
		tokens.push_back(Token(Token::OR,""));
		return;
	}
	else if( reserveWord == ","){
		tokens.push_back(Token(Token::COMMA,""));
		return;
	}
	else if( reserveWord == ";"){
		tokens.push_back(Token(Token::SEMICOLON,""));
		return;
	}
	else
		throw runtime_error("Tokenizing error");
}

