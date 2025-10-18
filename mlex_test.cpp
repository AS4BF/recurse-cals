#include <variant>
#include <deque>
#include <memory>
#include <string>
#include <iostream>
#include "./Lexer/lexer.h"
#include "./MLexer/mlexer.h"
#include "./Parser/parser.h"
#include "./MParser/mparser.h"
#include "./types/node.h"

using vT = std::variant<int, double, char>;
using std::string;
using std::deque;
using std::cout;
using std::endl;
using std::unique_ptr;

template<typename T>
void PrintTree(const unique_ptr<Node<T>>& tree){

	bool isbkt = tree->left != nullptr && tree->right != nullptr;

	if(isbkt){ cout << '['; }

	std::visit([](auto value) { cout << ' ' << value; }, tree->data);

	if(tree->left != nullptr){ PrintTree(tree->left); }

	if(tree->right != nullptr){ PrintTree(tree->right); }

	if(isbkt){ cout << ']'; }

}





int main(){
	std::unique_ptr<Lexer<int, double, char>> Math = std::make_unique<mlex::MLexer<int, double, char>>(mlex::MLexer<int, double, char>());
	
	string exp;	
	std::cin >> exp;
	
	auto res = make_unique<deque<vT>>(Math->lexe(&exp));
	std::unique_ptr<Parser<int, double, char>> mp = std::make_unique<MParser<int, double, char>>();

	unique_ptr<Node<vT>> tree = std::make_unique<Node<vT>>(mp->parse(std::move(res)));
	PrintTree<vT>(tree);
};

