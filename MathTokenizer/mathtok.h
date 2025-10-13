#ifndef MATHTOKENIZER_H
#define MATHTOKENIZER_H
#include "../Tokenizer/tokenizer.h"
#include <memory> 
#include <queue>


namespace tokenmath {
	using varQue = std::queue<std::variant<int, double, char>>;
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
			varQue tokenize(const string* expression) override;
	};

};
#endif
