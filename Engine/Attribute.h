#ifndef _attr_h_                   // include file only once
#define _attr_h_
#include <string>
#include <vector>

using namespace std;

class Attribute{
public:
	Attribute(string i_name, string i_type){
		name = i_name;
		type = i_type;
	}
	//constructors go here!

	//needs set and get functions
	string get_name(){return name;}
	string get_type(){return type;}
	Attribute& operator=(const Attribute& rhs){
		name = rhs.name;
		type = rhs.type;
		return *this;
	}
	bool operator==(const X& lhs, const X& rhs){ 
		if(lhs.get_name() == rhs.get_name())
			if(lhs.get_type() == rhs.get_type())
				return true;
		return false;
	}
private:
	string type;
	string name;
};
#endif
