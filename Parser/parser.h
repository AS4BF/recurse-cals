#ifndef PARSER_H
#define PARSER_H
#include <variant>
#include <deque>
#include <memory>
#include "../types/node.h"
#include "../types/bitree.h"

using std::deque;

template<typename... Types>
class Parser{
	public:
		using vT = std::variant<Types...>;
		virtual ~Parser() = 0;
		virtual Node<vT, BiNode<vT>> parse(std::unique_ptr<deque<vT>> lexems) = 0;
};

template<typename... Types>
Parser<Types...>::~Parser() = default;

#endif
