#include <memory>
#include <variant>
#include <iostream>
#include "operation.h"
#include "boolop.h"

using std::variant;
using std::visit;
using std::unique_ptr;
using dP = unique_ptr<variant<int, double, char>>;
using std::move;
using std::make_unique;
using vT = variant<int, double, char>;


struct Node{
	dP data;
	unique_ptr<Node> left;
	unique_ptr<Node> right;	

	Node(dP value, unique_ptr<Node> left = nullptr, unique_ptr<Node> right = nullptr) : data(move(value)), left(move(left)), right(move(right)){};
	
	~Node(){
		data.reset();
		left.reset();
		right.reset();
	};
};

variant<int, double, char> func(Node& token){
	variant<int, double, char> res;
	if(is_char(*token.data)){
		if(is_add(*token.data)){
			res = visit(Add{}, func(*token.left), func(*token.right));
		} else if(is_sub(*token.data)) {
			res = visit(Sub{}, func(*token.left), func(*token.right));
		} else if(is_mul(*token.data)) {
			res = visit(Mul{}, func(*token.left), func(*token.right));
		} else if(is_div(*token.data)) {	
			res = visit(Div{}, func(*token.left), func(*token.right));
		};
	} else { return *token.data; };
		return res;
	
};
	



int main(){
	auto right = make_unique<Node>(make_unique<vT>(1));
	auto left = make_unique<Node>(make_unique<vT>('*'), make_unique<Node>(make_unique<vT>(2)), make_unique<Node>(make_unique<vT>(2)));
	Node head(make_unique<variant<int, double, char>>('+'), move(left), move(right));
	std::variant<int, double, char> result = func(head);
	visit([](auto value){ std::cout << value << std::endl;}, result);
};
