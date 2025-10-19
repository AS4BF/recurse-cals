#ifndef BITREE_H
#define BITREE_H
#include <memory>
#include "node.h"

using std::unique_ptr;

template<typename T>
struct BiNode{
	std::unique_ptr<Node<T, BiNode<T>>> left; 
	std::unique_ptr<Node<T, BiNode<T>>> right; 

	BiNode& operator=(BiNode&& other){
		if(this!=&other){
			this->left = std::move(other.left);
			this->right = std::move(other.right);			
		}

		return *this;	
	}
};


template<typename T>
struct Node<T, BiNode<T>>{
	T data;
	BiNode<T> refs;
	
	Node& operator=(const Node& other) = delete;

	Node& operator=(Node&& other){
		if(this!=&other){
			this->data = other.data;
			this->refs = std::move(other.refs);
		}
		return *this;
	}

	Node(Node&& other){
		this->data = other.data;
		this->refs= std::move(other.refs);
	}	

	
	Node(T value, unique_ptr<Node<T, BiNode<T>>> left = nullptr, unique_ptr<Node<T, BiNode<T>>> right = nullptr)
	       	: data(value), refs{std::move(left), std::move(right)} {};

};

#endif
