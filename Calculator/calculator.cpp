#include "calculator.h"
using PairVector = std::vector<std::pair<char, std::variant<int, double, char>>>;
using vI = PairVector::iterator; 
using oT = std::variant<int, double>;

void Calculator::init(vI start, vI end) {
	this->it = start;
	this->end = end;
};

oT Calculator::expr(){
	oT left;
	oT right;
	bool its_term = (it->first == 'n' || it->first == '(' || it->first == ')');	
	if(its_term){
		left = term();	
	};	
	bool no_end = it < end;
	if(no_end){
		if(it->first == '+'){
			it++;
			right = expr();
			left += right;
		} else if(it->first == '-') {
			it++;
			right = expr();
			left += right;	
		};
	};	
	return left;
};

oT Calculator::term() {
	oT left;
	oT right;
	bool its_term = (it->first == 'n' || it->first == '(' || it->first == ')');
	if(its_term){
		left=fact();
	};
	bool no_end = it<end;
	if(no_end){
		if(it->first = '*'){
			it++;
			right = term();
			left = *= right;
		} else if(it->first = '/') {
			it++;
			right = term();
			left *= right;
		};
	};
	return left;
};

oT Calculator::fact(){
	oT left;
	if(it->first == 'n'){
		return it->second;	
	} else if(it->first == '(') {
		it++;
	       	left = expr();	
	}; 
	if(it->first == ')') {
		it++;
	}; 

	return left;
};

