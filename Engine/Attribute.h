#ifndef _attr_h_                   // include file only once
#define _attr_h_
#include <string>
#include <vector>

using namespace std;

class Attribute{
public:
	Attribute& operator=(const Attribute& rhs);
	Attribute(){}
	//constructors go here!

	//needs set and get functions

private:
	string type;
	string name;
};

Attribute& Attribute::operator=(const Attribute& rhs){
	name = rhs.name;
	return *this;
}
#endif