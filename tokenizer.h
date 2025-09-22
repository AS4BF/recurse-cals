#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <list>
#include <utility>

using std::pair;
using std::list;
using std::string;
		

class Tokenizer {
	public:
		virtual ~Tokenizer() = 0;
		virtual list<pair<string, int>> tokenize(const string* expression) const = 0;
};

#endif
