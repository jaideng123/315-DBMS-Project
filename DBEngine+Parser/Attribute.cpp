#include "Attribute.h"

/* ===================== Constructor/Destructor ============================ */

Attribute::Attribute(){
	attributeName = "";
}

Attribute::Attribute(string name){
	attributeName = name;
}

Attribute::Attribute(string name, int max){
	attributeName = name;
	maxLength = max;
}

Attribute::~Attribute(){

}

/* ========================================================================= */

/* ======================== Helper Functions =============================== */

void Attribute::addEntry(string entData){
	if ((entData.length() <= maxLength) || (maxLength == -1)){
		entries.push_back(Entry(entData));
	}
	else{
		cout << "Error : Entry length must be less than " << maxLength <<
			" characters long." << endl;
	}
}

void Attribute::addEntry(Entry ent){
	if (ent.getData().length() <= maxLength){
		entries.push_back(ent);
	}
	else{
		cout << "Error : Entry length must be less than " << maxLength <<
			" characters long." << endl;
	}
}

void Attribute::removeEntry(string entData){
	//removes entry from attribute given its data
	for (int i = 0; i < entries.size(); ++i){
		if (entries[i].getData() == entData){
			entries.erase(entries.begin() + i);
			return;
		}
	}
	cout << "Error in removeEntry() in Attribute.cpp :: " <<
						entData << " is not in attribute." << endl;
}

void Attribute::removeEntry(int index){
	//removes entry from attribute given its index

	if (index < entries.size()){
		entries.erase(entries.begin() + index);
		return;
	}

	cout << "Error in removeEntry() in Attribute.cpp :: " <<
		index << " is not in range of the entries vector." << endl;
}

Entry& Attribute::getEntry(string entData){
	for (int i = 0; i < entries.size(); ++i){
		if (entries[i].getData() == entData){
			return entries[i];
		}
	}
	cout << "Error in getEntry() in Attribute.cpp :: " <<
				entData << " is not in the attribute." << endl;
	//add: message for entry not in attribute
}

/* ========================================================================= */

/* ========================= Operator Overloads ============================ */

ostream& operator<<(ostream& os, Attribute& obj){
	os << obj.attributeName << " : ";
	for (int i = 0; i < obj.entries.size(); ++i){
		os << obj.entries[i].getData();
		if (i != (obj.entries.size() - 1)){
			os << ", ";
		}
	}
	return os;
}

Attribute& Attribute::operator=(const Attribute& other){
	if (this != &other){
		this->attributeName = other.attributeName;
		this->entries = other.entries;
	}
	return *this;
}

bool operator<(Attribute& lhs, Attribute& rhs) {
	if (lhs.attributeName < rhs.attributeName){
		return true;
	}
	return false;
}

bool operator>(Attribute& lhs, Attribute& rhs){
	return (rhs < lhs);
}

bool operator<=(Attribute& lhs, Attribute& rhs){
	return !(lhs > rhs);
}

bool operator>=(Attribute& lhs, Attribute& rhs){
	return !(lhs < rhs);
}

bool operator==(Attribute& lhs, Attribute& rhs){
	if (lhs.attributeName == rhs.attributeName){
		return true;
	}
	return false;
}

bool operator!=(Attribute& lhs, Attribute& rhs){
	return !(lhs == rhs);
}

/* ========================================================================= */