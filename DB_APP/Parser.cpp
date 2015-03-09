#include "Parser.h"

Parser::Parser(){
	cleanUpNames.push_back("projRel");
	cleanUpNames.push_back("renameRel");
	cleanUpNames.push_back("CrossProduct");
	cleanUpNames.push_back("SetUnion");
	cleanUpNames.push_back("SetDifference");
	cleanUpNames.push_back("equalsequals");
	cleanUpNames.push_back("notequals");
	cleanUpNames.push_back("less");
	cleanUpNames.push_back("lessequals");
	cleanUpNames.push_back("greater");
	cleanUpNames.push_back("greaterequals");
}

Parser::~Parser(){

}


//============================= Query's =======================================

string Parser::identifier(){
	stringstream stream;
	string identName;

	Token t = ts.get();
	switch (t.kind) {
	case number:
		stream.clear();
		stream << t.value;
		return  stream.str();
	case name:
		identName = t.name;
		return identName;
	default:
		cout << "Error :: Identifier Expected." << endl;
		break;
	}
	return "";
}

string Parser::attributeName(){
	string ident = identifier();

	return ident;
}

string Parser::relationName(){
	string ident = identifier();

	return ident;
}

vector<string> Parser::attributeList(){
	vector<string> typedAttList;
	string attName;

	Token t = ts.get();
	switch (t.kind){
	case name:
	{
		ts.putback(t);
		t = ts.get();
		while (t.kind != ')'){
			if (t.kind == name){
				attName = t.name;
				typedAttList.push_back(attName);
			}
			else if (t.kind == ','){
				//do nothing, ignore ','
			}
			else{
				cout << "Error in attributeList : Expected a name." << endl;
			}
			t = ts.get();
		}
		ts.putback(t);
		break;
	}
	default:
		cout << "Error in attribute list : Expected an attribute name" << endl;
	}

	return typedAttList;
}

string Parser::selection(){
	string relName;
	string cond;
	char ch;

	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		while (cin.get(ch) && ch != ')'){
			// hold the condition to be parsed over after we get the relation name
			cond += ch;
		}
		ts.putback(ch);

		t = ts.get();
		if (t.kind != ')'){
			cout << "Error in selection : Expected a ')' at the end of the condition statement." << endl;
			break;
		}

		relName = atomicExpression();

		/* To deal with the condition part */
		cond += ";";
		streambuf* orig = cin.rdbuf();
		istringstream input(cond);
		cin.rdbuf(input.rdbuf());
		ts.get();
		cond = condition(relName);
		cin.rdbuf(orig);
		/* =============================== */

		return cond;
	}
	default:
		cout << "Error :: ( condition ) expected for select clause." << endl;
		break;
	}
	return "";
}

string Parser::projection(){
	vector<string> atts;
	vector<Attribute> newRelAtts;
	string projRelName = "projRel";
	string relName;

	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		atts = attributeList();
		t = ts.get();
		if (t.kind != ')'){
			cout << "Error :: '(' expected" << endl;
			break;
		}

		relName = atomicExpression();

		newRelAtts = db.projection(relName, atts);
		
		db.createRelation(projRelName);
		for (int i = 0; i < newRelAtts.size(); ++i){
			db.getRelation(projRelName).addAttribute(newRelAtts[i]);
		}
		return projRelName;
	}
	default:
		cout << "Error :: ( attribute list ) expected for project clause." << endl;
		break;
	}
}

string Parser::renaming(){
	vector<string> atts;
	string renameRelName = "renameRel";
	string relName;

	Token t = ts.get();	
	if (t.kind == '('){
		t = ts.get();
		switch (t.kind){
		case name:
			ts.putback(t);
			atts = attributeList();

			if (ts.get().kind != ')'){
				cout << "Error in rename : Expected a ')'.";
				break;
			}

			db.createRelation(renameRelName);
			relName = atomicExpression();
			db.getRelation(renameRelName).getAttributes() = db.getRelation(relName).getAttributes();
			if ((db.getRelation(relName).getName() == "projRel") ||
				(db.getRelation(relName).getName() == "renameRel")){
				db.removeRelation(relName);
			}
			db.renameAttribute(renameRelName, atts);
			return renameRelName;
		default:
			cout << "Error in rename : Expected a name." << endl;
			break;
		}
	}
	else{
		cout << "Error in rename : Expected a '('" << endl;
	}

	return "";
}

string Parser::Union(){
	string relName;

	Token t = ts.get();
	switch (t.kind) {
	case name:
		relName = t.name;
		return relName;
	case '(':
	{
		relName = expression();
		t = ts.get();
		if (t.kind == ')'){
			ts.putback(t);
			return relName;
		}
		else{
			cout << "Error in Union the second expression doesn't have ')'" << endl;
		}
	}
	default:
		cout << "Error: Expected a relation name or an expression." << endl;
		break;
	}
	return "";
}

string Parser::difference(){
	string relName;

	Token t = ts.get();
	switch (t.kind) {
	case name:
		relName = t.name;
		return relName;
	case '(':
	{
		relName = expression();
		t = ts.get();
		if (t.kind == ')'){
			ts.putback(t);
			return relName;
		}
		else{
			cout << "Error in Difference the second expression doesn't have ')'" << endl;
		}
	}
	default:
		cout << "Error: Expected a relation name or an expression." << endl;
		break;
	}
	return "";
}

string Parser::product(){
	Token t = ts.get();
	string relName;
	switch (t.kind) {
	case name:
		relName = t.name;
		return relName;
	case '(':
	{
		relName = expression();
		t = ts.get();
		if(t.kind == ')'){
			ts.putback(t);
			return relName;
		}
		else{
			cout << "Error in Product the second expression doesn't have ')'" << endl;
		}
	}
	default:
		cout << "Error: Expected a relation name or an expression." << endl;
		break;
	}
	return "";
}

string Parser::atomicExpression(){
	string relName1;
	string relName2;//if its simply relName1 +/-/* relName2
	string finalRelName;//final result relation returned by +/-/*

	Token t = ts.get();
	switch (t.kind){
	case name:
		relName1 = t.name;
		t = ts.get();
		if (t.kind == uni || t.kind == dif || t.kind == prod){
			relName2 = atomicExpression();
			if (t.kind == uni){
				finalRelName = db.setUnion(relName1, relName2);
			}
			else if (t.kind == dif){
				finalRelName = db.setDiff(relName1, relName2);
			}
			else if (t.kind == prod){
				finalRelName = db.crossProduct(relName1, relName2);
			}
			return finalRelName;
		}
		ts.putback(t);
		return relName1;
	case '(':
		relName1 = expression();
		t = ts.get();
		t = ts.get();
		if (t.kind == ')' || t.kind == newLine){
			ts.putback(t);
			return relName1;
		}
		else{
			cout << "Error in atomicExpression : Expected a ')' at the end of the expression." << endl;
			break;
		}
	default:
		cout << "Error in atomicExpression : Expected a relation name or ( expr )." << endl;
		break;
	}

	return "";
}

string Parser::expression(){
	string relName;

	Token t = ts.get();
	switch (t.kind){
	case name: case '(':
		ts.putback(t);
		relName = atomicExpression();
		return relName;
	case sel:
		relName = selection();
		return relName;
	case pro:
		relName = projection();
		return relName;
	case ren:
		relName = renaming();
		return relName;
	case uni:
		relName = Union();
		return relName;
	case dif:
		relName = difference();
		return relName;
	case prod:
		relName = product();
		return relName;
	default:
		cout << "Error : expected an expression." << endl;
		break;
	}
	return "";
}

Token Parser::operand(string rName){
	string operandName;
	stringstream operandVal;

	Token t = ts.get();
	switch (t.kind){
	case name:
		operandName = t.name;
		if (!(db.getRelation(rName).attributeExists(operandName))){
			cout << "Error in condition statement : Attribute doesn't exist in " <<
				"the relation " << rName << "." << endl;
			break;
		}
		return t;
	case Literal:
		return t;
	case number:
		operandVal << t.value;
		return Token(Literal, operandVal.str());
	default:
		cout << "Error in Operand : Expected a name or a number." << endl;
		break;
	}
	return Token('0');
}

string Parser::condition(string rName){
	string firstConjunction = conjunction(rName);
	string secondConjunction;

	Token t = ts.get();
	switch (t.kind){
	case disuni:
		secondConjunction = condition(rName);
		return db.setUnion(firstConjunction, secondConjunction);
	default:
		ts.putback(t);
		return firstConjunction;
	}

	return "";
}

string Parser::conjunction(string rName){
	string firstComparison = comparison(rName);
	string secondComparison;

	Token t = ts.get();
	switch (t.kind){
	case conj:
		secondComparison = comparison(rName);
		return db.setDiff(firstComparison, db.setDiff(
			secondComparison, db.setUnion(firstComparison, secondComparison)));
	default:
		ts.putback(t);
		return firstComparison;
	}

	return "";
}

string Parser::comparison(string rName){
	Token op1 = operand(rName);
	vector<vector<Entry> > entries;
	string firstOperand = op1.name;
	string secondOperand;

	Token t = ts.get();
	Token op2 = operand(rName);
	secondOperand = op2.name;
	switch (t.kind){
	case eqeq:
		rName = eqeqHelper(rName, firstOperand, secondOperand, op1, op2, entries);
		return rName;
	case noteq:
		rName = noteqHelper(rName, firstOperand, secondOperand, op1, op2, entries);
		return rName;
	case '<':
		rName = lessHelper(rName, firstOperand, secondOperand, op1, op2, entries);
		return rName;
	case leq:
		rName = lesseqHelper(rName, firstOperand, secondOperand, op1, op2, entries);
		return rName;
	case '>':
		rName = greaterHelper(rName, firstOperand, secondOperand, op1, op2, entries);
		return rName;
	case geq:
		rName = greatereqHelper(rName, firstOperand, secondOperand, op1, op2, entries);
		return rName;
	case '(':
		if (ts.get().kind != ')'){
			cout << "Error in Comparison : expected a ')' at the end of the condition." << endl;
		}
	default:
		cout << "Error in Comparison : Expected an operation or a '('." << endl;
		break;
	}

	return "";
}

string Parser::query(){
	string relName = relationName();
	string newRelName;
	Relation rel;
	
	Token t = ts.get();
	switch(t.kind){
	case qu:
		if ((!db.relationExists(relName)) && (!db.isOnDisk(relName))){
			//if the relation already exists then dont do unnecessary stuff
			db.createRelation(relName);
			newRelName = expression();
			rel = db.getRelation(newRelName);
			db.getRelation(relName).getAttributes() = rel.getAttributes();
			db.cleanUp(cleanUpNames);//to get rid of the temporary relations
		}
		else{
			ts.get();
			cout << "Error : Relation already Exists." << endl;
		}
		break;
	default:
		cout << "Error :: Expected a '<-' for a query.";
		break;
	}
	return "";
}

//=============================== Commands ====================================

string Parser::type(){
	int length;
	int intValue;
	stringstream ss;
	ss.clear();
	Token t = ts.get();
	switch(t.kind){
	case varc:
	{
		if(ts.get().kind == '('){
			t = ts.get();
			if(t.kind == number){
				length = t.value;
				t = ts.get();
				if(t.kind == ')'){
					ss << length;
					return ss.str();
				}
				else{
					cout << "Error in type, missing ')'" << endl;
				}
			}
			else{
				cout << "Error in type, expected an integer" << endl;
			}
		}
		else{
			cout << "Error in type, expected '('" << endl;
		}
	}
	case integ:
	{
		return "-1";//lets us know its an integer for the type
	}
	default:
		cout << "Error in type, expected VARCHAR(integer) or INTEGER." << endl;
		break;
	}
	return "-2"; //failure return
}

vector<string> Parser::typedAttributeList(){
	vector<string> typedAttList;
	string attName;
	string attType;

	Token t = ts.get();
	switch (t.kind){
	case name:
	{
		ts.putback(t);
		t = ts.get();
		while (t.kind != ')'){
			if (t.kind == name){
				attName = t.name;
				typedAttList.push_back(attName);
			}
			else if ((t.kind == varc) || (t.kind == integ)){
				ts.putback(t);
				attType = type();
				typedAttList.push_back(attType);
			}
			else if(t.kind == ','){
				//do nothing, ignore ','
			}
			t = ts.get();
		}
		ts.putback(t);
		break;
	}
	default:
		cout << "Error in typed attribute list : Expected an attribute name" << endl;
	}

	return typedAttList;
}

string Parser::openCmd(){
	Token t = ts.get();
	string relName;
	switch (t.kind){
	case name:
		relName = t.name;
		db.openRelation(relName);
		break;
	default:
		cout << "Bad open command input. Requires a Name." << endl;
		break;
	}
	return "";
}

string Parser::closeCmd(){
	Token t = ts.get();
	string relName;
	switch (t.kind){
	case name:
		relName = t.name;
		db.closeRelation(relName);
		break;
	default:
		cout << "Bad close command input. Requires a Name." << endl;
		break;
	}
	return "";
}

string Parser::writeCmd(){
	string relName;

	Token t = ts.get();
	switch (t.kind){
	case name:
		relName = t.name;
		db.writeRelation(relName);
		break;
	default:
		cout << "Bad write command input. Requires a Name." << endl;
		break;
	}
	return "";
}

void Parser::exitCmd(){
	// if EXIT is typed, quit parsing
	cout << "\nExiting..." << endl;
	keepParsing = false;
}

string Parser::showCmd(){
	string relName;

	Token t = ts.get();
	switch (t.kind){
	case name:
		relName = t.name;
		db.showRelation(relName);
		break;
	case '(':
		relName = expression();
		t = ts.get();
		if (t.kind != ')'){
			cout << "Error in Show Command : Expected a ')' after the expression statement" << endl;
		}
		else{
			db.showRelation(relName);
		}
		db.cleanUp(cleanUpNames);//to get rid of the temporary relations
		break;
	default:
		cout << "Error in Show Command :: expected a name or an expression." << endl;
		break;
	}
	return "";
}

string Parser::createCmd(){
	string relName;
	vector<string> keyList;//Primary Keys
	vector<string> typedAttList;//name,type,name,type,...

	Token t = ts.get();
	switch (t.kind){
	case name:
		relName = t.name;
		if (db.relationExists(relName) || db.isOnDisk(relName)){
			// dont do unnecessary stuff if relation exists already
			cout << "Error : Relation already Exists." << endl;
			break;
		}
		if (ts.get().kind == '('){
			typedAttList = typedAttributeList();
			if (ts.get().kind == ')'){
				if (ts.get().kind == pk){
					if (ts.get().kind == '('){
						keyList = attributeList();
						if (ts.get().kind != ')'){
							cout << "Error in Create Command :: expected a ')'" <<
								"after the attribute list." << endl;
						}
						else{
							db.createRelation(relName, keyList);
							for (int i = 0; i < typedAttList.size(); i = i + 2){
								db.insertInto(relName, typedAttList[i], typedAttList[i + 1]);
							}
							break;
						}
					}
					else{
						cout << "Error in Create Command :: expected a '('"
							"after \"PRIMARY KEY\"." << endl;
					}
				}
				else {
					cout << "Error in Create Command :: expected a \"PRIMARY KEY\"" << 
						"after the typed attribute list." << endl;
				}
			}
			else{
				cout << "Error in Create Command :: expected a ')'" <<
					"after the typed-attribute list." << endl;
			}
		}
		else{
			cout << "Error in Create Command :: expected a '(' after the name." << endl;
		}
		break;
	default:
		cout << "Error in Create Command :: expected a relation name." << endl;
		break;
	}
	return "";
}

string Parser::updateCmd(){
	vector<string> atts;//attname,literal,...
	string values;
	string cond; //for condition
	string relName;

	Token t = ts.get();
	switch (t.kind){
	case name:
		relName = t.name;
		if (ts.get().kind == se){
			t = ts.get();
			while (t.kind != wh){
				if (t.kind == name){
					values = t.name;
					atts.push_back(values);
					t = ts.get();
					if (t.kind == '='){
						t = ts.get();
						if (t.kind == Literal){
							values = t.name;
							atts.push_back(values);
						}
						else if (t.kind == number){
							stringstream ss;
							ss << t.value;
							values = ss.str();
							atts.push_back(values);
						}
						else{
							cerr << "Error: Expected value for change";
							return"";
						}
					}
					else{
						cerr << "Error: Expected '=' sign";
						return "";
					}
				}
				else{
					cerr << "Error: expected name ";
					return "";
				}
				t = ts.get();
				if (t.kind != ','){
					ts.putback(t);
				}
				t = ts.get();
			}
			t = ts.get();
			if (t.kind == '('){
				cond = condition(relName);
				t = ts.get();
				if (t.kind != ')'){
					cout << "Error in Update : Expected a ')' after the condition statement." << endl;
					break;
				}
			}
			else{
				ts.putback(t);
				cond = condition(relName);
			}
			db.updateRelation(relName, cond, atts);
			db.cleanUp(cleanUpNames);
		}
		else{
			cout << "Error: expected \"SET\"";
			break;
		}
		break;
	default:
		cout << "Error in update command : Expected a relation name." << endl;
		break;
	}
	return "";
}

vector<string> Parser::getLiterals(){
	//This function is just a helper for the INSERT COMMAND
	vector<string> literals;
	string litName;
	stringstream ss;

	Token t = ts.get();
	while(t.kind != ')'){
		if(t.kind == name || t.kind == Literal){
			litName = t.name;
			literals.push_back(litName);
		}
		else if(t.kind == number){
			ss << t.value;
			litName = ss.str();
			literals.push_back(litName);
		}
		else if(t.kind == ','){
		//do nothing, ignore ','
		}
		else{
			cout << "Error in getting literals : Expected a name or a number" << endl;
		}
		t = ts.get();
	}
	ts.putback(t);
	return literals;
}

string Parser::insertCmd(){
	vector<string> literals;
	string relName;
	string relFromName;

	Token t = ts.get();
	switch (t.kind){
	case name: case Literal:
		relName = t.name;
		t = ts.get();
		if(t.kind == vf){
			t = ts.get();
			if(t.kind == vfr){
				relFromName = expression();
				for (int i = 0; i < db.getRelation(relFromName).getAttributes()[0].getNumEntries(); ++i){
					for (int k = 0; k < db.getRelation(relFromName).getNumAttributes(); ++k){
						literals.push_back(db.getRelation(relFromName).getAttributes()[k].getEntry(i).getData());
					}
					db.insertInto(relName, literals);
					literals.clear();
				}
				db.cleanUp(cleanUpNames);//to get rid of the temporary relations
				break;
			}
			else if(t.kind = '('){
				literals = getLiterals();
				if (ts.get().kind != ')'){
					cout << "Error in insert : Expected a ')' after literals." << endl;
				}
				else{
					db.insertInto(relName, literals);
				}
				break;
			}
			else{
				cout << "Error : Expected a '('." << endl;
				break;
			}
		}
		else{
			cout << "Error :: Expected \"VALUES FROM\"." << endl;
			break;
		}
	default:
		cout << "Error :: Expected a relation name" << endl;
		break;
	}
	return "";
}

string Parser::DeleteCmd(){
	string relName;
	string condRelName;
	bool parens = false;

	Token t = ts.get();
	switch(t.kind){
	case name:
		relName = t.name;
		if (ts.get().kind == wh)
		{
			t = ts.get();
			if (t.kind == '('){ parens = true; }
			else{ ts.putback(t); }
			condRelName = condition(relName);
			if ((parens == true) && (ts.get().kind != ')')){
				cout << "Error in Delete Command : Expected a ) at the end of the condition." << endl;
				break;
			}
			db.deleteTuplesFromRelation(relName, condRelName);
			db.cleanUp(cleanUpNames);//delete temporary relations from database
			break;
		}
		else{
			cout << "Error :: expected \"WHERE\"." << endl;
			break;
		}
	default:
		cout << "Error in delete command : Expected a relation name." << endl;
		break;
	}
	return "";
}

string Parser::command(){
	// open | close | write | exit | show | create | update | insert | delete
	Token t = ts.get();

	switch (t.kind){
	case op:
		openCmd();
		break;
	case cl:
		closeCmd();
		break;
	case wr:
		writeCmd();
		break;
	case quit:
		exitCmd();
		break;
	case sh:
		showCmd();
		break;
	case cr:
		createCmd();
		break;
	case up:
		updateCmd();
		break;
	case inInto:
		insertCmd();
		break;
	case df:
		DeleteCmd();
		break;
	default:
		cout << "ERROR : Improper command input." << endl;
		break;
	}
	return "";
}

string Parser::program(){
	// query | command
	Token t = ts.get();
	if (t.name != ""){
		t.kind = qu; //if name isnt empty then its a query
	}
	switch (t.kind){
	case qu:
		t.kind = name;
		ts.putback(t);
		query();
		break;
	case op: case cl: case wr: case quit:
	case sh: case cr: case up: case inInto: case df:
		ts.putback(t);
		command();
		break;
	case newLine:
		break;
	default:
		cout << "ERROR :: Expect a name for a query or a Command." << endl;
		break;
	}
	return "";
}

//=============================================================================

void Parser::parse(string commandLine){
	// function that actually does the parsing
	
while (this->getKeepParsing()){
	
	streambuf* orig = cin.rdbuf();		//keep
	istringstream input(commandLine);				//keep
	cin.rdbuf(input.rdbuf());	//redirect string 	//keep
	//p.parse(test1);	
		
	//this should be used if parsing from command line
		
		Token t = ts.get();
		ts.putback(t);
		program();
		if (ts.get().kind == newLine){
			cin.rdbuf(orig);
			return;
		}
		else{
			cout << "Error :: There must be a ';' at the end of a statement." << endl;
		}
	cin.rdbuf(orig);
	cout << endl;
	

}
	/* ----------------------- For automated Test cases --------------------------*/
	/*cout << input << "\n\n";
	program();
	cout << "\n\n";
	if (ts.get().kind == newLine){
		return;
	}
	else{
		cout << "Error :: There must be a ';' at the end of a statement." << endl;
	}*/
	
	//-----------------------------------------------------------------------------
}

//=============================================================================

// int main2(){
	//Parser p;
	//============================================ Test Cases ================================================
	// string test1 = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
	// string test2 = "CREATE TABLE species (kind VARCHAR(10)) PRIMARY KEY (kind);";
	// string test3 = "INSERT INTO animals VALUES FROM (Joe, cat, 4);";
	// string test4 = "INSERT INTO animals VALUES FROM (Spot, dog, 10);";
	// string test5 = "INSERT INTO animals VALUES FROM (Snoopy, dog, 3);";
	// string test6 = "INSERT INTO animals VALUES FROM (Tweety, bird, 1);";
	// string test7 = "INSERT INTO animals VALUES FROM (Joe, bird, 2);";
	// string test8 = "INSERT INTO species VALUES FROM RELATION project (kind) animals;";
	// string test9 = "UPDATE animals SET blue = red, bob = rick WHERE (aname == name && akind != kind);";
	// string test10 = "UPDATE animals SET blue = red, bob = rick WHERE aname == name;";
	// string test11 = "SHOW animals;";
	// string test12 = "SHOW answer;";
	// string test13 = "dogs <- select (kind == dog) animals;";
	// string test14 = "old_dogs <- select(age > 10) dogs;";
	// string test15 = "cats_or_dogs <- dogs + (select (kind == cat) animals);";
	// string test16 = "a <- rename (aname, akind) (project (name, kind) animals);";
	// string test17 = "common_names <- project (name) (select (aname == name && akind != kind) (a * animals));";
	// string test18 = "answer <- common_names;";
	// string test19 = "WRITE answer;";
	// string test20 = "CLOSE animals;";
	// string test21 = "EXIT;";
	//========================================================================================================
	
	
	//uncomment if you want to run automated test cases and comment while loop above
	/*streambuf* orig = cin.rdbuf();		//keep
	istringstream input(test1);				//keep
	cin.rdbuf(input.rdbuf());	//redirect string 	//keep
	p.parse(test1);			//keep

	input.str(test2);
	cin.rdbuf(input.rdbuf());
	p.parse(test2);

	input.str(test3);
	cin.rdbuf(input.rdbuf());
	p.parse(test3);

	input.str(test4);
	cin.rdbuf(input.rdbuf());
	p.parse(test4);

	input.str(test5);
	cin.rdbuf(input.rdbuf());
	p.parse(test5);

	input.str(test6);
	cin.rdbuf(input.rdbuf());
	p.parse(test6);

	input.str(test7);
	cin.rdbuf(input.rdbuf());
	p.parse(test7);

	input.str(test8);
	cin.rdbuf(input.rdbuf());
	p.parse(test8);

	input.str(test9);
	cin.rdbuf(input.rdbuf());
	p.parse(test9);

	input.str(test10);
	cin.rdbuf(input.rdbuf());
	p.parse(test10);

	input.str(test11);
	cin.rdbuf(input.rdbuf());
	p.parse(test11);

	input.str(test12);
	cin.rdbuf(input.rdbuf());
	p.parse(test12);

	input.str(test13);
	cin.rdbuf(input.rdbuf());
	p.parse(test13);

	input.str(test14);
	cin.rdbuf(input.rdbuf());
	p.parse(test14);

	input.str(test15);
	cin.rdbuf(input.rdbuf());
	p.parse(test15);

	input.str(test16);
	cin.rdbuf(input.rdbuf());
	p.parse(test16);

	input.str(test17);
	cin.rdbuf(input.rdbuf());
	p.parse(test17);

	input.str(test18);
	cin.rdbuf(input.rdbuf());
	p.parse(test18);
	
	input.str(test19);
	cin.rdbuf(input.rdbuf());
	p.parse(test19);

	input.str(test20);
	cin.rdbuf(input.rdbuf());
	p.parse(test20);

	input.str(test21);
	cin.rdbuf(input.rdbuf());
	p.parse(test21);


	//return buffer to terminal
	cin.rdbuf(orig);*/

// 	return 0;
// }

//=============================================================================

