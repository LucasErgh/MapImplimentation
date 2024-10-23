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

	void fixInsert(Node<K, D>*);
	void fixErase(Node<K,D>* p, Node<K,D>*& c);

	// Recursive delete function
	void deleteMap(Node<K, D>* node);

	// erase a given node
	void erase(const K& key, Node<K, D>* cur);
	// find node to replace when erase is called
	Node<K,D>* findReplacement(Node<K,D>* old);
	
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
	inline void erase(const K& key) { erase(key, root); print(); }
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
void Map<K,D>::fixInsert(Node<K, D>* node) {
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
void Map<K,D>::fixErase(Node<K,D>* p, Node<K,D>*& x){ // p for parent, x for cur. I need parent because im not using nill leaves
	// Example of Cases I usedhttps://www.cs.ucf.edu/~dmarino/ucf/cop3503/lectures/RBTrees02.pdf
	if (x != root && (!x || x->color == BLACK)) {
		
		if (x == p->left) {
			// Case 1: x is the left child
			Node<K, D>* w = p->right; // sibling
			if (w->color == RED) {
				// Case 1.1: Sibling is red
				w->color = BLACK;
				p->color = RED;
				leftRotate(p);
				w = p->right;
			} else if ((!w->left || w->left->color == BLACK) &&
				(!w->right || w->right->color == BLACK)) {
				// Case 1.2: Sibling is black and both of its children are black
				w->color = RED;
				x = p;
			} else if (!w->right || w->right->color == BLACK) {
				// Case 1.3: Sibling is black and its left child is red
					if (w->left) w->left->color = BLACK;
					w->color = RED;
					rightRotate(w);
					w = p->right;
			} else {
				// Case 1.4: Sibling is black and its right child is red
				w->color = p->color;
				p->color = BLACK;
				if (w->right) w->right->color = BLACK;
				if (w->left) w->left->color = RED;
				leftRotate(p);
				x = p; // return new node after rotation
			}
		} else { // Case 2: x is the right child (mirror case of above)
			Node<K, D>* w = x->parent->left;
			if (w->color == RED) {
				// Case 2.1: Sibling is red
				w->color = BLACK;
				p->color = RED;
				rightRotate(p);
				w = p->left;
			} else if ((!w->left || w->left->color == BLACK) &&
				(!w->right || w->right->color == BLACK)) {
				// Case 2.2: Sibling is black and both of its children are black
				w->color = RED;
				x = p;
			} else if (w->left == nullptr || w->left->color == BLACK) {
				// Case 2.3: Sibling's left child is black, right child is red
				if (w->right) w->right->color = BLACK;
				w->color = RED;
				leftRotate(w);
				w = p->left;
			} else {
				// Case 2.4: Sibling's left child is red
				w->color = p->color;
				p->color = BLACK;
				if (w->left) w->left->color = BLACK;
				if (w->right) w->right->color = RED;
				rightRotate(p);
				x = p;
			}
		}
	}
	if (root) root->color = BLACK;
}

template<typename K, typename D>
void Map<K,D>::leftRotate(Node<K, D>* g) {
	/* Naming convention for rotations
	  G 
	 / \
	U   P
	   / \
	  A   B 	*/
	Node<K,D> *p = g->right;

	g->right = p->left;
	if(p->left) p->left->parent = g;
/* 	   	It now looks like this
	 G   P
	/ \   \
   U   A   B  */

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
   / \   
  U   A    	*/
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
				fixInsert(node);
		}
	}
	else if (cur->key < node->key) {
		if (cur->right != nullptr) insert (cur->right, node);
		else{
			cur->right = node; 
			cur->right->parent = cur;
				fixInsert(node);
		}
	}
    fixInsert(cur);
}

// public version
template<typename K, typename D>
void Map<K,D>::insert(const K& key, const D& data) {
	if(root == nullptr) root = new Node<K,D>{key, data, nullptr, nullptr, nullptr, BLACK}; 
	else insert(root, new Node<K,D>{key, data});	
	print();
}

// this does a standard bst erase then calls fixErase to recolor and rotate as needed
template<typename K, typename D>
void Map<K,D>::erase(const K& key, Node<K, D>* cur) {
	if (cur == nullptr) return; // empty tree or node doesn't exist, just return

	if (key < cur->key) { // search left
		erase(key, cur->left);

	}
	else if (key > cur->key) { // search right
		erase(key, cur->right);
	}
	else { // found node to delete

		if(cur->left == nullptr){
			// when there isn't a left child we just replace with right child
			Node<K, D>* temp = cur->right;
			if (cur->parent->left == cur) cur->parent->left = temp;
			else  cur->parent->right = temp;
			if (temp) temp->parent = cur->parent;
			// fix tree and delete old node
			if (cur->color == BLACK) fixErase(cur->parent, temp);
			delete cur;
			return;
		} else if (cur->right == nullptr){
			// when there isn't a right child we just replace with left child
			Node<K,D>* temp = cur->left;
			// make parent point to new node and new node point to parent
			if (cur->parent->left == cur) cur->parent->left = temp;
			else  cur->parent->right = temp;
			if (temp) temp->parent = cur->parent;
			// fix tree and delete old node
			if (!temp || cur->color == BLACK) fixErase(cur->parent, temp);
			delete cur;
			return;
		} else{
			// if cur has both children we find a replacement
			Node<K,D>* temp = findReplacement(cur);
			// make parent point to new node and new node point to parent
			if (cur->parent->left == cur) cur->parent->left = temp;
			else cur->parent->right = temp;
			if (temp) temp->parent = cur->parent;
			// fix tree and delete old nodes
			fixErase(cur->parent, temp);
			delete cur;
		}
	}

}

template<typename K, typename D>
Node<K,D>* Map<K,D>::findReplacement(Node<K,D>* cur){
	cur = cur->right;
	while (cur != nullptr && cur->left != nullptr)
		cur = cur->left;
	return cur;
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