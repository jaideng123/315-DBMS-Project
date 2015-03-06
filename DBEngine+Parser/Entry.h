#ifndef ENTRY_H
#define ENTRY_H
#include "Headers.h"


class Entry
{
private:
	string entryData;

public:
	Entry();
	Entry(string data);
	~Entry();

	void setData(string entName) { entryData = entName; }

	string getData() { return entryData; }

	Entry& operator=(const Entry& other);

	/* ================= Operator Overloads ================== */

	friend ostream& operator<<(ostream& os, Entry& obj);
	friend istream& operator>>(istream& is, Entry& obj);
	friend bool operator<(Entry& lhs, Entry& rhs);
	friend bool operator>(Entry& lhs, Entry& rhs);
	friend bool operator<=(Entry& lhs, Entry& rhs);
	friend bool operator>=(Entry& lhs, Entry& rhs);
	friend bool operator==(Entry& lhs, Entry& rhs);
	friend bool operator!=(Entry& lhs, Entry& rhs);
	
	/* ======================================================= */
};

#endif /* ENTRY_H */
