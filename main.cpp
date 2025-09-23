#include <iostream>
#include <list>
#include <variant>
#include <utility>
#include <string>
#include <vector>
#include "tokenizer.h"
#include "mathtok.h"

using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::string;
using PairVector = std::vector<pair<string, std::variant<int, double, char>>>;


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
	
	delete tok;
};
