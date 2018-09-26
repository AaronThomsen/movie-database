#ifndef NODE_H
#define NODE_H

#include <cstdlib>

template <class T>
class Node{
private:
	T data;
	Node<T>* next;
	Node<T>* prev;
public:
	Node();
	Node(const T& item);
	Node(const T& item, Node<T>* nextNode);

	//Mutators
	void setData(const T& item);
	void setNext(Node<T>* nextNode);

	//Accessors
	T getData() const;
	Node<T>* getNext() const;
};

/************************************************
Default Constructor for 'Node' class which populates member fields
Pre:
Post: 'next' is populated with NULL, 'data' is left uninitialized
Return:
************************************************/
template <class T>
Node<T>::Node() : next(NULL), prev(NULL){
}

/************************************************
Constructor for 'Node' class which accepts a const ref to a piece of data
and uses it to populate data fields
Pre: const T& item - const ref to data of type T used to populate 'data' member field
Post: 'Data' contains arg passed and 'next' contains NULL
Return:
************************************************/
template <class T>
Node<T>::Node(const T& item) : data(item), next(NULL), prev(NULL){
}

/************************************************
Constructor for 'Node' class which accepts a const ref to a piece of data
and a pointer to the next node; it uses these data to populate the appropriate data fields
Pre: const T& item - const ref to data of type T used to populate 'data' member field
Node<T>* nextNode - pointer to a 'Node' class represetning the next node
Post: 'Data' contains arg passed and 'next' contains pointer to next node
Return:
************************************************/
template <class T>
Node<T>::Node(const T& item, Node<T>* nextNode) : data(item), next(nextNode), prev(NULL){
}

/************************************************
Mutator for 'Data' member variable
Pre: const T& item - const ref to data of type T used to populate 'data' member field
Post: 'Data' contains arg passed
Return:
************************************************/
template <class T>
void Node<T>::setData(const T& item){
	data = item;
}

/************************************************
Mutator for 'next' member variable
Pre: Node<T>* nextNode - a pointer to the next node
Post: 'next' contains arg passed
Return:
************************************************/
template <class T>
void Node<T>::setNext(Node<T>* nextNode){
	next = nextNode;
}

/************************************************
Accessor for 'Data' member variable
Pre:
Post: returns 'Data' member variable
Return: 'Data' member variable
************************************************/
template <class T>
T Node<T>::getData() const{
	return data;
}

/************************************************
Accessor for 'next' member variable
Pre:
Post: returns 'next' member variable
Return: 'next' member variable, a pointer representing the next node in the list
************************************************/
template <class T>
Node<T>* Node<T>::getNext() const{
	return next;
}


//Definition of 'NodeHead' Class
template <class U>
class NodeHead{
private:
	int count;
	Node<U>* front;
	Node<U>* rear;
public:
	NodeHead();//Default constructor

	//Mutators
	void setFront(Node<U>* first);
	void setRear(Node<U>* last);
	void shiftCount(int shift);

	//Accessors
	Node<U>* getFront() const;
	Node<U>* getRear() const;
	int getCount() const;
};

/************************************************
Default constructor for 'NodeHead' class
Pre:
Post: all member variables will be appropriately populated
Return:
************************************************/
template <class U>
NodeHead<U>::NodeHead() : count(0), front(NULL), rear(NULL){
}

/************************************************
Mutator for 'front' member variable
Pre: Node<U>* first - pointer representing first Node in linked list
Post: 'front' member variable contains argument value
Return:
************************************************/
template <class U>
void NodeHead<U>::setFront(Node<U>* first){
	front = first;
}

/************************************************
Mutator for 'rear' member variable
Pre: Node<U>* last - pointer representing last Node in linked list
Post: 'rear' member variable contains argument value
Return:
************************************************/
template <class U>
void NodeHead<U>::setRear(Node<U>* last){
	rear = last;
}

/************************************************
Mutator for 'count' member variable
Pre: int shift - int representing how much to incr/decr current count by
Post: 'count' will be appropriately modified
Return:
************************************************/
template <class U>
void NodeHead<U>::shiftCount(int shift){
	count += shift;
}

/************************************************
Accessor for 'front' member variable
Pre:
Post: returns pointer to 'Node' class
Return: Pointer to 'Node' class representing first item in linked list
************************************************/
template <class U>
Node<U>* NodeHead<U>::getFront() const{
	return front;
}

/************************************************
Accessor for 'rear' member variable
Pre:
Post: returns pointer to 'Node' class
Return: Pointer to 'Node' class representing last item in linked list
************************************************/
template <class U>
Node<U>* NodeHead<U>::getRear() const{
	return rear;
}

/************************************************
Accessor for 'count' member variable
Pre:
Post: returns int value stored in 'count' member variable
Return: int stored in count, representing # of items currently
in the list, is returned
************************************************/
template <class U>
int NodeHead<U>::getCount() const{
	return count;
}
#endif