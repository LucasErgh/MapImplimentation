#pragma once


#include "MyMap.h"

#include <stdexcept>
#include <math.h>

template<typename K, typename D>
int RecursiveInsert(Node<K, D>* cur) {
	int leftCount, rightCount;

	if (cur) {
		biggerBranch = RecursiveInsert(cur->right);
		rightCount = RecursiveInsert(cur->left);
	} else { // if cur does not exist then we are just counting black nodes
		return 0;
	}
	// now check if we are black, and which is larger between left and right
	if (cur->color == BLACK) {
		
	}
}

template<typename K, typename D>
void Map<K,D>::insert(const K& key, const D& data) {
	// TO-DO redo insert for red black tree
	if (head == nullptr) {
		head = new Node<K, D> { K, D, nullptr, nullptr, BLACK };
		return;	
	} 
	Node<K,D>* toInsert = new Node <K,D> { K, D, nullptr, nullptr, RED };
		  
}


template<typename K, typename D>
D Map<K,D>::find(const K& key, Node<K, D>* node) const {
	
	Node<K, D>* cur = node;

	 do{
		if (cur == nullptr) throw(std::invalid_argument("No Object Found"));
		if (key < cur->key) cur = node->left;
		else if (key > cur->key) cur = node->right;
		
	} while (cur->key != key);
	return cur->data;
	
}

template<typename K, typename D>
Map<K, D>::~Map() {
	deleteMap(root);
}

template<typename K, typename D>
void Map<K, D>::deleteMap(Node<K, D>* node) {
	if (node->left) {
		deleteMap(node->left);
	}
	if (node->right) {
		deleteMap(node->right);
	}

	delete node;
}