#include <BPTreeNodeElement.h>
#include <BPTreeNode.h>

/**
	Constructor for the key object in the B+ tree node
*/
BPTreeNodeElement::BPTreeNodeElement(){
	key   = -1;
	left  = nullptr;	/** pointer to node with keys lesser than key */
	right = nullptr;	/** pointer to node with keys more than key */
}

/**
	Alternate constructor allowing us to initialize key and  left, right pointers
*/
void BPTreeNodeElement::initialize(double k, BPTreeNode* l, BPTreeNode* r){
	key = k;
	left = l;
	right = r;
}

/**
	Setter to set left pointer of key object
*/
void BPTreeNodeElement::setLeft(BPTreeNode* l){
	left = l;
}			

/**
	Getter to get left pointer of key object
*/
BPTreeNode* BPTreeNodeElement::getLeft(){
	return left;
}

/**
	Setter to set right pointer of key object
*/
void BPTreeNodeElement::setRight(BPTreeNode* r){
	right = r;
}			

/**
	Getter to get right pointer of key object
*/
BPTreeNode* BPTreeNodeElement::getRight(){
	return right;
}

/** 
	Setter to set key value
*/
void BPTreeNodeElement::setKey(double k){
	key = k;
}

/** 
	Getter to get key value
*/
double BPTreeNodeElement::getKey(){
	return key;
}

/** 
	Setter to set values ( duplicate key handling )
*/
void BPTreeNodeElement::setValues(vector<string> t_values){
	values = t_values;
}

/** 
	Getter to get values
*/		
vector<string> BPTreeNodeElement::getValues(){
	return values;
}

/**
	Inserts value into key object's values array
*/
void BPTreeNodeElement::insert(string value){
	values.push_back(value);
}

