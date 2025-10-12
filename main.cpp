#include <iostream>
#include <list>
#include <variant>
#include <utility>
#include <string>
#include <vector>
#include "./Tokenizer/tokenizer.h"
#include "./MathTokenizer/mathtok.h"
#include "./Calculator/calculator.h"

using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::string;
using PairVector = std::vector<pair<char, std::variant<int, double, char>>>;
using rT = std::variant<int, double>;


void printPairList(const PairVector& expr){
	for(const auto& p : expr){
		std::visit([=](const auto& value){cout << p.first << '\t' << value  << endl; }, p.second);
	};
};

int main(){
	string expression = "";

	cin >> expression;

	Tokenizer* tok = new tokenmath::MathTok();
       	PairVector plt = tok->tokenize(&expression);

	printPairList(plt);

	Calculator* calc = new Calculator();

	rT result = calc->decide(plt.begin(), plt.end());
	std::visit([](const auto& value){cout << value << endl;}, result);
	delete calc;	
	delete tok;
};
