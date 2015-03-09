#include "Token_stream.h"

//=============================================================================

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream() : full(false), buffer(0){    // no Token in buffer

}

//=============================================================================

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t){
	if (!full){
		buffer = t;       // copy t to buffer
		full = true;      // buffer is now full
	}
}

//=============================================================================

Token Token_stream::get(){
	
	if (full) {       // do we already have a Token ready?
		// remove token from buffer
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
	case ';':    // for "newLine"
	case '?':    // for "quit"
	case '(': case ')': case ',':
	case uni: case dif: case prod:
		return Token(ch);        // let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;              // read a floating-point number
		return Token('8', val);   // let '8' represent "a number"
	}
	case '<':
	{
		if (cin.get(ch) && (ch == '-')){//<- case
			return Token(qu);
		}
		else if (ch == '='){//<= case
			return Token(leq);
		}
		else{
			cin.putback(ch);
			return Token('<');//else represent itself
		}
	}
	case '>':
	{
		if (cin.get(ch) && (ch == '=')){//>= case
			return Token(geq);
		}
		else{
			cin.putback(ch);
			return Token('>');//else represent itself
		}
	}
	case '=':
	{
		if (cin.get(ch) && (ch == '=')){//== case
			return Token(eqeq);
		}
		else{
			cin.putback(ch);
			return Token('=');//else represent itself
		}
	}
	case '!':
	{
		if (cin.get(ch) && (ch == '=')){//!= case
			return Token(noteq);
		}
		else{
			cin.putback(ch);
			return Token('!');//else represent itself
		}
	}
	case '&':
	{
		if (cin.get(ch) && (ch == '&')){//&& case
			return Token(conj);
		}
		else{
			cin.putback(ch);
			return Token('&');//else represent itself
		}
	}
	case '|':
	{
		if (cin.get(ch) && (ch == '|')){//|| case
			return Token(disuni);
		}
		else{
			cin.putback(ch);
			return Token('|');//else represent itself
		}
	}
	default:
		if (isalpha(ch) || ch == '_' || ch == '"') {
			string s;
			bool isLiteral = false;
			if (ch != '"'){
				s += ch; // apends the ch onto the string s
			}
			else{ isLiteral = true; }
			if (isLiteral){
				while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_' || ch == '"' || isspace(ch)) || ch == '/' || ch == '.' || ch == ':' || ch == '\'' || ispunct(ch)){
					if (ch != '"'){
						s += ch;
					}
					else if(ch =='"'){
						cin.get(ch);
						break;
					}
				}
			}
			else{
				while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_' || ch == '"')){
					if (ch != '"'){
						s += ch;
					}
				}
			}
			if (ch == ' ' && (s == "CREATE" || s == "INSERT" || s == "PRIMARY" || s == "VALUES" || s == "DELETE")){
				s += " ";
				while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			}
			cin.putback(ch);
			
			if (s == createTable) return Token(cr);
			if (s == "RELATION") return Token(vfr);
			if (s == Query) return Token(qu);
			if (s == integer) return Token(integ);
			if (s == varchar) return Token(varc);
			if (s == open) return Token(op);
			if (s == close) return Token(cl);
			if (s == write) return Token(wr);
			if (s == show) return Token(sh);
			if (s == primaryKey) return Token(pk);
			if (s == update) return Token(up);
			if (s == setA) return Token(se);
			if (s == Where) return Token(wh);
			if (s == insertInto) return Token(inInto);
			if (s == valuesFrom) return Token(vf);
			if (s == deleteFrom) return Token(df);
			if (s == proj) return Token(pro);
			if (s == sele) return Token(sel);
			if (s == rena) return Token(ren);
			if (s == Exit) return Token(quit);
			if (isLiteral) return Token(Literal, s);
			
			return Token(name, s);
		}
	}
}

//=============================================================================

void Token_stream::ignore(char c){
	// this function finds a value that is not defined and ignores it
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch = 0;
	while (cin >> ch)
		if (ch == c) return;
}

//=============================================================================
