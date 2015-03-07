#ifndef PARSER_H
#define PARSER_H

#include "Headers.h"
#include "Token_stream.h"
#include "Database.h"



class Parser
{
private:

	Token_stream ts; //used to get or putback tokens from the input stream

	bool keepParsing = true; // used for Exit Command

	

	vector<string> cleanUpNames;



	//=========================== Query's =====================================

	vector<string> attributeList();
	string identifier();
	string attributeName();
	string relationName();
	string selection();
	string projection();
	string renaming();
	string Union();
	string difference();
	string product();
	string atomicExpression();
	string expression();
	Token operand(string rName);
	string condition(string rName);
	string conjunction(string rName);
	string comparison(string rName);
	string query();

	//============================== Commands =================================

	vector<string> typedAttributeList();
	vector<string> getLiterals();
	string type();
	string openCmd();
	string closeCmd();
	string writeCmd();
	string showCmd();
	string createCmd();
	string updateCmd();
	string insertCmd();
	string DeleteCmd();
	string command();
	void exitCmd();

	//======================== CONDITION HELPER FUNCTIONS =========================

	string eqeqHelper(string rName, string firstOperand, string secondOperand, 
		Token op1, Token op2, vector<vector<Entry> > entries){
		string newRelName = "equalsequals";
		Relation temp = db.getRelation(rName);
		if (op1.kind == name){
			if (op2.kind == name){
				db.createRelation(newRelName);
				if (temp.getAttribute(firstOperand).getNumEntries() !=
					temp.getAttribute(secondOperand).getNumEntries()){
					cout << "Error in condition : number of entries of first attribute != " <<
						"number of entries in the second attribute." << endl;
					return rName;
				}
				for (int i = 0; i < temp.getAttribute(firstOperand).getNumEntries(); ++i){
					if (temp.getAttribute(firstOperand).getEntry(i).getData().compare(
						temp.getAttribute(secondOperand).getEntry(i).getData()) == 0){
						for (int k = 0; k < temp.getNumAttributes(); ++k){
							entries[i].push_back(temp.getAttribute(k).getEntry(i).getData());
						}
					}
				}
				for (int i = 0; i < entries.size(); ++i){
					db.insertInto(newRelName, entries[i]);
				}
			}
			else if (op2.kind == Literal){
				entries = db.selection(rName, secondOperand, eqeq, firstOperand);
				db.createRelation(newRelName);
				for (int i = 0; i < temp.getNumAttributes(); ++i){
					db.getRelation(newRelName).addAttribute(temp.getAttribute(i).getName(),
						temp.getAttribute(i).getMaxLength());
				}
				for (int i = 0; i < entries.size(); ++i){
					db.insertInto(newRelName, entries[i]);
				}
				/*for (int i = 0; i < db.getRelation(newRelName).getNumAttributes(); ++i){
					if (db.getRelation(newRelName).getAttribute(i).getName() != firstOperand){
						db.getRelation(newRelName).removeAttribute(db.getRelation(newRelName).getAttribute(i).getName());
					}
				}*/
				return newRelName;
			}
		}
	}

	string noteqHelper(string rName, string firstOperand, string secondOperand,
		Token op1, Token op2, vector<vector<Entry> > entries){
		string newRelName = "notequals";
		Relation temp = db.getRelation(rName);
		if (op1.kind == name){
			if (op2.kind == name){
				db.createRelation(newRelName);
				if (temp.getAttribute(firstOperand).getNumEntries() !=
					temp.getAttribute(secondOperand).getNumEntries()){
					cout << "Error in condition : number of entries of first attribute != " <<
						"number of entries in the second attribute." << endl;
					return rName;
				}
				for (int i = 0; i < temp.getAttribute(firstOperand).getNumEntries(); ++i){
					if (temp.getAttribute(firstOperand).getEntry(i).getData() !=
						temp.getAttribute(secondOperand).getEntry(i).getData()){
						for (int k = 0; k < temp.getNumAttributes(); ++k){
							entries[i].push_back(temp.getAttribute(k).getEntry(i).getData());
						}
					}
				}
				for (int i = 0; i < entries.size(); ++i){
					db.insertInto(newRelName, entries[i]);
				}
			}
			else if (op2.kind == Literal){
				entries = db.selection(rName, secondOperand, noteq, firstOperand);
				db.createRelation(newRelName);
				for (int i = 0; i < db.getRelation(rName).getNumAttributes(); ++i){
					db.getRelation(newRelName).addAttribute(db.getRelation(rName).getAttribute(i).getName(),
						db.getRelation(rName).getAttribute(i).getMaxLength());
				}
				for (int i = 0; i < entries.size(); ++i){
					db.insertInto(newRelName, entries[i]);
				}
				return newRelName;
			}
		}
	}

	string lessHelper(string rName, string firstOperand, string secondOperand,
		Token op1, Token op2, vector<vector<Entry> > entries){
		string newRelName = "less";
		Relation temp = db.getRelation(rName);
		if (op1.kind == name){
			if (op2.kind == name){
				db.createRelation(newRelName);
				if (temp.getAttribute(firstOperand).getNumEntries() !=
					temp.getAttribute(secondOperand).getNumEntries()){
					cout << "Error in condition : number of entries of first attribute != " <<
						"number of entries in the second attribute." << endl;
					return rName;
				}
				for (int i = 0; i < temp.getAttribute(firstOperand).getNumEntries(); ++i){
					if (temp.getAttribute(firstOperand).getEntry(i).getData() <
						temp.getAttribute(secondOperand).getEntry(i).getData()){
						for (int k = 0; k < temp.getNumAttributes(); ++k){
							entries[i].push_back(temp.getAttribute(k).getEntry(i).getData());
						}
					}
				}
				for (int i = 0; i < entries.size(); ++i){
					db.insertInto(newRelName, entries[i]);
				}
			}
			else if (op2.kind == Literal){
				entries = db.selection(rName, secondOperand, '<', firstOperand);
				db.createRelation(newRelName);
				for (int i = 0; i < db.getRelation(rName).getNumAttributes(); ++i){
					db.getRelation(newRelName).addAttribute(db.getRelation(rName).getAttribute(i).getName(),
						db.getRelation(rName).getAttribute(i).getMaxLength());
				}
				for (int i = 0; i < entries.size(); ++i){
					db.insertInto(newRelName, entries[i]);
				}
				return newRelName;
			}
		}
	}

	string lesseqHelper(string rName, string firstOperand, string secondOperand,
		Token op1, Token op2, vector<vector<Entry> > entries){
		string newRelName = "lessequals";
		Relation temp = db.getRelation(rName);
		if (op1.kind == name){
			if (op2.kind == name){
				db.createRelation(newRelName);
				if (temp.getAttribute(firstOperand).getNumEntries() !=
					temp.getAttribute(secondOperand).getNumEntries()){
					cout << "Error in condition : number of entries of first attribute != " <<
						"number of entries in the second attribute." << endl;
					return rName;
				}
				for (int i = 0; i < temp.getAttribute(firstOperand).getNumEntries(); ++i){
					if (temp.getAttribute(firstOperand).getEntry(i).getData() <=
						temp.getAttribute(secondOperand).getEntry(i).getData()){
						for (int k = 0; k < temp.getNumAttributes(); ++k){
							entries[i].push_back(temp.getAttribute(k).getEntry(i).getData());
						}
					}
				}
				for (int i = 0; i < entries.size(); ++i){
					db.insertInto(newRelName, entries[i]);
				}
			}
			else if (op2.kind == Literal){
				entries = db.selection(rName, secondOperand, leq, firstOperand);
				db.createRelation(newRelName);
				for (int i = 0; i < db.getRelation(rName).getNumAttributes(); ++i){
					db.getRelation(newRelName).addAttribute(db.getRelation(rName).getAttribute(i).getName(),
						db.getRelation(rName).getAttribute(i).getMaxLength());
				}
				for (int i = 0; i < entries.size(); ++i){
					db.insertInto(newRelName, entries[i]);
				}
				return newRelName;
			}
		}
	}

	string greaterHelper(string rName, string firstOperand, string secondOperand,
		Token op1, Token op2, vector<vector<Entry> > entries){
		string newRelName = "greater";
		Relation temp = db.getRelation(rName);
		if (op1.kind == name){
			if (op2.kind == name){
				db.createRelation(newRelName);
				if (temp.getAttribute(firstOperand).getNumEntries() !=
					temp.getAttribute(secondOperand).getNumEntries()){
					cout << "Error in condition : number of entries of first attribute != " <<
						"number of entries in the second attribute." << endl;
					return rName;
				}
				for (int i = 0; i < temp.getAttribute(firstOperand).getNumEntries(); ++i){
					if (temp.getAttribute(firstOperand).getEntry(i).getData() >
						temp.getAttribute(secondOperand).getEntry(i).getData()){
						for (int k = 0; k < temp.getNumAttributes(); ++k){
							entries[i].push_back(temp.getAttribute(k).getEntry(i).getData());
						}
					}
				}
				for (int i = 0; i < entries.size(); ++i){
					db.insertInto(newRelName, entries[i]);
				}
			}
			else if (op2.kind == Literal){
				entries = db.selection(rName, secondOperand, '>', firstOperand);
				db.createRelation(newRelName);
				for (int i = 0; i < db.getRelation(rName).getNumAttributes(); ++i){
					db.getRelation(newRelName).addAttribute(db.getRelation(rName).getAttribute(i).getName(),
						db.getRelation(rName).getAttribute(i).getMaxLength());
				}
				for (int i = 0; i < entries.size(); ++i){
					db.insertInto(newRelName, entries[i]);
				}
				return newRelName;
			}
		}
	}

	string greatereqHelper(string rName, string firstOperand, string secondOperand,
		Token op1, Token op2, vector<vector<Entry> > entries){
		string newRelName = "greaterequals";
		Relation temp = db.getRelation(rName);
		if (op1.kind == name){
			if (op2.kind == name){
				db.createRelation(newRelName);
				if (temp.getAttribute(firstOperand).getNumEntries() !=
					temp.getAttribute(secondOperand).getNumEntries()){
					cout << "Error in condition : number of entries of first attribute != " <<
						"number of entries in the second attribute." << endl;
					return rName;
				}
				for (int i = 0; i < temp.getAttribute(firstOperand).getNumEntries(); ++i){
					if (temp.getAttribute(firstOperand).getEntry(i).getData() >=
						temp.getAttribute(secondOperand).getEntry(i).getData()){
						for (int k = 0; k < temp.getNumAttributes(); ++k){
							entries[i].push_back(temp.getAttribute(k).getEntry(i).getData());
						}
					}
				}
				for (int i = 0; i < entries.size(); ++i){
					db.insertInto(newRelName, entries[i]);
				}
			}
			else if (op2.kind == Literal){
				entries = db.selection(rName, secondOperand, geq, firstOperand);
				db.createRelation(newRelName);
				for (int i = 0; i < db.getRelation(rName).getNumAttributes(); ++i){
					db.getRelation(newRelName).addAttribute(db.getRelation(rName).getAttribute(i).getName(),
						db.getRelation(rName).getAttribute(i).getMaxLength());
				}
				for (int i = 0; i < entries.size(); ++i){
					db.insertInto(newRelName, entries[i]);
				}
				return newRelName;
			}
		}
	}

	//=============================================================================

	string program(); // command or a query

public:
	Parser();
	~Parser();

	Database db;

	void parse(string commandLine); // used to parse

	int main2();

	bool getKeepParsing() { return keepParsing; }
};



#endif /* PARSER_H */

