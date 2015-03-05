#include "Relation.h"

/* ===================== Constructor/Destructor ============================ */

Relation::Relation(){
	relationName = "";
}

Relation::Relation(string name){
	relationName = name;
}

Relation::Relation(string name, vector<string> keys){
	relationName = name;
	primaryKeys = keys;
}

Relation::~Relation(){

}

/* ========================================================================= */

/* ========================= Helper Functions ============================== */

void Relation::addAttribute(string attName){
	attributes.push_back(Attribute(attName));
}

void Relation::addAttribute(string attName, int type){
	attributes.push_back(Attribute(attName, type));
}

void Relation::addAttribute(Attribute att){
	attributes.push_back(att);
}

void Relation::removeAttribute(string attName){
	for (int i = 0; i < attributes.size(); ++i){
		if (attributes[i].getName() == attName){
			attributes.erase(attributes.begin() + i);
			return;
		}
	}
	cout << "Error in removeAttribute() in Relation.cpp :: " <<
			attName << " attribute is not in the relation. " << endl;
}

void Relation::setTuples(){
	//set the tuples by taking one of each attribute in the same row
	int numEntries = attributes[0].getNumEntries();
	for (int i = 0; i < numEntries; ++i)
	{
		vector<Entry> tupleEntries;
		for (int j = 0; j < attributes.size(); ++j)
		{
			tupleEntries.push_back(attributes[j].getEntry(i));
		}
		tuples.push_back(tupleEntries);
	}
}

void Relation::setKeys(vector<string> keys){
	primaryKeys = keys;
}

Attribute& Relation::getAttribute(string attName){
	for (int i = 0; i < attributes.size(); ++i){
		if (attributes[i].getName() == attName){
			return attributes[i];
		}
	}
	cout << "Error in getAttribute() in Relation.cpp :: " <<
					attName << " is not in the relation." << endl;
}

bool Relation::attributeExists(string attName){
	//returns true if the attribute is in the relation
	for (int i = 0; i < attributes.size(); ++i){
		if (attName == attributes[i].getName()){
			return true;
		}
	}
	return false;
}

/* ========================================================================= */

/* ===================== Relation Algebra Functions ======================== */

vector<vector<Entry> > Relation::selection(string entryValue, char condition, string attName){
	//return only the tuples that have the given entry value
	this->setTuples();
	vector<vector<Entry> > selectTuples;
	int spot = 0;
	for (int i = 0; i < attributes.size(); ++i){
		if (attName == attributes[i].getName()){
			spot = i;
		}
	}
	switch (condition){
	case 'w'://for ==
		for (vector<Entry> ents : tuples)
		{
			if (ents[spot].getData() == entryValue)
			{
				selectTuples.push_back(ents);
			}
		}
		break;
	case 't'://for !=
		for (vector<Entry> ents : tuples)
		{
			if (ents[spot].getData() != entryValue)
			{
				selectTuples.push_back(ents);
			}
		}
		break;
	case '<':
		for (vector<Entry> ents : tuples)
		{
			if (ents[spot].getData() < entryValue)
			{
				selectTuples.push_back(ents);
			}
		}
		break;
	case 'y'://for <=
		for (vector<Entry> ents : tuples)
		{
			if (ents[spot].getData() <= entryValue)
			{
				selectTuples.push_back(ents);
			}
		}
		break;
	case '>':
		//as <- select (years > 3) animals;
		for (vector<Entry> ents : tuples)
		{
			if (ents[spot].getData() > entryValue)
			{
				selectTuples.push_back(ents);
			}
		}
		break;
	case 'u'://for >=
		for (vector<Entry> ents : tuples)
		{
			if (ents[spot].getData() >= entryValue)
			{
				selectTuples.push_back(ents);
			}
		}
		break;
	}
	
	return selectTuples;
}

vector<Attribute> Relation::projection(vector<string> attrProj){
	//return a subset of the attributes
	vector<Attribute> projValues;
	for(Attribute atr : attributes)
	{
		for(string str : attrProj)
		{
			if(atr.getName() == str)
			{
				projValues.push_back(atr);
			}
		}
	}
	return projValues;
}
/* ========================================================================= */

/* ========================= Operator Overloads ============================ */
ostream& operator<<(ostream& os, Relation& obj){
	os << "Relation : " << obj.relationName << endl;
	os << "Primary Keys : ";
	for (int i = 0; i < obj.primaryKeys.size(); ++i){
		os << obj.primaryKeys[i];
		if (i < (obj.primaryKeys.size() - 1)){
			os << ", ";
		}
	}
	os << "\nAttributes : " << endl;
	for (int i = 0; i < obj.attributes.size(); ++i){
		os << obj.attributes[i] << endl;
	}
	return os;
}

Relation& Relation::operator=(const Relation& other){
	if (this != &other){
		this->relationName = other.relationName;
		this->attributes = other.attributes;
	}
	return *this;
}

bool operator<(Relation& lhs, Relation& rhs) {
	if (lhs.relationName < rhs.relationName){
		return true;
	}
	else if (lhs.relationName == rhs.relationName){
		if (lhs.attributes.size() < rhs.attributes.size()){
			return true;
		}
	}
	return false;
}

bool operator>(Relation& lhs, Relation& rhs){
	return (rhs < lhs);
}

bool operator<=(Relation& lhs, Relation& rhs){
	return !(lhs > rhs);
}

bool operator>=(Relation& lhs, Relation& rhs){
	return !(lhs < rhs);
}

bool operator==(Relation& lhs, Relation& rhs){
	if (lhs.relationName == rhs.relationName){
		for (int i = 0; i < lhs.attributes.size(); ++i){
			if (lhs.attributes[i] != rhs.attributes[i]){
				return false;
			}
		}
	}
	else {
		return false;  
	}
	return true;
}

bool operator!=(Relation& lhs, Relation& rhs){
	return !(lhs == rhs);
}

/* ========================================================================= */
