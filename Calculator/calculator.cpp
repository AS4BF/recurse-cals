#include "calculator.h"
using varQue = std::queue<std::variant<int, double, char>>;
using std::get;
using oT = std::variant<int, double, char>;
using std::string;



oT Calculator::decide(varQue exp) {

	try { oT result = this->expr(); }
	catch(const string& error) { std::cout << error << std::endl; };	
	return result;
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
			visit(Add{}, left, right);
		} else if(is_sub()) {
			exp->pop();
			visit(Sub{}, left, right);	
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
			visit(Mul{}, left, right); 
		} else if(is_div()){
			exp->pop();

			if(visit([](auto& value){return value == 0;}), right) { throw string("Division by zero"); };
			visit(Div{}, left, right); 
		};

		return left;
	} catch (const string& error) { throw error; };
};

oT Calculator::fact(){
	
	if(!is_lbkt() || !is_rbkt() || exp->empty()){  //add not a number
		throw string("Invalid syntax");	
	};	
		
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

