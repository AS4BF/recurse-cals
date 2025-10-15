#ifndef	LEXER_H 
#define LEXER_H
#include <string>
#include <deque>
#include <variant>
using std::deque;
		
template<typename... Types>
class Lexer{
	public:
		using vT = std::variant<Types...>;
		virtual ~Lexer() = 0;
		virtual deque<vT> lexe(const std::string* expression) = 0;
	protected: 
		using sI = std::string::const_iterator;
		sI it;
		sI end;
};

template<typename... Types>
Lexer<Types...>::~Lexer() = default;

#endif
