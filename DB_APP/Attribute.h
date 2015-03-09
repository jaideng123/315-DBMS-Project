#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "Entry.h"



class Attribute
{
private:
	string attributeName;//can be an integer or string
	

	int maxLength = 0;//how long the Entries in a certain attribute can be

public:
	Attribute();
	Attribute(string name);
	Attribute(string name, int max);
	~Attribute();
	vector<Entry> entries;

	void setName(string attName) { attributeName = attName; }
	void addEntry(string entData);
	void addEntry(Entry ent);
	void removeEntry(string entData);
	void removeEntry(int index);

	int getNumEntries() { return entries.size(); }
	int getMaxLength() { return this->maxLength; }

	string getName() { return attributeName; }

	Entry& getEntry(string entData);
	Entry& getEntry(int index) { return entries[index]; }


	/* ================  OPERATOR OVERLOADS  ================= */

	Attribute& operator=(const Attribute& other);

	friend ostream& operator<<(ostream& os, Attribute& obj);
	friend bool operator<(Attribute& lhs, Attribute& rhs);
	friend bool operator>(Attribute& lhs, Attribute& rhs);
	friend bool operator<=(Attribute& lhs, Attribute& rhs);
	friend bool operator>=(Attribute& lhs, Attribute& rhs);
	friend bool operator==(Attribute& lhs, Attribute& rhs);
	friend bool operator!=(Attribute& lhs, Attribute& rhs);

	/* ======================================================= */
};

#endif /* ATTRIUBTE_H */
