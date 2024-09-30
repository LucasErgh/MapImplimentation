#ifndef PAIR_H
#define PAIR_H

template<typename K, typename D> // K for key and d for data
struct Pair {
	Pair(K k, D d) : first(k), second(d) { }

	const K first;
	D second;

};

#endif