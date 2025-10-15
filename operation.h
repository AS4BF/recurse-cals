#ifndef	OPERATION_H 
#define	OPERATION_H 
#include <variant>
#include <memory>


using std::variant;
using std::visit;
using oT = std::variant<int, double, char>;

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
	oT operator()(T1&& l, T2&& r){return l/r;};
      	
	oT operator()(int& l, int& r){return static_cast<double>(l)/r;}; 
};


#endif
