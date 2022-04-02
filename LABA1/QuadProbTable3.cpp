#include "QuadProbTable3.h"
#include <string>

QuadraticProbingTable3::QuadraticProbingTable3(int tableSize) {
	this->capacity = tableSize;
	this->size = 0;
	this->cells = new HashNode[tableSize];
	for (int i = 0; i < tableSize; i++)
		cells[i].state = FREE;
}

QuadraticProbingTable3::QuadraticProbingTable3(const QuadraticProbingTable3& table) {
	this->capacity = table.capacity;
	this->size = table.size;
	this->cells = new HashNode[this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		this->cells[i].value = table.cells[i].value;
		this->cells[i].key = table.cells[i].key;
		this->cells[i].state = table.cells[i].state;
	}
}



int QuadraticProbingTable3::hash(TValue value)
{
	int prime = 31;
	int hashCode = 0;
	for (int i = 0; i < value.length(); i++) {
		hashCode += value[i] * pow(prime, i);
	}
	return hashCode % capacity;
}


void QuadraticProbingTable3::rehash() {
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
	this->cells = new HashNode[capacity];

	for (int i = 0; i < capacity / 2; i++) {
		if (tempCells[i].state == BUSY) {
			insert(tempCells[i].key, tempCells[i].value);
		}
	}

	delete[] tempCells;
}

void QuadraticProbingTable3::insert(TKey key, TValue value) {
	if (size == capacity) {
		rehash();
	}

	int index = hash(key);
	int k = 1;

	while (cells[index].state == BUSY) {
		index = (index + (k + k * k) / 2) % capacity;
		k++;
	}

	cells[index].key = key;
	cells[index].value = value;
	cells[index].state = BUSY;

	size++;
}


void QuadraticProbingTable3::insert(TValue value) {
	if (size == capacity) {
		rehash();
	}

	int index = hash(value);
	int k = 1;

	while (cells[index].state == BUSY) {
		index = (index + (k + k * k) / 2) % capacity;
		k++;
	}
	
	cells[index].key = value;
	cells[index].value = value;
	cells[index].state = BUSY;

	size++;
}



bool QuadraticProbingTable3::remove(TKey key) {
	int index = hash(key);
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


bool QuadraticProbingTable3::find(TKey key)
{
	int index = hash(key);
	int iteration = 0;
	int k = 1;

	while (cells[index].state != FREE && cells[index].key != key && iteration < capacity) {
		index = (index + (k + k * k) / 2) % capacity;
		k++;
		iteration++;
	}
	return iteration != capacity && cells[index].state == BUSY;
}

TValue QuadraticProbingTable3::get(TKey key)
{
	int index = hash(key);
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



void QuadraticProbingTable3::clear()
{
	for (int i = 0; i < capacity; i++)
		cells[i].state = FREE;

	size = 0;
}

int QuadraticProbingTable3::getSize()
{
	return size;
}

bool QuadraticProbingTable3::isEmpty()
{
	return size == 0;
}

void QuadraticProbingTable3::print() {
	for (int i = 0; i < capacity; i++) {
		std::cout << "[" << i << "]: ";
		if (cells[i].state == BUSY) {
			std::cout << cells[i].value;
		}
		std::cout << std::endl;
	}
}


void QuadraticProbingTable3::printinFile(std::string Filename) {
	std::ofstream fout(Filename);
	for (int i = 0; i < capacity; i++) {
		fout << "[" << i << "]: ";
		if (cells[i].state == BUSY) {
			fout << cells[i].value;
		}
		fout << std::endl;
	}
};

QuadraticProbingTable3::~QuadraticProbingTable3()
{
	clear();
	delete[] cells;
}



int QuadraticProbingTable3::CountColissions() {
	int count = 0;
	for (int i = 0; i < capacity; i++) {
		if ((cells[i].state != FREE) && (hash(cells[i].key) != i)) count++;
	}
	return count;
};


