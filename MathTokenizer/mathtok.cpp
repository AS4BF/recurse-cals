#include "mathtok.h"
#include <iostream>

using PairVector = std::vector<std::pair<char, std::variant<int, double, char>>>;
using std::string;
using std::cerr;
using std::endl;


std::pair<char, std::variant<int, double, char>> tokenmath::MathTok::parseNumber(){ 
	bool is_float = false;
	string number = "";
	while(it < end && (std::isdigit(*it) || *it == '.' || *it == ',')) {
		if((*it == '.' || *it == ',') && it < end-1 && !is_float){
			is_float = true;
			number.push_back('.');
		} else if(std::isdigit(*it)) { 
			number.push_back(*it);
		}
		it++;
	};
	it--;
	if(!is_float){
		return std::make_pair('n', std::stoi(number));
	} else {
		return std::make_pair('n', std::stod(number));
	};
};



PairVector tokenmath::MathTok::tokenize(const string* expression) {
	PairVector tokens;
	
	this->it = expression->begin(); 
	this->end = expression->end();
	
	while(it < end) {
		if(std::isdigit(*it)){
			tokens.emplace_back(parseNumber());
		} else if(*it == Operation::Sub){
			tokens.emplace_back(Operation::Sub, *it);		
		} else if(*it == Operation::Add){
			tokens.emplace_back(Operation::Add, *it);
		} else if(*it == Operation::Mul) {
			tokens.emplace_back(Operation::Mul, *it);
		} else if(*it == Operation::Div) {
			tokens.emplace_back(Operation::Div, *it);
		} else if(*it == Operation::Lbkt) {
			tokens.emplace_back(Operation::Lbkt, *it);
		} else if(*it == Operation::Rbkt) {
			tokens.emplace_back(Operation::Rbkt, *it);
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
				tokens.emplace_back("add", c);
				break;
			case static_cast<char>(Operation::Sub):
				tokens.emplace_back("sub", c);
				break;
			case static_cast<char>(Operation::Mul):
				tokens.emplace_back("mul", c);
				break;
			case static_cast<char>(Operation::Div):
				tokens.emplace_back("div", c);
				break;
			case static_cast<char>(Operation::lbkt):
				tokens.emplace_back("lbkt", c);
				break;
			case static_cast<char>(Operation::rbkt):
				tokens.emplace_back("rbkt", c);
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
					tokens.emplace_back("int", std::stoi(num));
				} else {
					tokens.emplace_back("double", std::stod(num));
				};
				break;
		
		}; */
