#include "MyMap.h"
#include <math.h>

using namespace myMap;

template<typename K, typename D>
int Map<K,D>::depth(const Node<K, D>*& node) {
	int left = (node == nullptr) ? 0 : depth(node->left), 
		right = (node == nullptr) ? 0 : depth(node->right);

	if (left < right)	return right + 1;
	else				return left + 1;
}

template<typename K, typename D>
void Map<K,D>::balance(const Node<K, D>*& node) {
	int left = depth(node->left), right = node->right, diff = abs(left) - depth(right));

	// if we need to balance we balance
	if (diff > 1) {
		// rotate right
		if (left > right) {

		}
		// rotate left
		else {

		}

	}

}

template<typename K, typename D>
void Map<K,D>::insert(const K& key, const D& data) {

	

}

template<typename K, typename D>
void Map<K,D>::erase(const K& key) {

}

template<typename K, typename D>
D* Map<K,D>::find(const K& key) {

}