#ifndef _attr_h_                   // include file only once
#define _attr_h_

#include <string>
#include <vector>
#include <climits>
#include <stdexcept>

using namespace std;

class Attribute{
public:

	//constructors
	
	Attribute(string i_name, string i_type){
		name = i_name;
		if(i_type.substr(0,7) == "VARCHAR"){
			type = i_type;
			size_lim = find_size(i_type);
		}
		else if(i_type == "INTEGER"){
			type = i_type;
			size_lim = INT_MAX;
		}
		else if(i_type == "STRING"){
			type = i_type;
			size_lim = INT_MAX;
		}
		else
			throw runtime_error("Error: Type is not supported");
	}

	//set and get functions
	
	string get_name() const {return name;}
	string get_type() const {return type;}
	int get_size() const {return size_lim;}
	Attribute& operator=(const Attribute& rhs){
		name = rhs.name;
		type = rhs.type;
		return *this;
	}
	
private:
	int find_size(string t){
		string num = "";
		int index = t.size()-2;
		if(t[index+1] != ')')
			throw runtime_error("Error: VARCHAR requires valid size");
		char temp = t[index];
		while (temp != '('){
			if(!isdigit(temp))
				throw runtime_error("Error: VARCHAR requires valid size");
			num = temp + num;
			index--;
			temp = t[index];
		}
		if(num == "")
			throw runtime_error("Error: VARCHAR requires valid size");
		return stoi(num);
	}
	int size_lim;
	string type;
	string name;
};

inline bool operator==(const Attribute& lhs, const Attribute& rhs){
		if(lhs.get_name() == rhs.get_name())
			if(lhs.get_type() == rhs.get_type())
				return true;
		return false;
}
#endif
