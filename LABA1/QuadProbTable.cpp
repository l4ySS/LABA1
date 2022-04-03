#include "QuadProbTable.h"
#include <string>

#include "fstream"
#include "iostream"


QuadraticProbingTable::QuadraticProbingTable(int tableSize, FunctionType NewHashFunction) {
	this->HashFunction = NewHashFunction;
	this->capacity = tableSize;
	this->size = 0;
	this->cells = new HashNode[tableSize];
	for (int i = 0; i < tableSize; i++)
		cells[i].state = FREE;
}

QuadraticProbingTable::QuadraticProbingTable(const QuadraticProbingTable& table) {
	this->HashFunction = table.HashFunction;
	this->capacity = table.capacity;
	this->size = table.size;
	this->cells = new HashNode[this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		this->cells[i].value = table.cells[i].value;
		this->cells[i].key = table.cells[i].key;
		this->cells[i].state = table.cells[i].state;
	}
}



	/*int QuadraticProbingTable::hash(TValue value)
	{
	
	   return abs(HashFunction(value)) % capacity;
	}*/



void QuadraticProbingTable::rehash() {
	// 0. —охран€ем старый массив cells в tempCells
	// 1. »змен€ем внутреннее состо€ние:
	// измен€ем capacity
	// выдел€ем пам€ть под €чейки в соответствии с capacity (массив cells)
	// 2. ѕереносим €чейки из старой таблицы в новую:
	// 3. ќсвободить пам€ть, занимаемую массивом tempCells.

	int tempSize = capacity;
	HashNode* tempCells = new HashNode[tempSize];

	for (int i = 0; i < tempSize; i++) {
		if (cells[i].state == BUSY) {
			tempCells[i].key = cells[i].key;
			tempCells[i].value = cells[i].value;
			tempCells[i].state = BUSY;
		}
		cells[i].state = FREE;
	}

	this->capacity *= 2;
	this->size = 0;
	delete[] cells;
	this->cells = new HashNode[capacity];

	for (int i = 0; i < capacity / 2; i++) {
		if (tempCells[i].state == BUSY) {
			insert(tempCells[i].value);
		}
	}

	delete[] tempCells;
}





void QuadraticProbingTable::insert(TValue value) {
	if (size == capacity) {
		rehash();
	}

	int index = abs(HashFunction(value)) % capacity;
	int k = 1;

	while (cells[index].state == BUSY) {
		index = (index + (k + k * k) / 2) % capacity; // треугольные числа, проход по всем если capacity = степень двойки
		k++;
	}
	
	cells[index].key = value;
	cells[index].value = value;
	cells[index].state = BUSY;

	size++;
}

bool QuadraticProbingTable::remove(TKey key) {
	int index = abs(HashFunction(key)) % capacity;
	int iteration = 0;
	int k = 1;

	while (cells[index].state != FREE && cells[index].key != key && iteration < capacity) {
		index = (index + (k + k * k) / 2) % capacity;
		k++;
		iteration++;
	}

	if (cells[index].state == FREE || iteration >= capacity) {
		return false;
	}

	cells[index].state = REMOVED;
	size--;
	return true;
}


bool QuadraticProbingTable::find(TKey key)
{
	int index = abs(HashFunction(key)) % capacity;;
	int iteration = 0;
	int k = 1;

	while (cells[index].state != FREE && cells[index].key != key && iteration < capacity) {
		index = (index + (k + k * k) / 2) % capacity;
		k++;
		iteration++;
	}
	return iteration != capacity && cells[index].state == BUSY;
}

TValue QuadraticProbingTable::get(TKey key)
{
	int index = abs(HashFunction(key)) % capacity;;
	int iteration = 0;
	int k = 1;

	while (cells[index].state != FREE && cells[index].key != key && iteration < capacity) {
		index = (index + (k + k * k) / 2) % capacity;
		k++;
		iteration++;
	}

	if (iteration == capacity || cells[index].state == FREE) {
		throw std::string("Error: element is not found");
	}

	return cells[index].value;
}



void QuadraticProbingTable::clear()
{
	for (int i = 0; i < capacity; i++)
		cells[i].state = FREE;

	size = 0;
}

int QuadraticProbingTable::getSize()
{
	return size;
}

bool QuadraticProbingTable::isEmpty()
{
	return size == 0;
}

void QuadraticProbingTable::print() {
	for (int i = 0; i < capacity; i++) {
		std::cout << "[" << i << "]: ";
		if (cells[i].state == BUSY) {
			std::cout << cells[i].value;
		}
		std::cout << std::endl;
	}
}

void QuadraticProbingTable::printinFile(std::string Filename) {
	std::ofstream fout(Filename);
	for (int i = 0; i < capacity; i++) {
		fout << "[" << i << "]: ";
		if (cells[i].state == BUSY) {
			fout << cells[i].value;
		}
		fout << std::endl;
	}
};


QuadraticProbingTable::~QuadraticProbingTable()
{
	clear();
	delete[] cells;
}



int QuadraticProbingTable::CountColissions() {
	int count = 0;
	for (int i = 0; i < capacity; i++) {
		if ((cells[i].state != FREE) && (abs(HashFunction(cells[i].key)) % capacity != i)) count++;
	}

	return count;
};

