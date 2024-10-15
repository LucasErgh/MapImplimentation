#include <vector>


#define RED 1
#define BLACK 0

#ifndef MAP_H
#define MAP_H

template <typename K, typename D>
struct Node {
	K key;
	D data;
	Node* left;
	Node* right;
	bool color;

	Node(const K& key, const D& data, const Node* left, const Node* right, const bool& color = RED) 
		: key(key), data(data), left(nullptr), right(nullptr), color(color) { };
};


template <typename K, typename D>
class Map
{
private:
	Node<K, D>* root;

	void Violations(Node<K, D>*);
	void leftRotate(Node<K, D>*);
	void rightRotate(Node<K, D>*);

	// Recursive delete function
	void deleteMap(Node<K, D>* node);
	void erase(const K& key, Node<K, D>* cur);
	D find(const K& key, Node<K, D>* node);
	// Recusively find NewNodes correct position and inserts it, then on the way up from recursion checks for violations
	void insert(Node<K,D>* cur, Node<K,D>* NewNode);

public:
	inline Map() { root = nullptr; }
	inline Map(const K& key, const D& data) { root = new Node<K, D>(key, data); }

	~Map();

	// This function just creates the node and calls the private insert function 
	void insert(const K& key, const D& data);
	inline void erase(const K& key) { erase(key, root); }
	inline D find(const K& key) { return find(key, root); }

	void print(Node<K,D>* cur, int level);
	void print();
};

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//

template<typename K, typename D>
void Map<K,D>::print(Node<K,D>* cur, int space){
	if(!cur) return;
	
	// print right side
	print(cur->right, space + 1);

	// print this node
	for (int i = 0; i < space; ++i) std::cout << "     ";
	std::cout << cur->key << "(" << ((cur->color) ? "R" : "B") << ")" << std::endl;

	// print left side
	print(cur->left, space + 1);
}

template<typename K, typename D>
void Map<K,D>::print(){
	std::cout << std::endl;
	print(root, 0);
	std::cout << std::endl;
}

template<typename K, typename D>
void Map<K,D>::Violations(Node<K, D>* node) {
	//To-Do Impliment	
}

template<typename K, typename D>
void Map<K,D>::leftRotate(Node<K, D>* node) {
	//To-Do Impliment	
}

template<typename K, typename D>
void Map<K,D>::rightRotate(Node<K, D>* node) {
	//To-Do Impliment	
}

// private version
template<typename K, typename D>
void Map<K,D>::insert(Node<K,D>* cur, Node<K,D>* node) {
	// key already exists throw error
	if (cur->key == node->key) throw "Node already exists";
	// find position for node
	else if (cur->key > node->key) {
		if (cur->left != nullptr) insert (cur->left, node);
		else cur->left = node;
	}
	else if (cur->key < node->key) {
		if (cur->right != nullptr) insert (cur->right, node);
		else cur->right = node; 
	}
	Violations(cur);
 }

// public version
template<typename K, typename D>
void Map<K,D>::insert(const K& key, const D& data) {
	if(root == nullptr) root = new Node<K,D>{key, data, nullptr, nullptr, BLACK}; 
	else insert(root, new Node<K,D>{key, data, nullptr, nullptr, RED});
	print();
	
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

	if (cur)
		Violations(cur);

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
void Map<K, D>::deleteMap(Node<K, D>* node) { }

#endif