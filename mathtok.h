#ifndef MATHTOKENIZER_H
#define MATHTOKENIZER_H
#include "tokenizer.h"
#include <memory> 


namespace tokenmath {
	using PairVector = std::vector<std::pair<std::string, std::variant<int, double, char>>>;
	using std::string;
	class MathTok : public Tokenizer
	{	
		private:
			std::string::const_iterator it;
			std::string::const_iterator end;

			std::pair<string, std::variant<int, double, char>> parseNumber();
	
		public: 
			~MathTok() {};
			PairVector tokenize(const string* expression) override;
	};

};
#endif
