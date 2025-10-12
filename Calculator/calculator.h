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
using vI = PairVector::const_iterator;
using oT = std::variant<int, double>;

class Calculator
{
private:
	vI it;
       	vI end;
	oT result;

	oT expr(); 
        oT term();
        oT fact();

	inline bool is_end();
	inline bool is_next();
public:
	oT decide(vI start, vI end);	 		
};

#endif
