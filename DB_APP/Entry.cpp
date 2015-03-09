#include "Entry.h"

/* ===================== Constructor/Destructor ============================ */

Entry::Entry(){
	entryData = "";
}

Entry::Entry(string data){
	entryData = data;
}

Entry::~Entry(){

}

/* ========================================================================= */

/* ========================= Operator Overloads ============================ */

ostream& operator<<(ostream& os, Entry& obj){
	os << obj.entryData << endl;
	return os;
}

Entry& Entry::operator=(const Entry& other){
	if (this != &other){
		this->entryData = other.entryData;
	}
	return *this;
}

bool operator<(Entry& lhs, Entry& rhs){
	if (lhs.entryData < rhs.entryData){
		return true;
	}
	return false;
}

bool operator>(Entry& lhs, Entry& rhs){
	return (rhs < lhs);
}

bool operator<=(Entry& lhs, Entry& rhs){
	return !(lhs > rhs);
}

bool operator>=(Entry& lhs, Entry& rhs){
	return !(lhs < rhs);
}

bool operator==(Entry& lhs, Entry& rhs){
	if (lhs.entryData == rhs.entryData){
		return true;
	}
	return false;
}

bool operator!=(Entry& lhs, Entry& rhs){
	return !(lhs == rhs);
}

/* ========================================================================= */
