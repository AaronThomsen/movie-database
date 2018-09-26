#ifndef HashTable_h
#define HashTable_h

#include "HashEntry.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

// HASH TABLE CLASS
template <class keyType, class dataType>
class HashTable
{
private:
	int tableSize;
	int entryCount;
	Entry<keyType, dataType> *table;
	bool isPrime(int num);
	int nextPrime(int num);
	int hashFunction(const keyType sKey);
	void reHash();
	int numCollisions;
	int longestCollision;
	int populateCount;
	int addCount;
	int removeCount;
public:
	HashTable();
	HashTable(int);
	~HashTable();
	double getFillFactor();
	bool isEmpty() const;
	int getCount() const;
	int getAddCount() const{
		return addCount;
	}
	int getPopulateCount() const{
		return populateCount;
	}
	int getRemoveCount() const{
		return removeCount;
	}
	int getSize() const;
	int getNumCollisions() const;
	int getLongestCollision() const;
	int find(std::string);
	void add(const dataType &);
	dataType remove(const dataType &);
	dataType removeByString(std::string s);
	void displayTable();
	dataType findByString(std::string s);
	void writeToFile(ofstream &file);
};


/************************************************
Default constructor 
Pre:
Post: tableSize, entryCount, numCollisions, longestCollision are all set to 0
      table is created of size 0
Return:
************************************************/
template <class keyType, class dataType>
HashTable<keyType, dataType>::HashTable() : tableSize(0), entryCount(0), numCollisions(0), longestCollision(0), addCount(0), removeCount(0), populateCount(0)
{
	table = new Entry <keyType, dataType>[tableSize];

	for (int i = 0; i < tableSize; i++)
	{
		table[i].setData(NULL);
	}
}

/************************************************
Constructor accepting size of table
Pre: int s - number of elements to be placed in table
Post: entryCount, numCollisions, and longestCollision are all set to 0
	  table is created of size nearest prime to 2*n and initialized to null
Return:
************************************************/
template <class keyType, class dataType>
HashTable<keyType, dataType>::HashTable(int s) : entryCount(0), numCollisions(0), longestCollision(0), addCount(0), removeCount(0), populateCount(0)
{
	tableSize = nextPrime(s * 2);
	table = new Entry <keyType, dataType>[tableSize];
	for (int i = 0; i < tableSize; i++)
	{
		table[i].setData(NULL);
	}

}

/************************************************
Destructor that frees memory
Pre:
Post: table member variable is freed
Return:
************************************************/
template <class keyType, class dataType>
HashTable<keyType, dataType>::~HashTable(){
	delete[] table;
}

/************************************************
Hash function that accepts a string
Pre: const keyType sKey - a string (movie's title)
Post: movie title converted to upper case and index is retrieved
Return: int - index to place string
************************************************/
template <class keyType, class dataType>
int HashTable<keyType, dataType>::hashFunction(const keyType sKey)
{
	std::string temp = sKey;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
	unsigned int sum = 0, prime1 = 378551;
	for (size_t i = 0; i < temp.length(); i++){
		sum = sum * prime1 + static_cast<int>(temp[i]);
	}
	return (sum) % tableSize;
}

/************************************************
determines if an int is a prime number or not
Pre: int num - number to check
Post:
Return: bool - true if number is prime; false if it is not
************************************************/
template <class keyType, class dataType>
bool HashTable<keyType, dataType>::isPrime(int num){
	if (num < 2)
		return false;
	if (num == 2)
		return true;
	if (num % 2 == 0)
		return false;
	for (int i = 3; (i*i) <= num; i += 2){
		if (num % i == 0)
			return false;
	}
	return true;
}

/************************************************
Finds nearest prime number larger than argument
Pre: int num - number to find prime number
Post:
Return: int - the nearest prime number larger than 'num'
************************************************/
template <class keyType, class dataType>
int HashTable<keyType, dataType>::nextPrime(int num){
	if (isPrime(num)){
		return num;
	}
	return nextPrime(num + 1);
}

//Accessors
template<class keyType, class dataType>
int HashTable<keyType, dataType>::getSize() const
{
	return tableSize;
}
template<class keyType, class dataType>
int HashTable<keyType, dataType>::getNumCollisions() const{
	return numCollisions;
}

template<class keyType, class dataType>
int HashTable<keyType, dataType>::getLongestCollision() const{
	return longestCollision;
}

template <class keyType, class dataType>
int HashTable<keyType, dataType>::getCount() const
{
	return entryCount;
}

/************************************************
Determines if the table is empty or not
Pre:
Post:
Return: bool - true if table is empty; false if not
************************************************/
template<class keyType, class dataType>
bool HashTable<keyType, dataType>::isEmpty() const
{
	if (entryCount == 0)
		return true;
	else
		return false;
}

/************************************************
Determines the table's fill factor
Pre:
Post:
Return: double - number reprsenting the table's current fill factor
************************************************/
template<class keyType, class dataType>
double HashTable<keyType, dataType>::getFillFactor(){
	return static_cast<double>(entryCount) / tableSize;
}

/************************************************
Rehashes the current table with a table at least 2 times larger
Pre:
Post: A new table will be created with a size equal to the nearest prime number
      equal to twice the tables current size. All data in the old table is added
	  into the new table.
Return:
************************************************/
template<class keyType, class dataType>
void HashTable<keyType, dataType>::reHash(){
	Entry<keyType, dataType>* oldTable = table;
	int oldTableSize = tableSize;
	dataType temp;

	tableSize = nextPrime(oldTableSize * 2);
	table = new Entry<keyType, dataType>[tableSize];
	for (int i = 0; i < tableSize; i++){
		table[i].setData(NULL);
	}

	//Loop through old table and populate to new table
	for (int i = 0; i < oldTableSize; i++){
		if (oldTable[i].getData() != NULL){
			temp = oldTable[i].getData();
			add(temp);
		}
	}
	delete[]oldTable;
}

/************************************************
Finds the location of an existing item in the hash table, or
determines the location to place a new item in the table
Pre: std::string s - a string to enter into the hash table or an existing string
Post:
Return: int - the index in the table where the string can be inserted
			  OR the index at which the existing element could be added
************************************************/
// find function
template <class keyType, class dataType>
int HashTable<keyType, dataType>::find(std::string s)
{
	std::string temp1, temp2;
	int hashIndex = hashFunction(s), i = 1;
	int collisions = 0;
	std::transform(s.begin(), s.end(), s.begin(), ::toupper);
	bool firstCollision = true;
	populateCount++;
	removeCount++;
	while (table[hashIndex].getData() != NULL){
		if (firstCollision){
			numCollisions++;
			firstCollision = false;
		}
		temp1 = table[hashIndex].getData()->getTitle();
		std::transform(temp1.begin(), temp1.end(), temp1.begin(), ::toupper);
		if (temp1 == s){
			return hashIndex;
		}
		hashIndex += (i * i);//increment index by next square

		//If hashIndex goes out-of-bounds, subtract so the index loops around
		if (hashIndex >= tableSize){
			hashIndex -= tableSize;
		}
		i++;
		collisions++;
		populateCount++;
		removeCount++;
	}
	if (collisions > longestCollision){
		longestCollision = collisions;
	}

	return hashIndex;//hashIndex contains index of element in table, or index of empty slot to insert into table
}

/************************************************
Adds a new item to the hash table
Pre:
Post: hash table will have new item added to it. Table will be
	  rehashed if neccessary
Return:
************************************************/
template <class keyType, class dataType>
void HashTable<keyType, dataType>::add(const dataType &item)
{
	if (getFillFactor() >= 0.5){
		reHash();
	}

	int hashIndex = find(item->getTitle());//Get location to add item

	if (table[hashIndex].getData() == NULL)
	{
		table[hashIndex].setData(item);
		entryCount++;
		populateCount++;
	}

}

/************************************************
Removes an item from the hash table
Pre: const dataType& item - data to remove
Post: data will be removed from hash table
Return: dataType - the object of type dataType that was removed
************************************************/
template <class keyType, class dataType>
dataType HashTable<keyType, dataType>::remove(const dataType& item)
{
	int hashIndex = find(item->getTitle());
	dataType temp = table[hashIndex].getData();
	table[hashIndex].setData(NULL);
	entryCount--;

	return temp;
}

/************************************************
Removes from hash table by the key (a string)
Pre: std::string s - string to search for
Post: element containing string will be removed
Return: dataType - the object of type dataType that was removed
************************************************/
template <class keyType, class dataType>
dataType HashTable<keyType, dataType>::removeByString(std::string s){
	int hashIndex = find(s);
	dataType temp = table[hashIndex].getData();
	table[hashIndex].setData(NULL);
	entryCount--;

	return temp;
}

/************************************************
Finds the correct item in the hash table by string
Pre: std::string s  - the string to search for
Post:
Return: the data stored in the correct array index
************************************************/
template <class keyType, class dataType>
dataType HashTable<keyType, dataType>::findByString(std::string s){
	int hashIndex = find(s);

	return table[hashIndex].getData();
}

/************************************************
Displays the hash table. Array index is located next to each element
Pre:
Post: elements in hash table will be displayed
Return:
************************************************/
template <class keyType, class dataType>
void HashTable<keyType, dataType>::displayTable(){
	std::cout << std::endl << "\t\tTable Size: " << tableSize << std::endl << std::endl;
	for (int i = 0; i < tableSize; i++){
		if (table[i].getData() != NULL){
			std::cout << "\t[" << i << "] " << table[i].getData()->getTitle() << std::endl;
		}
	}
}

/************************************************
Writes contents of hash table to file in order
Pre: ofstream &file - the output file
Post: contents of hash table will be in file
Return:
************************************************/
template <class keyType, class dataType>
void HashTable<keyType, dataType>::writeToFile(ofstream &file){
	dataType m;
	for (int i = 0; i < tableSize; i++){
		m = table[i].getData();
		if (m){
			file << m->getTitle() << ", " << m->getShortTitle() << ", " << m->getGross() << ", " << m->getDirector() << ", " << m->getDate() << ", " << m->getRunTime() << endl;
		}
	}
}
#endif