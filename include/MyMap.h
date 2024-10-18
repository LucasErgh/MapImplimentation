#include <vector>


#define RED 0
#define BLACK 1

#ifndef MAP_H
#define MAP_H

template <typename K, typename D>
struct Node {
	K key;
	D data;
	Node* left;
	Node* right;
	Node* parent;
	bool color;

	Node(const K& key, const D& data, Node* left = nullptr,  Node* right = nullptr,  Node* parent = nullptr, const bool& color = RED) 
		: key(key), data(data), left(left), right(right), parent(parent), color(color) { };
};


template <typename K, typename D>
class Map
{
private:
	Node<K, D>* root;

 	int pathToLeaves(Node<K,D>* cur, int num = 0);
	void leftRotate(Node<K, D>*);
	void rightRotate(Node<K, D>*);

	void Violations(Node<K, D>*);

	// Recursive delete function
	void deleteMap(Node<K, D>* node);
	void erase(const K& key, Node<K, D>* cur);
	D find(const K& key, Node<K, D>* node);
	// Recusively find NewNodes correct position and inserts it, then on the way up from recursion checks for violations
	void insert(Node<K,D>* cur, Node<K,D>* NewNode);

public:
	class DeletionOfNonExistantElement{};

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
	for (int i = 0; i < space; ++i) std::cout << "  ";
	std::cout << ((!cur->color) ? "\033[31m" : "\033[0m" ) << cur->key << "\033[0m" << std::endl;
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
int Map<K,D>::pathToLeaves(Node<K,D>* cur, int num){
	if(cur == nullptr) return 0;
	int left = pathToLeaves(cur->left, num), right = pathToLeaves(cur->right, num);
	
	if (left > right) return left + cur->color; 
	else return right + cur->color;
}

template<typename K, typename D>
void Map<K,D>::Violations(Node<K, D>* node) {
	// I used this website https://pages.cs.wisc.edu/~cs400/readings/Red-Black-Trees/
	if (node != root && node->color == RED && node->parent->color == RED) { // Case 2 K's parent is red

		
		// check if we are right or left of node's grandparent
		if (node->parent == node->parent->parent->left){ // parent is in left branch
			Node<K,D>* unc = node->parent->parent->right;
			
			// case 1 - uncle is red we just recolor parent uncle and grandparent
			// Case 2b node's uncle exists and is red so we just recolor
			if (unc && !unc->color)
			{
				node->parent->color = BLACK;
				unc->color = BLACK;
				node->parent->parent->color = RED;
			}
			
			// Case 2a node's uncle is black or null
			else{ 
				if (node == node->parent->right){ // if were on the right we have to rotate left on parent then right on grandparent and recolor
					leftRotate(node->parent);
					node = node->parent;
				}
				// if we're on the left we just recolor and rotate right on grandparent
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rightRotate(node->parent->parent);
			}
			
		} else { // same as above but mirored
			Node<K,D> * unc = node->parent->parent->left;

			if (unc && !unc->color) {
				node->parent->color = BLACK;
				unc->color = BLACK;
				node->parent->parent->color = RED;
			} else {
				if (node == node->parent->left){
					rightRotate(node->parent);
					node = node->parent;
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				leftRotate(node->parent->parent);
			}
		}
	}

	// Now we check if its unbalanced 
	if(pathToLeaves(node->left) > pathToLeaves(node->right)) {
		rightRotate(node);
	} else if (pathToLeaves(node->left) < pathToLeaves(node->right)) {
		leftRotate(node);
	}

	root->color = BLACK; // root is always black
}

template<typename K, typename D>
void Map<K,D>::leftRotate(Node<K, D>* g) {
	/* Naming convention for rotations
	  G 
	   \
	    P
	   / \
	  A   B 	*/
	Node<K,D> *p = g->right;

	g->right = p->left;
	if(p->left) p->left->parent = g;
/* 	   	It now looks like this
	 G  P
	/    \
   A      B  */

	// update parents
	p->parent = g->parent;
	if(!g->parent) root = p; // check if g was root 
	else if (g == g->parent->left) g->parent->left = p;
	else g->parent->right = p;

	// make p's left kid g and make that its parent
	p->left = g;
	g->parent = p;
/*    P  	This is what it looks like now
	 / \
	G   B
     \   
      A    	*/
}

template<typename K, typename D>
void Map<K,D>::rightRotate(Node<K, D>* g) {
	// Pretty much same as leftRotate but mirrored	
	Node<K,D> *p = g->left;

	g->left = p->right;
	if(p->right) p->right->parent = g;

	p->parent = g->parent;
	if(!g->parent) root = p;
	else if (g == g->parent->left) g->parent->left = p;
	else g->parent->right = p;

	p->right = g;
	g->parent = p;
}

// private version
template<typename K, typename D>
void Map<K,D>::insert(Node<K,D>* cur, Node<K,D>* node) {
	// key already exists replace data
	if (cur->key == node->key) {cur->data = node->data; delete node; return;}
	// find position for node
	else if (cur->key > node->key) {
		if (cur->left != nullptr) insert (cur->left, node);
		else {
			cur->left = node;
			cur->left->parent = cur;
				Violations(node);
		}
	}
	else if (cur->key < node->key) {
		if (cur->right != nullptr) insert (cur->right, node);
		else{
			cur->right = node; 
			cur->right->parent = cur;
				Violations(node);
		}
	}
	Violations(cur);
 }

// public version
template<typename K, typename D>
void Map<K,D>::insert(const K& key, const D& data) {
	if(root == nullptr) root = new Node<K,D>{key, data, nullptr, nullptr, nullptr, BLACK}; 
	else insert(root, new Node<K,D>{key, data});	
	print();
}

template<typename K, typename D>
void Map<K,D>::erase(const K& key, Node<K, D>* cur) {
	Node<K, D>* newCur;
	if (cur == nullptr) return; // empty tree, just return

	if (key < cur->key) {
		if (!cur->left) return; // do nothing if element does not exist
		if (cur->left->key == key) {
			delete cur->left;
			cur->left = nullptr;
			return;
		}
		else erase(key, cur->left);
	}
	else if (key > cur->key) {
		if(!cur->right) return; // do nothing if element does not exist
		if (cur->right->key == key) {
			delete cur->right;
			cur->right = nullptr;
			return;
		}
		else erase(key, cur->right);
	}

	if (cur) Violations(cur);

	print();
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