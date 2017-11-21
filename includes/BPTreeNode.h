// http://www.cplusplus.com/forum/articles/10627/ followed good practices for #include here

#ifndef BPTREE_NODE_H
#define BPTREE_NODE_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <stack>

class BPTreeNodeElement;

using namespace std;

class BPTreeNode{
	bool isLeaf;
	int order;
	int filled;

	BPTreeNode* next = nullptr;
	BPTreeNode* prev = nullptr;

	BPTreeNodeElement* keyNodes = nullptr;

	public:
		BPTreeNode(int, bool);
		BPTreeNode(int, bool, BPTreeNodeElement*);
		void getState();
		void setFilled(int);
		BPTreeNode* getNext();
		BPTreeNode* getPrev();
		void setNext(BPTreeNode*);
		void setPrev(BPTreeNode*);
		bool isOverflow();
		void insert(double, string, stack<BPTreeNode*>&, BPTreeNode*&);
		void insert(BPTreeNodeElement*, stack<BPTreeNode*>&, BPTreeNode*&);
		void splitNode(stack<BPTreeNode*>&, BPTreeNode*&);
		void search(double, vector<string>&);
		void rangeSearch(double, double, vector<string>&);
		void leafSanityCheck();
		BPTreeNode* findPosition(double);
};

#endif
