#include <iostream>
#include <list>
#include <utility>
#include <string>
#include "tokenizer.h"
#include "mathtok.h"

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::pair;
using std::string;
using PairList = std::list<pair<string, int>>;

void printPairList(const list<pair<string, int>>& expr){
	for(const auto& p : expr){
		cout << p.first << '\t' << p.second << endl;
	};
};

int main(){
	string expression = "";

	cin >> expression;

	Tokenizer* tok = new tokenmath::MathTok();
       	PairList plt = tok->tokenize(&expression);
	printPairList(plt);
	
	delete tok;
};
