#include "calculator.h"

using varStack = std::stack<std::variant<int, double, char>>;
using std::get;
using oT = std::variant<int, double, char>;
using std::string;



oT Calculator::decide(std::unique_ptr<varStack>&& exp) {
	this->exp = std::move(exp);
	try { 
		oT result = this->expr();
		this->exp.reset();
		return result;
	}
	catch(const string& error) { this->exp.reset(); throw error; };	
};



inline bool Calculator::is_lbkt() const{
	return is_char() && get<char>(exp->top()) == '(';
};

inline bool Calculator::is_rbkt() const {
	return is_char() && get<char>(exp->top()) == ')';
};

inline bool Calculator::is_char() const {
	return exp->top().index() == 2;	
};

inline bool Calculator::is_add() const {
	return is_char() && get<char>(exp->top()) == '+';
};

inline bool Calculator::is_sub() const {
	return is_char() && get<char>(exp->top()) == '-';
};

inline bool Calculator::is_mul() const {
	return is_char() && get<char>(exp->top()) == '*';
};

inline bool Calculator::is_div() const {
	return is_char() && get<char>(exp->top()) == '/';
};


oT Calculator::expr(){

	try{
		oT right = term();

		if(exp->empty()){ return right; };
		oT left;
		if(is_add()){
			exp->pop();
			left = expr();
			right = visit(Add{}, left, right);
		} else if(is_sub()) {
			exp->pop();
			left = expr();
			right = visit(Sub{}, left, right);	
		};

		return right;
	} catch (const string& error) { throw error; };
};

oT Calculator::term() {

	try{
		oT right = fact();
		if(exp->empty()){ return right; };	
		oT left;
		if(is_mul()){ 
			exp->pop();
			left = term();
			right = visit(Mul{}, left, right); 
		} else if(is_div()){
			exp->pop();
			left = term();
			if(visit(is_null{}, right)) { throw string("Division by zero"); };
			right = visit(Div{}, left, right); 
		};

		return right;
	} catch (const string& error) { throw error; };
};

oT Calculator::fact(){
	
	/* if(is_lbkt() || !is_rbkt() || exp->empty() ) { 
		throw string("Invalid syntax");	
	};	*/
		
	oT left;
	if(exp->empty()){
		throw string("Invalid syntax");		
	} else if(!is_char()) {
		left = exp->top();
		exp->pop();
	} else if(is_rbkt()) {
		exp->pop();
		try { left = expr(); }	
		catch (const string& error){ throw error; };

		if(is_lbkt()){
		       	exp->pop();
		} else { throw string("Invalid expression inside (...)");};
	} else { throw string("Invalid syntax"); };
	return left;
};

