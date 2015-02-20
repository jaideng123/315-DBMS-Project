#ifndef _token_h_                   // include file only once
#define _token_h_

#include <string>

using namespace std;

class Token{
public:
	enum Token_Type {IDENTIFIER,TABLE,OPEN,CLOSE,WRITE,CREATE,INSERT,SHOW,
						UPDATE,DELETE,SELECT,UNION,DIFF,PRODUCT,PROJECT,
						RENAME,LEFTPAREN,RIGHTPAREN,PRIMARY,KEY,INTO,VALUES,
						FROM,LEFTARROW,EQUALSIGN,EQ,LT,LEQ,GT,SET,GEQ,NEQ,AND,OR,
						WHERE,COMMA,SEMICOLON,NUMBER,VARCHAR,INTEGER,RELATION,
						LITERAL,EXIT};
	Token(Token_Type itype,string val){
		type = itype;
		value = val;
	}					
	
	string get_value(){return value;}
	Token_Type get_type(){return type;}
private:
	Token_Type type;
	string value;
};

#endif
