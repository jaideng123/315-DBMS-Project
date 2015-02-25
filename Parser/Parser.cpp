#include "Parser.h"
#include <stdexcept>
#include <algorithm>

using namespace std;

void Parser::parse(string input){
	Tokenizer t(input);
	tokens = t.get_tokens();
	current_token = 0;
	if(tokens[current_token].get_type() == Token::IDENTIFIER){
		string name = tokens[current_token].get_value();
		Table t = query();
		t.set_name(name);
		if(!db->table_exists(name))
			db->tables.push_back(t);
		else
			*db->find_table(name) = t;
	}
	else{
		command();
	}

}

//parse query
Table Parser::query(){

	if(!is_next(Token::LEFTARROW))
		throw runtime_error("Parsing Error");
	current_token++;
	return expr();
	if(!is_next(Token::SEMICOLON))
		throw runtime_error("Parsing Error");
}

//determine type of expression
Table Parser::expr(){
	if(is_next(Token::SELECT))
		return select_expr();
		
	else if(is_next(Token::RENAME))
		return rename_expr();
		
	else if(is_next(Token::PROJECT))
		return project_expr();
		
	else if(is_next(Token::IDENTIFIER)){
		current_token++;
		Table t = db->get_table(tokens[current_token].get_value());
		if(is_next(Token::UNION))
			return union_expr(t);
		else if(is_next(Token::DIFF))
			return diff_expr(t);
		else if(is_next(Token::PRODUCT))
			return prod_expr(t);
		else if(is_next(Token::SEMICOLON) || is_next(Token::RIGHTPAREN))
			return db->get_table(tokens[current_token].get_value());
		else
			throw runtime_error("Parsing Error");
	}
	
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		Table t = atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		current_token++;
		if(is_next(Token::UNION))
			return union_expr(t);
		else if(is_next(Token::DIFF))
			return diff_expr(t);
		else if(is_next(Token::PRODUCT))
			return prod_expr(t);
		else{
			current_token--;
			return t;
		}
	}
	
	else
		throw runtime_error("Parsing Error");
}

//for nested instructions
//takes atomic expression without ()
Table Parser::atomic_expr(){
	if(is_next(Token::IDENTIFIER)){
		current_token++;
		return db->get_table(tokens[current_token].get_value());
	}
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		Table t = atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		return t;
	}
	else{
		return expr();
	}
}

//for select expressions
Table Parser::select_expr(){
	//select
	current_token++;
	//(condition)
	int condition_loc = current_token;
	eat_condition();
	vector<int> sel;
	//expr
	if(is_next(Token::IDENTIFIER)){
		current_token++;
		Table t = db->get_table(tokens[current_token].get_value());
		int current_loc = current_token;
		current_token = condition_loc;
		sel = condition(t);
		current_token = current_loc;
		return db->set_select(t,sel);
	}
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		Table t = atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		current_token++;
		int current_loc = current_token;
		current_token = condition_loc;
		sel = condition(t);
		current_token = current_loc;
		return db->set_select(t,sel);
	}
	else
		throw runtime_error("Parsing Error");
}

//helper function to skip condition
void Parser::eat_condition(){
	current_token++;
	int paren_count = 1;
	while(paren_count > 0){
		if(is_next(Token::RIGHTPAREN)){
			paren_count--;
			current_token++;
		}
		else if(is_next(Token::LEFTPAREN)){
			paren_count++;
			current_token++;
		}
		else 
			current_token++;
	}
	return;

}

//for rename expressions
Table Parser::rename_expr(){
	//rename
	current_token++;
	//(attr_list)
	if(!is_next(Token::LEFTPAREN))
		throw runtime_error("Parsing Error");
	current_token++;
	vector<string> new_attr;
	while(!is_next(Token::RIGHTPAREN)){
		if(!is_next(Token::IDENTIFIER))
			throw runtime_error("Parsing Error");
		current_token++;
		new_attr.push_back(tokens[current_token].get_value());
		if(!is_next(Token::COMMA))
			break;
		current_token++;
	}
	if(!is_next(Token::RIGHTPAREN))
		throw runtime_error("Parsing Error");
	current_token++;
	//expr
	if(is_next(Token::IDENTIFIER)){
		current_token++;
		Table t = db->get_table(tokens[current_token].get_value());
		return db->set_rename(t,new_attr);
	}
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		Table t = atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		current_token++;
		return db->set_rename(t,new_attr);
	}
	else
		throw runtime_error("Parsing Error");
}

//for project expressions
Table Parser::project_expr(){
	//project
	current_token++;
	//(attr_list)
	if(!is_next(Token::LEFTPAREN))
		throw runtime_error("Parsing Error");
	current_token++;
	vector<string> sel_attr;
	while(!is_next(Token::RIGHTPAREN)){
		if(!is_next(Token::IDENTIFIER))
			throw runtime_error("Parsing Error");
		current_token++;
		sel_attr.push_back(tokens[current_token].get_value());
		if(!is_next(Token::COMMA))
			break;
		current_token++;
	}
	if(!is_next(Token::RIGHTPAREN))
		throw runtime_error("Parsing Error");
	current_token++;
	//expr
	if(is_next(Token::IDENTIFIER)){
		current_token++;
		Table t = db->get_table(tokens[current_token].get_value());
		return db->set_project(t,sel_attr);
	}
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		Table t = atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		current_token++;
		return db->set_project(t,sel_attr);
	}
	else
		throw runtime_error("Parsing Error");
}

//for union expressions
Table Parser::union_expr(Table t1){
	//+ 
	current_token++;
	//expr
	if(is_next(Token::IDENTIFIER)){
		current_token++;
		Table t2 = db->get_table(tokens[current_token].get_value());
		return db->set_union(t1,t2);
	}
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		Table t2 = atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		current_token++;
		return db->set_union(t1,t2);
	}
	else
		throw runtime_error("Parsing Error");
}

//for difference expressions
Table Parser::diff_expr(Table t1){
	//- 
	current_token++;
	//expr
	if(is_next(Token::IDENTIFIER)){
		current_token++;
		Table t2 = db->get_table(tokens[current_token].get_value());
		return db->set_difference(t1,t2);
	}
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		Table t2 = atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		current_token++;
		return db->set_difference(t1,t2);
	}
	else
		throw runtime_error("Parsing Error");
}

//for product expressions
Table Parser::prod_expr(Table t1){
	//*
	current_token++;
	//expr
	if(is_next(Token::IDENTIFIER)){
		current_token++;
		Table t2 = db->get_table(tokens[current_token].get_value());
		return db->set_product(t1,t2);
	}
	else if(is_next(Token::LEFTPAREN)){
		current_token++;
		Table t2 = atomic_expr();
		if(!is_next(Token::RIGHTPAREN))
			throw runtime_error("Parsing Error");
		current_token++;
		return db->set_difference(t1,t2);
	}
	else
		throw runtime_error("Parsing Error");
}

//for condition parsing, it will start pointing
//at just before the first left parentheses and should end
//pointing at the last right parentheses
vector<int> Parser::condition(Table t){
	if(!is_next(Token::LEFTPAREN))
		throw runtime_error("Parsing Error");
	current_token++;
	vector<int> indices;
	int paren_count = 1;
	while(paren_count > 0){
		if(is_next(Token::RIGHTPAREN)){
			paren_count--;
			current_token++;
			break;
		}
		else if(is_next(Token::LEFTPAREN)){
			paren_count++;
			current_token++;
		}
		else if(is_next(Token::IDENTIFIER)){
			indices = comparison(t);
		}
		//check for conjunctions
		else if(is_next(Token::AND)){
			current_token++;
			if(is_next(Token::LEFTPAREN))
				return and_indices(indices,condition(t));
			else if(is_next(Token::IDENTIFIER))
				return and_indices(indices,comparison(t));
			else
				throw runtime_error("Parsing Error");
		}
		else if(is_next(Token::OR)){
			current_token++;
			if(is_next(Token::LEFTPAREN))
				return or_indices(indices,condition(t));
			else if(is_next(Token::IDENTIFIER))
				return or_indices(indices,comparison(t));
			else
				throw runtime_error("Parsing Error");
		}
		else
			throw runtime_error("Parsing Error");
	}
	return indices;
}

//for comparisons in condition
vector<int> Parser::comparison(Table t){
	vector<int> indices;
	//operand 1
	current_token++;
	string id = tokens[current_token].get_value();
	Token::Token_Type token;
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
	else
		throw runtime_error("Parsing Error");
	token = tokens[current_token].get_type();
	//operand 2
	if(is_next(Token::NUMBER)){
		current_token++;
		indices = compare(t,id,token,tokens[current_token]);
	}
	else if(is_next(Token::LITERAL) &&(
				tokens[current_token].get_type() == Token::EQ ||
				tokens[current_token].get_type() == Token::NEQ)){
		current_token++;
		indices = compare(t,id,token,tokens[current_token]);
	}
	else
		throw runtime_error("Parsing Error");
	//check for conjunctions
	if(is_next(Token::AND)){
		current_token++;
		if(is_next(Token::LEFTPAREN))
			return and_indices(indices,condition(t));
		else if(is_next(Token::IDENTIFIER))
			return and_indices(indices,comparison(t));
		else
			throw runtime_error("Parsing Error");
	}
	else if(is_next(Token::OR)){
		current_token++;
		if(is_next(Token::LEFTPAREN))
			return or_indices(indices,condition(t));
		else if(is_next(Token::IDENTIFIER))
			return or_indices(indices,comparison(t));
		else
			throw runtime_error("Parsing Error");
	}
	return indices;
}

//v1 || v2
vector<int> Parser::or_indices(vector<int> v1, vector<int> v2){
	for (int i = 0; i < v2.size(); ++i)
	{
		if(find(v1.begin(),v1.end(),v2[i]) == v1.end())
			v1.push_back(v2[i]);
	}
	return v1;
}

//v1 && v2
vector<int> Parser::and_indices(vector<int> v1, vector<int> v2){
	vector<int> v;
	for (int i = 0; i < v2.size(); ++i)
	{
		if(find(v1.begin(),v1.end(),v2[i]) != v1.end())
			v.push_back(v2[i]);
	}
	return v;
}

//get indices of records matching comparison
vector<int> Parser::compare(Table t,string id,Token::Token_Type op,Token token){
	//find index of field to compare
	int attr_index = -1;
	for (int i = 0; i < t.get_attributes().size(); ++i){
		if(t.get_attributes()[i].get_name() == id)
			attr_index = i;
	}
	if(attr_index == -1)
		throw runtime_error("Error: Attribute does not exist");
	//get indices of corresponding records
	vector<int> indices;
	vector<Record> rec = t.get_records();
	if(token.get_type() == Token::NUMBER){
		if(op == Token::EQ){
			for (int i = 0; i < rec.size(); ++i){
				if(stoi(rec[i].get_entry(attr_index)) == stoi(token.get_value()))
					indices.push_back(i);
			}
		}
		else if(op == Token::LT){
			for (int i = 0; i < rec.size(); ++i){
				if(stoi(rec[i].get_entry(attr_index)) < stoi(token.get_value()))
					indices.push_back(i);
			}
		}
		else if(op == Token::LEQ){
			for (int i = 0; i < rec.size(); ++i){
				if(stoi(rec[i].get_entry(attr_index)) <= stoi(token.get_value()))
					indices.push_back(i);
			}
		}
		else if(op == Token::GT){
			for (int i = 0; i < rec.size(); ++i){
				if(stoi(rec[i].get_entry(attr_index)) > stoi(token.get_value()))
					indices.push_back(i);
			}
		}
		else if(op == Token::GEQ){
			for (int i = 0; i < rec.size(); ++i){
				if(stoi(rec[i].get_entry(attr_index)) >= stoi(token.get_value()))
					indices.push_back(i);
			}
		}
		else if(op == Token::NEQ){
			for (int i = 0; i < rec.size(); ++i){
					if(stoi(rec[i].get_entry(attr_index)) != stoi(token.get_value()))
						indices.push_back(i);
			}
		}
	}
	else if(token.get_type() == Token::LITERAL){
		if(op == Token::EQ){
			for (int i = 0; i < rec.size(); ++i){
				if(rec[i].get_entry(attr_index) == token.get_value())
					indices.push_back(i);
			}
		}
		else if(op == Token::NEQ){
			for (int i = 0; i < rec.size(); ++i){
				if(rec[i].get_entry(attr_index) != token.get_value())
					indices.push_back(i);
			}
		}
	}
	return indices;
}

void Parser::command(){

	if(tokens[current_token].get_type() == Token::OPEN){
		open_cmd();
	}
	else if(tokens[current_token].get_type() == Token::CLOSE){
		close_cmd();
	}
	else if(tokens[current_token].get_type() == Token::WRITE){
		write_cmd();
	}
	else if(tokens[current_token].get_type() == Token::EXIT){
		exit_cmd();
	}
	else if(tokens[current_token].get_type() == Token::SHOW){
		show_cmd();
	}
	else if(tokens[current_token].get_type() == Token::CREATE){
		create_cmd();
	}
	else if(tokens[current_token].get_type() == Token::UPDATE){
		update_cmd();
	}
	else if(tokens[current_token].get_type() == Token::INSERT){
		insert_cmd();
	}
	else if(tokens[current_token].get_type() == Token::DELETE){
		delete_cmd();
	}
	else
		throw runtime_error("Parsing Error");
	return;
}

void Parser::open_cmd(){
	if(is_next(Token::IDENTIFIER))
		current_token++;
	else
		throw runtime_error("Parsing Error");
}

void Parser::close_cmd(){
	if(is_next(Token::IDENTIFIER))
		current_token++;
	else
		throw runtime_error("Parsing Error");
}

void Parser::write_cmd(){
	if(is_next(Token::IDENTIFIER))
		current_token++;
	else
		throw runtime_error("Parsing Error");
}

void Parser::exit_cmd(){
	if(is_next(Token::SEMICOLON))
		return;
	throw runtime_error("Parsing Error");
}

void Parser::show_cmd(){
	Table t = expr();
	t.print();
	return;
}

void Parser::create_cmd(){
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
			if(!is_next(Token::NUMBER))
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
	if(!is_next(Token::IDENTIFIER))
		throw runtime_error("Parsing Error");
	current_token++;
	if(!is_next(Token::SET))
		throw runtime_error("Parsing Error");
	current_token++;

	while(!is_next(Token::WHERE)){
		if(!is_next(Token::IDENTIFIER))
			throw runtime_error("Parsing Error");
		current_token++;
		if(!is_next(Token::EQUALSIGN))
			throw runtime_error("Parsing Error");
		current_token++;
		if(!is_next(Token::LITERAL))
			throw runtime_error("Parsing Error");
		current_token++;
		if(!is_next(Token::COMMA))
			break;
		current_token++;
	}

	if(is_next(Token::WHERE)){
		current_token++;
		Table t("NULL");
		condition(t);
	}
	else
		throw runtime_error("Parsing Error");
	
	

}

void Parser::insert_cmd(){
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
	}
	else if(is_next(Token::LEFTPAREN))
	{
		current_token++;
		while(!is_next(Token::RIGHTPAREN)){
			if(!is_next(Token::LITERAL))
				throw runtime_error("Parsing Error");
			current_token++;
			if(!is_next(Token::COMMA))
				break;
			current_token++;
		}
		current_token++;
	}
	else
		throw runtime_error("Parsing Error");
}

void Parser::delete_cmd(){
	if(!is_next(Token::FROM))
		throw runtime_error("Parsing Error");
	current_token++;
	if(!is_next(Token::IDENTIFIER))
		throw runtime_error("Parsing Error");
	current_token++;
	if(is_next(Token::WHERE)){
		current_token++;
		Table t("NULL");
		condition(t);
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