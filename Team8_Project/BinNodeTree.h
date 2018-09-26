#ifndef _BINNODETREE_H
#define _BINNODETREE_H
#include "BinNode.h"

template<class Type>
class BinNodeTree
{                                                                // pointer to point to the tree root node.
protected:
	/*******************************************************************
	* Protected BinNode Tree Method Section (helper functions)         *
	*******************************************************************/
	BinNode<Type>* rootPtr;
	int getHeightHelper(BinNode<Type>* subTreePtr) const;
	int getNumberOfNodeHelper(BinNode<Type>* subTreePtr) const;
	void destroyTree(BinNode<Type>* subTreePtr);                                            // Recursive delete all nodes from the tree.
	BinNode<Type>* moveValueUpTree(BinNode<Type>* subTreePtr);                              // Copies values up the tree to overwrite value in current node until a leaf
	// is reached; the leaf is the remove since its value is stored in the parent.
	BinNode<Type>* findNode(BinNode<Type>* treePtr, const Type target, bool& success) const;// Recursively searches for target value in the tree by using a inorder
	// traversal.
	void inorder(void(*visit)(Type&), BinNode<Type>* treePtr) const;                          // Recursive traversal method.
	void postorder(void visit(Type&), BinNode<Type>* treePtr) const;
	void preorder(void visit(Type&), BinNode<Type>* treePtr) const;
	void biggestToSmallest(void(*visit)(Type&), BinNode<Type>* treePtr) const;
	void breadthfirst(void(*visit)(Type&), BinNode<Type>* treePtr, int) const;
	BinNode<Type>* copyTree(const BinNode<Type>* treePtr) const;                            // Copied the tree rooted at treePtr and return a pointer to the copy.
	BinNode<Type>* addNewNode(Type item, BinNode<Type>* ptr);
	BinNode<Type>* findSmallestProtectected(BinNode<Type>* ptr);
	BinNode<Type>* removeValue(void(*del)(BinNode<Type>*), BinNode<Type>* Ptr, Type& value);
	void printIndentedTreeHelper(void visit(Type& item), BinNode<Type>* treePtr, int indent = 0) const;
public:
	/*******************************************************************
	* Constructor and destructor section                              *
	*******************************************************************/
	BinNodeTree();
	~BinNodeTree();
	BinNodeTree(const Type&);
	BinNodeTree(const Type&, const BinNodeTree<Type>* leftPtr, const BinNodeTree<Type>* rightPtr);
	/*******************************************************************
	* Public BinNodeTree Method section                               *
	*******************************************************************/
	bool isEmpty() const;
	int getHeight() const;
	int addCount;
	int removeCount;
	virtual void add(const Type&);          // add a node.
	virtual void remove(void(*del)(BinNode<Type>*), Type target);         // remove a node.
	void clear();
	void inorderTraversal(void(*visit)(Type&)) const;
	void postorderTraversal(void visit(Type&)) const;
	void preorderTraversal(void visit(Type&)) const;
	void breadthfirstTraversal(void(*visit)(Type&)) const;
	void setRootData(const Type& rootData);
	bool getEntry(const Type&)const;
	BinNode<Type>* createNode(Type item);
	int max(int, int) const;
	Type searchByDouble(double gross);
	void BinNodeTree<Type>::printIndentedTree(void visit(Type& item)) const;
	void biggestToSmallest(void(*visit)(Type&)) const;
};

/*********************************************************************************
Task: Default Constructor
Requirements: None
Result: set rootPtr pointer to point to NULL
*********************************************************************************/
template<class Type>
BinNodeTree<Type>::BinNodeTree() : rootPtr(NULL), addCount(0), removeCount(0)
{ }
/*********************************************************************************
Task: Default Constructor
Requirements: None
Result: Creates a binary tree node
*********************************************************************************/
template<class Type>
BinNodeTree<Type>::BinNodeTree(const Type& newData): removeCount(0)
{
	addCount = 0;
	rootPtr = new BinNode<Type>(newData, NULL, NULL);
}
/*********************************************************************************
Task: Default Constructor
Requirements: None
Result: Creates a binary tree
*********************************************************************************/
template<class Type>
BinNodeTree<Type>::BinNodeTree(const Type& rootData, const BinNodeTree<Type>* leftPtr, const BinNodeTree<Type>* rightPtr) : addCount(0), removeCount(0)
{
	rootPtr = new BinNode<Type>(rootData, copyTree(leftTreePtr->rootPtr), copyTree(rightTreePtr->rootPtr));
}
/*********************************************************************************
Task: Destructor
Requirements: None
Result: Deletes allocated memory
//*********************************************************************************/
template<class Type>
BinNodeTree<Type>::~BinNodeTree()
{
	destroyTree(rootPtr);
}
/*********************************************************************************
Task: Delete each node in the tree
Requirements: A BinNode pointer
Result: Try is emty
*********************************************************************************/
template<class Type>
void BinNodeTree<Type>::destroyTree(BinNode<Type>* subTreePtr)
{
	if (subTreePtr != NULL)
	{
		if (subTreePtr->getLeftChildPtr() != NULL)
		{
			destroyTree(subTreePtr->getLeftChildPtr());
		}
		if (subTreePtr->getRightChildPtr() != NULL)
		{
			destroyTree(subTreePtr->getRightChildPtr());
		}
		delete subTreePtr;
	}
}
/*********************************************************************************
Task: Checks if the binary tree is empty
Requirements: None
Result: returns true (if empty) or false (if not empty)
*********************************************************************************/
template<class Type>
bool BinNodeTree<Type>::isEmpty() const
{
	if (rootPtr == NULL)
		return true;
}
/*********************************************************************************
Task: Checks the height of the tree
Requirements: None
Result: returns the tree height
*********************************************************************************/
template<class Type>
int BinNodeTree<Type>::getHeight() const
{
	return getHeightHelper(rootPtr);
}

/*********************************************************************************
Task: Creates a node
Requirements: data item of Type parameter
Result: returns point to this newly created node
*********************************************************************************/
template<class Type>
BinNode<Type>* BinNodeTree<Type>::createNode(Type item)
{
	BinNode<Type>* newNode = new BinNode<Type>(item);
	return newNode;
}
/*********************************************************************************
Task: Protected function that helps public function add new node to tree
Requirements: data item parameter, and pointer to node you want to add
Result: returns pointer to tree
*********************************************************************************/
template<class Type>
BinNode<Type>* BinNodeTree<Type>::addNewNode(Type item, BinNode<Type>* nodePtr)
{
	if (rootPtr == NULL)
	{
		rootPtr = createNode(item);
		addCount++;
	}
	else if (*item <= nodePtr->getData())
	{
		if (nodePtr->getLeftChildPtr() != NULL)
		{
			addNewNode(item, nodePtr->getLeftChildPtr());
		}
		else
		{
			nodePtr->setLeftChildPtr(createNode(item));
			addCount++;
		}
	}
	else if (*item > nodePtr->getData())
	{
		if (nodePtr->getRightChildPtr() != NULL)
		{
			addNewNode(item, nodePtr->getRightChildPtr());
		}
		else
		{
			nodePtr->setRightChildPtr(createNode(item));
			addCount++;
		}
	}
	return nodePtr;
}
/*********************************************************************************
Task: public add function that calls helper to add item to tree
Requirements: data item parameter
Result: modified tree
*********************************************************************************/
template<class Type>
void BinNodeTree<Type>::add(const Type& item)
{
	addNewNode(item, rootPtr);
}
/*********************************************************************************
Task: Find the smallest value in the tree
Requirements: A node pointer.
Result: return pointer to the node which holds the smallest value in right subtree.
*********************************************************************************/
template<class Type>
BinNode<Type>* BinNodeTree<Type>::findSmallestProtectected(BinNode<Type>* ptr)
{
	BinNode<Type>* temp = ptr;

	//Travel down to left-most leaf, which will be smallest value
	while (temp->getLeftChildPtr()){
		temp = temp->getLeftChildPtr();
	}

	return temp;
}
/*********************************************************************************
Task: remove the given value node in the tree.
Requirements: A node pointer, a data type Type.
Result: remove the node in the tree and return the pointer of the newly modify tree.
*********************************************************************************/
template<class Type>
BinNode<Type>* BinNodeTree<Type>::removeValue(void(*del)(BinNode<Type>* d), BinNode<Type>* ptr, Type &value)
{
	removeCount++;
	if (rootPtr == NULL)
	{
		return NULL;
	}
	else if (*value == ptr->getData()){
		if (ptr->getLeftChildPtr() != NULL && ptr->getRightChildPtr() != NULL)
		{
			BinNode<Type>* leaf = findSmallestProtectected(ptr->getRightChildPtr());
			Type temp = ptr->getData();
			ptr->setData(leaf->getData());
			leaf->setData(temp);
			leaf = removeValue(del, ptr->getRightChildPtr(), value);
			ptr->setRightChildPtr(leaf);
		}
		else
		{
			BinNode<Type>* temp = ptr;
			if (ptr->getLeftChildPtr() == NULL)
			{
				ptr = ptr->getRightChildPtr();
			}
			else if (ptr->getRightChildPtr() == NULL)
			{
				ptr = ptr->getLeftChildPtr();
			}
			del(temp);
		}
	}
	else if (*value < ptr->getData())
	{
		BinNode<Type>* temp = removeValue(del, ptr->getLeftChildPtr(), value);
		ptr->setLeftChildPtr(temp);
	}
	else if (*value > ptr->getData())
	{
		BinNode<Type>* temp = removeValue(del, ptr->getRightChildPtr(), value);
		ptr->setRightChildPtr(temp);
	}

	return ptr;
}
/*********************************************************************************
Task: remove a given node in the binary tree
Requirements: A given data type Type.
Result: The node in the binary search tree is removed.
*********************************************************************************/
template<class Type>
void BinNodeTree<Type>::remove(void(*del)(BinNode<Type>*), Type value)
{
	rootPtr = removeValue(del, rootPtr, value);
}

/*********************************************************************************
Task: remove node to binary tree
Requirements: A data type Type
Result: returns true if add is successful.
*********************************************************************************/
template<class Type>
void BinNodeTree<Type>::clear()
{
	destroyTree(rootPtr);
}
/*********************************************************************************
Task: Replace the data items in the root of binary tree if the root is not empty.
Requirements: newData is the data items
Result: new data is stored in the root of binary tree.
*********************************************************************************/
template<class Type>
bool BinNodeTree<Type>::getEntry(const Type& anEntry) const
{
	BinNode<Type>* temp = rootPtr;
	while (temp != NULL)
	{
		if (temp->getData() == anEntry)
			return true;
		else
		{
			if (temp->getData() <= anEntry)
				temp = temp->getLeftChildPtr();
			else
				temp = temp->getRightChildPtr();
		}
	}
	return false;
}
/*********************************************************************************
Task: Copys tree
Requirements: pointer to tree paramter
Result: returns pointer to first node of tree
*********************************************************************************/
template<class Type>
BinNode<Type>* BinNodeTree<Type>::copyTree(const BinNode<Type>* treePtr) const
{
	BinNode<Type>* newTreePtr = NULL;
	// copy tree node during preorder traversal.
	if (treePtr != NULL)
	{
		//copy node
		newTreePtr = new BinNode<Type>(treePtr->getData(), NULL, NULL);
		newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
		newTreePtr->setLeftChildPtr(copyTree(treePtr->getRightChildPtr()));
	} // end if
	// else tree is empty (newTreePtr is NULL)
	return newTreePtr;
}// end copy

/*********************************************************************************
Task: Checks the height of the tree
Requirements: None
Result: returns the tree height
*********************************************************************************/
template<class Type>
int BinNodeTree<Type>::getHeightHelper(BinNode<Type>* subTreePtr) const
{
	if (subTreePtr == NULL)
		return 0;
	else
		return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
}
/*********************************************************************************
Task: Determines maximum value of expression
Requirements: two int parameters
Result: returns the greater value
*********************************************************************************/
template<class Type>
int BinNodeTree<Type>::max(int x, int y) const
{
	if (x > y)
		return x;
	else
		return y;
}


/*********************************************************************************
Task: Traverse the tree in order (with helper function)
Requirements: visit parameter, and binary node pointer parameter
Result: performs the visit on each node in order
*********************************************************************************/
template<class Type>
void BinNodeTree<Type>::inorder(void(*visit)(Type& item), BinNode<Type>* treePtr) const
{
	if (treePtr != NULL)
	{
		inorder(visit, treePtr->getLeftChildPtr());
		Type item = treePtr->getData();
		visit(item);
		inorder(visit, treePtr->getRightChildPtr());
	}
}

template<class Type>
void BinNodeTree<Type>::inorderTraversal(void(*visit)(Type&)) const
{
	inorder(visit, rootPtr);
}
/*********************************************************************************
Task: Traverses the tree in post order
Requirements: visit function, binary node pointer parameter
Result: calls visit function for each node's data in postorder
*********************************************************************************/
template<class Type>
void BinNodeTree<Type>::postorder(void visit(Type& item), BinNode<Type>* treePtr) const
{
	if (treePtr != NULL)
	{
		postorder(visit, treePtr->getLeftChildPtr());
		postorder(visit, treePtr->getRightChildPtr());
		Type item = treePtr->getData();
		visit(item);
	}
}
template<class Type>
void BinNodeTree<Type>::postorderTraversal(void visit(Type&)) const
{
	postorder(visit, rootPtr);
}

/*********************************************************************************
Task: Traverse the tree in preorder (with helper function)
Requirements: visit parameter, and binary node pointer parameter
Result: performs the visit on each node in preorder
*********************************************************************************/
template<class Type>
void BinNodeTree<Type>::preorder(void visit(Type& item), BinNode<Type>* treePtr) const
{
	if (treePtr != NULL)
	{
		Type item = treePtr->getData();
		visit(item);
		preorder(visit, treePtr->getLeftChildPtr());
		preorder(visit, treePtr->getRightChildPtr());
	}
}
template<class Type>
void BinNodeTree<Type>::preorderTraversal(void visit(Type&)) const
{
	preorder(visit, rootPtr);
}

/************************************************
displays the items in the BST from biggest to smallest
Pre: void (*visit) (Type &) - pointer to function that will execute on each node visited
	 BinNode<Type>* treePtr - a node in the bst
Post: all nodes in the BST will be displayed in order from largest to smallest
Return:
************************************************/
template <class Type>
void BinNodeTree<Type>::biggestToSmallest(void(*visit)(Type&), BinNode<Type>* treePtr) const{
	if (!treePtr)
		return;

	biggestToSmallest(visit, treePtr->getRightChildPtr());
	Type item = treePtr->getData();
	visit(item);
	biggestToSmallest(visit, treePtr->getLeftChildPtr());
}

template <class Type>
void BinNodeTree<Type>::biggestToSmallest(void(*visit)(Type&)) const{
	biggestToSmallest(visit, rootPtr);
}


/*********************************************************************************
Task: Traverse the tree in breadth-first order (with helper function)
Requirements: visit parameter, and binary node pointer parameter
Result: performs the visit on each node in breadth-first order
*********************************************************************************/
template <class Type>
void BinNodeTree<Type>::breadthfirst(void(*visit)(Type& item), BinNode<Type>* treePtr, int level) const
{
	if (treePtr != NULL)
	{
		if (level < getHeight())
		{
			Type item = treePtr->getData();
			visit(item);
			breadthfirst(visit, treePtr->getLeftChildPtr(), level + 1);
			breadthfirst(visit, treePtr->getRightChildPtr(), level + 1);
		}
	}
}

template <class Type>
void BinNodeTree<Type>::breadthfirstTraversal(void(*visit)(Type& item)) const
{
	breadthfirst(visit, rootPtr, 0);
}

/************************************************
Searches through the BST and returns the node with the matching key value
Pre:	double gross - the gross amount to search for
Post:
Return: Type - the data contained within the matching node
************************************************/
template <class Type>
Type BinNodeTree<Type>::searchByDouble(double gross){
	BinNode<Type>* temp = rootPtr;
	while (temp != NULL)
	{
		if (*temp->getData() == gross)
			return temp->getData();
		else
		{
			if (*temp->getData() <= gross)
				temp = temp->getRightChildPtr();
			else
				temp = temp->getLeftChildPtr();
		}
	}
	return NULL;
}

/************************************************
Recursively prints an indented tree sideways
Pre: void visit(type & item) - function pointer
	 BinNode<Type>* treePtr - a node in the BST
	 int indet - indent level for current node
Post: the tree will be displayed sideways
Return:
************************************************/
template<class Type>
void BinNodeTree<Type>::printIndentedTreeHelper(void visit(Type& item), BinNode<Type>* treePtr, int indent) const
{

	if (treePtr != NULL)
	{

		printIndentedTreeHelper(visit, treePtr->getRightChildPtr(), indent + 8);
		if (indent)
			std::cout << setw(indent) << " ";
		Type item = treePtr->getData();
		visit(item);
		std::cout << "\n";

		printIndentedTreeHelper(visit, treePtr->getLeftChildPtr(), indent + 8);

	}
}
template<class Type>
void BinNodeTree<Type>::printIndentedTree(void visit(Type& item)) const
{
	int indent = 0;
	printIndentedTreeHelper(visit, rootPtr, indent);
}
#endif