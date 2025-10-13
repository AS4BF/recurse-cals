#include "mathtok.h"
#include <iostream>

using varQue = std::queue<std::variant<int, double, char>>;
using std::string;
using std::cerr;
using std::endl;


std::variant<int, double, char> tokenmath::MathTok::parseNumber(){ 
	bool is_float = false;
	string number = "";
	while(it < end && (std::isdigit(*it) || *it == '.' || *it == ',')) {
		if((*it == '.' || *it == ',') && it < end-1 && !is_float){
			is_float = true;
			number.push_back('.');
		} else if(std::isdigit(*it)) { 
			number.push_back(*it);
		} else { throw string("Invalid number"); }
		it++;
	};
	it--;
	if(!is_float){
		return std::stoi(number);
	} else {
		return std::stod(number);
	};
};



varQue tokenmath::MathTok::tokenize(const string* expression) {
	varQue tokens;
	
	this->it = expression->begin(); 
	this->end = expression->end();
	
	while(it < end) {

		if(std::isdigit(*it)){
			tokens.push(parseNumber());
		} else if(*it == Operation::Sub){
			tokens.push(Operation::Sub);
		} else if(*it == Operation::Add){
			tokens.push(Operation::Add);
		} else if(*it == Operation::Mul) {
			tokens.push(Operation::Mul);
		} else if(*it == Operation::Div) {
			tokens.push(Operation::Div);
		} else if(*it == Operation::Lbkt) {
			tokens.push(Operation::Lbkt);
		} else if(*it == Operation::Rbkt) {
			tokens.push(Operation::Rbkt);
		};
		it++;
	};
	
	return tokens;
};
	/*
	 * for(auto it = expression->begin(); it < expression->end(); ++it){
		char c = *it;
		switch(c){
			case static_cast<char>(Operation::Add):
				tokens.push("add", c);
				break;
			case static_cast<char>(Operation::Sub):
				tokens.push("sub", c);
				break;
			case static_cast<char>(Operation::Mul):
				tokens.push("mul", c);
				break;
			case static_cast<char>(Operation::Div):
				tokens.push("div", c);
				break;
			case static_cast<char>(Operation::lbkt):
				tokens.push("lbkt", c);
				break;
			case static_cast<char>(Operation::rbkt):
				tokens.push("rbkt", c);
				break;
			default:
				bool is_float = false;
				string num = "";
				/* if(std::isdigit(c)){
					while(it < expression->end()){
						num.push_back(*it);
						if(std::isdigit(*(it+1))){
							it++;		
						} else if {
							
						} else {
							break;
						};
					}; 
				} else {
					std::cerr << "incorrect expression";
					break;
				};
		
				if(!is_float){
					tokens.push("int", std::stoi(num));
				} else {
					tokens.push("double", std::stod(num));
				};
				break;
		
		}; */
