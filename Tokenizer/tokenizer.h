#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <variant>
#include <utility>
#include <stack>

using varStack = std::stack<std::variant<int, double, char>>;
using std::variant;
using std::string;
		

class Tokenizer {
	public:
		virtual ~Tokenizer() = 0;
		virtual varStack tokenize(const string* expression) = 0;
};

#endif
