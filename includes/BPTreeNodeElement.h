#ifndef BPTREE_NODE_ELEMENT_H
#define BPTREE_NODE_ELEMENT_H

class BPTreeNode;

#include <vector>
#include <string>

using namespace std;

class BPTreeNodeElement{
	double key;
	vector<string> values;

	BPTreeNode* left;
	BPTreeNode* right;	
		
	public:
		BPTreeNodeElement();
		BPTreeNodeElement(const BPTreeNodeElement&);
		void initialize(double, BPTreeNode*, BPTreeNode*);
		BPTreeNode* getLeft();
		BPTreeNode* getRight();
		double getKey();
		void setKey(double);
		void setLeft(BPTreeNode*);
		void setRight(BPTreeNode*);
		void setValues(vector<string>);
		void insert(string);
		vector<string> getValues();
};

#endif
