#include <iostream>
#include <variant>
#include <utility>
#include <string>
#include <queue>
#include "./Tokenizer/tokenizer.h"
#include "./MathTokenizer/mathtok.h"
#include "./Calculator/calculator.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using rT = std::variant<int, double, char>;
using varQue = std::queue<rT>;


int main(){
	string expression = "";

	cin >> expression;
	
	Tokenizer* tok = new tokenmath::MathTok();
       	auto plt = std::make_unique<varQue>(tok->tokenize(&expression));

	Calculator* calc = new Calculator();
	try {
		rT result = calc->decide(std::move(plt));
		std::visit([](const auto& value){cout << value << endl;}, result);
	} catch( string& error ) { cout << error; };

	delete calc;	
	delete tok;
};
