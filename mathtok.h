#ifndef MATHTOKENIZER_H
#define MATHTOKENIZER_H
#include "tokenizer.h"

namespace tokenmath
{
	enum class Operation: char {Add = '+', Sub = '-', Mul = '*', Div = '/', lbkt = '(', rbkt = ')'};
	using PairList = std::list<std::pair<std::string, int>>;
	using std::string;
	class MathTok : public Tokenizer
	{
		public: 
			~MathTok() {};
			PairList tokenize(const string* expression) const override;
	};


}

#endif
