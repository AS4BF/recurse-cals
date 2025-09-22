#include "mathtok.h"

using PairList = std::list<std::pair<std::string, int>>;
using std::string;
using tokenmath::Operation;

PairList tokenmath::MathTok::tokenize(const string* expression) const {
	PairList tokens;
	for(auto it = expression->begin(); it <= expression->end(); ++it){
		char c = *it;
		switch(c){
			case static_cast<char>(Operation::Add):
				tokens.emplace_back("add", static_cast<int>(c));
				break;
			case static_cast<char>(Operation::Sub):
				tokens.emplace_back("sub", static_cast<int>(c));
				break;
			case static_cast<char>(Operation::Mul):
				tokens.emplace_back("mul", c);
				break;
			case static_cast<char>(Operation::Div):
				tokens.emplace_back("div", c);
				break;
			case static_cast<char>(Operation::lbkt):
				tokens.emplace_back("lbkt", c);
				break;
			case static_cast<char>(Operation::rbkt):
				tokens.emplace_back("rbkt", c);
				break;
			default:
				if(std::isdigit(c)){
					string num = "";
					while(it < expression->end()){
						num.push_back(*it);
						if(std::isdigit(*(it+1))){
							it++;		
						} else {
							break;
						};
					};
					tokens.emplace_back("num", std::stoi(num));
				};
				break;
		};
	};	
	return tokens;
};
