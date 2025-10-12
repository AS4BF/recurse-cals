#include "calculator.h"
using PairVector = std::vector<std::pair<char, std::variant<int, double, char>>>;
using vI = PairVector::const_iterator; 
using oT = std::variant<int, double>;

oT Calculator::decide(vI start, vI end) {
	this->it = start;
	this->end = end;

	oT result = this->expr();
	
	return result;
};

inline bool Calculator::is_end(){
	return !(it < end);
};

inline bool Calculator::is_next(){
	return (it->first == 'n' || it->first == '(' || it->first == ')');
};

oT Calculator::expr(){
	oT left;
	oT right;

	if(is_next()){ left = term(); };

	if(is_end()){ goto end; };

	if(it->first == '+'){
		it++;
		right = expr();
		left += right;
	} else if(it->first == '-') {
		it++;
		right = expr();
		left += right;	
	};

	end:
	return left;
};

oT Calculator::term() {
	oT left;
	oT right;

	if(is_next()){ left=fact(); };

	if(is_end()){ goto end; };

	if(it->first = '*'){
		it++;
		right = term();
		left = *= right;
	} else if(it->first = '/') {
		it++;
		right = term();
		left *= right;
	};

	end:
	return left;
};

oT Calculator::fact(){
	oT left;
	
	if(it->first == 'n'){
		left = it->second;
		it++;	
	} else if(it->first == '(') {
		it++;
	       	left = expr();	
	};

	if(it->first == ')'){ it++; }; 

	return left;
};

