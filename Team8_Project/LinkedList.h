#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"
#include <iomanip>//Used for displaying list
using namespace std;

template <class T>
class LinkedList{
protected:
	NodeHead<T> head;
public:
	~LinkedList();//Destructor 
	void addNode(T val);//Adds node to end of list
	void insertNode(T val);//Adds node to beginning of list
	void deleteNode(T val);
	void displayList() const;
	void clearList();
	int getCount() const;
};

/************************************************
Destructor which destroys all dynamically-allocated nodes
Pre:
Post: all nodes destroyed
Return:
************************************************/
template <class T>
LinkedList<T>::~LinkedList(){
	clearList();//Destroy all Nodes
}

/************************************************
Adds node to linked list
Pre: data to add of type 'T'
Post: data is now added to END of linked list and head is appropriately modified
Return:
************************************************/
template <class T>
void LinkedList<T>::addNode(T val){
	Node<T>* newNode;
	Node<T>* currNode;

	newNode = new Node<T>(val);//Allocate a new Node and store it in newNode

	if (!head.getFront()){//If the head's front is pointing to NULL, we have an empty list
		head.setFront(newNode);
		//Increment head's count
		head.shiftCount(1);
		head.setRear(newNode);
	}
	else{//Otherwise, we add the node to the end of the list
		currNode = head.getFront();

		while (currNode->getNext()){//Move to last node in list
			currNode = currNode->getNext();
		}

		//Link last node to new node (New node already points to NULL because of constructor)
		currNode->setNext(newNode);

		//Increment head's count
		head.shiftCount(1);

		//Make head's rear point to new node
		head.setRear(newNode);
	}
}

/************************************************
Adds node to linked list
Pre: data of type 'T' to add
Post: data will be inserted at FRONT of linked list
Return:
************************************************/
template <class T>
void LinkedList<T>::insertNode(T val){
	Node<T>* newNode;

	newNode = new Node<T>(val);//Allocate a new Node and store it in newNode

	if (!head.getFront()){//If the list is empty
		head.setFront(newNode);
		//Increment head's count
		head.shiftCount(1);
		head.setRear(newNode);
	}
	else{
		newNode->setNext(head.getFront());//Link the new node to the first node in the list
		head.setFront(newNode);//Point the front to the new node
		head.shiftCount(1);//Increment head's count
	}
}

/************************************************
deletes the node containing the given value of type T
Pre: T val - data to delete of type T
Post: appropriate node with matched value will be deleted OR nothing if value not found in list
Return:
************************************************/
template <class T>
void LinkedList<T>::deleteNode(T val){
	Node<T>* currNode;
	Node<T>* prevNode = NULL;
	Node<T>* firstNode = head.getFront();
	Node<T>* lastNode = head.getRear();

	if (!firstNode){//If head is pointing to NULL (empty list), do nothing
		return;
	}

	if (firstNode->getData() == val){//If val to delete is first node
		currNode = firstNode->getNext();
		delete firstNode;
		head.shiftCount(-1);//Remove one from head's count
		head.setFront(currNode);
		if (!currNode){//If list is now empty, make sure head's rear doesn't point to deleted node
			head.setRear(NULL);
		}
	}
	else{
		currNode = head.getFront();
		while (currNode != NULL && currNode->getData() != val){//While we aren't at the end of the list and the node data isn't matched
			prevNode = currNode;
			currNode = currNode->getNext();
		}

		if (currNode){//If node with proper value was found
			prevNode->setNext(currNode->getNext());

			if (!currNode->getNext()){//If node to delete is at end of list, set head's rear equal to new last node (the prev node)
				head.setRear(prevNode);
			}

			delete currNode;
			head.shiftCount(-1);
		}
	}


}

/************************************************
Displays contents of the linked list in a formatted fashion
Pre:
Post: Data in linked list will be displayed in a formatted fashion
Return:
************************************************/
template <class T>
void LinkedList<T>::displayList() const{
	Node<T>* currNode;

	currNode = head.getFront();//Set curren`t pointer to front of list

	while (currNode){//While we aren't at the end of the list
		cout << setw(10) << "\t\t\t|___" << setfill('_') << setw(10) << currNode->getData() << setw(10) << "___|" << endl;
		currNode = currNode->getNext();
		cout << setfill(' ');
	}
}

/************************************************
Removes all nodes in the linked list and head values reset
Pre:
Post: All data in linked list displayed and head values are reset
Return:
************************************************/
template <class T>
void LinkedList<T>::clearList(){
	if (!head.getFront()){//If the list is empty, do nothing
		return;
	}

	Node<T>* currNode = head.getFront();
	Node<T>* nextNode;

	while (currNode){
		nextNode = currNode->getNext();
		delete currNode;
		currNode = nextNode;
	}

	//All nodes now deleted, so reset head values
	head.setFront(NULL);
	head.setRear(NULL);
	head.shiftCount(-head.getCount());//Reset count to 0
}

/************************************************
Returns the count member variable in the 'head' class
Pre:
Post: appropriate member variable returned
Return: int containing number of nodes in the linked list
************************************************/
template <class T>
int LinkedList<T>::getCount() const{
	return head.getCount();
}
#endif