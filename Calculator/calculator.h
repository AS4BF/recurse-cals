#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <vector>
#include <utility>
#include <iostream>


using std::pair;
using std::string;
using std::variant;
using std::vector;
using PairVector = std::vector<std::pair<std::string, std::variant<int, double, char>>>;

class Calculator
{
private:
	std::vector::iterator it;
	std::variant<int, double> result;
	void is_mul_or_div(){
		if(op == "+"){
			std::visit 	
		} else if(op == "-"){
		
		}
	};

	void is_add_or_sub(){

	};

	void is_lbkt_or_rbkt(string op){
		if(op == "("){
			std::visit([](){}, this->result)
		} else if (op == ")"){
			
		};
	};
		
public:
	


};

#endif
