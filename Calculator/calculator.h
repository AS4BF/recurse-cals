#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <vector>
#include <utility>
#include <iostream>
#include <variant>


using std::pair;
using std::string;
using std::variant;
using std::vector;
using PairVector = std::vector<std::pair<char, std::variant<int, double, char>>>;
using vI = PairVector::iterator;
using oT = std::variant<int, double>;

class Calculator
{
private:
	vI it;
       	vI end;
	oT result;	
public:
	void init(vI start, vI end);	
	oT expr();	
	oT term();
	oT fact();
};

#endif
