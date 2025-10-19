#ifndef NODE_H
#define NODE_H
#include <memory>
using std::unique_ptr;

template<typename T, typename S>
struct Node{
		T data;
		S refs;

	Node& operator=(Node& other){
		if(this!=other){
			this->data = other.data;
			this->refs = other.refs;
		}
		return *this;	
	}

	Node& operator=(Node&& other){
		if(this!=&other){
			this->data = other.data;
			this->refs = other.refs;
		}
		return *this;
	}

	Node(Node&& other){
		this->data = other.data;
		this->refs = other.refs;
	}	
};

#endif
