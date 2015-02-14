#ifndef _record_h_                   // include file only once
#define _record_h_

#include <string>
#include <vector>

using namespace std;

class Record{
public:

	//constructors
	
	Record(){}
	Record(vector<string> r){values = r;}

	//get + set functions
	
	vector<string> get_values() const {return values;}
	string get_entry(int index){return values[index];}
	int get_size() const {return values.size();}
	void set_val(vector<string> r){values = r;}
	
	//entry functions
	
	//adds a entry
	void add_entry(string new_entry){
		values.push_back(new_entry);
	}
	
	//removes entry
	void remove_entry(int index){
		if(index >= 0 && index < values.size())
			values.erase(values.begin() + index);
	}
	
	//overloading assignment operator for record class
	Record& operator=(const Record& rhs){
		values = rhs.values;
		return *this;
	}


private:
	vector<string> values;
};

//overloading equals-equals operator for record class
inline bool operator==(const Record& lhs, const Record& rhs){
		if(lhs.get_size() == rhs.get_size()){
			for(int i = lhs.get_values().size(); i > 0; i--)
			{
				if(lhs.get_values()[i] != rhs.get_values()[i])
					return false;
			}
			return true;
		}
		return false;
}
#endif
