#pragma once

#include <iostream>
#include "HashTable.h"


class QuadraticProbingTable : public HashTable {
	int capacity;
	int size;

	const int FREE = 0;
	const int BUSY = 1;
	const int REMOVED = -1;

	struct HashNode {
		TKey key;
		TValue value;
		int state;
	};

	HashNode* cells;

public:
	QuadraticProbingTable(int tableSize);
	QuadraticProbingTable(const QuadraticProbingTable& table);

	void insert(TKey key, TValue value);
	void insert(TValue value);

	bool remove(TKey key);
	bool find(TKey key);

	void clear();

	int getSize();
	bool isEmpty();

	TValue get(TKey key);

	void print();
	void printinFile(std::string Filename);

	~QuadraticProbingTable();



	int CountColissions();


protected:
	int hash(TValue value);

	void rehash();
};