#pragma once


#include "MyMap.h"

#include <stdexcept>
#include <math.h>

template<typename K, typename D>
void CheckBalance() {
	//To-Do Impliment	
}

template<typename K, typename D>
void Map<K,D>::insert(const K& key, const D& data) {

	if (root == nullptr) {
		root = new Node<K, D>(key, data);
		return;
	}

	Node<K, D>* newNode = new Node<K,D>(key, data);

	Node<K, D>* parent = root;
	// find where to insert
	while (true) {
		if (parent == nullptr) {
			parent = newNode;
			return;
		}

		if (parent->key < newNode->key) {
			if (parent->right == nullptr) {
				parent->right = newNode; 
				break;
			}
			parent = parent->right;
		}
		else if (parent->key > newNode->key) {
			if (parent->left == nullptr) {
				parent->left = newNode;
				break;
			}
			parent = parent->left;
		}
	}
	balance(root);
}

template<typename K, typename D>
void Map<K,D>::erase(const K& key, Node<K, D>* cur) {
	Node<K, D>* newCur;
	if (cur == nullptr) return;
	if (key < cur.key) {
		if (cur->left->key == key) {
			delete cur.left;
			cur->left = nullptr;
			return;
		}
		else erase(key, cur->left);
	}
	else if (key > cur->key) {
		if (cur->right->key == key) {
			delete cur->right;
			cur->right = nullptr;
			return;
		}
		else erase(key, cur->right);
	}
	balance();

}


template<typename K, typename D>
D Map<K,D>::find(const K& key, Node<K, D>* node) {
	
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
	if (node->left != nullptr) {
		deleteMap(node->left);
	}
	if (node->right != nullptr) {
		deleteMap(node->right);
	}

	delete node;

}