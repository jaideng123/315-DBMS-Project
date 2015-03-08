#ifndef RELATION_H
#define RELATION_H

#include "Attribute.h"


class Relation
{
private:
	string relationName;
	
	vector<string> primaryKeys;
	
	vector<vector<Entry> > tuples; //tuples of the relation
	vector<Attribute> attributes;
public:
	Relation();
	Relation(string name);
	Relation(string name, vector<string> keys);
	~Relation();
	
	//int getSize(){ return this->attributes[0].entries.size(); }

	/* ================= Helper Functions ==================== */

	void setName(string rName) { relationName = rName; }
	void addAttribute(string attName);
	void addAttribute(string attName, int type);
	void addAttribute(Attribute att);
	void addKey(string key){ primaryKeys.push_back(key); }
	void removeAttribute(string attName);
	void setTuples();
	void setKeys(vector<string> keys);
	vector<Attribute>& getAttributes(){ return attributes; }

	int getNumAttributes() { return attributes.size(); }
	int getNumKeys() { return primaryKeys.size(); }

	bool attributeExists(string attName);

	string getName() { return relationName; }
	string getKey(int index) { return primaryKeys[index]; }

	Attribute& getAttribute(string attName);
	Attribute& getAttribute(int index) { return attributes[index]; }

	/* ======================================================= */

	/* ================ Relational Algebra =================== */

	vector<vector<Entry> > selection(string entryValue, char condition, string attName);
	vector<Attribute> projection(vector<string> attrProj);

	/* ======================================================= */

	/* ================  OPERATOR OVERLOADS  ================= */

	Relation& operator=(const Relation& other);

	friend ostream& operator<<(ostream& os, Relation& obj);
	friend bool operator<(Relation& lhs, Relation& rhs);
	friend bool operator>(Relation& lhs, Relation& rhs);
	friend bool operator<=(Relation& lhs, Relation& rhs);
	friend bool operator>=(Relation& lhs, Relation& rhs);
	friend bool operator==(Relation& lhs, Relation& rhs);
	friend bool operator!=(Relation& lhs, Relation& rhs);

	/* ======================================================= */
};

#endif /* RELATION_H */
