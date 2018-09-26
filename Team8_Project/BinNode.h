#ifndef _BINNODE_H
#define _BINNODE_H
#include <cstddef>


template <class Type>
class BinNode
{
private:
	Type data;                 // data portion
	BinNode<Type>* left;      // Pointer to left child
	BinNode<Type>* right;     // Pointer to right child
public:
	BinNode();
	BinNode(const Type& d);
	BinNode(const Type& d, BinNode<Type>* leftPtr, BinNode<Type>* rightPtr);
	void setData(const Type&);
	Type getData() const;
	bool isLeaf() const;
	BinNode<Type>* getLeftChildPtr() const;
	BinNode<Type>* getRightChildPtr() const;
	void setLeftChildPtr(BinNode<Type>* leftPtr);
	void setRightChildPtr(BinNode<Type>* rightPtr);
}; // End BinNode


/*********************************************************************************
Task: Default Constructor
Requirements: None
Result: Creates a BinNode
*********************************************************************************/
template<class Type>
BinNode<Type>::BinNode() : data(0), left(NULL), right(NULL)
{ }
/*********************************************************************************
Task: Parameterize Constructor
Requirements: None
Result: Creates a BinNode with data
*********************************************************************************/
template<class Type>
BinNode<Type>::BinNode(const Type& d) : data(d), left(NULL), right(NULL)
{ }

/*********************************************************************************
Task: The copy BinNode Constructor
Requirements: 2 BinNode pointer parameter, 1 data type of template Type parameter
Result: Creates a BinNode object with 2 pointers to left and right child node
and a piece of data
*********************************************************************************/
template<class Type>
BinNode<Type>::BinNode(const Type& BinNodeData, BinNode<Type>* leftPtr, BinNode<Type>* rightPtr) : data(BinNodeData), left(leftPtr), right(rightPtr)
{ }
/*********************************************************************************
Task: Initializes the data member of BinNode
Requirements: parameter of template type Type
Result: BinNode holds a piece of data
*********************************************************************************/
template<class Type>
void BinNode<Type>::setData(const Type& d)
{
	data = d;
}
/*********************************************************************************
Task: Gets the data item of a BinNode
Requirements: None
Result: returns data of template type Type
*********************************************************************************/
template<class Type>
Type BinNode<Type>::getData()const
{
	return data;
}
/*********************************************************************************
Task: Checks if the BinNode has leaf
Requirements: None
Result: returns true (if has leaf) or false (if not has leaf)
*********************************************************************************/
template<class Type>
bool BinNode<Type>::isLeaf() const
{
	if (left->data || right->data)
		return true;
	else
		return false;
}
/*********************************************************************************
Task: Gets the left BinNode
Requirements: None
Result: Returns pointer to left BinNode
*********************************************************************************/
template<class Type>
BinNode<Type>* BinNode<Type>::getLeftChildPtr() const
{
	return left;
}
/*********************************************************************************
Task: Gets the left BinNode
Requirements: None
Result: Returns pointer to left BinNode
*********************************************************************************/
template<class Type>
BinNode<Type>* BinNode<Type>::getRightChildPtr() const
{
	return right;
}

/*********************************************************************************
Task: Sets the left pointer to a left BinNode
Requirements: a Node pointer parameter
Result: left data member points to new Node
*********************************************************************************/
template<class Type>
void BinNode<Type>::setLeftChildPtr(BinNode<Type>* leftPtr)
{
	left = leftPtr;
}
/*********************************************************************************
Task: Sets the right pointer to a right BinNode
Requirements: a Node pointer parameter
Result: right data member points to new Node
*********************************************************************************/
template<class Type>
void BinNode<Type>::setRightChildPtr(BinNode<Type>* rightPtr)
{
	right = rightPtr;
}

#endif