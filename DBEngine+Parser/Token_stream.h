#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include "Headers.h"
#include "Token.h"

class Token_stream {
private:
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using putback()

public:
	Token_stream();   // make a Token_stream that reads from cin
	Token get();      // get a Token (get() is defined elsewhere)
	void putback(Token t);    // put a Token back
	void ignore(char c);
};


const char newLine = ';'; // used to print the value at any time
const char number = '8'; // used to represent a number
const char name = 'a'; // used to represent a letter
const char Literal = 'b';

const string createTable = "CREATE TABLE";
const char cr = '!';

const string open = "OPEN";
const char op = '@';

const string close = "CLOSE";
const char cl = '#';

const string write = "WRITE";
const char wr = '$';

const string Exit = "EXIT";
const char quit = '?';

const string show = "SHOW";
const char sh = '%';

const string primaryKey = "PRIMARY KEY";
const char pk = '^';

const string update = "UPDATE";
const char up = '&';

const string setA = "SET";
const char se = '_';

const string Where = "WHERE";
const char wh = '[';

const string insertInto = "INSERT INTO";
const char inInto = ']';

const string valuesFrom = "VALUES FROM";
const char vf = '{';

const string valuesFromRel = "VALUES FROM RELATION";
const char vfr = '}';

const string deleteFrom = "DELETE FROM";
const char df = '>';

const string Query = "<-";
const char qu = '<';

const string sele = "select";
const char sel = '/';

const string proj = "project";
const char pro = '|';

const string rena = "rename";
const char ren = '\\';

const string unio = "UNION";
const char uni = '+';

const string diff = "DIFFERENCE";
const char dif = '-';

const string prdct = "PRODUCT";
const char prod = '*';

const string integer = "INTEGER"; 
const char integ = 's';

const string varchar = "VARCHAR";
const char varc = 'q';

const string equalsequals = "==";
const char eqeq = 'w';

const string notequals = "!=";
const char noteq = 't';

const string lessequal = "<=";
const char leq = 'y';

const string greatequal = ">=";
const char geq = 'u';

const char conj = 'p'; // for conjunction '&&'

const char disuni = 'l'; // for disunion '||'

const char deleteTuples = 'h';

const char deleteAttributes = 'k';

#endif /* TOKEN_STREAM_H */
