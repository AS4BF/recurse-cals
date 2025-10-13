#ifndef MATHTOKENIZER_H
#define MATHTOKENIZER_H
#include "../Tokenizer/tokenizer.h"
#include <memory> 
#include <stack>


namespace tokenmath {
	using varStack = std::stack<std::variant<int, double, char>>;
	using std::string;
	enum Operation : char {Add='+', Sub='-', Mul='*', Div='/', Lbkt='(', Rbkt=')'};
	class MathTok : public Tokenizer
	{	
		private:
			std::string::const_iterator it;
			std::string::const_iterator end;

			std::variant<int, double, char> parseNumber();
	
		public: 
			~MathTok() {};
			varStack tokenize(const string* expression) override;
	};

};
#endif
