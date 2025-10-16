#ifndef NODE_H
#define NODE_H
#include <memory>
using std::unique_ptr;

template<typename T>
struct Node{
	T data;
	using nP = unique_ptr<Node<T>>;
	nP left;
	nP right;
	
	Node operator=(Node& other){
		this->data = other.data;
		this->left = std::move(other.left);
		this->right = std::move(other.right);	
	}
	Node(Node&& other){
		this->data = other.data;
                this->left = std::move(other.left);
                this->right = std::move(other.right);	
	}	

	Node(T value, nP left = nullptr, nP right = nullptr)
	       	: data(value), left(move(left)), right(move(right)){};
};

#endif
