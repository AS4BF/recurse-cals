#include <iostream>
#include <variant>
#include <string>
#include <stack>
#include <memory>
#include "./Tokenizer/tokenizer.h"
#include "./MathTokenizer/mathtok.h"
#include "./Calculator/calculator.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using rT = std::variant<int, double, char>;
using varStack = std::stack<rT>;


int main(){
	string expression = "";

	cin >> expression;
	
	Tokenizer* tok = new tokenmath::MathTok();
	try { 
		auto plt = std::make_unique<varStack>(tok->tokenize(&expression)); 

		Calculator* calc = new Calculator();
		rT result = calc->decide(std::move(plt));
		std::visit([](const auto& value){cout << value << endl;}, result);
		delete calc;
	} 
	catch( string& error ) { cout << error << endl; };

	delete tok;
};
