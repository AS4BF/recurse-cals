#ifndef MPARSER_H
#define MPARSER_H
#include "../Parser/parser.h"
#include <variant>
#include <deque>
#include <memory>
#include "../types/node.h"

using std::deque;
using std::unique_ptr;
using std::make_unique;
using std::variant;


template<typename... Types>
class MParser : public Parser<Types...>{
	private:
		using typename Parser<Types...>::vT;
		unique_ptr<deque<vT>> lexems;	
		Node<vT> expr();
		Node<vT> term();
		Node<vT> fact(); 

		inline bool is_lbkt() const;
		inline bool is_rbkt() const;
		inline bool is_char() const;
		inline bool is_add() const;
		inline bool is_sub() const;
		inline bool is_mul() const;
		inline bool is_div() const;
public:
		~MParser() {};
		Node<vT> 
		parse(unique_ptr<deque<vT>> lexems) override; 
};

#include "mparser_impl.inl"

#endif
