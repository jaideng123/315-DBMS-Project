#ifndef _record_h_                   // include file only once
#define _record_h_
#include <string>
#include <vector>

using namespace std;

class Record{
public:
	Record& operator=(const Record rhs);
	Record(){}
	//constructors go here!

	//needs set and get functions

private:
	vector<string> values;
};

Record& Record::operator=(const Record rhs){
	values = rhs.values;
	return *this;
}
#endif