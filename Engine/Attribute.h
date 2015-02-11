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
	Attribute& operator=(const Attribute& rhs){
	name = rhs.name;
	return *this;
}
private:
	string type;
	string name;
};
#endif