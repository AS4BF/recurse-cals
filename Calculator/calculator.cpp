#include "calculator.h"

using varQue = std::queue<std::variant<int, double, char>>;
using std::get;
using oT = std::variant<int, double, char>;
using std::string;



oT Calculator::decide(std::unique_ptr<varQue>&& exp) {
	this->exp = std::move(exp);
	try { 
		oT result = this->expr();
		this->exp.reset();
		return result;
	}
	catch(const string& error) { 
		std::cout << error;	
		this->exp.reset(); throw error; };	
};



inline bool Calculator::is_lbkt() const{
	return is_char() && get<char>(exp->front()) == '(';
};

inline bool Calculator::is_rbkt() const {
	return is_char() && get<char>(exp->front()) == ')';
};

inline bool Calculator::is_char() const {
	return exp->front().index() == 2;	
};

inline bool Calculator::is_add() const {
	return is_char() && get<char>(exp->front()) == '+';
};

inline bool Calculator::is_sub() const {
	return is_char() && get<char>(exp->front()) == '-';
};

inline bool Calculator::is_mul() const {
	return is_char() && get<char>(exp->front()) == '*';
};

inline bool Calculator::is_div() const {
	return is_char() && get<char>(exp->front()) == '/';
};


oT Calculator::expr(){

	try{
		oT left = term();

		if(exp->empty()){ return left; };
		oT right;
		if(is_add()){
			exp->pop();
			right = expr();
			left = visit(Add{}, left, right);
		} else if(is_sub()) {
			exp->pop();
			right = expr();
			left = visit(Sub{}, left, right);	
		};

		return left;
	} catch (const string& error) { throw error; };
};

oT Calculator::term() {

	try{
		oT left = fact();
		if(exp->empty()){ return left; };	
		oT right;
		if(is_mul()){ 
			exp->pop();
			right = term();
			left = visit(Mul{}, left, right); 
		} else if(is_div()){
			exp->pop();
			right = term();
			if(visit(is_null{}, right)) { throw string("Division by zero"); };
			left = visit(Div{}, left, right); 
		};

		return left;
	} catch (const string& error) { throw error; };
};

oT Calculator::fact(){
	
	/* if(is_lbkt() || !is_rbkt() || exp->empty() ) { 
		throw string("Invalid syntax");	
	};	*/
		
	oT left;		
	if(!is_char()){
		left = exp->front();
		exp->pop();
	} else if(is_lbkt()) {
		exp->pop();
		try { left = expr(); }	
		catch (const string& error){ throw error; };

		if(is_rbkt()){
		       	exp->pop();
		} else { throw string("Invalid expression inside (...)");};
	};
	return left;
};

