#include <memory>
#include <variant>
#include "./types/node.h"
#include "./types/bitree.h"
#include <iostream>
#include "./Parser/parser.h"
#include "./MParser/mparser.h"
#include "./Lexer/lexer.h"
#include "./MLexer/mlexer.h"
#include "./boolop.h"
#include "./operation.h"
#include <deque>

using std::unique_ptr;
using std::make_unique;
using std::cout;
using std::cin;
using std::endl;
using vT = std::variant<int, double, char>;
using std::visit;
using std::deque;
using node = Node<vT, BiNode<vT>>;

void PrintNode(unique_ptr<node>& tree){
	if(std::holds_alternative<char>(tree->data))
		cout << '[';
	visit([](auto& value){ cout << value << ' '; }, tree->data);	
	if(tree->refs.left != nullptr) { PrintNode(tree->refs.left); }
	if(tree->refs.right != nullptr) { PrintNode(tree->refs.right); }
	if(std::holds_alternative<char>(tree->data))
		cout << ']';
};

vT solve(const unique_ptr<node>& tree){
	vT res;
	if(std::holds_alternative<char>(tree->data)){
		if(is_add(tree->data))
		{ res = visit(Add{}, solve(tree->refs.left), solve(tree->refs.right)); }
		else if(is_sub(tree->data))
		{ res = visit(Sub{}, solve(tree->refs.left), solve(tree->refs.right)); }
		else if(is_mul(tree->data))
		{ res = visit(Mul{}, solve(tree->refs.left), solve(tree->refs.right)); }
		else if(is_div(tree->data))
		{ res = visit(Div{}, solve(tree->refs.left), solve(tree->refs.right)); }
	} else {
		res = tree->data;
	}	
	return res;	
};

int main(){
	auto lexer = make_unique<mlex::MLexer<int, double, char>>();
	auto parser = make_unique<MParser<int, double, char>>();
	std::string expression;
	cin >> expression;
	auto lexems = make_unique<deque<vT>>(lexer->lexe(&expression));
	auto res = make_unique<node>(parser->parse(std::move(lexems)));
	PrintNode(res);
	vT answer = solve(res);	
	cout << endl;
	visit([](auto& value){ cout << value; }, answer);
	cout << endl;
		
}
