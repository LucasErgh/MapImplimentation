#ifndef MAP_H
#define MAP_H



template <typename K, typename D>
struct Node {
	K key;
	D data;
	Node* left;
	mapNode* right;

	Node(const K& key, const D& data) : key(key), data(data), left(nullptr), right(nullptr) { };
};

namespace myMap {

	template <typename K, typename D>
	class Map
	{
	private:
		Node<K,D>* root;

		int depth(const Node<K, D>*& node);
		void balance(const Node<K, D>*&);

	public:
		inline Map() { root = nullptr; }
		inline Map(const K& key, const D& data) { root = new Node<K, D>(key, data); }

		void insert(const K& key, const D& data);
		void erase(const K& key);
		D* find(const K& key);
	};

}

#endif