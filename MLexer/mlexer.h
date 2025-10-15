#ifndef MATHTOKENIZER_H
#define MATHTOKENIZER_H
#include "../Lexer/lexer.h"
#include <memory>
#include <deque>
#include <variant>



namespace mlex{
	using std::string;
	using std::deque;
	enum Operation : char {Add='+', Sub='-', Mul='*', Div='/', Lbkt='(', Rbkt=')'};
	
	template<typename... Types>	
	class MLexer :  public Lexer<Types...> 
	{
		private:
			typename Lexer<Types...>::vT parseNumber();
		public:
			~MLexer() {};
			deque<typename Lexer<Types...>::vT> lexe(const string* expression) override;
	};

};

#include "mlexer_impl.inl"
#endif
