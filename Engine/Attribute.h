#ifndef _attr_h_                   // include file only once
#define _attr_h_
#include <string>
#include <vector>

using namespace std;

class Attribute{
public:
	Attribute(){}
	//constructors go here!

	//needs set and get functions
	Attribute& operator=(const Attribute& rhs){
	name = rhs.name;
	return *this;
}
private:
	string type;
	string name;
};
#endif