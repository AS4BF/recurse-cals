#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <utility>
#include <queue>
#include <iostream>
#include <variant>
#include <memory>
#include <type_traits>


using std::string;
using std::variant;
using std::visit;
using varQue = std::queue<std::variant<int, double, char>>;
using oT = std::variant<int, double, char>;
using std::common_type;

//struct Operation{
	template <typename T1, typename T2>
	struct Add
	{ typename common_type<T1, T2>::type operator()(T1&& l, T2&& r){return l+r;}; };
	template <typename T1, typename T2>
	struct Sub
	{ typename common_type<T1, T2>::type operator()(T1&& l, T2&& r){return l-r;}; };
	template <typename T1, typename T2>
	struct Mul
	{ typename common_type<T1, T2>::type operator()(T1&& l, T2&& r){return l*r;}; };
	template <typename T1, typename T2>
	struct Div
	{ typename common_type<T1, T2>::type operator()(T1&& l, T2&& r){return l/r;}; };
//};

class Calculator
{
private:
	std::unique_ptr<varQue> exp;

	oT expr(); 
        oT term();
        oT fact();

	inline bool is_lbkt() const;
	inline bool is_rbkt() const;
	inline bool is_char() const;
	inline bool is_add() const;
	inline bool is_sub() const;
	inline bool is_mul() const;
	inline bool is_div() const;
public:
	oT decide(std::unique_ptr<varQue> exp);	 		
};

#endif
