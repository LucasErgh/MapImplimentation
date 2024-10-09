#ifndef MAP_H
#define MAP_H

#define RED = 1
#define BLACK = 0

template <typename K, typename D>
struct Node {
	K key;
	D data;
	Node* left;
	Node* right;
	bool color;

	Node(const K& key, const D& data) : key(key), data(data), left(nullptr), right(nullptr) { };
};


template <typename K, typename D>
class Map
{
private:
	Node<K, D>* root;

	// This will return the number of black nodes on decent
	int RecursiveInsert(Node<K, D>*);
	// Recursive map deletion 
	void deleteMap(Node<K, D>* node);
	// Recursive erase, returns int to check if tree is balanced 
	int erase(const K& key, Node<K, D>* cur);
	// returns data for given node
	D find(const K& key, Node<K, D>* node) const;

public:
	inline Map() { root = nullptr; }
	inline Map(const K& key, const D& data) { root = new Node<K, D>(key, data); }

	~Map();

	void insert(const K& key, const D& data);
	inline void erase(const K& key) { erase(key, root); }
	inline D find(const K& key) const { return find(key, root); }
};

#endif