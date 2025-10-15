#ifndef NODE_H
#define NODE_H
#include <memory>
using std::unique_ptr;

template<typename T>
struct Node<T>{
	T data;
	using nP = unique_ptr<Node<T>>;
	nP left;
	nP right;	

	Node(T value, nP left = nullptr, nP right = nullptr)
	       	: data(value), left(move(left)), right(move(right)){};
};

#endif
