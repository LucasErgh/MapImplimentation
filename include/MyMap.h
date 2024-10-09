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

	void CheckBalance();
	void deleteMap(Node<K, D>* node);
	void erase(const K& key, Node<K, D>* cur);
	D find(const K& key, Node<K, D>* node);

public:
	inline Map() { root = nullptr; }
	inline Map(const K& key, const D& data) { root = new Node<K, D>(key, data); }

	~Map();

	void insert(const K& key, const D& data);
	inline void erase(const K& key) { erase(key, root); }
	inline D find(const K& key) { return find(key, root); }
};

#endif