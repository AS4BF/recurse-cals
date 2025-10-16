#ifndef MPARSER_IMPL_H
#define MPARSER_IMPL_H
#include <variant>
#include <deque>
#include <memory>
#include "../types/node.h"

using std::deque;
using std::variant;
using std::unique_ptr;
using std::make_unique;
using std::variant;

template<typename... Types>
Node<typename MParser<Types...>::vT>
MParser<Types...>::expr(){

	auto right = make_unique<Node<typename MParser<Types...>::vT>>(term());	
	unique_ptr<Node<typename MParser<Types...>::vT>> left; 
	typename MParser<Types...>::vT value;	
	if(!lexems->empty()){
		if(is_char()){
			if(is_add()){ value = typename MParser<Types...>::vT('+'); }
			if(is_sub()){ value = typename MParser<Types...>::vT('-'); }		
		} 

		lexems->pop_front();
		if(!lexems->empty()) { left = make_unique<Node<typename MParser<Types...>::vT>>(expr()); }
	}

	return Node<typename MParser<Types...>::vT>(value, std::move(left), std::move(right));		
};

template<typename... Types>
Node<typename MParser<Types...>::vT>
MParser<Types...>::term(){
	
	auto right = make_unique<Node<typename MParser<Types...>::vT>>(fact());	
	unique_ptr<Node<typename MParser<Types...>::vT>> left; 
	typename MParser<Types...>::vT value;
	if(!lexems->empty()){		
		if(is_char()){
			if(is_mul()){ value = typename MParser<Types...>::vT('*'); }
			if(is_div()){ value = typename MParser<Types...>::vT('/'); }		
		} 

		lexems->pop_front();
		if(!lexems->empty()) { left = make_unique<Node<typename MParser<Types...>::vT>>(term()); }
	}
	
	return Node<typename MParser<Types...>::vT>(value, std::move(left), std::move(right));		
};



template<typename... Types>
Node<typename MParser<Types...>::vT>
MParser<Types...>::fact(){
		
	unique_ptr<Node<typename MParser<Types...>::vT>> right; 
	unique_ptr<Node<typename MParser<Types...>::vT>> left; 

	typename MParser<Types...>::vT value;

	if(is_char()){
		if(is_lbkt()){ 
			value = typename MParser<Types...>::vT('(');
			lexems->pop_front();
			right = make_unique<Node<typename MParser<Types...>::vT>>(expr());
			if(is_rbkt()){ value = typename MParser<Types...>::vT(')'); }
		};
	} else { value = typename MParser<Types...>::vT(lexems->front()); } 
	lexems->pop_front();

	
	return Node<typename MParser<Types...>::vT>(value, std::move(left), std::move(right));		
};

using std::get;
using std::holds_alternative;

template<typename... Types>
inline bool MParser<Types...>::is_lbkt() const{
	return get<char>(lexems->front()) == '(';
};

template<typename... Types>
inline bool MParser<Types...>::is_rbkt() const {
	return get<char>(lexems->front()) == ')';
};

template<typename... Types>
inline bool MParser<Types...>::is_char() const {
	return holds_alternative<char>(lexems->front());	
};

template<typename... Types>
inline bool MParser<Types...>::is_add() const {
	return get<char>(lexems->front()) == '+';
};

template<typename... Types>
inline bool MParser<Types...>::is_sub() const {
	return get<char>(lexems->front()) == '-';
};

template<typename... Types>
inline bool MParser<Types...>::is_mul() const {
	return get<char>(lexems->front()) == '*';
};

template<typename... Types>
inline bool MParser<Types...>::is_div() const {
	return get<char>(lexems->front()) == '/';
};

template<typename... Types>
Node<typename MParser<Types...>::vT>
MParser<Types...>::parse(unique_ptr<deque<typename MParser<Types...>::vT>> lexems){
	this->lexems = std::move(lexems);
	auto res = expr();
	return res;
};
#endif
