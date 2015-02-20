#include "Tokenizer.h"

Tokenizer::Tokenizer(string line){
	storedLine = line;
	position = storedLine.begin();
}

void Tokenizer::tokenizeInput(){
	while(position != storedLine.end()){
		
		//process whitespace - handles single space, tab, new line
		if((*position == ' ') || (*position == '\n') || (*position == '\t')){
			++position;
		}
		//check if alpaha
		else if(isalpha(*position)) {
			//Check if reserve word
			if(isupper(*position)) {
				isReserveWord();
			}
			else if(islower(*position)) {
				
				isIdentifier();
			}
		}
		//Look for literals
		else if(*position == '"') {
			isLiteral();
		}
		else if(ispunct(*position)) {
			isSymbol();
		}
		else if(isdigit(*position)) {
			isNumber();
		}
		
		
	}
}

void Tokenizer::isNumber(){
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
void Tokenizer::isReserveWord(){
	string::iterator current = position;
	string word;
	//Get complete word - Checks for whitespace and parenthesis
	while ( (current != storedLine.end()) && (!(isspace(*current))) && (*current != '(') && (*current != ')')) {
		word += *current;
		++current;
	}
	
	/*
		Omit because Tristian said so. All glory to the hypnotoad

	//Grabs the Second part of reserve word sperarted by space
	if((word == "CREATE") || (word == "INSERT") || (word == "DELETE") || (word == "VALUES") || (word == "PRIMARY") ){
		//Skip only a single space between two part Reserve word
		if(*current == ' '){
			current++;
			word += *current;
		
			//Grabs second part of full word
			while( (!(isspace(*current ))) || (*current != '(') || (*current != ')') ) {
				word += *current
				current++;
			}
		}
	}
	*/
	//Update position to end of word
	position += word.size();

	lookupANDstore(word);
}	

void Tokenizer::isSymbol(){
	string::iterator current = position;
	string symbol;
	while ((current != storedLine.end()) && ispunct(*current)){
		symbol += *current;
		++current;
	}
	position += symbol.size();
	lookupANDstore(symbol);

}

void Tokenizer::isLiteral(){
	string::iterator current = position;
	string lit;
	//Add other supported literal symbols here
	// NOTE - literals must be lowercase or '_' !!!!!
	if(*current == '"'){
		while ( (current != storedLine.end()) && *current != '"'){
			lit += *current;
			++current;
		}
		position += (lit.size()+1);

		tokens.push_back(Token(Token::LITERAL, lit));
	}
}

void Tokenizer::isIdentifier(){
	string::iterator current = position;
	string ident;
	//Add other supported literal symbols here
	// NOTE - literals must be lowercase or '_' !!!!!
	while ( (current != storedLine.end()) && ( ( islower(*current)) || (*current == '_') )  ){
		ident += *current;
		++current;
	}
	position += ident.size();

	tokens.push_back(Token(Token::IDENTIFIER, ident));
}


void Tokenizer::lookupANDstore(string reserveWord){
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
	else if( reserveWord == "SET"){	//START HERE
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
	else if( reserveWord == "VARCHAR"){
		tokens.push_back(Token(Token::VARCHAR,""));
		return;
	}
	
	//*************************************
	//Symbol Section
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
}