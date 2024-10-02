#pragma once


#include "MyMap.h"

#include <stdexcept>
#include <math.h>

template<typename K, typename D>
int Map<K,D>::balanceFactor(const Node<K, D>* node) {
	//int left = (node == nullptr) ? 0 : balanceFactor(node->left), 
	//	right = (node == nullptr) ? 0 : balanceFactor(node->right);
	//return left - right;

	return	((node == nullptr) ? 0 : balanceFactor(node->left) + 1)		// left balance factor
			-															// minus
			((node == nullptr) ? 0 : balanceFactor(node->right) + 1);	// right balance factor
}

template<typename K, typename D>
void Map<K,D>::balance(Node<K, D>* node) {
	
	// recurse to leaves
	if (node->left != nullptr) balance(node->left);
	if (node->right != nullptr) balance(node->right);
	
	
	// now from bottem up balance
	int bf = balanceFactor(node);

	// rotate right
	if (bf > 1) {
		Node<K, D>* temp = node;
		node = temp->left;
		node->right = temp;
		temp->left = nullptr;
	}
	// rotate left
	else if (bf < -1) {
		Node<K, D>* temp = node;
		node = temp->right;
		node->right = temp;
		temp->right = nullptr;
	}
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