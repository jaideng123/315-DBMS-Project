#ifndef _record_h_                   // include file only once
#define _record_h_
#include <string>
#include <vector>

using namespace std;

class Record{
public:
	Record(){}
	Record(vector<string> r){values = r;}
	//constructors go here!

	//needs set and get functions
	vector<string> get_values(){return values;}

	string get_entry(int index){
		return values[index];
	}

	int get_size(){
		return values.size();
	}

	void set_val(vector<string> r){values = r;}


	Record& operator=(const Record& rhs){
		values = rhs.values;
		return *this;
	}

	void add_entry(string new_entry){
		values.push_back(new_entry);
	}
	
	void remove_entry(int index){
		if(index >= 0 && index < values.size())
			values.erase(values.begin() + index);
	}

private:
	vector<string> values;
};
#endif