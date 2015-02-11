#ifndef _record_h_                   // include file only once
#define _record_h_
#include <string>
#include <vector>

using namespace std;

class Record{
public:
	Record(){}
	//constructors go here!

	//needs set and get functions

	Record& operator=(const Record& rhs){
		values = rhs.values;
		return *this;
	}

private:
	vector<string> values;
};
#endif