#ifndef TOKEN_H
#define TOKEN_H

#include "Headers.h"

class Token {

public:
	char kind;        // what kind of token
	double value;     // for numbers: a value 
	string name;
	Token() {}
	Token(char ch) : kind(ch), value(0) { } // make a Token from a char
	Token(char ch, string s) : kind(ch), name(s) {}
	Token(char ch, double val) : kind(ch), value(val) { } // make a Token from a char and a double
};

#endif /* TOKEN_H */
