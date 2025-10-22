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
using std::string;

/*Op.data +,-
 * Op.next().data *,/
 * Op.next().data ( or # ) or NUM # = nullptr
 */
/* template<typename... Types>
Node<vT> func(Op){
	//if(lexems.empty){ throw }
	for(Op.data){  
		if(Op.next() != nullptr){
			right = func(Op.next());
			if(lexems.front() == Op){
				left = func(Op); 
				lexems.pop_front();
				return Node<vT>(Op.data, left, right);	
			
			return right;
		} else {
			value = lexems.front();
			lexems.pop_front();
			return Node<vT>(value);
		}
	}
} */




template<typename... Types>
typename MParser<Types...>::node
MParser<Types...>::expr(){

	typename MParser<Types...>::node right = term();	
	unique_ptr<typename MParser<Types...>::node> left; 
	typename MParser<Types...>::vT value;	

	if(!lexems->empty() && is_char()){
		
		bool isadd = is_add();
		bool issub = is_sub();

		if(isadd){ value = typename MParser<Types...>::vT('+'); 
		} else if(issub){ value = typename MParser<Types...>::vT('-'); }
		if(isadd || issub){	
			lexems->pop_front();
			if(!lexems->empty()) {
			       	left = make_unique<typename MParser<Types...>::node>(expr());
		       	} else { throw string("Invalid syntax"); }

			return typename MParser<Types...>::node(value, std::move(left), std::move(make_unique<typename MParser<Types...>::node>(std::move(right))));		
		}

	}

	return right;
};

template<typename... Types>
typename MParser<Types...>::node
MParser<Types...>::term(){
	
	typename MParser<Types...>::node right = fact();	
	unique_ptr<typename MParser<Types...>::node> left; 
	typename MParser<Types...>::vT value;

	if(!lexems->empty() && is_char()){

		bool ismul = is_mul();
		bool isdiv = is_div();

		if(ismul){ value = typename MParser<Types...>::vT('*');
	       	} else if(isdiv){ value = typename MParser<Types...>::vT('/'); }
		
		if(ismul || isdiv){	
			lexems->pop_front();
			if(!lexems->empty()) {
			       	left = make_unique<typename MParser<Types...>::node>(term());
		       	} else { throw string("Invalid syntax"); }

			return typename MParser<Types...>::node(value, std::move(left), std::move(make_unique<typename MParser<Types...>::node>(std::move(right))));
		}
	
	} 
	return right;
	
};



template<typename... Types>
typename MParser<Types...>::node
MParser<Types...>::fact(){
		
	auto right = typename MParser<Types...>::node(std::variant<Types...>(0)); 

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
		right = typename MParser<Types...>::node(value);
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
typename MParser<Types...>::node
MParser<Types...>::parse(unique_ptr<deque<typename MParser<Types...>::vT>> lexems){
	this->lexems = std::move(lexems);

	auto res = expr();
	return res;
};
#endif
