#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <utility>
#include <stack>
#include <iostream>
#include <variant>
#include <memory>
#include <type_traits>


using std::string;
using std::variant;
using std::visit;
using varStack = std::stack<std::variant<int, double, char>>;
using oT = std::variant<int, double, char>;

//struct Operation{
	struct Add
	{ 
		template <typename T1, typename T2>
		oT operator()(T1&& l, T2&& r){return l+r;}; };
	struct Sub
	{ 
		template <typename T1, typename T2>
		oT operator()(T1&& l, T2&& r){return l-r;}; };
	struct Mul
	{
		template <typename T1, typename T2>
	       	oT operator()(T1&& l, T2&& r){return l*r;}; };
	struct Div
	{
		template <typename T1, typename T2>
	       	oT operator()(T1&& l, T2&& r){return l/r;}; };
//};

class Calculator
{
private:
	std::unique_ptr<varStack> exp;

	oT expr(); 
        oT term();
        oT fact();
	struct is_null {
		template<typename T>
		bool operator()(T& value) const {
			return value == 0;	
		};
	};	

	inline bool is_lbkt() const;
	inline bool is_rbkt() const;
	inline bool is_char() const;
	inline bool is_add() const;
	inline bool is_sub() const;
	inline bool is_mul() const;
	inline bool is_div() const;
public:
	oT decide(std::unique_ptr<varStack>&& exp);	 		
};

#endif
