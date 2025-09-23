#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <variant>
#include <utility>
#include <vector>

using std::pair;
using std::variant;
using std::string;
using std::vector;
		

class Tokenizer {
	public:
		virtual ~Tokenizer() = 0;
		virtual vector<pair<string, variant<int, double, char>>> tokenize(const string* expression) = 0;
};

#endif
