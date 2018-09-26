#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"


//Definition for 'Stack' class, which inherits using protected specifier
//from 'LinkedList' class of type T
template <class T>
class Stack : protected LinkedList<T>{
private:
	Node<T>* top;
public:
	Stack();//Default constructor
	~Stack();//Destructor
	void push(T);
	T pop();
	bool isEmpty();
	int getCount();
	void displayStack();
	void clearStack();
};

/************************************************
Default Constructor for 'Stack' class which populates member fields
Pre:
Post: 'top' is populated with NULL
Return:
************************************************/
template <class T>
Stack<T>::Stack() : top(NULL){
}

/************************************************
Destructor for 'Stack' class, which destroys all nodes using the
'clearStack()' member function
Pre:
Post: all nodes are de-allocated from the heap
Return:
************************************************/
template <class T>
Stack<T>::~Stack(){
	clearStack();
}

/************************************************
Add's a node containing data of type 'T' to the top of the stack
Pre: T data - data of type T
Post: data of type T is added to top of stack using 'insertNode()' taken from
'LinkedList' class. Top is modified to now point to new top of stack
Return:
************************************************/
template <class T>
void Stack<T>::push(T data){
	insertNode(data);//Place node at top of stack
	top = head.getFront();//Point top to newly added node
}

/************************************************
Removes node on top of stack
Pre:
Post: Node containing data of type T is removed from stack and
head is appropriately modified to contain new top of stack
Return:
************************************************/
template <class T>
T Stack<T>::pop(){
	if (isEmpty()){//If stack has no items, there is nothing to pop
		std::cout << "Stack is empty" << std::endl;
		return NULL;
	}
	else{
		Node<T>* temp = top->getNext();//Point temp to second item from top of stack
		T data = top->getData();
		delete top;
		top = temp;
		head.setFront(temp);//We have to set the head to temp for displayList() to work properly
		head.shiftCount(-1);
		return data;
	}
}

/************************************************
Determined wether stack is empty or not
Pre:
Post: returns bool indicating status of stack
Return: Returns true if stack is empty, false if it has at least 1 node
************************************************/
template <class T>
bool Stack<T>::isEmpty(){
	if (top){//If top is anything but NULL, stack isn't empty
		return false;
	}
	else{
		return true;
	}
}

/************************************************
Returns number of nodes currently in the stack
Pre:
Post: head's member function will be returned
Return: Uses head member function (defined in Node.h) to return int representing
number of nodes currently on the stack
************************************************/
template <class T>
int Stack<T>::getCount(){
	return head.getCount();
}

/************************************************
Displays all nodes currently on the stack in a formatted fashion
Pre: Stack must have at least one node
Post: All nodes on stack will be displayed, or message will indicate stack is empty
if isEmpty() returns true
Return:
************************************************/
template <class T>
void Stack<T>::displayStack(){
	if (isEmpty()){
		cout << "\t\t(The stack is currently empty)" << endl;
		return;
	}
	displayList();
}

/************************************************
Deletes all nodes in stack and sets top equal to NULL
Pre:
Post: All nodes in stack will be destroyed and top
pointer is reset to NULL for future modifications
Return:
************************************************/
template <class T>
void Stack<T>::clearStack(){
	clearList();
	top = NULL;
}
#endif