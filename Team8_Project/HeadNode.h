#ifndef HEADNODE_H
#define HEADNODE_H

#include "MovieStack.h"
#include "BinNodeTree.h"
#include "HashTable.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>


class HeadNode{
private:
	//Member variables
	int count;
	int arySize;
	BinNodeTree<Movie*>* pTree;//Pointer to a BST
	HashTable<std::string, Movie*>* pHash;
	MovieStack* pStack;//Pointer to a MovieStack containing pointers
	static Movie* latestMovieAddress;

	//Private file I/O methods
	bool populateFromFile();
	int getLineCount();

	//Static Display functions
	static void visitAbbr(Movie* &m){
		std::cout << m->getShortTitle();
	};
	static void visit(Movie* &m){
		std::cout << "\t" << m->getTitle() << " (" << m->getGross() << "b)" << std::endl;
	};
	static void freeMovie(Movie* &m){
		delete m;
	};

	//Function used by undo stack; populates 'latestMovieAddress' variable to push movie onto stack
	//after remove is called
	static void removeAddress(BinNode<Movie*>* moviePtr){
		latestMovieAddress = moviePtr->getData();
	};


	std::string abbreviateTitle(const std::string &title);
	void displayMovie(Movie* m);

	//Input validation
	template <class T>
	bool validateNum(T num);
	bool validateDate(std::string d);
public:
	//Default constructor
	HeadNode();
	~HeadNode();//Destructor

	//Accessors
	int getCount() const{
		return count;
	}
	int getArySize() const{
		return arySize;
	}
	//Main menu functions (user prompts included)
	void displayTree();
	void displayIndentedTree();
	void displayHash();
	void add();
	void remove();
	void undoDelete();
	void findByTitle();
	void compare();
	void saveToFile();
	void quitSave();
	void efficiency();
};
#endif