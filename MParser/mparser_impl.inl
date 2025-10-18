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

	Node<typename MParser<Types...>::vT> right = term();	
	unique_ptr<Node<typename MParser<Types...>::vT>> left; 
	typename MParser<Types...>::vT value;	

	if(!lexems->empty() && is_char()){
		
		bool isadd = is_add();
		bool issub = is_sub();

		if(isadd){ value = typename MParser<Types...>::vT('+'); }
		if(issub){ value = typename MParser<Types...>::vT('-'); }		
		if(isadd || issub){
			lexems->pop_front();
			if(!lexems->empty()) { left = make_unique<Node<typename MParser<Types...>::vT>>(expr()); }
			return Node<typename MParser<Types...>::vT>(value, std::move(left), std::move(make_unique<Node<typename MParser<Types...>::vT>>(std::move(right))));		
		}
	}

	return right;
};

template<typename... Types>
Node<typename MParser<Types...>::vT>
MParser<Types...>::term(){
	
	Node<typename MParser<Types...>::vT> right = fact();	
	unique_ptr<Node<typename MParser<Types...>::vT>> left; 
	typename MParser<Types...>::vT value;

	if(!lexems->empty() && is_char()){

		bool ismul = is_mul();
		bool isdiv = is_div();

		if(ismul){ value = typename MParser<Types...>::vT('*'); }
		if(isdiv){ value = typename MParser<Types...>::vT('/'); }	
	
		if(ismul || isdiv){	
			lexems->pop_front();
			if(!lexems->empty()) { left = make_unique<Node<typename MParser<Types...>::vT>>(term()); } 
			return Node<typename MParser<Types...>::vT>(value, std::move(left), std::move(make_unique<Node<typename MParser<Types...>::vT>>(std::move(right))));
		}

	}
	return right;
	
};



template<typename... Types>
Node<typename MParser<Types...>::vT>
MParser<Types...>::fact(){
		
	auto right = Node<typename MParser<Types...>::vT>(std::variant<Types...>(0)); 

	typename MParser<Types...>::vT value;

	bool ischar = is_char();


	if(ischar){
		if(is_rbkt()){ 
			lexems->pop_front();
			right = expr();
			
			if(is_lbkt()){
				lexems->pop_front();
			} //else { throw }
		}
	} else { 
		value = typename MParser<Types...>::vT(lexems->front());
		lexems->pop_front();
		right = Node<typename MParser<Types...>::vT>(value);
	} 

	return right;	
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
